#!/usr/local/bin
# -*- coding: utf-8 -*-
import sys, os, shutil
import utils

VERSION_NAME = "0.3.1.SERVER"

def getVersionStr():
	return 'Labrador Assembler Version %s' % VERSION_NAME

class Assembler:
	def __init__(self, in_folder_path, stylesheet_path, share_dir, custom_dir, temp_out_dir, webroot_dir, log_file):
		self.in_folder_path = in_folder_path
		self.stylesheet_path = stylesheet_path
		self.share_dir = share_dir
		self.custom_dir = custom_dir
		self.temp_out_dir = temp_out_dir
		self.webroot_dir = webroot_dir
		self.log_file = log_file
		self.count = 0
		self.XML_PREFIX = '<?xml version="1.0" encoding="UTF-8"?>'

	def __str__(self):
		return getVersionStr()

	def doAssembleWork(self):
		# 1.判断路径是否存在（index.xml和a、c、l三个目录是否存在）
		if not self.ensureInputFolderExists():
			print "Error: Input folder does not exists."
			return

		# 2.确保目录存在
		self.ensureOutputFolderExists()

		# 3.将所有stylesheet_path中文件复制到temp_out_dir中
		self.copyResourceFiles()

		# 3.5 将footer需要的三个xml移动到temp_out_dir中
		self.mvFooterXML()
		# 4.分别为index.xml、a、c、l文件夹下的文件添加对应的xslt引用语句
		self.processFilesRecursively()

		# 5.将temp_out_dir中的内容复制到webroot_dir中
		print 'Moving to webroot...'
		self.mv2webroot()

		# 6.移动样式表
		self.mvAssets()
		self.mvXSL()
		print 'Done!'

		return

	def ensureInputFolderExists(self):
		if not os.path.exists(self.custom_dir):
			os.makedirs(self.custom_dir)

		baseFolderPath = self.in_folder_path
		stylesheetPath = self.stylesheet_path

		return os.path.exists(self.in_folder_path) and os.path.exists(stylesheetPath)

	def xsltPath(self, type):
		return '<?xml-stylesheet type="text/xsl" href="%s"?>' % type

	# 确认输出目录是否存在，如果不存在，就创建这个目录
	def ensureOutputFolderExists(self):
		if not os.path.exists(self.temp_out_dir):
			os.makedirs(self.temp_out_dir)

		if not os.path.exists(self.webroot_dir):
			os.makedirs(self.webroot_dir)

	def copyResourceFiles(self):
		# 导航文件直接在temp_out_path中生成，所以不用复制，需要复制的是stylesheets目录
		utils.fileMover(self.stylesheet_path, self.temp_out_dir + "/xml_stylesheets")

	def processFilesRecursively(self):
		aFolderPath = self.in_folder_path + "/a"
		cFolderPath = self.in_folder_path + "/c"
		lFolderPath = self.in_folder_path + "/l"

		# index first
		self.changeContent(self.in_folder_path, self.temp_out_dir, 'index.xml', self.xsltPath('./xml_stylesheets/index.xsl'))

		# c
		for root, dirs, files in os.walk(cFolderPath):
			for fileName in files:
				inFolder = root
				outFilePath = self.temp_out_dir + root[len(self.in_folder_path):]
				self.changeContent(inFolder, outFilePath, fileName, self.xsltPath('../xml_stylesheets/column.xsl'))

		# l
		for root, dirs, files in os.walk(lFolderPath):
			for fileName in files:
				inFolder = root
				outFilePath = self.temp_out_dir + root[len(self.in_folder_path):]
				self.changeContent(inFolder, outFilePath, fileName, self.xsltPath('../xml_stylesheets/list.xsl'))

		# a
		for root, dirs, files in os.walk(aFolderPath):
			for fileName in files:
				inFolder = root
				outFilePath = self.temp_out_dir + root[len(self.in_folder_path):]
				self.changeContent(inFolder, outFilePath, fileName, self.xsltPath('../../xml_stylesheets/article.xsl'))

				self.count = self.count + 1
				print 'Processed %d' % self.count
		pass

	def changeContent(self, inPath, outPath, fileName, content):
		if not os.path.exists(outPath):
			os.makedirs(outPath)

		filePath = inPath + "/" + fileName
		readFile = open(filePath)
		contents = readFile.readlines()
		readFile.close()

		outFilePath = outPath + "/" + fileName
		# process the document in 2 steps
		# 1. Strip the html tags
		firstLine = contents[0]
		firstLine = firstLine[len("<html><body>"):]
		lastLine = contents[-1]
		lastLine = lastLine[:-len("</body></html>")]
		contents = [firstLine] + contents[1:-1] + [lastLine]
		# 2. Add the xml tag and xslt tag
		contents = [self.XML_PREFIX, content] + contents
		writeFile = open(outFilePath, 'w')
		writeFile.write(''.join(contents))
		writeFile.close()

	def mv2webroot(self):
		utils.fileMover(self.temp_out_dir, self.webroot_dir)

	def mvAssets(self):
		homePath = os.getenv('HOME')
		assetsPath = '%s/labrador/etc/templets/stylesheets/new_web/assets/' % homePath
		targetAssetsPath = '%s/assets/' % self.webroot_dir
		utils.fileMover(assetsPath, targetAssetsPath)

		targetCustomPath = targetAssetsPath + "custom/"
		utils.fileMover(self.custom_dir, targetCustomPath)

	def mvFooterXML(self):
		homePath = os.getenv('HOME')
		xmlPath = '%s/labrador/etc/templets/webroot/*.xml' % homePath
		targetXmlPath = self.temp_out_dir
		cmdMoveXml = "cp " + xmlPath + " " + targetXmlPath
		os.system(cmdMoveXml)

	def mvXSL(self):
		homePath = os.getenv('HOME')
		xslPath = '%s/labrador/etc/templets/stylesheets/new_web/*.xsl' % homePath
		targetXslPath = '%s/xml_stylesheets/' % self.webroot_dir
		cmdMoveXsl = "cp " + xslPath + " " + targetXslPath
		os.system(cmdMoveXsl)
