# -*- encoding: utf-8 -*-
# 日志记录类
# 这里采用了缓冲队列，只有在队列记录满，或者主动请求flush方法的时候才输出日志
import time

outPath = None
logBuff = []
LOG_WINDOW_SIZE = 5000

do_log = True

def setLogPath(path):
	global outPath
	if not outPath:
		outPath = path

def flushCurrentLog():
	global logBuff, outPath
	if len(logBuff) == 0:
		return
	logFile = open(outPath, 'a+')
	logFile.write('\n'.join(logBuff))
	logFile.write('\n')
	logFile.flush()
	logFile.close()
	logBuff = []

def error(message):
	log('ERROR', 'Console', [message, ])

def warning(message):
	log('WARNING', 'Console', [message, ])

def info(message):
	log('INFO', 'Console', [message, ])

def debug(message):
	log('DEBUG', 'Console', [message, ])

def flush():
	flushCurrentLog()

def log(level, column, message):
	if not do_log:
		return
	logTime = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
	logStr = formatLog(logTime, level, column, message)
	logBuff.append(logStr)

	if len(logBuff) >= LOG_WINDOW_SIZE:
		flushCurrentLog()

def formatLog(time, level, column, message):
	return '[%s] [%s] [%s] [%s]' % (time, level, column, ' '.join(message))

def runUnitTest():
	setLogPath('/tmp/l1.log')
	for i in xrange(1,10050):
		error(str(i))
		warning(str(i))
		info(str(i))
		debug(str(i))
		log('WARNING', 'TEST', [str(i), ])
	flush()

if __name__ == '__main__':
	runUnitTest()
