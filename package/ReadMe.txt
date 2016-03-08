* 出新包前
    1.更新SVN代码
    2.删除FileInfo，Upload，UploadBackup文件夹
    3.执行package.py脚本
    4.上传SVN代码
    5.再出新包

* 热更新流程
    1. 更新SVN代码
    2. 执行package.py脚本
    3. 上传SVN代码


* 各文件作用说明
package.py：打包有改动的文件并上传到服务器
config.json：打包的配置文件，参数描述如下
    "package_path": "Upload/innet",                             -- 打包路径，Upload/Name。Name：值为内网、外网、安卓、苹果等等渠道，需要配置到脚本，用于热更新下载
    "zip_url": "http://ipas.fzxgame.cn/three/config/innet/",    -- 下载包的地址（高能提醒：请确保后缀路径，如innet与package_path后缀路径是一致的）
    "targets": ["../client/res", "../client/src"],              -- 打包的路径
    "key": "PatGame)^)!",                                       -- 脚本加密key
    "sign": "__BIG_DEVIL__",                                    -- 脚本加密sign
    "upload_script": "UploadTools/run.sh"                       -- 上传包工具位置


