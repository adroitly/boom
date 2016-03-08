#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
reload(sys)
sys.setdefaultencoding('utf8')

def getPath():
	return os.path.split(os.path.realpath(__file__))[0]

def deleteBinFolder():
	binPath = getPath() + "/bin"
	if not os.path.exists(binPath):
		return
	# 防止出错，先创建一个文件进去
	open(binPath + "/a.txt" , "a+")
	shutil.rmtree(binPath)

def colorPrint(text):
	print("\033[1;11;40m")
	print(text)
	print("\033[0m")

def runBuildPython(pythonName):
	colorPrint(pythonName)
	command = "python " + getPath() + "/../../BuildFiles/" + pythonName + ".py " + getPath()
	os.system(command)

def rebuildAssert():
	isRebuild = raw_input("请输入是否重新编译资源工程:默认为(n)").strip()
	if "y" == isRebuild or "Y" == isRebuild:
		colorPrint("ReBuilding.....")
		command = 'cocos compile -p android -s %s -m %s -o %s' % (getPath(), "release", getPath() + "/bin")
		if 0 != os.system(command):
			colorPrint("ReBuild Filed")

def runAntBuild():
	#切换工作目录到当前目录
	os.chdir(getPath())
	os.system("pwd")
	command = "ant buildApk"
	# command = "ant release"
	result = os.system(command)
	if result != 0:
		colorPrint("Build失败")
	else:
		colorPrint("Build成功")

if __name__ == "__main__":
	deleteBinFolder()
	rebuildAssert()
	runBuildPython("UpdateAntVersion")
	runBuildPython("CopyResource")
	runBuildPython("CheckVersion")
	runAntBuild()
	runBuildPython("CopyApk")