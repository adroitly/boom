<?php

/*
    * 描述：测试消息推送功能（该功能只在developer环境有效，发布环境无效）
    * 配置1 deviceToken：消息推送token，需要从真机打印出来（去掉中间空格）
    * 配置2 pass：p12的密码

    * 运行命名：php 路径名/push-notification-test.php
*/ 

//手机注册应用返回唯一的deviceToken
// $deviceToken = '837e5226 42930513 101e46dd 28c7d919 878feca5 16cc997e d975c5ff 661dc198';
$deviceToken = '43d83291 80f3daaf 18b04c9d cc176592 ff56ac59 c0845dac 6b929f62 a7a27d7b';

//ck.pem通关密码
$pass = '123456';   
//消息内容
$message = '这是一条跨时代具有历史意义的推送';
//badge我也不知是什么
$badge = 4;
//sound我也不知是什么（或许是推送消息到手机时的提示音）
$sound = 'default';
//建设的通知有效载荷（即通知包含的一些信息）
$body = array();
$body['aps'] = array('alert' => $message);
//把数组数据转换为json数据
$payload = json_encode($body);
echo strlen($payload),"\r\n";

//下边的写法就是死写法了，一般不需要修改，
//唯一要修改的就是：ssl://gateway.sandbox.push.apple.com:2195这个是沙盒测试地址，ssl://gateway.push.apple.com:2195正式发布地址
$ctx = stream_context_create();
$pem = dirname(__FILE__) .'/'.'ck.pem';
stream_context_set_option($ctx, 'ssl', 'local_cert', $pem);  
stream_context_set_option($ctx, 'ssl', 'passphrase', $pass);
$fp = stream_socket_client('tls://gateway.sandbox.push.apple.com:2195',$err,$errstr, 60, STREAM_CLIENT_CONNECT|STREAM_CLIENT_PERSISTENT, $ctx);
if (!$fp) {
    print "Failed to connect $err $errstr\n";
    return;
}
else {
   print "Connection OK\n<br/>";
}
// send message
$msg = chr(0) . pack("n",32) . pack('H*', str_replace(' ', '', $deviceToken)) . pack("n",strlen($payload)) . $payload;
print "Sending message :" . $payload . "\n";  
fwrite($fp, $msg);
fclose($fp);
/*
35 Connection OK 
Sending message :{"aps":{"alert":"A test message!"}} 
*/
    
?>
