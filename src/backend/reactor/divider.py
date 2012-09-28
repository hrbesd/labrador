# -*- encoding:utf-8 -*-
# 用来处理断句，并进行请求，将结果存放到服务器
from bs4 import BeautifulSoup, Comment, Tag, NavigableString
import datetime, re, html

class Divider:
	MAX_STEP = 100

	def __init__(self, soup, configPath):
		self.soup = soup
		self.dividerPattern = re.compile(ur"([^。！？；……!?;\n\r]+)([。！？；……!?;\n\r])", re.UNICODE)

	def divide(self, element): # element is NavigableString
		resultSentence = []
		content = element.strip()
		m = self.dividerPattern.findall(content)
		for parts in m:
			if len(parts) == 2:
				sentence = parts[0].strip() + parts[1].strip()
				sentenceLength = len(sentence)
				currentLength = 0
				while currentLength < sentenceLength:
					left = currentLength
					right = min(sentenceLength, left + self.MAX_STEP)
					currentLength = right
					words = sentence[left:right]
					sentenceTag = self.soup.new_tag('span')
					sentenceTag['class'] = 'tts_data'
					sentenceTag.string = words
					resultSentence.append(sentenceTag)
		return resultSentence

	def processSentence(self, element):
		if isinstance(element, NavigableString):
			results = self.divide(element)
			if len(results) == 0:
				return
			resultTag = self.soup.new_tag('p')
			for result in results:
				resultTag.append(result)
			element.replaceWith(resultTag)
		elif isinstance(element, unicode):
			return
		else:
			for child in element:
				self.processSentence(child)

	def doWork(self):
		soup = self.soup
		# first of all, process the fixed elements, like `title', `author', `lastmodified'
		# `lastmodified' need to be changed to human readable text
		bodyData = soup.find_all('bodydata')
		if len(bodyData) > 0: # data files
			# TODO 修改设计方式
			for element in soup.find_all(['title', 'author']):
				if len(element.contents) == 0:
					continue
				content = element.contents[0].strip()
				dataTag = self.soup.new_tag('span')
				dataTag['class'] = 'tts_data'
				dataTag.string = content
				element.contents[0] = dataTag

			for element in soup.find_all('lastmodified'):
				if len(element.contents) == 0:
					continue
				content = element.contents[0].strip()

				# 现在时间是字符串了，reactor只负责显示
				"""
				try:
					modifiedDate = datetime.datetime.fromtimestamp(long(content) / 1000)
					dateStr = modifiedDate.strftime(u'%Y年%m月%d日'.encode('utf-8'))
					content = dateStr.decode('utf-8')
				except:
					content = u""

				"""

				dataTag = self.soup.new_tag('span')
				dataTag['class'] = 'tts_data'
				dataTag.string = "<time>" + content + "</time>"
				element.contents[0] = dataTag

			for element in bodyData:
				self.processSentence(element)
		else: # navigation files
			for element in soup.find_all('name'):
				if len(element.contents) > 0 and element.contents[0]:
					try:
						content = element.contents[0].strip()
						dataTag = self.soup.new_tag('span')
						dataTag['class'] = 'tts_data'
						dataTag.string = content
						element.contents[0] = dataTag
					except Exception, e:
						print e

		return soup
