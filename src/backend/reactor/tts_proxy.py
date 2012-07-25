#!/usr/bin/python
# -*- encoding:utf-8 -*-
import urllib2, base64
import Queue
import bottle
from bottle import run, route, request
from xml.dom.minidom import parseString
from threading import Thread

NUM_WORKER_THREADS = 8

taskQueue = Queue.Queue(0)

conDict = {'jobRequestTemplate':'%s/TextToSpeech/webservice/text2Speech/text2Speech?key=%s&text=%s&base64=null', 'serverUrl':'http://116.255.231.36:8080', 'ttsKey':'zhangjianzong'}

def doWork(text):
	urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text))
	try:
		conn = urllib2.urlopen(urlPath)
		conn.close()
	except Exception as e:
		print e

def proxyWorker():
	while True:
		item = taskQueue.get(True)
		doWork(item)
		taskQueue.task_done()

@route('/text2Speech')
def text2Speech():
	text = request.GET.get('text', default=None)
	if text is not None:
		addTask(text)
	return "DONE"

def addTask(text):
	global taskQueue
	taskQueue.put(text)

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