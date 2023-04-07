#ifndef _DEFINE_H
#define _DEFINE_H

//收发标志
#define SEND	1
#define RECV    2

//字节序
#define BIG_ENDIAN      0
#define LITTLE_ENDIAN   1


#define PROCESS_OK      0
#define PROCESS_ERROR   -1

#ifndef TRUE
#define TRUE  1
#define FALSE 0
typedef int BOOL;
#endif

#ifndef NULL
#define NULL  0
#endif



#ifdef WIN32
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#define SOCKET int
#define closesocket close
#define INVALID_SOCKET -1
#define SOCKET_ERROR (-1)
typedef struct sockaddr SOCKADDR;
#endif


//#define TEST_IN_TESTSERVER


#define MAX_TELE_LEN 2048
#define MAX_REPORT_LENGTH 4096*500
#define SOCKET_MAX_BUFFER_LEN	10*1024


#define Com_Version_1	"V1.10"
#define Com_Version_112	"V1.1.2"

#define UserType_VIP	1//白名单用户
#define UserType_CARD	2//储值卡用户

#define CHARGER_ByteSeq		BIG_ENDIAN
//报文帧格式
#define REPORT_MIN_LEN	6
#define REPORT_HEAD_LEN	3

#define FRAME_START	0x68
#define FRAME_END	0x16

#define HeartTime_Period	15 //15s
#define RealDataTime_Period	5 //5s

//功能码
#define Func_Login_REQ			0x10	//登录请求（充电桩）
#define Func_Login_ACK			0x11	//登录确认（监控平台）
#define Func_Time_Sync			0x20	//校时（监控平台）
#define Func_Time_ACK			0x21	//校时确认（充电桩）
#define Func_PriceMode_Down		0x30	//下发计费模型（监控平台）
#define Func_PriceMode_Ack		0x31	//下发计费模型确认（充电桩）
#define Func_Heart				0x40	//心跳（充电桩）
#define Func_Heart_ACK			0x41	//心跳（监控平台）
#define Func_Card_REQ			0x50	//刷卡鉴权（充电桩）
#define Func_Card_ACK			0x51	//刷卡鉴权确认（监控平台）
#define Func_Charge_REQ			0x60	//充电请求（充电桩）
#define Func_Charge_ACK			0x61	//充电请求确认（监控平台）
#define Func_ChargeRecord		0x70	//上传交易记录（充电桩）
#define Func_ChargeRecord_ACK	0x71	//上传交易记录确认（监控平台）
#define Func_Charge_RealData	0x80	//充电即时信息（充电桩）
#define Func_Charge_BMS			0x81	//BMS信息（充电桩）
#define Func_Alarm				0x82	//告警信息（充电桩）
#define Func_APPStart_REQ		0x90	//远程启动（监控平台）
#define Func_APPStart_ACK		0x91	//远程启动确认（充电桩）
#define Func_APPStop_REQ		0xA0	//远程停止（监控平台）
#define Func_APPStop_ACK		0xA1	//远程停止确认（充电桩）


//充电桩的状态机
#define TimeOut_Five					5//5S
#define StepTimeOut						10//10s
#define LoginTimeOut					15//15s

// timeout 5->15s
//0个桩同时充电请求,还是5个桩在15秒内收不到后台充电请求确认返回. 改成超时时间120秒
#define ChargeReqTimeOut				5//15//5s


#define CurStep_NULL					0//空闲态
#define CurStep_Need_Connect			1//需要连接状态
#define CurStep_SOCKET_INIT_OK			2//SOCKET建立
#define CurStep_Connect_OK				3//TCP连接建立
#define CurStep_Login_Waiting			4//登录请求等待返回
#define CurStep_Login_OK				5//登录成功
#define CurStep_Login_Fail				6//登录失败
#define CurStep_TimeSync_Waiting		7//等待后台校时 15s
#define CurStep_TimeSync_ACK			8//充电桩确认校时
#define CurStep_PriceMode_Waiting		9//等待后台下发计费模型
#define CurStep_PriceMode_ACK			10//确认后台下发计费模型
#define CurStep_LoginFullSuccess		11//登录握手成功  此状态是上诉阶段性成功

#define CurStep_Card_REQ				12//刷卡鉴权请求
#define CurStep_Card_REQ_Waiting		13//刷卡鉴权请求

#define CurStep_Charge_REQ				14//充电请求
#define CurStep_Charge_REQ_Waiting		15//充电请求等待

#define CurStep_Charge_BMS				16//上送BMS
#define CurStep_Charge_BMS_Waiting		17//BMS等待

#define CurStep_Charge_RealData			18//上送即时信息
#define CurStep_Charge_Stop				19//停止充电,上送充电记录



//#登录请求的结果定义
//01允许   02 拒绝
#define LOGIN_ANSWER_PASS	1
#define LOGIN_ANSWER_REJUST	2


//A枪状态	1Byte	BIN码	00-无 01-空闲 02-充电 03-故障 04-待机 05-已排队 06-维护 07-已预约
#define GUN_STATUS_NULL		0
#define GUN_STATUS_FREE		1
#define GUN_STATUS_CHARGING	2
#define GUN_STATUS_ERR		3
#define GUN_STATUS_StandBy	4
#define GUN_STATUS_ONTEAM	5
#define GUN_STATUS_REPAIR	6
#define GUN_STATUS_YY		7

//充电机状态	1Byte	BIN码	01-故障02-待机03-工作
#define CHARGE_STATUS_NULL		0
#define CHARGE_STATUS_ERR		1
#define CHARGE_STATUS_STANDBY	2
#define CHARGE_STATUS_WORK		3




#define MAX_CHARGE_NUM_ONE_WORKTHREAD	30//一个工作线程50个设备


//登录模式
#define LOGIN_MODEL_ALL				0
#define LOGIN_MODEL_ONLY_MONITOR	1

#endif
