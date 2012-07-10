# -*- encoding:utf-8 -*-
# 为reactor提供命令行参数的包装、处理
# 不进行reactor的实际操作
import reactor_main, argparse

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument('-v', '--version', help='显示当前版本号', action='store_true')
	parser.add_argument('--rule-dir', required=True, help='reactor规则文件位置', default='reactor.rrule')
	parser.add_argument('--config-dir', help='reactor配置文件位置', default='reactor.config')
	parser.add_argument('--source-dir', required=True, help='analyser分析之后输出的文件路径')
	parser.add_argument('--worker-dir', required=True, help='reactor要输出的文件路径')
	parser.add_argument('--log-file', help='reactor日志文件', default='reactor_log.log')

	args = parser.parse_args()
	if args.version:
		print reactor_main.getVersionStr()
		return

	reactorObj = reactor_main.Reactor(args.rule_dir, args.source_dir, args.worker_dir, args.log_file)
	reactorObj.doReactorWork()


if __name__ == '__main__':
	main()
