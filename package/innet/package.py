#!/usr/bin/python
# -*- coding: utf8 -*-

import os 
import shutil
import sys 
import json
import xml.etree.ElementTree as ET
from hashlib import md5
import zipfile

# utils
kVersionListFileName 	= "version-list.json"
kPackageSuffix 			= ".zip"

# header
def printHead():
	print '\033[1;32;40m'

	print '*' * 60
	print '配置表的参数 :'
	print '*targets : 需要打包的目标资源，数组形式表示'
	print '*key : Lua文件加密的Key'
	print '*sign : Lua文件加密的Sign'
	print '*zip_url : ZIP的下载地址'
	print '*' * 60

	print '*注意 :'
	print '*目标资源里的所有文件不能带有中文'
	print '*文件路径可以填写相对于配置文件的路径'
	print '*加密算法使用的是XXTEA'
	print '*' * 60

	print '\033[0m'

def tips(text, isErrorTips):
	if isErrorTips:
		print '\033[1;31;40m'
	else:
		print '\033[1;32;40m'
	print '*' * 60
	print(text)
	print '*' * 60
	print '\033[0m'

def getScriptDirectory():
	return os.path.dirname(os.path.realpath(__file__)) 

def getFileInfoDir():
	path = getScriptDirectory()
	return os.path.join(path, "FileInfo")

def setUploadDir(path):
	assert(path)
	scriptPath = getScriptDirectory()
	global g_uploadDir
	g_uploadDir = os.path.join(scriptPath, path)

def getUploadDir():
	global g_uploadDir
	return g_uploadDir

def getFileInfoPath():
	dirPath = getFileInfoDir()
	return os.path.join(dirPath, "file-md5.xml")

def getFileInfoOriginPath():
	return getFileInfoPath() + ".origin" 

def getVersionListPath():
	dirPath = getUploadDir()
	return os.path.join(dirPath, kVersionListFileName) 

def getResourceDir():
	return os.path.join(getUploadDir(), 'Resources')

def getUploadBackupDir():
	return os.path.join(getScriptDirectory(), "UploadBackup")

def removeResourceDir():
	resourceDir = getResourceDir()
	if os.path.exists(resourceDir):
		shutil.rmtree(resourceDir)

def getZipName(version):
	return version + kPackageSuffix

def getZipFilePath(version):
	zipName = getZipName(version)
	zipDir = getUploadDir()
	return os.path.join(zipDir, zipName)

def getAbsolutePathWithTarget(aRelativePath, aTargetDir):
	if not aRelativePath.startswith('.'):
		return aRelativePath 

	path = os.path.join(aTargetDir, aRelativePath)
	path = os.path.abspath(path)
	return path

def getAbsolutePath(aRelativePath):
	return getAbsolutePathWithTarget(aRelativePath, getScriptDirectory()) 

def createTmpResource(resourcePath):
	if os.path.exists(resourcePath):
		shutil.rmtree(resourcePath) 
	os.makedirs(resourcePath) 

def createDir(dirPath):
	if os.path.exists(dirPath):
		return
	os.makedirs(dirPath)

def letNeedDirExist():
	createDir(getFileInfoDir())
	createDir(getUploadDir())
	createTmpResource(getResourceDir()) 
	createDir(getUploadBackupDir())

def readJsonData(path):
	if not os.path.exists(path):
		return None 
	fileData = file(path).read() 
	return json.JSONDecoder().decode(fileData)  

def writeJsonData(path, data):
	jsonFile = open(path, 'w+') 
	jsonFile.write(json.dumps(data, indent=4))
	jsonFile.close() 

# input 
def getConfigPath():
	scriptDir = getScriptDirectory()
	configPath = os.path.join(scriptDir, "config.json")
	if not os.path.exists(configPath):
		print("config.json文件不存在")
		sys.exit(0)
	return configPath

# Config 
def readConfigData():
	filePath = getConfigPath()
	dirPath = os.path.dirname(filePath) 
	configData = readJsonData(filePath)
	for i in range(0, len(configData['targets'])):
		configData['targets'][i] = getAbsolutePathWithTarget(configData['targets'][i], dirPath) 
	return configData 

# MD5 
def getFileMd5(filePath):
    m = md5()
    targetFile = open(filePath, 'rb')    #需要使用二进制格式读取文件内容
    m.update(targetFile.read())
    targetFile.close()
    return m.hexdigest()


# FileInfo 
def getLastFileInfos(path):
	tree = ET.ElementTree()
	if os.path.exists(path):
		tree.parse(path)
	return tree.getroot() 

