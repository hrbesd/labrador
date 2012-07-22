# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import time
import urllib2

class TTSClient:
	def generateSound(self, text):
		if len(text) == 0:
			return False

		if text[0] == '&':
			return False

		conn = urllib2.urlopen('http://127.0.0.1:7800/text2Speech?text=' + text.encode('utf-8'))
		conn.close()
		return True

def main():
	print "Got Here!!!"
	t = TTSClient()
	print "Got Here2!!!!"
	for i in range(10000):
		t.generateSound(u'你好中国')
		print "Processed %d" % i

if __name__ == '__main__':
	start = time.time()
	main()
	print "\n\n\n\nUsed %.3fs for 10000 requests!" % (time.time() - start)