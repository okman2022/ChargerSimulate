#include "stdafx.h"
#include "ChargeDev.h"
#include "monitor_comapi.h"


//充电设施对象类
ChargeDev::ChargeDev()
{
	need_connect=false;
	need_StartCharge=false;
	need_StopCharge=false;
	isvip_type=true;//默认白名单充电

	my_sock = INVALID_SOCKET;
	//报文缓存区清空初始
	mi_uncode_len=0;
	memset(mi_uncode_tele,0,sizeof(mi_uncode_tele));

	//初始状态是：空闲态
	mi_CurStep=CurStep_NULL;
	last_StepTimeoutNum=0;
	last_Steptime=0;
	last_Hearttime=0;

	My_Comapi_obj=NULL;

	memset(my_devid,0,sizeof(my_devid));
	memset(my_devname,0,sizeof(my_devname));

	memset(&my_chargeinfo,0,sizeof(Charge_Info));
	memset(&my_pricemode,0,sizeof(Charge_PriceMode));
	memset(&my_chargetime,0,sizeof(Charge_Time));
	memset(&my_chargestat,0,sizeof(Charge_Status));
	memset(&my_chargeCard,0,sizeof(Charge_Card));
	memset(&my_ChargeOrder,0,sizeof(Charge_Order));

	my_ChargeOrder.isvip=UserType_VIP;
	strcpy(my_ChargeOrder.vin,VIPCHARGE_TEST_VIN);
	strcpy(my_ChargeOrder.card_no,VIPCHARGE_TEST_CARD);

	 
}

ChargeDev::~ChargeDev()
{
}

int ChargeDev::Reset_ChargeDev()
{	
	return 0;
}

int ChargeDev::initChargeCard(char*card_no,char*passwd)
{
  if(card_no)
	  memcpy(my_chargeCard.card_no,card_no,KEYID_LEN);
  if(passwd)
  	memcpy(my_chargeCard.card_pw,passwd,KEYID_LEN);
	return 0;
}

int ChargeDev::init_ChargeDev(Charge_Info *src_info)
{
	memset(&my_chargeinfo,0,sizeof(Charge_Info));
  if(src_info)
  	memcpy(&my_chargeinfo,src_info,sizeof(Charge_Info));

	strcpy(my_devname,my_chargeinfo.charge_name);
	memcpy(my_devid,my_chargeinfo.charge_id,KEYID_LEN);

	//根据通讯规约版本,构造不同通讯类对象
	if(strcmp(my_chargeinfo.com_version,Com_Version_1)==0)
		My_Comapi_obj=new ComApi();
	else if(strcmp(my_chargeinfo.com_version,Com_Version_112)==0)
		My_Comapi_obj=new CMonitor_Comapi(my_chargeinfo.login_model_val);
	else
		My_Comapi_obj=new ComApi();

	my_chargestat.state_a=GUN_STATUS_FREE;
	my_chargestat.state_b=GUN_STATUS_FREE;
	my_chargestat.state_charge=CHARGE_STATUS_STANDBY;

	//登录模式描述
	memset(login_model_desc,0,sizeof(login_model_desc));
	switch (my_chargeinfo.login_model_val)
	{
	case LOGIN_MODEL_ALL:
		sprintf(login_model_desc,"全业务模式");
		break;
	case LOGIN_MODEL_ONLY_MONITOR:
		sprintf(login_model_desc,"仅监视模式");
		break;
	}

	return 0;
}



