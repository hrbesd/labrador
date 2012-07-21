#!/usr/bin/python
# -*- encoding:utf-8 -*-
import soaplib
from soaplib.core.server import wsgi
from soaplib.core.service import DefinitionBase, soap
from soaplib.core.model.primitive import String

import urllib2, base64
import Queue
from xml.dom.minidom import parseString
from threading import Thread, Semaphore

sem = Semaphore(8)
taskQueue = Queue.Queue()

class TTSWorkerThread(Thread):
	def __init__(self, text):
		super(TTSWorkerThread, self).__init__()
		self.text2send = text
		self.configDict = {'jobRequestTemplate':'%s/TextToSpeech/webservice/text2Speech/text2Speech?key=%s&text=%s&base64=null', 'serverUrl':'http://116.255.231.36:8080', 'ttsKey':'zhangjianzong'}

	def run(self):
		global sem
		conDict = self.configDict
		urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(self.text2send.encode('utf8')))
		try:
			conn = urllib2.urlopen(urlPath)
			print conn.read()
			conn.close()
		except Exception as e:
			print e

		sem.release()

class TTSProxyService(DefinitionBase):
	@soap(String, String, String, _returns=String)
	def text2Speech(self, key, text, base64):
		self.addTask(text)
		return "DONE"

	def addTask(self, text):
		global taskQueue
		taskQueue.put(text)

def queryList():
	while True:
		if not taskQueue.empty():
			global sem
			sem.acquire()
			text = taskQueue.get()
			th = TTSWorkerThread(text)
			th.start()

def main():
	from wsgiref.simple_server import make_server
	queryThread = Thread(target=queryList)
	queryThread.start()
	soap_app = soaplib.core.Application([TTSProxyService], 'tns')
	wsgi_app = wsgi.Application(soap_app)
	print 'listening on 127.0.0.1:7789'
	print 'wsdl is at: http://127.0.0.1:7789/?wsdl'
	server = make_server('localhost', 7789, wsgi_app)
	server.serve_forever()

if __name__ == '__main__':
	main()