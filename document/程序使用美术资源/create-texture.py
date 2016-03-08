#!/usr/bin/python
#coding:utf-8
import json
import os
import os.path
import sys
import shutil
import FileUtils

reload(sys)
sys.setdefaultencoding('utf8')

s_configFile = "./create-texture-config.json"
s_rePath = "../../client/res/ui/"
s_packerPath = "./TexturePacker.app/Contents/MacOS/TexturePacker"
s_plistFormat = "cocos2d"
s_maxWidth = "2048"
s_maxHeight = "2048"
# 自由尺寸（是否输出2的N次幂）
s_isAllowFreeSize = True

# CopyTempDir

s_tempFolderPath = "./temp/"

kConfigDataMerge = "merge"
kConfigDataCopy	= "copy"
kConfigDefaultFormay = "default_pixel_format"

# 程序流程
# newFolder,
# readLanguage
# readConfig
# copySourceToTempFolder
# copyLangageSourceToTempFolder
# ActionInTempFolder
# deleteFoler


def getScriptDirectory():
	return os.path.dirname(os.path.realpath(__file__))

def getAbsolutePath(relativePath):
	if not relativePath.startswith("."):
		return relativePath 
	path = os.path.join(getScriptDirectory(), relativePath)
	path = os.path.abspath(path)
	return path

def loadConfigData(configPathStr):
	configPath = getAbsolutePath(configPathStr)
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

def colorPrint(text):
	print("\033[1;11;40m")
	print(text)
	print("\033[0m")

def copyFile(source, target):
	sourceAbsolutePath = getAbsolutePath(source)
	targetAbsoluterPath = getAbsolutePath(target)
	if os.path.isfile(sourceAbsolutePath):
		open(targetAbsoluterPath, "wb").write(open(sourceAbsolutePath, "rb").read())

#递归copyFolder
def copyFolder(sourceFolder, targetFolder):
	sourceAbsolutePath = getAbsolutePath(sourceFolder)
	targetAbsoluterPath = getAbsolutePath(targetFolder)
	
	if False == os.path.exists(sourceAbsolutePath):
		return
	if False == os.path.exists(targetAbsoluterPath):
		newFolder(targetAbsoluterPath)

	for _file in os.listdir(sourceAbsolutePath):
		source = os.path.join(sourceAbsolutePath, _file)
		target = os.path.join(targetAbsoluterPath, _file)
		if os.path.isfile(source):
			if not os.path.exists(targetAbsoluterPath):
				os.makedirs(targetAbsoluterPath)
			copyFile(source, target) 
		else:
			copyFolder(source, target)

# 遍历文件夹下的文件
def copyFiles(sourcePath,  targetPath):
	sourceAbsolutePath = getAbsolutePath(sourcePath)
	targetAbsolutePath = getAbsolutePath(targetPath)
	if False == os.path.exists(sourceAbsolutePath):
		return
	if False == os.path.exists(targetAbsolutePath):
		newFolder(targetAbsolutePath)
		
	for _file in os.listdir(sourceAbsolutePath): 
		sourceFile = os.path.join(sourceAbsolutePath,  _file)
		targetFile = os.path.join(targetAbsolutePath,  _file)
		copyFile(sourceFile, targetFile)

def sendPackerFile(sourcePath, targetFolder, format):
	targetPath = s_rePath + targetFolder
	targetAbsolutePath = getAbsolutePath(targetPath)
	sourceAbsolutePath = getAbsolutePath(sourcePath)
	fileName = targetFolder
	# 获取文件名
	if targetFolder.find("/") != -1:
		index = targetFolder.rindex("/") + 1
		fileName = targetFolder[index : ]
	# 文件名的替换
	pngName = targetAbsolutePath + "/" + fileName + ".png"
	plistName = targetAbsolutePath + "/" + fileName + ".plist"
	texturePackerPath = getAbsolutePath(s_packerPath)

	command = "".join([texturePackerPath, " ", sourceAbsolutePath, \
		" --sheet ", pngName, " --data ", plistName, \
		" --format ", s_plistFormat, \
		" --max-width ", s_maxWidth, " --max-height ", s_maxHeight, \
		" --opt ", format \
		])
	if s_isAllowFreeSize:
		command = "".join([command, " --allow-free-size"])
	result = os.system(command)
	if result != 0:
		print("创建" + pngName + "失败")
		colorPrint("失败文件夹在" + sourceAbsolutePath)
		exit()
	else:
		print("创建" + pngName + "成功")


