#!/usr/local/bin
# -*- coding: utf-8 -*-

# 把in中的xml文件，结合templates文件夹下的template.html文件以及对应的css、js文件，自动生成一个符合标准的网页
# 使用方法：python assembler.py in_folder_path out_folder_path
# 参数说明：
#          in_folder_path: 原始xml文件所在的目录（根目录即可）
#          out_folder_path: 生成之后的没文件的目标路径
# 依赖条件：此python文件与templates文件夹相对位置固定（../templates），保证文件可以复制过来
import sys, os, shutil, re, codecs, datetime
from xml.dom.minidom import parseString # xml解析类库

class Assembler:
	def __init__(self, in_folder_path, out_folder_path):
		self.in_folder_path = in_folder_path
		self.out_folder_path = out_folder_path

	def __str__(self):
		return self.in_folder_path + "  " + self.out_folder_path

	def doAssembleWork(self):
		print 'Step 1: Making sure the folder exists'
		if not self.ensureInputFolderExists():
			print "Error: Input folder does not exists."
			return

		self.ensureOutputFolderExists()

		print 'Step 2: Copying template resources'
		self.copyResourceFiles()

		print 'Step 3: For every xml data file, generate the html file using given template'
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
		for root, dirs, files in os.walk(topPath):
			for fileName in files:
				# 只处理对应的后缀
				if fileName.strip().endswith(targetPostfix):
					processFunction(root, fileName)

	# 生成html代码
	def genHtml(self, root, fileName):
		srcFile = root + "/" + fileName
		resultFileDir = self.out_folder_path + root[len(self.in_folder_path):] + "/"
		resultFilePath = resultFileDir + fileName.replace('.xml', '.html')
		# 首先，解析对应的xml文件
		xmlFile = open(srcFile, 'r')
		domString = xmlFile.read()
		xmlFile.close()

		domString = domString.replace("BR" , "BR/")
		domString = domString.replace("&nbsp;", " ")

		self.dom = parseString(domString)

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

		# 针对lastModified做特殊处理
		# 因为lastModified是以long的形式呈现的，这里需要转换为Date的字符串表示
		if value == 'lastModified':
			modifiedDate = datetime.datetime.fromtimestamp(long(result) / 1000)
			dateStr = modifiedDate.strftime(u'%Y年%m月%d日'.encode('utf-8'))
			result = dateStr.decode('utf-8')

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