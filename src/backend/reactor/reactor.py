#!/usr/bin/python
# -*- encoding:utf-8 -*-
# 为reactor提供命令行参数的包装、处理
# 不进行reactor的实际操作
import reactor_main, argparse
import cProfile, pstats
import time
from subprocess import Popen

args = None

def main():
	start = time.time()

	# start the proxy
	proxy = Popen(['python', '../../butts/reactor/tts_proxy.py'])

	time.sleep(2)

	reactorObj = reactor_main.Reactor(args.rule_dir, args.config_dir, args.source_dir, args.worker_dir, args.log_file)
	reactorObj.doReactorWork()

	print "\n\n\n\nUsed %.3fs for reactor!" % (time.time() - start)


if __name__ == '__main__':
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
		print reactor_main.getVersionStr()
	else:
		logName = 'profiler.log'
		cProfile.run('main()', logName)

		# show it
		print 'Profiler result:'
		p = pstats.Stats(logName)
		p.strip_dirs().sort_stats('cumulative').print_stats()
