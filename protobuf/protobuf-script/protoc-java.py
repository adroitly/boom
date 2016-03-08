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

def protoJAVA(name):
	os.chdir(protocal_path)
	cmd = "protoc " + name + " --java_out" + "=../protobuf-java"
	res = os.system(cmd)
	if 0!=res:
		value = "Compile " + name + " Failed"
		print(value)
		sys.exit(0)

def copyJAVA(name):
	os.chdir(protocal_path)
	os.popen("rm -R /Users/jiujiu/Desktop/three/three-message/src/com/protobuf", 'r');
	os.popen("cp -R ../protobuf-java/com/protobuf /Users/jiujiu/Desktop/three/three-message/src/com/protobuf", 'r');

os.popen("rm -R /Users/jiujiu/Desktop/works/protobuf/protobuf-java/com", 'r');

for name in all_proto_list:
	print name;
	protoJAVA(name);
	copyJAVA(name);




print "Compile Successful"



