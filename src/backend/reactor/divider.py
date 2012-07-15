# -*- encoding:utf-8 -*-
# 用来处理断句，并进行请求，将结果存放到服务器
from tts_client import TTSClient
from BeautifulSoup import BeautifulSoup, Comment, Tag
import datetime, re

class Divider:
	MAX_STEP = 100

	def __init__(self, soup, configPath):
		self.soup = soup
		self.client = TTSClient(configPath)
		self.dividerPattern = re.compile(ur"([^。，！？……,!?\n\r]+)([。，！？……,!?\n\r])", re.UNICODE)

	def doWork(self):
		soup = self.soup
		print soup.prettify()
		# first of all, process the fixed elements, like `title', `author', `lastmodified'
		# `lastmodified' need to be changed to human readable text

		# TODO 修改设计方式
		for element in soup.findAll(['title', 'author']):
			content = element.contents[0].strip()
			soundPath = self.client.generateSound(content)
			print soundPath
			if soundPath:
				dataTag = Tag(soup, 'data', [('id', soundPath)])
				dataTag.insert(0, content)
				element.contents[0] = dataTag

		for element in soup.findAll('lastmodified'):
			content = element.contents[0].strip()
			print content
			try:
				modifiedDate = datetime.datetime.fromtimestamp(long(content) / 1000)
				dateStr = modifiedDate.strftime(u'%Y年%m月%d日'.encode('utf-8'))
				content = dateStr.decode('utf-8')
			except:
				content = u"未知"
			soundPath = self.client.generateSound(content)
			print soundPath
			if soundPath:
				dataTag = Tag(soup, 'data', [('id', soundPath)])
				dataTag.insert(0, content)
				element.contents[0] = dataTag

		for element in soup.findAll('bodydata'):
			dividedSentences = Tag(soup, 'bodydata')
			# TODO 按照树状结构重建翻译之后的节点
			content = element.contents[0].strip()
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
							print soundPath
							sentenceTag = Tag(soup, 'data', [('id', soundPath)])
							sentenceTag.insert(0, words)
							dividedSentences.append(sentenceTag)			
			element.replaceWith(dividedSentences)

		return soup
