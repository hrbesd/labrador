#!/usr/local/bin
# -*- coding: utf-8 -*-
import sys, os, shutil
from BeautifulSoup import BeautifulSoup

VERSION_NAME = "0.3.1.SERVER"

def getVersionStr():
	return 'Labrador Assembler Version %s' % VERSION_NAME

class Assembler:
	def __init__(self, in_folder_path, stylesheet_path, share_dir, temp_out_dir, webroot_dir, log_file):
		self.in_folder_path = in_folder_path
		self.stylesheet_path = stylesheet_path
		self.share_dir = share_dir
		self.temp_out_dir = temp_out_dir
		self.webroot_dir = webroot_dir
		self.log_file = log_file

	def __str__(self):
		return getVersionStr()

	def doAssembleWork(self):
		# 1.判断路径是否存在（index.xml和a、c、l三个目录是否存在）
		if not self.ensureInputFolderExists():
			print "Error: Input folder does not exists."
			return

		#2. 调用外部工具，生成导航栏目；在调用之前先确保目录存在
		self.ensureOutputFolderExists()
		self.genNavFiles()

		# 3.将所有stylesheet_path中文件复制到temp_out_dir中
		self.copyResourceFiles()

		# 4.分别为index.xml、a、c、l文件夹下的文件添加对应的xslt引用语句
		self.processFilesRecursively()

		# 5.将temp_out_dir中的内容复制到webroot_dir中
		self.mv2webroot()

		print 'Done!'

		return

	def ensureInputFolderExists(self):
		baseFolderPath = self.in_folder_path
		stylesheetPath = self.stylesheet_path
		print baseFolderPath
		print stylesheetPath
		return os.path.exists(self.in_folder_path) and os.path.exists(stylesheetPath)

	def xsltPath(self, type):
		return '<?xml-stylesheet type="text/xsl" href="%s"?>' % type

	# 确认输出目录是否存在，如果不存在，就创建这个目录
	def ensureOutputFolderExists(self):
		if not os.path.exists(self.temp_out_dir):
			os.makedirs(self.temp_out_dir)

		if not os.path.exists(self.webroot_dir):
			os.makedirs(self.webroot_dir)

	def genNavFiles(self):
		indexPath = ""
		for fileName in os.listdir(self.share_dir):
			if fileName.endswith('.xml'):
				indexPath = self.share_dir + "/" + fileName.replace(' ', r'\ ')

		if len(indexPath) > 0:
			command = '../../butts/assembler/producer --index-file=%s --webroot-dir=%s --log-file=%s' % (indexPath, self.temp_out_dir, self.log_file)
			print command
			os.system(command)
		else:
			print 'Index file not found!'

	def copyResourceFiles(self):
		# 导航文件直接在temp_out_path中生成，所以不用复制，需要复制的是stylesheets目录
		self.fileMover(self.stylesheet_path, self.temp_out_dir + "/xml_stylesheets")

	def processFilesRecursively(self):
		indexFile = self.temp_out_dir + "/index.xml"
		aFolderPath = self.temp_out_dir + "/a"
		cFolderPath = self.temp_out_dir + "/c"
		lFolderPath = self.temp_out_dir + "/l"

		# index first
		self.addContentAtLineNumber(indexFile, self.xsltPath('./xml_stylesheets/index.xsl'), 2)

		# c
		for root, dirs, files in os.walk(cFolderPath):
			for fileName in files:
				srcFile = root + "/" + fileName
				self.addContentAtLineNumber(srcFile, self.xsltPath('./xml_stylesheets/column.xsl'), 2)

		# l
		for root, dirs, files in os.walk(lFolderPath):
			for fileName in files:
				srcFile = root + "/" + fileName
				self.addContentAtLineNumber(srcFile, self.xsltPath('./xml_stylesheets/list.xsl'), 2)

		# a
		for root, dirs, files in os.walk(lFolderPath):
			for fileName in files:
				parentFile = root + "/" + fileName
				dataFile = self.in_folder_path + "/" + fileName[:2] + "/" + fileName

				data = open(dataFile)
				dataContent = data.read()
				data.close()

				parent = open(parentFile)
				parentContent = parent.read()
				parent.close()

				dataSoup = BeautifulSoup(dataContent)
				parentSoup = BeautifulSoup(parentContent)

				dataSoup.article.insert(0, parentSoup)
				print dataSoup

				writeFile = open(filePath, 'w')
				writeFile.write(dataSoup.prettify())
				writeFile.close()

				self.addContentAtLineNumber(dataFile, self.xsltPath('../../xml_stylesheets/list.xsl'), 2)

		pass

	def addContentAtLineNumber(self, filePath, content, lineNo):
		readFile = open(filePath)
		contents = readFile.readlines()
		readFile.close()

		contents = contents[:lineNo - 1] + [content] + contents[lineNo - 1:]
		writeFile = open(filePath, 'w')
		writeFile.write('\n'.join(contents))
		writeFile.close()

	def mv2webroot(self):
		self.fileMover(self.temp_out_dir, self.webroot_dir)

	def fileMover(self, src, target):
		# 由于shutil的copytree方法要求目录不能存在，因此首先要做判断，如果已经存在，就先使用shutil的rmtree来删除目录
		if os.path.exists(target):
			shutil.rmtree(target)
		shutil.copytree(src, target)
