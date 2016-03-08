#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
import FileUtils
import ColorPrint
reload(sys)
sys.setdefaultencoding('utf8')

s_sourcePath = "../proj.android/"

s_configFile = "./copy-config.json"
s_filterFile = "./copy-filter.json"

g_projectPath = "/"

g_filterData = []

s_copyFileKey = "files"
s_copyFolderKey = "folder"
s_isNewKey = "isNew"
s_targetFolderKey = "targetFolder"
s_sourceKey = "source"
s_isFilterKey = "isFilter"

s_filterProjectKey = "filterProject"

s_jsonTrue = "true"
s_jsonFalse = "false"

if len(sys.argv) >= 2 :
	g_projectPath = sys.argv[1]

def loadConfigData(configPathStr):
	configPath = FileUtils.getAbsolutePath(configPathStr)
	if not os.path.exists(configPath):
		ColorPrint.errorPrint("配置文件不存在")
		return False

	file_object = open(configPath)
	try:
		fileText = file_object.read()
	finally:
		file_object.close()
	jsonDecode = json.loads(fileText)
	return jsonDecode

# 检查是否过滤
def isFilterFormConfig(value):
	isFilter = s_jsonFalse
	if value.has_key(s_isFilterKey):
		isFilter = value[s_isFilterKey]
	if s_jsonFalse == isFilter:
		return isFilter

	for _, filteData in enumerate(g_filterData):
		filterProject = filteData[s_filterProjectKey]
		if -1 != filterProject.find(g_projectPath):
			return s_jsonTrue

	return s_jsonFalse

def getFileTargetFolder(value):
	if value.has_key(s_targetFolderKey):
		return "/" + value[s_targetFolderKey]
	return "/"

def getFolderTargetFolder(value):
	if value.has_key(s_targetFolderKey):
		return "/" + value[s_targetFolderKey]
	return "/" + value[s_sourceKey]

def isNewFromConfig(value):
	if value.has_key(s_isNewKey):
		return value[s_isNewKey]
	return s_jsonFalse

def copyFiles(configData):
	if False == configData.has_key(s_copyFileKey):
		ColorPrint.errorPrint("没有定义复制文件")
		return
	copyFilesConfig = configData[s_copyFileKey]
	for _, value in enumerate(copyFilesConfig):
		targetFolder = getFileTargetFolder(value)
		source = value[s_sourceKey]
		isNew = isNewFromConfig(value)
		isFilter = isFilterFormConfig(value)

		if s_jsonTrue == isFilter:
			continue

		if not os.path.exists(g_projectPath + targetFolder):
			FileUtils.newFolder(g_projectPath + targetFolder)

		if s_jsonTrue == isNew:
			FileUtils.deleteFile(g_projectPath + targetFolder + source)
			FileUtils.copyFile(s_sourcePath + source , g_projectPath + targetFolder + source)
			ColorPrint.colorPrint("Copy " + s_sourcePath + source)

		elif not os.path.isfile(g_projectPath + targetFolder + source):
			FileUtils.copyFile(s_sourcePath + source , g_projectPath + targetFolder + source)
			ColorPrint.colorPrint("Copy " + s_sourcePath + source)


def copyFolder(configData):
	if False == configData.has_key(s_copyFolderKey):
		ColorPrint.errorPrint("没有定义复制文件夹")
		return
	copyFolderData = configData[s_copyFolderKey]
	for _, value in enumerate(copyFolderData):
		targetFolder = getFolderTargetFolder(value)
		source = value[s_sourceKey]
		isNew = isNewFromConfig(value)
		isFilter = isFilterFormConfig(value)

		if s_jsonTrue == isFilter:
			continue

		if s_jsonTrue == isNew:
			FileUtils.newFolder(g_projectPath + targetFolder)
			ColorPrint.errorPrint("NewFolder " + g_projectPath + targetFolder)

		ColorPrint.colorPrint("Copy " + s_sourcePath + source)
		FileUtils.copyFolder(s_sourcePath + source, g_projectPath + targetFolder)

if __name__ == "__main__":
	configData = loadConfigData(s_configFile)
	g_filterData = loadConfigData(s_filterFile)
	copyFolder(configData)
	copyFiles(configData)