def hasFile(root, rootPath, md5): 
	if root == None: 
		return False 

	rootPath = '_' + rootPath.replace('/', '/_') #由于xml的tag必须字符开头，所以加一个_在文件名前头
	target = '{rootPath}[@md5="{md5}"]'.format(rootPath=rootPath, md5=md5) 
	return (root.find(target) != None)

def indentXML(elem, level = 0):
    i = '\n' + level*'  '
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + '  '
        for e in elem:
            indentXML(e, level+1)
        if not e.tail or not e.tail.strip():
            e.tail = i
    if level and (not elem.tail or not elem.tail.strip()):
        elem.tail = i
    return elem

def walkFileForXML(filePath, root):
	name = os.path.basename(filePath) 
	if name.startswith('.'):
		return 

	tag = '_' + name #由于xml的tag必须字符开头，所以加一个_在文件名前头
	if os.path.isfile(filePath):
		filemd5 = getFileMd5(filePath) 
		ET.SubElement(root, tag, attrib={'md5':filemd5}) 
		return 

	if len(os.listdir(filePath)) == 0:
		return 

	root = ET.SubElement(root, tag)
	for filename in os.listdir(filePath):
		walkFileForXML(os.path.join(filePath, filename), root) 

def refreshNewFileInfos(targets, path, version):
	if os.path.exists(path):
		backupInfo = path + ".backup" 
		shutil.copy(path, backupInfo)

	root = ET.Element('Resources', attrib={'Version':version}) 
	for target in targets:
		walkFileForXML(target, root) 
	tree = ET.ElementTree(root) 
	indentXML(root) 
	tree.write(path) 

	originFile = getFileInfoOriginPath() 
	if not os.path.exists(originFile):
		shutil.copy(path, originFile) 


# Encrypt 
def encryptLua(filePath, key, sign):
	cmd = [
		getAbsolutePath('./XXTEA'), 
		'-k "' + key + '"', 
		'-s "' + sign + '"',
		'-f "' + filePath + '"', 
	] 
	cmd = ' '.join(cmd)
	os.system(cmd)
		 

def doEncrypt(filePath, key, sign):
	if os.path.isfile(filePath):
		if filePath.endswith('.lua'):
			encryptLua(filePath, key, sign)
		return 

	for filename in os.listdir(filePath):
		doEncrypt(os.path.join(filePath, filename), key, sign) 


# Temp Resource
def mkdir(dirPath):
	if os.path.exists(dirPath):
		return 
	lastDirPath = os.path.dirname(dirPath) 
	mkdir(lastDirPath) 
	os.mkdir(dirPath) 

def copyFile(originFile, targetFile): 
	if not os.path.exists(originFile):
		return 
	mkdir(os.path.dirname(targetFile)) 
	shutil.copy(originFile, targetFile) 

def copyModifyFile(resourcePath, targetPath, rootPath, fileInfos):
	name = os.path.basename(targetPath) 
	if name.startswith('.'):
		return 

	rootPath = os.path.join(rootPath, name)
	if os.path.isfile(targetPath):
		filemd5 = getFileMd5(targetPath) 
		if not hasFile(fileInfos, rootPath, filemd5):
			targetFile = os.path.join(resourcePath, rootPath) 
			copyFile(targetPath, targetFile)
		return 

	for filename in os.listdir(targetPath):
		copyModifyFile(resourcePath, os.path.join(targetPath, filename), rootPath, fileInfos)


def copyTargets(resourcePath, targets, fileInfos): 
	for filePath in targets:
		copyModifyFile(resourcePath, filePath, '', fileInfos)  

# Zip 
def zipFile(zfile, path, root):
	name = os.path.basename(path) 
	arcname = os.path.join(root, name) 

	if os.path.isfile(path):
		zfile.write(path, arcname) 
		return 

	for filename in os.listdir(path):
		zipFile(zfile, os.path.join(path, filename), arcname) 

def doZip(resourcePath, zipFilePath):
	if len(os.listdir(resourcePath)) == 0:
		tips('所有文件未发生变化，不需要打包', False)
		return True

	zfile = zipfile.ZipFile(zipFilePath, 'w', compression=zipfile.ZIP_DEFLATED)
	zipFile(zfile, resourcePath, '') 
	zfile.close() 
	return False

# next Version
def getNextVersion(version):
	vs = version.split('.') 
	num = str(int(vs[1]) + 1)
	return vs[0] + '.' + num 

def isForFullPackage(version):
	vs = version.split('.') 
	return (int(vs[1]) == 0 and vs[0] != '1')

def getVersion(fileInfos):
	if fileInfos == None:
		version = '1.0'
	else:
		version = getNextVersion(fileInfos.get('Version'))
	tmpInput = raw_input('请输入版本号（不输入为{version}）：'.format(version=version)).strip()
	if len(tmpInput) > 0:
		version = tmpInput
	return version 

