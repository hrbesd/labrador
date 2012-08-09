#!/usr/bin/python
# -*- encoding:utf-8 -*-
import urllib2, sys

conDict = {'jobRequestTemplate':'%s/TextToSpeech/webservice/text2Speech/text2Speech?key=%s&text=%s&base64=null', 'serverUrl':'http://123.166.118.135:8080', 'ttsKey':'zhangjianzong'}

def doWork(text):
	urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text))
	try:
		conn = urllib2.urlopen(urlPath)
		conn.close()
	except Exception as e:
		print e

if __name__ == '__main__':
	if len(sys.argv) > 0:
		doWork(sys.argv[0])