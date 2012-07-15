# -*- encoding:utf-8 -*-
# 用来处理断句，并进行请求，将结果存放到服务器
from tts_client import TTSClient
from BeautifulSoup import BeautifulSoup, Comment, Tag, NavigableString
import datetime, re, html

class Divider:
	MAX_STEP = 100

	def __init__(self, soup, configPath):
		self.soup = soup
		self.client = TTSClient(configPath)
		self.dividerPattern = re.compile(ur"([^。，！？；……,!?;\n\r]+)([。，！？；……,!?;\n\r])", re.UNICODE)

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
					soundPath = self.client.generateSound(words)
					if soundPath:
						sentenceTag = Tag(self.soup, 'data', [('id', soundPath)])
						sentenceTag.insert(0, words)
						resultSentence.append(sentenceTag)
		return resultSentence

	def processSentence(self, element):
		if type(element) == NavigableString:
			results = self.divide(element)
			resultTag = Tag(self.soup, 'p')
			for result in results:
				resultTag.append(result)
			element.replaceWith(resultTag)
		else:
			for child in element:
				self.processSentence(child)

	def doWork(self):
		soup = self.soup
		# first of all, process the fixed elements, like `title', `author', `lastmodified'
		# `lastmodified' need to be changed to human readable text

		# TODO 修改设计方式
		for element in soup.findAll(['title', 'author']):
			content = element.contents[0].strip()
			soundPath = self.client.generateSound(content)
			if soundPath:
				dataTag = Tag(soup, 'data', [('id', soundPath)])
				dataTag.insert(0, content)
				element.contents[0] = dataTag

		for element in soup.findAll('lastmodified'):
			content = element.contents[0].strip()
			try:
				modifiedDate = datetime.datetime.fromtimestamp(long(content) / 1000)
				dateStr = modifiedDate.strftime(u'%Y年%m月%d日'.encode('utf-8'))
				content = dateStr.decode('utf-8')
			except:
				content = u"未知"
			soundPath = self.client.generateSound(content)
			if soundPath:
				dataTag = Tag(soup, 'data', [('id', soundPath)])
				dataTag.insert(0, content)
				element.contents[0] = dataTag

		for element in soup.findAll('bodydata'):
			self.processSentence(element)

		return soup
