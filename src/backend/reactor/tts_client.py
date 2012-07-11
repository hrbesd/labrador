# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import httplib
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
		jobUrl = conDict['jobRequestTemplate'] % (conDict['ttsKey'], text)
		conn = httplib.HTTPConnection(conDict['serverUrl'])
		conn.request('GET', jobUrl)
		jobResult = conn.getresponse().read()
		conn.close()
		dom = parseString(jobResult)
		jobList = dom.getElementsByTagName('jobID')
		jobID = ""
		for jobNode in jobList:
			xmlData = jobNode.toxml()
			jobID = xmlData[7:-8]
		print jobID
		return jobID

	def getAudioPath(self, jobID):
		conDict = self.configDict
		requestUrl = conDict['audioPath'] % jobID
		conn = httplib.HTTPConnection(conDict['serverUrl'])
		conn.request('GET', requestUrl)
		audioResult = conn.getresponse().read()
		conn.close()
		dom = parseString(audioResult)
		urlList = dom.getElementsByTagName('url')
		for urlNode in urlList:
			xmlData = urlNode.toxml()
			audioPath = xmlData[5:-6]
			print audioPath
			return audioPath

def main():
	client = TTSClient('reactor_config.config')
	jobID = client.sendJobRequest('中国中国早上好')
	client.getAudioPath(jobID)

if __name__ == '__main__':
	main()
