#!/usr/bin/python
# -*- encoding:utf-8 -*-
import urllib2, codecs
import Queue
import bottle
from bottle import run, route, request
from threading import Thread
from bs4 import BeautifulSoup, NavigableString
import logger
import time

NUM_WORKER_THREADS = 8
taskQueue = Queue.Queue(0)

logger.setLogPath('/tmp/tts_proxy.%d.log' % (int(time.time())))
#request voice server
conDict = {'jobRequestTemplate':'%s/TextToSpeech/webservice/text2Speech/text2Speech?key=%s&text=%s&base64=null', 'serverUrl':'http://116.255.231.36:8083', 'ttsKey':'zhangjianzong'}

def doWork(url):
	xmlDataFile = codecs.open(url, 'r', 'utf-8')
	xmlData = xmlDataFile.read()
	xmlDataFile.close()

	soup = BeautifulSoup(xmlData, 'xml')
	for data_element in soup.find_all('span'):
		if data_element.has_attr('class') and data_element['class'] == 'tts_data':
			for element in data_element:
				if type(element) == NavigableString:
					urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(element.encode('utf-8')))
					logger.debug(urlPath)
 					conn = urllib2.urlopen(urlPath)
 					conn.close()

	# issue 241
	for img_element in soup.find_all('img'):
		if img_element.has_attr('alt') and len(img_element['alt']) > 0:
			img_alt = img_element['alt']
			urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(img_alt.encode('utf-8')))
			logger.debug(urlPath)
			conn = urllib2.urlopen(urlPath)
			conn.close()

	logger.flush()

def proxyWorker():
	while True:
		item = taskQueue.get(True)
		doWork(item)
		taskQueue.task_done()

@route('/genSoundForFile')
def genSoundForFile():
	path = request.GET.get('path', default=None)
	if path is not None:
		addTask(path)
	return "DONE"

def addTask(filePath):
	global taskQueue
	taskQueue.put(filePath)

def main():
	for i in range(NUM_WORKER_THREADS):
		t = Thread(target=proxyWorker)
		t.daemon = True
		t.start()

	bottle.debug(False)

	try:
		run(host='localhost', port=7800, quiet=True)
	except Exception as e:
		print e

if __name__ == '__main__':
	main()
