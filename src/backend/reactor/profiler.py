import time, codecs

count = 0

def exeTime(func):
    def newFunc(*args, **args2):
    	global count
    	l = codecs.open('tts_logger.log', 'a+', 'utf-8')
    	text = args[1]
        start = time.time()
        back = func(*args, **args2)
        logText = "%.4fs taken for text %s" % (time.time() - start, text)
        l.write(logText)
        l.close()
        count += 1
        return back
    return newFunc
