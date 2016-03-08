package org.cocos2dx.helper;

import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;

public class Platform {
	private static Activity s_activity;
	private static String appVersion;
	public static void init(Activity activity)
	{
		s_activity = activity;
		appVersion = getVersion();
		System.out.println("appVersion = " + appVersion);
	}
	public static void openUrl(String url)
	{
		
	}
	public static void registerRemoteNotification()
	{
		
	}
	public static String getAppVersion()
	{
	   return appVersion;
	}
	/**
	 * 获取版本号
	 * @return 当前应用的版本号
	 */
	private static String getVersion()
	{
		try {
		        PackageManager manager = s_activity.getPackageManager();
		        PackageInfo info = manager.getPackageInfo(s_activity.getPackageName(), 0);
		        String version = info.versionName;
		        return version;
		    } catch (Exception e) {
		        e.printStackTrace();
		        return "0.0.0";
		    }
	}
}
