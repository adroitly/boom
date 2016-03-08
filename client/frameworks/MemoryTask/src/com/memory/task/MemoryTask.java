package com.memory.task;

import android.content.Context;
import android.os.AsyncTask;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

public class MemoryTask extends AsyncTask<Void, Object, Void> {
	
	
	private int second = 10000;
	private float percent = 0.1f; 
	
	private FrameLayout layout;
	private Context context;
	private MemoryListener listener;
	
	private TextView tips;

	
	public MemoryTask(Context context, FrameLayout layout, MemoryListener listener) {
		this.context = context;
		this.layout = layout;
		this.listener = listener;
		this.init();
	}
	
	private void init(){
		
		tips = new TextView(this.context);
		final ViewGroup.LayoutParams layout_params =
	            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,
	                                       ViewGroup.LayoutParams.WRAP_CONTENT);
		tips.setLayoutParams(layout_params);
		layout.addView(tips);
		tips.setText("asdasd");
	}

	public void showTip(boolean isShow){

		int visible = isShow? View.VISIBLE : View.GONE;
		tips.setVisibility(visible);
	}
	
	/**
	 *  percent ÷µ∑∂Œß 1-100
	 **/
	public void setMemoryWarning(int percent){
		
		this.percent = percent * 0.01f;
	}
	
	/**
	 *  second µ•Œª √Î
	 **/
	public void setRefresh(int second){
		
		this.second = second * 1000;
	}
	
	@Override
	protected void onProgressUpdate(Object... values) {
		super.onProgressUpdate(values);
//		long unused = Long.valueOf(values[0]+"");
//		long total =Long.valueOf(values[1]+"");
		float percent = Float.valueOf(values[2]+"");

		if (percent <= this.percent){
			listener.notifyLowMemory();
		}
		String tipStr = String.format("%.2f%s", percent,"%");
		tips.setText(tipStr);
	}

	@Override
	protected Void doInBackground(Void... params) {

		while (!isCancelled()) {
			try {
				long unused = MemeryInfo.getmem_UNUSED(this.context);
				long total = MemeryInfo.getmem_TOLAL();
				float persent = unused *1f/ total;
				publishProgress(unused,total,persent);
				Thread.sleep(second);
			} catch (InterruptedException e) {
				e.printStackTrace();
				return null;
			}
		}
		return null;
	}


}