def getFormat(value, defultFormat):
	if value.has_key("pixel_format"):
		return value["pixel_format"]
	return defultFormat

def mergeFolder(tempSourcePath, targetFolder, format):
	sourceAbsolutePath = getAbsolutePath(tempSourcePath)
	if False == os.path.exists(sourceAbsolutePath):
		return
	for _file in os.listdir(sourceAbsolutePath):
		source = os.path.join(sourceAbsolutePath, _file)
		target = os.path.join(targetFolder, _file)
		if os.path.isdir(source):
			sendPackerFile(source, target, format)

def checkSendPackerFiles(tempSourcePath, targetFolder, format):
	if tempSourcePath[len(tempSourcePath) - 1] == "/":
		mergeFolder(tempSourcePath, targetFolder, format)
	else:
		sendPackerFile(tempSourcePath, targetFolder, format)

def checkCopyFiles(sourcePath, targetSourcePath):
	lastChar = sourcePath[len(sourcePath) - 1]
	if lastChar == "/":
		copyFolder(sourcePath,targetSourcePath)
	else:
		copyFiles(sourcePath,targetSourcePath)

def mergeActionByConfig(configData):
	colorPrint("从临时文件夹打包大图中")
	mergeData = configData[kConfigDataMerge]
	defultFormat = configData[kConfigDefaultFormay]
	for _, value in enumerate(mergeData):
		sourceFolder = value["source"]
		targetFolder = value["rename"]
		tempSourcePath = s_tempFolderPath + sourceFolder
		format = getFormat(value, defultFormat)
		checkSendPackerFiles(tempSourcePath, targetFolder, format)

def copyActionByConfig(config):
	colorPrint("从临时文件夹拷贝到目标文件夹中")
	copyData = configData[kConfigDataCopy]
	for _, value in enumerate(copyData):
		sourceFolder = value["source"]
		targetFolder = value["rename"]
		targetPath = s_rePath + targetFolder
		tempSourcePath = s_tempFolderPath + sourceFolder
		checkCopyFiles(tempSourcePath, targetPath)
		print("拷贝文件夹到 " + getAbsolutePath(targetPath) + " 成功")
	

def fixPngWarning():
	path = FileUtils.getAbsolutePath(s_rePath)
	os.chdir(path)
	os.system("find . -type f -name \"*.png\" -exec convert {} -strip {} \;")

def copySourceFiles(prefixStr, configData):
	for _, value in enumerate(configData):
		sourceFolder = value["source"]
		sourcePath = prefixStr + sourceFolder
		tempSourcePath = getAbsolutePath(s_tempFolderPath + sourceFolder)
		if False == os.path.exists(tempSourcePath):
			newFolder(tempSourcePath)
		checkCopyFiles(sourcePath, tempSourcePath)
		if os.path.exists(getAbsolutePath(sourcePath)):
			print("拷贝" + getAbsolutePath(sourcePath))

def copySourceToTempFolder(configData):
	colorPrint("拷贝资源文件到临时目录")
	copyData = configData[kConfigDataCopy]
	mergeData = configData[kConfigDataMerge]
	copySourceFiles("./", copyData)
	copySourceFiles("./", mergeData)

def copyLangageSourceToTempFolder(configData, language):
	colorPrint("拷贝语言文件到临时目录")
	copyData = configData[kConfigDataCopy]
	mergeData = configData[kConfigDataMerge]
	languagePath = "./" + language + "/"
	copySourceFiles(languagePath, copyData)
	copySourceFiles(languagePath, mergeData)

# 语言
def getLanguagePath():
	allLanguage = [
					"ch",
				]
	if len(allLanguage) == 1:
		return allLanguage[0]
	print("\n可以输入的语言有:")
	print(allLanguage)
	languageStr = raw_input('请输入配置文件语言(回车表示ch)：').strip()
	languageStr = languageStr.rstrip()
	language = languageStr.lstrip()
	if 0 == len(language):
		language = "ch"
	# 中文，英文，繁体
	# Traditional Chinese
	if allLanguage.index(language) < 0:
		print("ErrorLanguage = " + language)
		exit()

	return language


if __name__ == "__main__":
	colorPrint("创建临时文件夹")
	newFolder(s_tempFolderPath)
	
	language = getLanguagePath()

	configData = loadConfigData(s_configFile)

	copySourceToTempFolder(configData)
	copyLangageSourceToTempFolder(configData,language)

	mergeActionByConfig(configData)
	copyActionByConfig(configData)

	colorPrint("删除临时文件夹")
	deleteFoler(s_tempFolderPath)
	fixPngWarning() 

