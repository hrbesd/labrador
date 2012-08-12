#!/usr/bin/env python
#-*- coding:utf-8 -*-

from dnspod.apicn import *
import sys
def main():

	if len(sys.argv) <> 3:
		print "You Need Correct Arguments!\nUsage : addDNSRecord record_name ip_address"
		exit()

	email = '9807068@qq.com'
	password = '123456'
	domain_id = '1916162'


	api = RecordCreate(sys.argv[1], "A", u'默认'.encode("utf8"), sys.argv[2], 600, domain_id=domain_id,email=email,password=password)
	record = api().get("record", {})
	record_id = record.get("id")
	print "Record id", record_id
    
    
if __name__ == '__main__':
    main()
