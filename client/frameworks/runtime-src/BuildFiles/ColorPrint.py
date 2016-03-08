#!/usr/bin/python
#coding:utf-8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

def colorPrint(text):
	print("\033[1;11;40m")
	print(text)
	print("\033[0m")

def errorPrint(text):
	print("\033[1;31;40m")
	print(text)
	print("\033[0m")