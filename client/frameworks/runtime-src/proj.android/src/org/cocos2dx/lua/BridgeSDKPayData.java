package org.cocos2dx.lua;
/**
 * 支付信息类，无需改动，若有需要改动请协调
 * @author patgame
 *
 */
public class BridgeSDKPayData {
	private float  price;      // 产品价格
	private String productId;  // 付费产品ID
	private String userId;     // 用户ID
	private String userName;   // 用户名
	private String serverId;   // 区服ID
	public float getPrice() {
		return this.price;
	}
	public String getProductId() {
		return this.productId;
	}
	public String getUserId() {
		return this.userId;
	}
	public String getUserName() {
		return this.userName;
	}
	public String getServerId() {
		return this.serverId;
	}
	private BridgeSDKPayData(float  price, String productId, String userId, String userName, String serverId) 
	{
		// TODO Auto-generated constructor stub
		this.price = price;
		this.productId = productId;
		this.userId = userId;
		this.userName = userName;
		this.serverId = serverId;
	}
	private static void pay(        
			String priceStr,      // 产品价格
			String productId,  // 付费产品ID
			String userId,     // 用户ID
			String userName,   // 用户名
			String serverId   // 区服ID
    )
	{
		float price = Float.parseFloat(priceStr); 
		BridgeSDKPayData payInfo = new BridgeSDKPayData(price, productId, userId, userName, serverId);
		BridgeSDKInstance.pay(payInfo);
	}
}
