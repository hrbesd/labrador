# -*- encoding:utf-8 -*-
# 用来处理断句，并进行请求，将结果存放到服务器
from tts_client import TTSClient

class Divider:
	SEPERATOR_CANDIDATE = ['.', '。', ',', '，', '!', '！', '?' , '？', '……']

	def __init__(self):
