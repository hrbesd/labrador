import time
import logger

def exeTime(func):
    def newFunc(*args, **args2):
    	l = open('tts_logger.log', 'a')
    	print args[1]
    	text = args[1]
        start = time.time()
        back = func(*args, **args2)
        l.write("%.4fs taken for text {%s}" % (time.time() - start, text))
        l.close()
        return back
    return newFunc
