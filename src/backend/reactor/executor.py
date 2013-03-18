# -*- encoding:utf-8 -*-
# 真正执行命令的Python文件
import logger
from config_parser import ConfigParser

class Executor:
	def __init__(self, configFilePath):
		self.configPath = configFilePath

	# condition
	def missing(self, target, args):
		if len(args) < 1:
			return False
		return not target.has_attr(args[0])

	def has(self, target, args):
		if len(args) < 1:
			return False
		return target.has_attr(args[0])

	def equal(self, target, args):
		if len(args) != 2:
			return False

		attrName, attrValue = args
		return target.has_attr(attrName) and str(target[attrName]) == str(attrValue)

	def let(self, target, args):
		if len(args) != 2:
			return False

		attr, value = args
		target_val = 0
		try:
			target_val = int(target[attr])
		except Exception, e:
			target_val = 0
		return target_val <= int(value)

	def insideSite(self, url):
		return False

	def outsideSite(self, url):
		return False

	# actions
	def remove(self, target):
		target.extract()

	def fill(self, target, args):
		targetElement, filePath = args
		filePath = ''.join(filePath)
		# add base dir for config file
		filePath = self.configPath + "/" + filePath
		parser = ConfigParser(filePath)
		alt_dict = parser.parseFile()
		element, attr = targetElement.split(' ')
		if target.has_attr('hash'):
			targetHash = target['hash'].encode('ascii')
			if alt_dict.has_key(targetHash): # 对于未经过配置的内容，不做替换处理
				target[attr] = alt_dict[targetHash]


	def replace(self, target, args):
		targetElement, content = args
		parts = targetElement.split(' ')
		if len(parts) == 1: # element
			for sub_element in soup.findAll(target):
				contents = sub_element.contents
				target_tag = Tag(soup, ''.join(content))
				target_tag.contents = contents
				sub_element.replaceWith(target_tag)
		else: # attribute
			element, attr = parts
			if target.has_attr(attr):
				target[attr] = ''.join(content)

	def set(self, target, args):
		targetElement, attr, content = args
		if content.find('(') != -1:
			methodName, value = content.split('(')
			value = value[:-1]
			getattr(Executor, methodName)
			content = methodName(self, value)
		elif content.find('[') != -1:
			attrName = content[1:-1]
			if target.has_attr(attrName):
				content = target[attrName]
			else:
				content = ''

		target[attr] = content

		pass

	def pageTitle(self, url):
		#TODO do that
		return 'test'

	# log
	def doLog(self, level, filename, message):
		logger.log(level, filename, message)

	# end of reactor
	def finished(self):
		logger.flush()
