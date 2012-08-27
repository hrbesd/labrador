#!/usr/local/bin
# -*- encoding: utf-8 -*-
from bs4 import BeautifulSoup, Comment, Tag, NavigableString
from xml.dom.minidom import parseString
from reactor_rule_parser import *
from executor import Executor
from divider import Divider
from rule_item import *
import re, sys, os, codecs, html
import utils, tts_client

VERSION_NAME = "0.3.1.SERVER"

def getVersionStr():
	return 'Labrador Reactor Version %s' % VERSION_NAME

class Reactor:
	def __init__(self, rule_file_path, config_file_path, site_config, in_folder_path, out_folder_path, shared_dir, log_file):
		self.rule_file_path = rule_file_path + "/reactor_rules.rrule"
		self.config_file_path = config_file_path + "/reactor_config.config"
		self.in_folder_path = in_folder_path
		self.out_folder_path = out_folder_path
		self.shared_dir = shared_dir
		self.rule_list = []
		self.log_file = log_file
		self.buildRules()
		self.executor = Executor(config_file_path)
		self.count = 0
		self.client = tts_client.TTSClient()
		self.INVALID_TAGS = ['table', 'tbody', 'tr', 'td']

	def __str__(self):
		return 'Reactoring files in folder "' + self.in_folder_path + '" to folder "' + self.out_folder_path

	def buildRules(self):
		parser = RuleParser()
		self.rule_list = parser.parseFile(self.rule_file_path)

	def doReactorWork(self):
		if not self.ensureInputFolderExists():
			print "Error: Input folder does not exists."
			return

		self.ensureOutputFolderExists()

		print 'Generating navigation files...'
		self.genNavFiles()

		print 'Begin processing...'
		self.processFilesRecursively(self.doWork)

		self.executor.finished()

		print 'Done!'
		return

	def ensureInputFolderExists(self):
		return os.path.exists(self.in_folder_path)

	# 确认输出目录是否存在，如果不存在，就创建这个目录
	def ensureOutputFolderExists(self):
		if not os.path.exists(self.out_folder_path):
			os.makedirs(self.out_folder_path)

	# 生成index.xml，l、c目录下的xml
	def genNavFiles(self):
		indexPath = self.shared_dir + "/dir.xml"

		if len(indexPath) > 0:
			command = '../../butts/reactor/producer --index-file=%s --webroot-dir=%s --log-file=%s' % (indexPath, self.out_folder_path, self.log_file)
			os.system(command)
		else:
			print 'Index file not found!'

	def getDataFilePathForFileName(self, fileName):
		return self.in_folder_path + "/" + fileName[:2] + "/" + fileName

	def dataFileExists(self, fileName):
		return os.path.exists(self.getDataFilePathForFileName(fileName))

	def integrateParentWithData(self, fileName, parentFile):
		dataFile = self.getDataFilePathForFileName(fileName)
		data = codecs.open(dataFile, 'r', 'utf-8')
		dataContent = data.read()
		data.close()

		parent = codecs.open(parentFile, 'r', 'utf-8')
		parentContent = parent.read()
		parent.close()

		dataSoup = BeautifulSoup(dataContent, 'xml')
		parentSoup = BeautifulSoup(parentContent, 'xml')

		dataSoup.article.insert(0, parentSoup.parentPageUrl)

		return unicode(dataSoup)

	# 递归处理文件
	def processFilesRecursively(self, processFunction):
		for root, dirs, files in os.walk(self.out_folder_path):
			for fileName in files:
				processFunction(root, fileName)

	def doWork(self, root, fileName):
		if not fileName.endswith('.xml'):
			return

		srcFile = root + "/" + fileName
		resultFilePath = srcFile

		xmlData = ''
		if self.dataFileExists(fileName):
			xmlData = self.integrateParentWithData(fileName, srcFile)
		else:
			xmlDataFile = codecs.open(srcFile, 'r', 'utf-8')
			xmlData = xmlDataFile.read()
			xmlDataFile.close()

		xmlData = html.unescape_string(xmlData)
		# get rid of something like "&amp;nbsp;"
		# &amp;nbsp; => &nbsp; => " "
		xmlData = html.unescape_string(xmlData)

		soup = BeautifulSoup(xmlData, 'xml')
		soup = self.semantify(soup, resultFilePath)

		# 最后做断句处理
		divider = Divider(soup, self.config_file_path)
		soup = divider.doWork()

		resultFile = codecs.open(resultFilePath, 'w', 'utf-8')
		resultFile.write(unicode(soup))
		resultFile.close()

		# 文章内容生成之后，向Proxy发送文章URL，请求生成语音内容
		self.client.callProxy(resultFilePath.encode('utf-8'))

		self.count += 1
		print 'Processed: %d' % self.count

	# 语义化处理
	def semantify(self, soup, resultFilePath):
		# 建立originUrl为key，[hash, absoluteUrl]为value的字典
		hashNodeRecords = {}
		try:
			dom = parseString(unicode(soup))
			hashNodes = dom.getElementsByTagName('hashnode')
			for hashNode in hashNodes:
				hashValue = (hashNode.getElementsByTagName('hash')[0]).toprettyxml()[7:-8].strip()
				absolute = (hashNode.getElementsByTagName('absoluteurl')[0]).toprettyxml()[13:-15].strip()
				origin = (hashNode.getElementsByTagName('originalurl')[0]).toprettyxml()[13:-15].strip()
				hashNodeRecords[origin] = [hashValue, absolute]
		except Exception as e:
			pass

		# 去掉注释
		comments = soup.find_all(text=(lambda text:isinstance(text, Comment)))
		[comment.extract() for comment in comments]

		# 将相对URL替换为绝对URL，并添加hash属性
		for img_element in soup.find_all('img'):
			if img_element.has_attr('src'):
				originUrl = img_element['src']
				if hashNodeRecords.has_key(originUrl) and hashNodeRecords[originUrl]:
					img_element['src'] = hashNodeRecords[originUrl][1]
					img_element['hash'] = hashNodeRecords[originUrl][0]

		# 利用反射机制，动态调用方法，所有方法的实现都在executor.Executor类中
		for rule in self.rule_list:
			for script_code in soup.find_all(rule.target.split(' ')[0]):
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

		return soup
