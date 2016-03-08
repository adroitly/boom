package org.cocos2dx.helper;


import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
/**
 * 添加推送
 * @author patgame
 *
 */
public class PushNotification {
	private static Activity context;
	private static Class className;
	//通知栏
	private static NotificationManager manager;
	//通知栏ID
	private static int notificationID = 0;
	/**
	 * 初始化
	 * @param activity
	 * @param _class
	 */
	public static void init(Activity activity, Class _class)
	{
		context = activity;
		className = _class;
		manager = (NotificationManager)activity.getSystemService(Context.NOTIFICATION_SERVICE);
	}
	
	/**
	 * 
	 * @param icon
	 * @param logTitle
	 * @param title
	 * @param content
	 */
	public static void pushNotification(int icon, String logTitle, String title, String content)
	{
        //构建一个通知对象(需要传递的参数有三个,分别是图标,标题和 时间)
        Notification notification = new Notification(icon,logTitle,System.currentTimeMillis());
        Intent intent = new Intent(context, className);
        PendingIntent pendingIntent = PendingIntent.getActivity(context,0,intent,0);
        notification.setLatestEventInfo(context, title, content, pendingIntent);  
        notification.flags = Notification.FLAG_AUTO_CANCEL;//点击后自动消失
        manager.notify(notificationID, notification);//发动通知,id由自己指定，每一个Notification对应的唯一标志
	}

}
