package org.cocos2dx.helper;

import java.text.BreakIterator;

import android.util.Log;
/**
 * SDK调用C++接口类
 * @author patgame
 *
 */
public class BridgeNotification {
	public enum BridgeNotificationType {
		InitSDKSuccessful(1), 
		InitSDKFailed(2), 
		LoginSuccessful(3), 
		LoginFailed(4), 
		LogoutSuccessful(5), 
		LogoutFailed(6),
		PaySuccessful(7), 
		PayFailed(8),
		PayCancel(9);

		private final int value;

		BridgeNotificationType(int value) {
			this.value = value;
		}
		public int getValue() {

			return this.value;
		}
	}
	/**
	 * 外部调用
	 * @param bridgeNotificationType
	 */
	public static void bridgeCallBack(BridgeNotificationType bridgeNotificationType)
	{
		bridgeNotificationCallBack(bridgeNotificationType.getValue());
	}
	/**
	 * 返回到C++调用
	 * @param bridgeNotificationType
	 */
	private native static void bridgeNotificationCallBack(int bridgeNotificationType);

}
