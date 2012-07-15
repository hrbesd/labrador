#!/usr/local/bin
# -*- encoding: utf-8 -*-

from BeautifulSoup import BeautifulSoup, Comment, Tag
from xml.dom.minidom import parseString
from reactor_rule_parser import *
from executor import Executor
from divider import Divider
from rule_item import *
import re, sys, os, codecs, html

VERSION_NAME = "0.3.1.SERVER"

def getVersionStr():
	return 'Labrador Reactor Version %s' % VERSION_NAME

class Reactor:
	def __init__(self, rule_file_path, config_file_path, in_folder_path, out_folder_path, log_file_path):
		self.rule_file_path = rule_file_path + "/reactor_rules.rrule"
		self.config_file_path = config_file_path + "/reactor_config.config"
		self.in_folder_path = in_folder_path
		self.out_folder_path = out_folder_path
		self.rule_list = []
		self.buildRules()
		self.executor = Executor(log_file_path)

	def __str__(self):
		return 'Reactoring files in folder "' + self.in_folder_path + '" to folder "' + self.out_folder_path + '", using rule file "' + self.rule_file_path + '"'

	def buildRules(self):
		parser = RuleParser()
		self.rule_list = parser.parseFile(self.rule_file_path)

	def doReactorWork(self):
		if not self.ensureInputFolderExists():
			print "Error: Input folder does not exists."
			return
		self.ensureOutputFolderExists()
		self.processFilesRecursively(self.in_folder_path, self.doWork)
		self.executor.finished()

		return

	def ensureInputFolderExists(self):
		return os.path.exists(self.in_folder_path)

	# 确认输出目录是否存在，如果不存在，就创建这个目录
	def ensureOutputFolderExists(self):
		if not os.path.exists(self.out_folder_path):
			os.makedirs(self.out_folder_path)

	# 递归处理文件
	def processFilesRecursively(self, topPath, processFunction):
		for root, dirs, files in os.walk(topPath):
			for fileName in files:
				processFunction(root, fileName)

	def doWork(self, root, fileName):
		srcFile = root + "/" + fileName
		resultFileDir = self.out_folder_path + root[len(self.in_folder_path):] + "/"
		resultFilePath = resultFileDir + fileName

		xmlDataFile = codecs.open(srcFile, 'r', 'utf-8')
		xmlData = xmlDataFile.read()
		xmlDataFile.close()

		xmlData = html.unescape_string(xmlData)

		soup = BeautifulSoup(xmlData)
		soup = BeautifulSoup(soup.prettify())

		# 建立originUrl为key，[hash, absoluteUrl]为value的字典
		hashNodeRecords = {}
		try:
			dom = parseString(soup.prettify())
			hashNodes = dom.getElementsByTagName('hashnode')
			for hashNode in hashNodes:
				hashValue = (hashNode.getElementsByTagName('hash')[0]).toprettyxml()[7:-8].strip()
				absolute = (hashNode.getElementsByTagName('absoluteurl')[0]).toprettyxml()[13:-15].strip()
				origin = (hashNode.getElementsByTagName('originalurl')[0]).toprettyxml()[13:-15].strip()
				hashNodeRecords[origin] = [hashValue, absolute]
		except Exception as e:
			pass

		# 将相对URL替换为绝对URL，并添加hash属性
		for img_element in soup.findAll('img'):
			if img_element.has_key('src'):
				originUrl = img_element['src']
				if hashNodeRecords.has_key(originUrl) and hashNodeRecords[originUrl]:
					img_element['src'] = hashNodeRecords[originUrl][1]
					img_element['hash'] = hashNodeRecords[originUrl][0]

		# 去掉注释
		comments = soup.findAll(text=(lambda text:isinstance(text, Comment)))
		[comment.extract() for comment in comments]

		# 利用反射机制，动态调用方法，所有方法的实现都在executor.Executor类中
		for rule in self.rule_list:
			for script_code in soup.findAll(rule.target.split(' ')[0]):
				# 默认所有对象都需要处理
				# 当指定条件的对象不能满足的时候，再跳过处理过程
				needToProcess = True
				for condition in rule.condition:
					conMethod = getattr(Executor, condition[0])
					if not conMethod(self.executor, script_code, condition[1:]):
						needToProcess = False # 条件不满足，跳过
						break

				if needToProcess:
					for act in rule.action:
						actMethod = getattr(Executor, act[0])
						if len(act) == 1:
							actMethod(self.executor, script_code)
						else:
							args = [rule.target] + act[1:]
							actMethod(self.executor, script_code, args)

					if len(rule.logLevel.strip()) > 0 and len(rule.logMsg) > 0:
						self.executor.doLog(rule.logLevel, resultFilePath, rule.logMsg)

		# 最后做断句处理
		divider = Divider(soup, self.config_file_path)
		soup = divider.doWork()

		if not os.path.exists(resultFileDir):
			os.makedirs(resultFileDir)

		resultFile = codecs.open(resultFilePath, 'w', 'utf-8')
		resultData = soup.prettify().decode('utf-8')
		resultFile.write(resultData)
		resultFile.close()
