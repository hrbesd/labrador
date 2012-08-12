#-*- encoding:utf-8 -*-
import os, shutil

def fileMover(src, target):
	# 由于shutil的copytree方法要求目录不能存在，因此首先要做判断，如果已经存在，就先使用shutil的rmtree来删除目录
	if os.path.exists(target):
		shutil.rmtree(target)
	shutil.copytree(src, target)