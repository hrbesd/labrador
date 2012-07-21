# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
from suds.client import Client

class TTSClient:
	def __init__(self):	
		self.tts_client = Client('http://127.0.0.1:7789/SOAP/?wsdl')

	def generateSound(self, text):
		global sem

		if len(text) == 0:
			return False

		if text[0] == '&':
			return False

		self.tts_client.service.text2Speech('zhangjianzong', text, 'null')
		return True

def main():
	print "Got Here!!!"
	t = TTSClient()
	print "Got Here2!!!!"
	for i in range(10000):
		t.generateSound(u'你好中国')
		print "Processed %d" % i

if __name__ == '__main__':
	logName = 'tts_client.log'
	cProfile.run('main()', logName)

	# show it
	print 'TTS Client result:'
	p = pstats.Stats(logName)
	p.strip_dirs().sort_stats('cumulative').print_stats()
