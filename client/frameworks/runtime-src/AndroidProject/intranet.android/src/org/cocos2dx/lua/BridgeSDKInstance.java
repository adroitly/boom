package org.cocos2dx.lua;
import java.io.Serializable;
import java.util.Random;

import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;
import org.cocos2dx.helper.BridgeNotification;
import org.cocos2dx.helper.BridgeNotification.BridgeNotificationType;
import org.cocos2dx.helper.ChannelConfig;
/**
 * SDK接口类
 * @author patgame
 *
 */
public class BridgeSDKInstance{
	private static Cocos2dxHelperListener cocos2dxHelperListener;
	private static Activity mActivity;
	private static String userId = null;
	
//	Test
	private static String SaveKey = "BridgeSDK";
	private static int SaveModel = 0;
	private static String UserIdKey = "UserId";
	public static void init(Cocos2dxHelperListener listener, Activity activity)
	{
		cocos2dxHelperListener = listener;
		mActivity = activity;
	}
	
	/**必填，SDK初始化
	 * 成功:BridgeNotification.bridgeCallBack(BridgeNotificationType.InitSDKSuccessful);
	 * 失败:BridgeNotification.bridgeCallBack(BridgeNotificationType.InitSDKFailed);
	 */
	public static void initSDK()
	{
		BridgeNotification.bridgeCallBack(BridgeNotificationType.InitSDKSuccessful);
		userId = getData(UserIdKey, null);
	}
	
	/**
	 * 必填：登录接口
	 * 成功：BridgeNotification.bridgeCallBack(BridgeNotificationType.LoginSuccessful);
	 * 失败：BridgeNotification.bridgeCallBack(BridgeNotificationType.LoginFailed);
	 */
	public static void login()
	{
		BridgeNotification.bridgeCallBack(BridgeNotificationType.LoginSuccessful);
	}
	
	/**
	 * 
     * 必填：登出
     * 成功：BridgeNotification.bridgeCallBack(BridgeNotificationType.LogoutSuccessful);
     * 失败：BridgeNotification.bridgeCallBack(BridgeNotificationType.LogoutFailed);
     */
	public static void logout()
	{
		BridgeNotification.bridgeCallBack(BridgeNotificationType.LogoutSuccessful);
		if (userId != null)
		{
			saveData(UserIdKey, userId);
		}
		userId = null;
	}
	
	/**
	 *
     * 必填：与我们服务器协商渠道信息
	 * @return
	 */
	public static String getChannelName()
	{
		return ChannelConfig.InTranet;
	}
	
	/**
	 * 必填：由合作商sdk登录成功后的用户ID
	 * @return
	 */
	public static String getUserId()
	{
//		测试接口
		if ( null == userId )
		{
			long tempUserId = -1;
			while(tempUserId < 1)
			{
				Random random = new Random(System.currentTimeMillis());
				tempUserId = random.nextLong() % 1000000000;
			}
			userId = String.valueOf(tempUserId);
			
			saveData(UserIdKey, userId);
		}
		return userId;
	}
	
	/**
	 * 必填：由合作商sdk登录成功后的用户名
	 * @return
	 */
	public static String getUserName()
	{
		return "AndroidTest";
	}
	
	 /**
     * 必填：支付接口
     * 成功：BridgeNotification.bridgeCallBack(BridgeNotificationType.PaySuccessful);
     * 失败：BridgeNotification.bridgeCallBack(BridgeNotificationType.PayFailed);
     * 取消：BridgeNotification.bridgeCallBack(BridgeNotificationType.PayCancel);
     */
	public static void pay(BridgeSDKPayData payInfo)
	{
		BridgeNotification.bridgeCallBack(BridgeNotificationType.PaySuccessful);
	}
	
	public static String getAppVersion()
	{
		return "0.2.0";
	}
	
	public static void onResume() {
	}

    public static void onPause() {
    }
    public static void onExit()
    {
    	
    }
    
//	TESTsaveData
    private static void saveData(String key, String value)
    {
		Context ctx = mActivity;
		SharedPreferences sp =ctx.getSharedPreferences(SaveKey, SaveModel);
		Editor editor=sp.edit();
		editor.putString(key, value);
		editor.commit();
    }
    
    private static String getData(String key, String defultValue)
    {
		Context ctx = mActivity;
		SharedPreferences sp =ctx.getSharedPreferences(SaveKey, SaveModel);
        String value = sp.getString(key, defultValue);
        return value;
    }
}
