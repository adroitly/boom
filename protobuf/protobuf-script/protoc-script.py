#!/usr/bin/python

import FileUtils
import os
import sys

protocal_path = FileUtils.getAbsolutePath("../protobuf-datas")

all_proto_list = []
for parent, dirnames, filenames in os.walk(protocal_path):
	for filename in filenames:
		finalname = filename
		prefix = os.path.relpath(parent, protocal_path)
		if prefix != '.':
			finalname = os.path.join(prefix, filename)
		_, ext = os.path.splitext(finalname)
		if ext == ".proto":
			all_proto_list.append(finalname)

def protoPB(name):
	target_name, _ = os.path.splitext(name)
	target_name = target_name + ".pb"

	protocal_pb_path = FileUtils.getAbsolutePath("../../client/res/protocol")
	target_name = protocal_pb_path + "/" + target_name

	dirname = target_name.rsplit("/", 1)[0]
	FileUtils.createDirIfNeed(dirname)

	cmd = "protoc " + name + " -o " + target_name
	res = os.system(cmd)
	if 0!=res:
		value = "Compile " + name + " Failed"
		print(value)
		sys.exit(0) 

def protoJAVA(name):
	os.chdir(protocal_path)
	cmd = "protoc " + name + " --java_out" + "=../protobuf-java"
	res = os.system(cmd)
	if 0!=res:
		value = "Compile " + name + " Failed"
		print(value)
		sys.exit(0)


os.chdir(protocal_path)
res = os.system("svn update")
if 0!=res:
	print("svn update error!!!")
	sys.exit(0) 

for name in all_proto_list:
	protoPB(name)
	# protoJAVA(name)


print "Compile Successful"



