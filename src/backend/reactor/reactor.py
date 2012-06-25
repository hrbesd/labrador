#!/usr/local/bin
# -*- encoding: utf-8 -*-

from BeautifulSoup import BeautifulSoup, Comment, Tag
from xml.dom.minidom import parseString
from reactor_rule_parser import *
from rule_item import *
import re, sys, os, codecs, html

class Reactor:
	def __init__(self, rule_file_path, in_folder_path, out_folder_path):
		self.rule_file_path = rule_file_path
		self.in_folder_path = in_folder_path
		self.out_folder_path = out_folder_path
		self.rule_list = []
		self.buildRules()

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
		except:
			pass

		# 去掉注释
		comments = soup.findAll(text=(lambda text:isinstance(text, Comment)))
		[comment.extract() for comment in comments]

		# 根据rrule文件做处理，需要设计单独的执行命令的类
		for rule in self.rule_list:
			for script_code in soup.findAll(rule.target.split(' ')[0]):
				if len(rule.condition) > 0:
					for condition in rule.condition:
						if condition == '-':
							pass
		"""
		# 去掉缺失alt属性的img标签
		for img_element in soup.findAll('img'):
			if img_element.has_key('src'):
				originUrl = img_element['src']
				if hashNodeRecords[originUrl]:
					img_element['src'] = hashNodeRecords[originUrl][1]
					imgHash = hashNodeRecords[originUrl][0]
					if not img_element.has_key('alt'):
						# 判断配置文件里面是否有配置
						if self.alt_dict.has_key(imgHash):
							img_element['alt'] = self.alt_dict[imgHash]
						else:
							#img_element.extract()
							pass

		# 去掉属性为type是audio或video的embed标签
		for embed_element in soup.findAll('embed'):
			if embed_element.has_key('type') and (embed_element['type'] == 'audio' or embed_element['type'] == 'video'):
				embed_element.extract()

		# 去掉带有action属性的form
		for form_element in soup.findAll('form'):
			if form_element.has_key('action'):
				form_element.extract()

		# 内容空白的canvas
		for canvas_element in soup.findAll('canvas'):
			has_content = False
			for content in canvas_element.contents:
				if not content.strip() == '':
					has_content = True
			if not has_content:
				canvas_element.extract()

		# 如果<a>的target属性是_blank，改为_self
		for a_element in soup.findAll('a'):
			if a_element.has_key('target') and a_element['target'] == '_blank':
				a_element['target'] = '_self'

		# 替换标签
		for tag_name in self.replacable_element_list:
			for sub_element in soup.findAll(tag_name):
				contents = sub_element.contents
				target_tag = Tag(soup, self.replacable_element_list[tag_name])
				target_tag.contents = contents
				sub_element.replaceWith(target_tag)
"""
		if not os.path.exists(resultFileDir):
			os.makedirs(resultFileDir)

		resultFile = codecs.open(resultFilePath, 'w', 'utf-8')
		resultData = soup.prettify().decode('utf-8')
		resultFile.write(resultData)
		resultFile.close()

def main():
	if len(sys.argv) < 3:
		print "usage: python reactor.py rule_file in_folder_path out_folder_path"
		return

	rule_file_path = sys.argv[1]
	in_folder_path = sys.argv[2]

	if len(sys.argv) == 3:
		out_folder_path = sys.argv[2] + "/out"
	else:
		out_folder_path = sys.argv[3]

	reactor = Reactor(rule_file_path, in_folder_path, out_folder_path)
	reactor.doReactorWork()

if __name__ == '__main__':
	main()
