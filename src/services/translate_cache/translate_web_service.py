# -*- encoding: utf-8 -*-

import server.bottle, hashlib, os, urllib2
from server.bottle import route,  run

# 记录缓存的文件夹
output_folder = "cache/"
debug = True
GOOGLE_API_KEY = "AIzaSyD_18Z6FkUQI5R-JprYSiDgE87qZB3rjX0"

# 做对应的翻译工作，其中lang是目标语言，text是要翻译的内容
@route('/translate/:lang/:text', method="GET")
def doTranslate(lang, text):
	digest = hashlib.md5()
	digest.update(text)
	resultFileName = digest.hexdigest()
	resultFolderName = resultFileName[:6]
	targetFolder = output_folder + resultFolderName
	if not os.path.exists(targetFolder):
		os.makedirs(targetFolder)

	targetFile = targetFolder + "/" + resultFileName
	# miss
	if not os.path.isfile(targetFile):
		if debug:
			print "[miss] " + text

		real_url = "https://www.googleapis.com/language/translate/v2?key=%s8&source=zh-CN&target=%s&q=%s" % (GOOGLE_API_KEY, lang, text);

		if debug:
			print "[request] " + real_url

		result = urllib2.urlopen(real_url).read()

		# cache it!
		cache_file = open(targetFile, 'w')
		cache_file.write(result)
		cache_file.close()
	else: # hit
		if debug:
			print "[hit] " + text
		cache_file = open(targetFile, 'r')
		result = cache_file.read()
		cache_file.close()

	if debug:
		print result

	server.bottle.response.set_header('Access-Control-Allow-Origin', '*')

	return result

server.bottle.debug(debug)
run(host='localhost', port='9999')
