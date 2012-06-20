#!/usr/local/bin
# -*- coding: utf-8 -*-

# 把in中的xml文件，结合templates文件夹下的template.html文件以及对应的css、js文件，自动生成一个符合标准的网页
# 使用方法：python assembler.py in_folder_path out_folder_path
# 参数说明：
#          in_folder_path: 所有文件所在的目录，这个目录结构应该包括一个整个站点的描述xml文件，然后三个子目录，分别是spider、parser和reactor，而对assembler来说，它要求reactor文件夹必须存在
#          out_folder_path: 生成之后的没文件的目标路径
# 依赖条件：此python文件与templates文件夹相对位置固定（../templates），保证文件可以复制过来
import sys, os, shutil, re, codecs, datetime
import html # 使用开源的html组件，将html进行解码。由于不是标准库，所以首先需要安装这个库。文件放到libs目录下了。
from xml.dom.minidom import parseString # xml解析类库

class Assembler:
	def __init__(self, in_folder_path, out_folder_path):
		self.in_folder_path = in_folder_path
		self.out_folder_path = out_folder_path

	def __str__(self):
		return self.in_folder_path + "  " + self.out_folder_path

	def doAssembleWork(self):
		if not self.ensureInputFolderExists():
			print "Error: Input folder does not exists."
			return

		self.ensureOutputFolderExists()
		self.copyResourceFiles()
		self.processFilesRecursively(self.in_folder_path, ".xml", self.genHtml)

		print 'Done!'

		return

	def ensureInputFolderExists(self):
		return os.path.exists(self.in_folder_path)

	# 确认输出目录是否存在，如果不存在，就创建这个目录
	def ensureOutputFolderExists(self):
		if not os.path.exists(self.out_folder_path):
			os.makedirs(self.out_folder_path)

	def copyResourceFiles(self):
		srcPath = "../templates/assets"
		targetPath = self.out_folder_path + "/assets"

		# 由于shutil的copytree方法要求目录不能存在，因此首先要做判断，如果已经存在，就先使用shutil的rmtree来删除目录
		if os.path.exists(targetPath):
			shutil.rmtree(targetPath)

		shutil.copytree(srcPath, targetPath)

	def processFilesRecursively(self, topPath, targetPostfix, processFunction):
		self.genIndex(topPath)
		topPath = topPath + "/reactor" # 
		for root, dirs, files in os.walk(topPath):
			for fileName in files:
				# 只处理对应的后缀
				if fileName.strip().endswith(targetPostfix):
					processFunction(root, fileName)

	def genIndex(self, topPath):
		indexFilePath = self.out_folder_path + "/index.html"
		dataFile = open(topPath + "/website.xml", 'r')
		domString = dataFile.read()
		dataFile.close()

		resultString = u"""<!DOCTYPE html><html lang="en"><head><meta charset="utf-8"><meta name="robots" content="noindex" /><title>页面信息</title></head><body>"""
		indexDom = parseString(domString)
		nodes = indexDom.getElementsByTagName('node')
		for node in nodes:
			hashNode = node.getElementsByTagName('hashName')[0].toprettyxml()[10:-12].strip()
			if hashNode != "":
				pageName = node.getElementsByTagName('name')[0].toprettyxml()[6:-8].strip()
				resultString += '<p><a href="pages/' + hashNode + '.html">' + pageName + '</a></p>'

		resultString += u"</body></html>"
		resultFile = codecs.open(indexFilePath, 'w', 'utf-8')
		resultFile.write(resultString)
		resultFile.close()

	# 生成html代码
	def genHtml(self, root, fileName):
		srcFile = root + "/" + fileName
		resultFileDir = self.out_folder_path + "/pages/"
		resultFilePath = resultFileDir + fileName.replace('.xml', '.html')

		# 首先，解析对应的xml文件
		xmlFile = open(srcFile, 'r')
		domString = xmlFile.read()
		xmlFile.close()

		domString = domString.replace("BR" , "BR/")
		domString = domString.replace("&nbsp;", " ")

		try:
			self.dom = parseString(domString)
		except Exception as e:
			print e
			return

		# 接着加载template文件
		templateFile = codecs.open('../templates/template.html', 'r', 'utf-8')
		templateData = templateFile.read()
		templateFile.close()

		# 然后，用正则表达式修改其中对应的内容
		pattern = re.compile(ur'\$\{[^\}]+\}', re.UNICODE)
		resultData = pattern.sub(self.templateString, templateData)

		# 最后，将文件存盘
		if not os.path.exists(resultFileDir):
			os.makedirs(resultFileDir)

		resultFile = codecs.open(resultFilePath, 'w', 'utf-8')
		resultFile.write(resultData)
		resultFile.close()
		return

	def templateString(self, match):
		value = match.group()
		value = value[2:-1]

		result = self.dom.getElementsByTagName(unicode(value))[0].toxml()
		# 去掉开头和结尾的xml标签
		result = result[result.find('>') + 1:result.rfind('<')]

		# 同时，对html进行一次反解码
		result = html.unescape_string(result)

		# 针对lastmodified做特殊处理
		# 因为lastmodified是以long的形式呈现的，这里需要转换为Date的字符串表示
		if value == 'lastmodified':
			try:
				modifiedDate = datetime.datetime.fromtimestamp(long(result) / 1000)
				dateStr = modifiedDate.strftime(u'%Y年%m月%d日'.encode('utf-8'))
				result = dateStr.decode('utf-8')
			except:
				result = u"未知"

		return result
		
# 当以单独的命令执行的时候，调用这个方法
# 这个方法负责解析in_folder_path与out_folder_path这两个目录
def main():
	if len(sys.argv) < 2:
		print "usage: python assembler.py in_folder_path out_folder_path"
		return

	in_folder_path = sys.argv[1]

	if len(sys.argv) == 2:
		out_folder_path = "out"
	else:
		out_folder_path = sys.argv[2]

	assembler = Assembler(in_folder_path, out_folder_path)
	assembler.doAssembleWork()

if __name__ == '__main__':
	main()
