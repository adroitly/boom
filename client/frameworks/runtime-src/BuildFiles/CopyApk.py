#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
import FileUtils
import CheckVersion
import ColorPrint

reload(sys)
sys.setdefaultencoding('utf8')
g_projectPath = "/"

s_publishFolder = "../../../publish/"
s_binFolder = "/bin/"

if len(sys.argv) >= 2 :
	g_projectPath = sys.argv[1]

def getProjectName():
	return g_projectPath.split("/")[-1]

def getApkFileName():
	folderPath = FileUtils.getAbsolutePath(g_projectPath + s_binFolder)
	if not os.path.exists(folderPath):
		ColorPrint.errorPrint("没有找到目录" + folderPath)
		return None
	for _file in os.listdir(folderPath):
		if -1 != _file.find("release.apk"):
			return _file
	return None
def createTargetFolder(versionName):
	path = FileUtils.getAbsolutePath(s_publishFolder + versionName)
	FileUtils.createFolder(path)

def renameFile(filePath, versionName):
	projectName = getProjectName()
	targetFolder = getTargetFolderPath(versionName)
	fileName = os.path.join("/", projectName + "_v" + versionName + ".apk")
	ColorPrint.colorPrint("copyTo " + targetFolder + fileName)
	FileUtils.renameFile(filePath, targetFolder + fileName)

def fileAction(apkFileName, versionName):
	apkFilePath = FileUtils.getAbsolutePath(g_projectPath + s_binFolder + apkFileName)
	targetFolder = getTargetFolderPath(versionName)
	targetFile = os.path.join(targetFolder, apkFileName)
	FileUtils.copyFile(apkFilePath, targetFolder + "/" +apkFileName)
	renameFile(targetFile, versionName)

def getTargetFolderPath(versionName):
	return FileUtils.getAbsolutePath(s_publishFolder + versionName)

if __name__ == "__main__":
	versionName = CheckVersion.findAntFileVersionName()
	apkFileName = getApkFileName()
	createTargetFolder(versionName)
	if not apkFileName:
		ColorPrint.errorPrint("没有找到APK文件")
	else:
		fileAction(apkFileName, versionName)
		path = getTargetFolderPath(versionName)
		command = 'open ' + path
		os.system(command)