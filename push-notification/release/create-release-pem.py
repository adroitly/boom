#!/usr/bin/python
# -*- coding: utf8 -*-

import os
import sys

m_cerName = "aps.cer"
m_keyName = "aps.p12"
def getScriptDirectory():
	path = os.path.abspath(sys.argv[0])
	path = os.path.realpath(path)
	path = os.path.dirname(path)
	return path

def checkFileExist(filePath):
	if not os.path.exists(filePath):
		errorMsg = "文件 =" + filePath + "不存在"
		print(errorMsg)
		sys.exit(0)

def checkSystemReturn(res, errorMsg):
	if 0 != res:
		print(errorMsg)
		sys.exit(0)

def printHead():
	print '\033[1;32;40m'
	print '*' * 60
	print '如何创建消息推送的私钥文件，共需要两个文件'
	print 'aps.cer：在苹果开发网站，开通消息推送功能并注册证书、下载'
	print 'aps.p12：下载aps.cer后双击安装，在keychain右键导出'
	print '最后只要将ck.pem交给服务器即可'
	print '*' * 60
	print '\033[0m'

def printExportPassword():
	print '\033[1;32;40m'
	print '*' * 60
	print '请一直输入导出p12文件的密码，需要多次输入'
	print '*' * 60
	print '\033[0m'

def printCheckSuccessInfo():
	print '\033[1;32;40m'
	print '*' * 60
	print '如果显示类似如下信息表示证书生成成功，不用等待返回即可强制关闭终端：'
	print 'CONNECTED(00000003)'
	print 'depth=1 /C=US/O=Entrust, Inc./OU=www.entrust.net/rpa is incorporated by reference/OU=(c) 2009 Entrust, Inc./CN=Entrust Certification Authority - L1C'
	print 'verify error:num=20:unable to get local issuer certificate'
	print 'verify return:0'
	print '.....'
	print '*' * 60
	print '\033[0m'

currentPath = getScriptDirectory()
os.chdir(currentPath)

printHead()
checkFileExist(os.path.join(currentPath, m_cerName))
res = os.system("openssl x509 -in " + m_cerName + " -inform der -out PushCert.pem")
checkSystemReturn(res, "导出PushCert.pem错误")

printExportPassword()
checkFileExist(os.path.join(currentPath, m_keyName))
res = os.system("openssl pkcs12 -nocerts -out PushKey.pem -in " + m_keyName)
checkSystemReturn(res, "导出PushKey.pem错误")

res = os.system("cat PushCert.pem PushKey.pem > ck.pem")
checkSystemReturn(res, "合并PushCert.pem PushKey.pem错误")

printCheckSuccessInfo()
res = os.system("openssl s_client -connect gateway.sandbox.push.apple.com:2195 -cert PushCert.pem -key PushKey.pem")
checkSystemReturn(res, "错误提示：证书不可用，请检查p12证书是否是正确")



