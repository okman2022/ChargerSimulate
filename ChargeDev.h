#ifndef CHARGEDEV_H
#define CHARGEDEV_H

#define TEMP_BUF_LEN 4096*100 
#include "comapi.h"


#define WRITE_TIME_OUT 50000
#define MAX_TIMEOUTNUM	3

class ChargeDev  
{
public:
	ChargeDev();
	virtual ~ChargeDev();

public:
	int init_ChargeDev(Charge_Info *src_info);
	int init_ChargeCard(char*card_no,char*passwd);

	int Reset_ChargeDev();
	int packet_log(int flag,char*name,const char *t, int len);
	
	int Send_Data(CBufferAccess &ba_all,char*desc);
	int  SocketSendData(SOCKET newFd,const char *buf,int len);
	bool selectWriteNet(SOCKET sFd,long WriteTimeout);


	int Send_Login();
	int Recv_LoginAck(char*buf,int len);
	int Recv_TimeSync(char*buf,int len);
	int Send_TimeAck();
	int Send_PriceModeAck();
	int Send_Heart();
	int Send_CardREQ();
	int Send_ChargeREQ();
	int Recv_ChargeAck(char*buf,int len);
	int Send_BMS();
	int Recv_BMSAck(char*buf,int len);
	int Send_ChargeRealData();
	int Send_ChargeRecord();
	

private:

public:
	char my_devname[128];
	char my_devid[KEYID_LEN+1];
	char login_model_desc[32];

	ComApi* My_Comapi_obj;
	
	SOCKET my_sock; 	       //连接套接字
	//该设备的接收报文缓存
	int mi_uncode_len;
	char mi_uncode_tele[TEMP_BUF_LEN];

	Charge_Info	my_chargeinfo;
	Charge_PriceMode my_pricemode;
	Charge_Time my_chargetime;
	Charge_Status my_chargestat;
	Charge_Card my_chargeCard;
	Charge_Order my_ChargeOrder;//当前充电订单

	//状态机
	int mi_CurStep;
	int last_Steptime;
	int last_StepTimeoutNum;
	
	int last_Hearttime;
	int last_RealDataTime;

	bool need_connect;//需要开始通讯
	bool isvip_type;//白名单充电
	bool need_StartCharge;//需要开始充电
	bool need_StopCharge;//需要停止充电

};
#endif
