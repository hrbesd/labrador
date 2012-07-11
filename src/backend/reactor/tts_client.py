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
		urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text))
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

def main():
	client = TTSClient('reactor_config.config')
	jobID = client.sendJobRequest('这下终于好用啦！！哈哈哈哈哈哈哈，南京市长江大桥，中国银行行长')
	client.getAudioPath(jobID)

if __name__ == '__main__':
	main()
