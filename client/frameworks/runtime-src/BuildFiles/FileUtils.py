#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
reload(sys)
sys.setdefaultencoding('utf8')

def getScriptDirectory():
	return os.path.dirname(os.path.realpath(__file__))

def getAbsolutePath(relativePath):
	if not relativePath.startswith("."):
		return relativePath 
	path = os.path.join(getScriptDirectory(), relativePath)
	path = os.path.abspath(path)
	return path

def writeFile(filepath , text):
    fp = open(filepath , "wb");
    fp.write(text);
    fp.close();

def deleteFile(path):
	absolutePath = getAbsolutePath(path)
	if os.path.isfile(absolutePath):
		os.remove(absolutePath)

# 删除文件夹
def deleteFoler(path):
	absolutePath = getAbsolutePath(path)
	if not os.path.exists(absolutePath):
		return
	# 防止出错，先创建一个文件进去
	open(absolutePath + "/a.txt" , "a+")
	shutil.rmtree(absolutePath)

def newFolder(path):
	deleteFoler(path)
	absolutePath = getAbsolutePath(path)
	os.makedirs(absolutePath)

def createFolder(path):
	absolutePath = getAbsolutePath(path)
	if not os.path.exists(absolutePath):
		os.makedirs(absolutePath)

def copyFile(source, target):
	sourceAbsolutePath = getAbsolutePath(source)
	targetAbsoluterPath = getAbsolutePath(target)
	if os.path.isfile(sourceAbsolutePath):
		open(targetAbsoluterPath, "wb").write(open(sourceAbsolutePath, "rb").read())

def renameFile(source, target):
	if not os.path.exists(source):
		return
	os.rename(source, target)

def copyFolder(sourceFolder, targetFolder):
	sourceAbsolutePath = getAbsolutePath(sourceFolder)
	targetAbsoluterPath = getAbsolutePath(targetFolder)
	for _file in os.listdir(sourceAbsolutePath):
		source = os.path.join(sourceAbsolutePath, _file)
		target = os.path.join(targetAbsoluterPath, _file)
		if os.path.isfile(source):
			if not os.path.exists(targetAbsoluterPath):
				os.makedirs(targetAbsoluterPath)
			copyFile(source, target) 
		else:
			copyFolder(source, target)
