#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
import FileUtils

from xml.dom import minidom

reload(sys)
sys.setdefaultencoding('utf8')

s_antPath = "/ant.properties"
s_wirteAction = "write"
s_getAction = "get"


def getAntFileVersion(path, key):
	return antFileAction(path, key, s_getAction)

def changeAntFileVersion(path, key, value):
	antFileAction(path, key, s_wirteAction, str(value))

def antFileAction(path, key, action, value = "1"):
	antFile = path + s_antPath
	fp = open(antFile, "r")
	str = fp.read()
	fp.close()
	#查找的位置
	findKeyIndex = str.find(key)
	#没有找到，直接退出
	if findKeyIndex == -1:
		print antFile,"Not Found",key
		return
	index = len(key)
	#取到开始的字符
	lastText = str[0 : findKeyIndex + index]
	#取到之后的字符
	nextText = str[findKeyIndex + index: ]
	#查找下一个回车
	nexiIndex = nextText.find("\n")
	#分割下个字符串
	if -1 == nexiIndex:
		nexiIndex = len(nextText)
	#剩下的就是version
	findValue = nextText[0 : nexiIndex]
	if action == s_getAction:
		return findValue
	elif action == s_wirteAction:
		valueNextText = nextText[nexiIndex: ]
		text = lastText + "=" + value + valueNextText
        FileUtils.writeFile(antFile , text)