#!/usr/bin/python
# -*- encoding:utf-8 -*-
# 为reactor提供命令行参数的包装
# 根据参数执行不同的命令
import reactor_main, argparse
import cProfile, pstats
import time
import logger

args = None

def parseArgs():
	'''Parse Command Line Arguments
	
	-v, --version
		Tell user the reactor version, in the format of MAJOR_VERSION.MINOR_VERSION.SUB_VERSION.[Desktop/Server/Cloud]

	--rule-dir
		The reactor DSL dir location

	--config-dir
		The configuration dir for reactor

	--source-dir
		Tell the reactor about the analyser files

	--worker-dir
		Where to write the reactor files

	--site-config
		The configuration dir of the site

	--shared-dir
		The sitemap.xml file

	--log-file
		Where to write the log. All reactor logs are written into one single log file, seperated by different components.

	'''
	parser = argparse.ArgumentParser()
	parser.add_argument('-v', '--version', help='显示当前版本号', action='store_true')
	parser.add_argument('--rule-dir', help='reactor规则文件位置', default='reactor.rrule')
	parser.add_argument('--config-dir', help='reactor配置文件位置', default='reactor.config')
	parser.add_argument('--source-dir', help='analyser分析之后输出的文件路径')
	parser.add_argument('--worker-dir', help='reactor要输出的文件路径')
	parser.add_argument('--site-config', help='site config')
	parser.add_argument('--shared-dir', help='shared dir')
	parser.add_argument('--log-file', help='reactor日志文件', default='reactor_log.log')

	args = parser.parse_args()
	if args.version:
		showVersion()
	else:
		main()

def showVersion():
	print reactor_main.getVersionStr()

def main():
	start = time.time()

	# create singleton class
	logger.setLogPath(args.log_file)

	reactorObj = reactor_main.Reactor(args.rule_dir, args.config_dir, args.site_config, args.source_dir, args.worker_dir, args.shared_dir)
	reactorObj.doReactorWork()

	print "\n\n\n\nUsed %.3fs for reactor!" % (time.time() - start)


if __name__ == '__main__':
	parseArgs()
