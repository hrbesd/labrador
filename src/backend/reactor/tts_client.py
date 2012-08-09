# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import time
import urllib, urllib2, html
import threading
from subprocess import Popen

NUM_THREAD_MAX = 8
mutex = threading.Semaphore(NUM_THREAD_MAX)

def callProxy(text):
	global mutex
	Popen(['python', '../../butts/reactor/tts_proxy.py', text])
	mutex.release()

class TTSClient:
	def generateSound(self, text):
		text = html.unescape_string(text)
		if len(text.strip()) == 0:
			return False

		mutex.acquire()
		t = threading.Thread(target=callProxy, args=[text, ])
		t.start()
		return True

def main():
	t = TTSClient()
	for i in range(10000):
		t.generateSound(u'你好中国')
		print "Processed %d" % i

if __name__ == '__main__':
	start = time.time()
	main()
	print "\n\n\n\nUsed %.3fs for 10000 requests!" % (time.time() - start)