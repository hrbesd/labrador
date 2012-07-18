# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import urllib2, base64
from xml.dom.minidom import parseString
import profiler
from threading import Thread, Semaphore

class TTSClient:
	configDict = {}

	def __init__(self, configPath):	
		self.configDict = {}
		self.sem = Semaphore(4) # limited by tts service
		configItems = [item for item in open(configPath).readlines()]
		for item in configItems:
			key, value = item.split(':', 1)
			self.configDict[key] = value.strip()

	@profiler.exeTime
	def sendJobRequest(self, text):
		self.sem.acquire(True)
		conDict = self.configDict
		urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text.encode('utf8')))
		try:
			conn = urllib2.urlopen(urlPath)
			conn.close()
		except Exception as e:
			print 'Error occurred while processing %s' % text
			print e
		self.sem.release()

	def generateSound(self, text):
		if len(text) == 0:
			return False

		th = Thread(target=self.sendJobRequest, args = (text, ))
		th.start()
