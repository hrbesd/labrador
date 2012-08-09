# -*- encoding:utf-8 -*-
# 调用TTS服务，并获取生成的mp3的结果
import urllib, urllib2

# 将文章地址发送给TTSProxy，在TTSProxy中针对每个文章做请求
class TTSClient:
	def callProxy(self, filePath):
		url = 'http://localhost:7800/genSoundForFile?path=%s' % filePath
		print url
		conn = urllib2.urlopen(url)
		conn.close()

def main():
	client = TTSClient()
	for x in xrange(1,10000):
		p = u'/user/local/bin/path/我是中文/%s' % x
		client.callProxy(p.encode('utf-8'))

if __name__ == '__main__':
	main()