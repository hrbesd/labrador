# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
from suds.client import Client

class TTSClient:
	def __init__(self):	
		self.tts_client = Client('http://127.0.0.1:7789/?wsdl')

	def generateSound(self, text):
		if len(text) == 0:
			return False

		result = self.tts_client.service.text2Speech('zhangjianzong', text, 'null')
		return result

if __name__ == '__main__':
	t = TTSClient()
	for i in range(10000):
		t.generateSound(u'你好中国')