#ifndef EXTERN_H
#define EXTERN_H

#include "define.h"
#include "WorkThread.h"
#include "mystruct.h"

extern CWorker *g_pWorker;
extern int g_workthread_num;

//��ǰ���̵����г��׮�豸
extern Charge_Info *g_ChargeDevs;
extern int g_ChargeDev_num;

extern Charge_Houtai g_ChargeHoutai;

extern int login_timeout_num;
extern int chargeReq_timeout_num;
#endif 
