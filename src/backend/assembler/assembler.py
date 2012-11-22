#!/usr/bin/python
# -*- encoding:utf-8 -*-
# 对assembler类的封装，用于进行参数解析等工作
# 不进行assembler的实际操作
import assembler_main, argparse

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument('-v', '--version', help='显示当前版本号', action='store_true')
	parser.add_argument('--site-config', help='site config')
	parser.add_argument('--config-dir', help='config dir')
	parser.add_argument('--rule-dir', help='rule dir')
	parser.add_argument('--source-dir', help='reactor文件提供的文件内容')
	parser.add_argument('--worker-dir', help='输出的文件路径')
	parser.add_argument('--shared-dir', help='共享文件路径')
	parser.add_argument('--webroot-dir', help='所有文件处理完成之后，文件存放的路径')
	parser.add_argument('--stylesheet-dir', help='xslt文件所在目录')
	parser.add_argument('--log-file', help='日志文件', default='assembler_log.log')

	args = parser.parse_args()
	if args.version:
		print assembler_main.getVersionStr()
		return

	config_path = args.site_config
	config_path = config_path[:config_path.rindex('/')] + "/custom"

	assemblerObj = assembler_main.Assembler(args.source_dir,
		args.stylesheet_dir,
		args.shared_dir,
		args.worker_dir,
		args.webroot_dir,
		args.log_file)
	assemblerObj.doAssembleWork()


if __name__ == '__main__':
	main()