# VersionList
def getVersionDetail(version):
	vs = version.split('.') 
	vs[0] = int(vs[0])
	vs[1] = int(vs[1])
	return vs 

def cmpVersion(v1, v2):
	vs1 = getVersionDetail(v1['version'])
	vs2 = getVersionDetail(v2['version']) 
	if vs1[0] == vs2[0]:
		return vs1[1] - vs2[1]
	return vs1[0] - vs2[0]


def refreshVersionList(path, version, url, needReload, packageSizeKB):
	needRemove = isForFullPackage(version) 
	versionList = readJsonData(path) 
	if versionList == None:
		versionList = [] 

	zipName = getZipName(version)
	url = os.path.join(url, zipName) 
	hasVersion = False 
	for v in versionList:
		if v['version'] == version:
			v['url'] = url
			v['reload'] = needReload
			v['remove'] = needRemove 
			v['size_kb'] = packageSizeKB
			hasVersion = True 
			break 

	if not hasVersion:
		versionList.append({
			'version': version,
			'url': url,
			'reload': needReload, 
			'remove': needRemove,
			'size_kb' : packageSizeKB
		})

	versionList.sort(cmpVersion)
	writeJsonData(path, versionList) 

def getNeedReload():
	return True
	# needReload = raw_input('需要重新加载游戏？(y/n)(默认y)：').strip()
	# return not (len(needReload) > 0 and (needReload == 'n' or needReload == 'N'))

def backupZipFile(zipFilePath, version):
	targetPath = os.path.join(getUploadBackupDir(), getZipName(version))  
	shutil.copy(zipFilePath, targetPath)

# upload 
def uploadToLocal(resourcePath, versionListPath, version):
	targetDir = '/Library/WebServer/Documents/game_package'
	zipName = getZipName(version)
	targetResource = os.path.join(targetDir, zipName)  
	shutil.copy(resourcePath, targetResource)

	targetList = os.path.join(targetDir, kVersionListFileName)
	shutil.copy(versionListPath, targetList) 

def fileInfoWithSpanVersion(inputVersion, oldFileInfo):
	if isForFullPackage(inputVersion):
		return getLastFileInfos(getFileInfoOriginPath())
	return oldFileInfo

def uploadToServer(uploadScript):
	if not uploadScript:
		tips("未配置上传脚本", True)
		system.exit(0)

	uploadScriptPath = os.path.join(getScriptDirectory(), uploadScript)	
	if not os.path.exists(uploadScriptPath):
		tips("上传脚本不存在，请查看config.json参数upload_script是否配置正确", True)
		system.exit(0)

	res = os.system(uploadScriptPath)
	if res != 0:
		tips("上传包失败，请检查上传脚本", True)
		system.exit(0)

def deleteOriginZipFile():
	zipFilePath = getZipFilePath("1.0")
	if os.path.exists(zipFilePath):
		os.remove(zipFilePath)

# __init__ 
def main():
	configData = readConfigData()
	setUploadDir(configData["package_path"])

	# 删除临时文件
	removeResourceDir()

	# 前置
	printHead()
	letNeedDirExist()

	# 获取是否修改文件FileInfo
	fileInfos = getLastFileInfos(getFileInfoPath()) 

	# 获取版本
	version = getVersion(fileInfos) 

	# 跨版本，使用原始的FileInfo
	fileInfos = fileInfoWithSpanVersion(version, fileInfos)
	
	# 拷贝目标资源到临时目录
	resourceDir = getResourceDir()
	copyTargets(resourceDir, configData['targets'], fileInfos) 

	# Lua脚本加密
	doEncrypt(resourceDir, configData['key'], configData['sign'])  

	# 压缩临时文件
	zipFilePath = getZipFilePath(version)
	res = doZip(resourceDir, zipFilePath)
	if res:
		removeResourceDir()
		return

	# 更新version-list
	packageSize = os.path.getsize(zipFilePath)
	refreshVersionList(getVersionListPath(), version, configData['zip_url'], getNeedReload(), packageSize/1024)

	# 打包成功
	tips('打包成功！当前版本：' + version, False)

	# 备份压缩包到UploadBackup文件夹
	backupZipFile(zipFilePath, version)

	# 删除临时文件
	removeResourceDir()

	# 上传包到本地
	# uploadToLocal(zipFilePath, getVersionListPath(), version)

	# 1.0版本的包不用上传
	deleteOriginZipFile()

	# 上传包到服务器
	tips("开始上传资源包到服务器", False)
	uploadToServer(configData['upload_script'])
	tips("上传资源包到服务器结束", False)
	
	# 更新FileInfo
	refreshNewFileInfos(configData['targets'], getFileInfoPath(), version)

	# 删除包
	os.remove(zipFilePath)

main()