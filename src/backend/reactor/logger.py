# -*- encoding: utf-8 -*-
# 日志记录类
# 这里采用了缓冲队列，只有在队列记录满，或者主动请求flush方法的时候才输出日志
import time

class Logger:

	def __init__(self, path):
		self.outPath = path
		self.logBuff = []
		self.LOG_WINDOW_SIZE = 5000

	def flushCurrentLog(self):
		if len(self.logBuff) == 0:
			return
		logFile = open(self.outPath, 'a+')
		logFile.write('\n'.join(self.logBuff))
		logFile.write('\n')
		logFile.flush()
		logFile.close()
		self.logBuff = []

	def log(self, level, column, message):
		logTime = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
		logStr = self.formatLog(logTime, level, column, message)
		self.logBuff.append(logStr)

		if len(self.logBuff) >= self.LOG_WINDOW_SIZE:
			self.flushCurrentLog()

	def flush(self):
		self.flushCurrentLog()

	def formatLog(self, time, level, column, message):
		return '[%s] [%s] [%s] [%s]' % (time, level, column, ' '.join(message))