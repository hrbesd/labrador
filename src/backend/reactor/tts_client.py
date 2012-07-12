# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import urllib2, base64
from xml.dom.minidom import parseString

class TTSClient:
	configDict = {}

	def __init__(self, configPath):	
		self.configDict = {}
		configItems = [item for item in open(configPath).readlines()]
		for item in configItems:
			key, value = item.split(':', 1)
			self.configDict[key] = value.strip()

	def sendJobRequest(self, text):
		conDict = self.configDict
		urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text.encode('utf8')))
		jobResult = urllib2.urlopen(urlPath).read()
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
			return audioPath

	def generateSound(self, text):
		if len(text) == 0:
			return False
		print text + "   " + str(len(text))
		jobID = self.sendJobRequest(text)
		return self.getAudioPath(jobID)

def main():
	client = TTSClient('reactor_config.config')
	print client.generateSound('<bodydata>据全国征兵工作会议和省政府有关征兵工作的要求，为圆满完成哈尔滨市今冬征兵任务，特发此令。</bodydata>')

if __name__ == '__main__':
	main()