#!/usr/bin/python
# -*- coding: utf8 -*-

import os
import re
import sys
import shutil
import json 
from hashlib import md5 

# 路径
def getScriptDirectory():
	path = os.path.abspath(sys.argv[0])
	path = os.path.realpath(path)
	path = os.path.dirname(path)
	return path

def getAbsolutePath(aRelativePath):
	if not aRelativePath.startswith("."):
		return aRelativePath 

	path = os.path.join(getScriptDirectory(), aRelativePath)
	path = os.path.abspath(path)
	return path

# 小函数
def isEndsWithList(aFilename, aEndList):
	for tmp in aEndList:
		if aFilename.endswith(tmp):
			return True
	return False

# 文件操作
def getFileMd5(aFile):
	tmpFile = open(aFile, 'rb')
	md5Obj = md5()
	md5Obj.update(tmpFile.read())
	tmpFile.close()
	return md5Obj.hexdigest() 


def createDirIfNeed(aDirPath):
	if not os.path.exists(aDirPath):
		os.mkdir(aDirPath)


def listdirIgnoreHideFile(aFile):
	if not os.path.exists(aFile):
		return

	resultList = []
	for tmpFile in os.listdir(aFile):
		if not tmpFile.startswith('.'):
			resultList.append(tmpFile)

	return resultList


# 复制文件
def copyFiles(aSourceDir, aTargetDir, aEndList):
	aSourceDir = getAbsolutePath(aSourceDir)
	aTargetDir = getAbsolutePath(aTargetDir)
	createDirIfNeed(aTargetDir)

	for filename in os.listdir(aSourceDir):
		if not isEndsWithList(filename, aEndList):
			continue
		sourceFile = os.path.join(aSourceDir, filename)
		targetFile = os.path.join(aTargetDir, filename)
		shutil.copy(sourceFile, targetFile)


def copyFileIfNeed(aSourcePath, aTargetPath):
	if not os.path.isfile(aSourcePath):
		return 

	if os.path.exists(aTargetPath):
		sourceMd5 = getFileMd5(aSourcePath)
		targetMd5 = getFileMd5(aTargetPath)
		if sourceMd5 == targetMd5:
			return 
	
	shutil.copy(aSourcePath, aTargetPath)


# 删除文件
def removeFile(aFilePath):
	if not os.path.exists(aFilePath):
		return 

	if os.path.isfile(aFilePath):
		os.remove(aFilePath)
		return 

	for tmpFile in listdirIgnoreHideFile(aFilePath):
		removeFile(os.path.join(aFilePath, tmpFile))

	os.rmdir(aFilePath)
