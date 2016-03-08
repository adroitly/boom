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

s_xmlPath = "/AndroidManifest.xml"
s_antPath = "/ant.properties"
s_androidVerionCodeKey = "android:versionCode"
s_androidVerionNameKey = "android:versionName"
s_antVersionNameKey = "app_version="
s_antVersionCodeKey = "app_versionCode="


if len(sys.argv) >= 2 :
	g_projectPath = sys.argv[1]

def findAntFileVersionName():
	return findAntFileVersion(s_antVersionNameKey)

def readXML(xmlPath):
	return minidom.parse(xmlPath)

def writeXMl(xmlConfig, xmlPath):
	f = file(xmlPath,"w")
	xmlConfig.writexml(f)
	f.close()

def findNodes(xmlConfig, key):
	return xmlConfig.getElementsByTagName(key)

def findAntFileVersion(key):
	return AntVersion.getAntFileVersion(g_projectPath, key)
def main():
	xmlConfig = readXML(g_projectPath + s_xmlPath)
	xmlConfigRoot = xmlConfig.documentElement
	verionCode = xmlConfigRoot.getAttribute(s_androidVerionCodeKey)
	verionName = xmlConfigRoot.getAttribute(s_androidVerionNameKey)
	antVersionCode = findAntFileVersion(s_antVersionCodeKey)
	antVersionName = findAntFileVersion(s_antVersionNameKey)
	hasChange = False
	if verionCode != antVersionCode:
		hasChange = True
		xmlConfigRoot.setAttribute(s_androidVerionCodeKey, antVersionCode)
	if verionName != antVersionName:
		hasChange = True
		xmlConfigRoot.setAttribute(s_androidVerionNameKey, antVersionName)
	if hasChange:
		writeXMl(xmlConfig, g_projectPath + s_xmlPath)

if __name__ == "__main__":
	main()