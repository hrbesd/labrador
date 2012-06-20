#!/usr/local/bin
# -*- encoding: utf-8 -*-

from BeautifulSoup import BeautifulSoup, Comment, Tag
from xml.dom.minidom import parseString
import re, sys, os, codecs, html

class Reactor:
	def __init__(self, in_folder_path, out_folder_path):
		self.in_folder_path = in_folder_path
		self.out_folder_path = out_folder_path
		self.initConfig()

	def __str__(self):
		return self.in_folder_path + "  " + self.out_folder_path

	basic_removable_element_list = ['applet', 
		'area', 
		'map', 
		'iframe', 
		'script', 
		'style', 
		'object', 
		'audio', 
		'video',
		'font', 
		'big', 
		'basefont', 
		'link'
	]

	replacable_element_list = {
		'u' : 'ins', 
		'b' : 'strong', 
		's' : 'del', 
		'i' : 'em', 
	}

	alt_dict = {
	}

	def initConfig(self):
		configFile = codecs.open('img_alt.config', 'r', 'utf-8')
		for line in configFile.readlines():
			hashKey, alt = line.split(" ")
			self.alt_dict[hashKey] = alt
		configFile.close()

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

		# 去掉多余标签内容
		for removable_element in self.basic_removable_element_list:
			for script_code in soup.findAll(removable_element):
				script_code.extract()

		# 去掉注释
		comments = soup.findAll(text=(lambda text:isinstance(text, Comment)))
		[comment.extract() for comment in comments]

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

		if not os.path.exists(resultFileDir):
			os.makedirs(resultFileDir)

		resultFile = codecs.open(resultFilePath, 'w', 'utf-8')
		resultData = soup.prettify().decode('utf-8')
		resultFile.write(resultData)
		resultFile.close()

def main():
	if len(sys.argv) < 2:
		print "usage: python reactor.py in_folder_path out_folder_path"
		return

	in_folder_path = sys.argv[1]

	if len(sys.argv) == 2:
		out_folder_path = "out"
	else:
		out_folder_path = sys.argv[2]

	reactor = Reactor(in_folder_path, out_folder_path)
	reactor.doReactorWork()

if __name__ == '__main__':
	main()
