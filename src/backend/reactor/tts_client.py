# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import urllib2, base64
from xml.dom.minidom import parseString
import profiler

class TTSClient:
	configDict = {}

	def __init__(self, configPath):	
		self.configDict = {}
		configItems = [item for item in open(configPath).readlines()]
		for item in configItems:
			key, value = item.split(':', 1)
			self.configDict[key] = value.strip()

	@profiler.exeTime
	def sendJobRequest(self, text):
		conDict = self.configDict
		urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text.encode('utf8')))
		try:
			conn = urllib2.urlopen(urlPath)
			conn.close()
		except Exception as e:
			print 'Error occurred when processing %s' % text
			print e
		'''jobResult = urllib2.urlopen(urlPath).read()
		dom = parseString(jobResult)
		jobList = dom.getElementsByTagName('jobID')
		jobID = ""
		for jobNode in jobList:
			xmlData = jobNode.toxml()
			jobID = xmlData[7:-8]
		return jobID

	def getAudioPath(self, jobID):
		conDict = self.configDict
		requestUrl = conDict['audioPath'] % (conDict['serverUrl'], jobID)
		audioResult = urllib2.urlopen(requestUrl).read()
		dom = parseString(audioResult)
		urlList = dom.getElementsByTagName('url')
		for urlNode in urlList:
			xmlData = urlNode.toxml()
			audioPath = xmlData[5:-6]
			return audioPath'''

	def generateSound(self, text):
		if len(text) == 0:
			return False
		self.sendJobRequest(text)
		'''jobID = self.sendJobRequest(text)
		return self.getAudioPath(jobID)'''
