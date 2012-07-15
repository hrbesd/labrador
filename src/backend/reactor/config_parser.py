# -*- encoding: utf-8 -*-
# 认为配置文件中的内容是以键值对的形式保存的
import codecs

class ConfigParser:
	def __init__(self, filePath):
		self.filePath = filePath
		self.alt_dict = {}

	def parseFile(self):
		try:
			configFile = codecs.open(self.filePath, 'r', 'utf-8')
			for line in configFile.readlines():
				hashKey, alt = line.split(" ")
				self.alt_dict[hashKey.encode('ascii')] = alt
			configFile.close()
			return self.alt_dict
		except:
			return self.alt_dict