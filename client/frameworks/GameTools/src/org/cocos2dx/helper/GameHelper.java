package org.cocos2dx.helper;

import java.io.ByteArrayOutputStream;
import java.lang.ref.WeakReference;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper.Cocos2dxHelperListener;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Build;
import android.os.Vibrator;
import android.provider.Settings.Secure;

public class GameHelper {

	
	final static int showWeb = 2;
	private static Cocos2dxHelperListener cocos2dxHelperListener;
	public static WeakReference<Activity> mActivity;
	private static Vibrator vibrator = null;

	public static void init(Cocos2dxHelperListener listener, Activity activity) {
		GameHelper.cocos2dxHelperListener = listener;
		vibrator = (Vibrator) activity
				.getSystemService(Service.VIBRATOR_SERVICE);
		GameHelper.mActivity = new WeakReference<Activity>(activity);
		GameHelper.initWX(activity);
	}
	public static void setClipText(final String text)
    {
//        GameHelper.cocos2dxHelperListener.runOnGLThread(new Runnable() {
//
//			@Override
//			public void run() {
//				ClipboardManager clipboard = (ClipboardManager)GameHelper.mActivity.get().getSystemService(Context.CLIPBOARD_SERVICE);
//				clipboard.setText(text);
//			}
//		});
    }


	public static boolean isNetworkConnected(Context context) {
		if (context != null) {

			ConnectivityManager mConnectivityManager = (ConnectivityManager) context
					.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo mNetworkInfo = mConnectivityManager
					.getActiveNetworkInfo();
			if (mNetworkInfo != null) {

				return mNetworkInfo.isAvailable();
			}
		}
		return false;
	}

	public static void GameEnd() {

		GameHelper.cocos2dxHelperListener.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				endGame();
			}
		});
	}

	public static void shake(long milliseconds) {

		// vibrator.vibrate(milliseconds);
	}

	public static void openWeb(final String url) {

		mActivity.get().runOnUiThread(new Runnable() {

			@Override
			public void run() {

				openBrower(url);
			}
		});

	}

	@SuppressLint("NewApi")
	public static String getUUID() {
		String android_id = Secure.getString(GameHelper.mActivity.get()
				.getContentResolver(), Secure.ANDROID_ID);
		return android_id;
	}

//	public static String getMemory() {
//
//		String memory = "";
//		float unused = MemeryInfo.getmem_UNUSED(GameHelper.mActivity.get());
//		float total = MemeryInfo.getmem_TOLAL();
//		memory = (unused / total * 100f) + "";
//		return memory;
//	}

	private static void openBrower(String url) {

		try {
			Intent intent = new Intent();
			intent.setAction("android.intent.action.VIEW");
			Uri content_url = Uri.parse(url);
			intent.setData(content_url);
			GameHelper.mActivity.get().startActivity(intent);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void shareToWx(final String content) {
	}

	private static String getAndroidVersion() {

		Context context = mActivity.get();

		try {
			PackageInfo pi = context.getPackageManager().getPackageInfo(
					context.getPackageName(), 0);

			return pi.versionName;

		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}

		return "-1";
	}
	
	public static String getAndroidPackageName(){
		Context context = mActivity.get();
		return context.getPackageName();
	}

	private static String buildTransaction(final String type) {
		return (type == null) ? String.valueOf(System.currentTimeMillis())
				: type + System.currentTimeMillis();
	}

	private static byte[] bmpToByteArray(final Bitmap bmp,
			final boolean needRecycle) {
		ByteArrayOutputStream output = new ByteArrayOutputStream();
		bmp.compress(CompressFormat.PNG, 100, output);
		if (needRecycle) {
			bmp.recycle();
		}

		byte[] result = output.toByteArray();
		try {
			output.close();
		} catch (Exception e) {
			e.printStackTrace();
		}

		return result;
	}

	private static void initWX(Context context) {
	}

//	public static String getDeviceInfo() {
//
//		String System = Build.VERSION.RELEASE;
//		@SuppressWarnings("deprecation")
//		String sdk = Build.VERSION.SDK;
//		String Model = Build.MODEL;
//		String appVersion = getVersionCode();
//		String platForm = XxWanHelper22.getPlatFormId();
//
//		String info = String.format("系统版本：%s，系统代号：%s, 设备型号：%s，App版本：%s，平台：%s",
//				System, sdk, Model, appVersion, platForm);
//
//		return info;
//	}

	public static void handleLowMemory() {

		GameHelper.cocos2dxHelperListener.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				onLowMemory();
			}
		});
	}


	public static native void pauseGame();

	public static native void resumeGame();

	public static native void endGame();

	public static native void WXresponse(int code);

	public static native int getAlarmTime();

	public static native void onLowMemory();

}
