# -*- encoding: utf-8 -*-

class RuleItem:
	def __init__(self):
		self.target = ''
		self.condition = []
		self.action = []
		self.logLevel = ''
		self.logMsg = ''

	def setTarget(self, target):
		self.target = target

	def addCondition(self, con):
		self.condition.append(con)

	def addAction(self, action):
		self.action.append(action)

	def setLog(self, level, msg):
		self.logLevel = level
		self.logMsg = msg

	def __str__(self):
		return self.target + "  " + str(self.condition) + "   " + str(self.action) + "  " + self.logLevel + "  " + self.logMsg