# -*- encoding: utf-8 -*-
# 使用PyParsing编写reactor规则的DSL解析器
from pyparsing import *
from rule_item import *

class RuleParser:
	# 关键字
	conOperator = Suppress('->')
	actOperator = Suppress('=>')
	logOperator = Suppress('==>')
	logSeperator = Suppress('|')
	endConfig = Suppress('===')
	startArg = Suppress('(')
	endArg = Suppress(')')

	# 字母表
	legalPathDict = alphanums + '_./\\:"'
	htmlContent = alphanums + '_'

	def __init__(self):
		element = Word(self.htmlContent)
		attribute = Word(self.htmlContent)
		target = Group(element + Optional(attribute)).setResultsName('target')

		opName = Word(self.htmlContent)
		arg = Word(self.legalPathDict)
		actExpr = opName + Optional(self.startArg + arg + self.endArg)

		conExpr = Group(actExpr)
		condition = self.conOperator + conExpr

		logLevel = oneOf('info warning error debug')
		sentence = OneOrMore(Word(alphanums))
		logMessage = sentence
		logExpr = logLevel + self.logSeperator + logMessage
		log = self.logOperator + logExpr

		action = Group(self.actOperator + actExpr)

		elementConfig = Group(target 
			+ Group(ZeroOrMore(condition)).setResultsName('condition') 
			+ Group(ZeroOrMore(action)).setResultsName('action')
			+ Group(ZeroOrMore(log)).setResultsName('log')
			+ self.endConfig).setResultsName('rule_detail')
		self.ruleFile = Group(OneOrMore(elementConfig)).setResultsName('rule_item')

	def parseFile(self, filePath):
		fileToParse = open(filePath)
		fileContent = fileToParse.read()
		fileToParse.close()

		parsedRules = self.ruleFile.parseString(fileContent)
		rules = []
		for item in parsedRules.rule_item:
			newRule = RuleItem()
			newRule.target = ' '.join(item.target)
			for con in item.condition:
				newRule.addCondition(list(con))
			for act in item.action:
				newRule.addAction(list(act))
			if len(item.log) > 1:
				newRule.setLog(item.log[0], item.log[1:])
			rules.append(newRule)

		return rules