#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
import FileUtils
import AntVersion

from xml.dom import minidom

reload(sys)
sys.setdefaultencoding('utf8')

s_antPath = "../proj.android/"
s_versionFilePath = "./version.json"

def loadConfigData(configPathStr):
	configPath = FileUtils.getAbsolutePath(configPathStr)
	if not os.path.exists(configPath):
		print("配置文件不存在")
		return False

	file_object = open(configPath)
	try:
		fileText = file_object.read()
	finally:
		file_object.close()
	jsonDecode = json.loads(fileText)
	return jsonDecode

def main():
	configData = loadConfigData(s_versionFilePath)
	for jsonKey in configData:
		AntVersion.changeAntFileVersion(FileUtils.getAbsolutePath(s_antPath), jsonKey, configData[jsonKey])

if __name__ == '__main__':
	main()