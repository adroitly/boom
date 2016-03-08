#!/usr/bin/python
# -*- coding: utf8 -*-

import os
import sys

KEY		= 'PatGame)^)!'
SIGN 	= '__BIG_DEVIL__'

# 改变路径为绝对路径
def getScriptDirectory():
	path = os.path.abspath(sys.argv[0])
	path = os.path.realpath(path)
	path = os.path.dirname(path)
	return path


def getAbsolutePath(aRelativePath):
	if not aRelativePath.startswith('.'):
		return aRelativePath 

	path = os.path.join(getScriptDirectory(), aRelativePath)
	path = os.path.abspath(path)
	return path


def doEncrypt(aFilePath):
	cmd = [
		getAbsolutePath('./XXTEA'), 
		'-k "' + KEY + '"', 
		'-s "' + SIGN + '"',
		'-f "' + aFilePath + '"', 
	] 
	cmd = ' '.join(cmd)
	os.system(cmd) 


def isLua(aPath):
	(_, ext) = os.path.splitext(aPath);
	return (ext == '.lua');


def searchLua(aFilePath):
	if os.path.isfile(aFilePath) and isLua(aFilePath):
		doEncrypt(aFilePath)
	if os.path.isdir(aFilePath):
		for filename in os.listdir(aFilePath):
			searchLua(os.path.join(aFilePath, filename))


def main(aAppDir):
	searchLua(aAppDir);


main(sys.argv[1])
