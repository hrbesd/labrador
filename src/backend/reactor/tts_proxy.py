#!/usr/bin/python
# -*- encoding:utf-8 -*-
import soaplib
from soaplib.core.util.wsgi_wrapper import run_twisted
from soaplib.core.server import wsgi
from soaplib.core.service import DefinitionBase, soap
from soaplib.core.model.primitive import String

import urllib2, base64
import Queue
from xml.dom.minidom import parseString

NUM_WORKER_THREADS = 8

taskQueue = Queue.Queue(0)

conDict = {'jobRequestTemplate':'%s/TextToSpeech/webservice/text2Speech/text2Speech?key=%s&text=%s&base64=null', 'serverUrl':'http://116.255.231.36:8080', 'ttsKey':'zhangjianzong'}

def doWork(text):
	urlPath = conDict['jobRequestTemplate'] % (conDict['serverUrl'], conDict['ttsKey'], urllib2.quote(text.encode('utf8')))
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

class TTSProxyService(DefinitionBase):
	@soap(String, String, String, _returns=String)
	def text2Speech(self, key, text, base64):
		self.addTask(text)
		return "DONE"

	def addTask(self, text):
		global taskQueue
		taskQueue.put(text)

def main():
	for i in range(NUM_WORKER_THREADS):
		t = Thread(target=proxyWorker)
		t.daemon = True
		t.start()

	soap_app = soaplib.core.Application([TTSProxyService], 'tns')
	wsgi_app = wsgi.Application(soap_app)
	print 'listening on 127.0.0.1:7789'
	print 'wsdl is at: http://127.0.0.1:7789/SOAP/?wsdl'
	run_twisted(((wsgi_app, "SOAP"),), 7789)

if __name__ == '__main__':
	main()