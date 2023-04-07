#include "stdafx.h"
#include "chargersimulate.h"
#include <QtWidgets/QApplication>
/*#include "comapi.h"*/
#include "extern.h"

#include <WINSOCK2.H>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")


CWorker *g_pWorker=NULL;
int g_workthread_num=0;

Charge_Info *g_ChargeDevs=NULL;
int g_ChargeDev_num=0;

Charge_Houtai g_ChargeHoutai;
int login_timeout_num=0;
int chargeReq_timeout_num=0;

int main(int argc, char *argv[])
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息

	QApplication a(argc, argv);

	ChargerSimulate w;
	w.show();
	return a.exec();
}
