#include "IncludeMe.h"
#include "VersionConfig.h"
#include "OperateDiskProc.h"

#include "StructOrganize.h"
#include "ServXml_NsrPara.h"
#include "BusinessBase.h"
#include "SerialProtocol.h"
#include "CUniversialSerialCommunicate.h"
#include "YWXMLGY.h"
#include "CGlobalArgLib.h"
#include "commonFunc.h"

#include "ManageBusinessFunc.h"
#include "DeclareBusinessFunc.h"
#include "SaleBusinessFunc.h"
#include "ServXml_InvUpload.h"
#include "InvBusinessFunc.h"
#include "uniAcceptFrameworkApi.h"

#include "LOGCTRL.h"
//#define NO_POS_DEBUG
#include "pos_debug.h"


#define TEST_TEST		0

int main()
{
	DBG_PRINT(("Programe started !!!"));

	CDB *m_db = CDB::GetInstance();
	m_db->Open();
	m_db->Init();
	CommonSleep(300);
	
	UINT8 index;
	for(index = 0; index<DET_ARRAY_LEN; index++)
	{
		s_DetArray[index] = new CInvDet;
		DBG_ASSERT_EXIT((s_DetArray[index] != NULL), (" s_DetArray[index] == NULL!"));
	}

	CBusinessBase::InitBusiness();
	g_globalArgLib = CGlobalArgLib::GetInstance();
	g_globalArgLib->InitGlobalArg();
	g_YwXmlArg = CYWXML_GY::GetInstance();
	g_gNetArg = g_gNetArg->GetInstance();

	INT8 tmpbuf[32];
	memset(tmpbuf, 0, sizeof(tmpbuf));
	sprintf(tmpbuf, "%u", g_globalArgLib->m_corpInfo->m_Kpjhm);
	g_gNetArg->SetBaseInfo(g_globalArgLib->m_corpInfo->m_Nsrsbh, tmpbuf, g_globalArgLib->m_corpInfo->m_Jspsbh);
	g_gNetArg->SetServPara(g_globalArgLib->m_netPara->m_ServIP, g_globalArgLib->m_netPara->m_ServPort,g_globalArgLib->m_netPara->m_ServAddr);
	g_gNetArg->SetZskl(g_globalArgLib->m_strZskl);

	CManageBusinessFunc manFunc;
	g_YwXmlArg->m_jqbh = g_globalArgLib->m_corpInfo->m_jqbh;
	g_YwXmlArg->m_sksbkl = g_globalArgLib->m_strSksbkl;
	manFunc.UpdateUploadInvInfo(*g_YwXmlArg);

	pthread_t threadWrt;   /**< 接收线程 */
	DBG_PRINT(("已初始化，启动次线程前"));
	pthread_create(&threadWrt, NULL, PthreadInvUpLoad, NULL);
	DBG_PRINT(("已初始化，启动次线程后"));

#if TEST_TEST == 0
	
	SerialProtocol *pSerialProtocol = SerialProtocol::getInstance();
	CUniversialSerialCommunicate uniSerCommunicate;
	
	DBG_PRINT(("g_globalArgLib->m_netPara->m_IsDhcp = %u", g_globalArgLib->m_netPara->m_IsDhcp));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalIP = %s", g_globalArgLib->m_netPara->m_LocalIP.c_str()));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalMask = %s", g_globalArgLib->m_netPara->m_LocalMask.c_str()));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalGate = %s", g_globalArgLib->m_netPara->m_LocalGate.c_str()));
	DBG_PRINT(("g_globalArgLib->m_netPara->m_LocalDNS = %s", g_globalArgLib->m_netPara->m_LocalDNS.c_str()));
	uniSerCommunicate.setNetWork(g_globalArgLib->m_netPara->m_IsDhcp, g_globalArgLib->m_netPara->m_LocalIP.c_str(), g_globalArgLib->m_netPara->m_LocalMask.c_str(), g_globalArgLib->m_netPara->m_LocalGate.c_str(), g_globalArgLib->m_netPara->m_LocalDNS.c_str());
	
	DBG_PRINT(("g_globalArgLib->m_serialBaudRate = %u", g_globalArgLib->m_serialBaudRate));
	if (SUCCESS != pSerialProtocol->InitPort(SERIAL_DEVICE, g_globalArgLib->m_serialBaudRate))
	{
		DBG_PRINT(("open serial failed"));
		return 0;
	}
	
	while(1) {
		DBG_PRINT(("serial wait for data 版本号：1.0029 !!!"));
		if (SERCMD_SUCCESS == pSerialProtocol->revData())
		{
			uniSerCommunicate.handleSerialCMD();
		}	
	}

#else

//	g_globalArgLib->m_pthreadFlag = 1;
	g_YwXmlArg->m_sksbkl = "23456789";
//	g_YwXmlArg->m_jqbh = "661505270063";
	g_YwXmlArg->m_jqbh = "661505270127";
	g_YwXmlArg->m_fplxdm = "025";
	g_YwXmlArg->m_nsrsbh = g_globalArgLib->m_corpInfo->m_Nsrsbh;
	g_YwXmlArg->m_kpjh = tmpbuf;
	g_YwXmlArg->m_sksbbh = g_globalArgLib->m_corpInfo->m_Jspsbh;


	string strErr("");
	CSaleBusinessFunc salefunc;
	CInvBusinessFunc invFunc;
	CManageBusinessFunc manFunc;
	CDeclareBusinessFunc decFunc;
	CInvVol invVol;
	CInvHead invHead;
	UINT32 invNum = 0;
	CUserInfo userInfo;
	CInvKind invKind;
	string str1("");

// 	int spnum = 1;
// 	invHead.m_jqbh = g_YwXmlArg->m_jqbh;
//  	invHead.m_zskl = "88888888";
//  	invHead.m_xfsh = g_globalArgLib->m_corpInfo->m_Nsrsbh;
// 	invHead.m_xfmc = g_globalArgLib->m_corpInfo->m_Nsrmc;
//  	invHead.m_fplxdm = g_YwXmlArg->m_fplxdm;
// 	invHead.m_payerCode = "123456789012345";	
// 	invHead.m_fkdw = "个人";
// 	invHead.m_sphsl = spnum;
// 	CInvDet* pInvDet = NULL;
// 	for (int i=0; i<invHead.m_sphsl; i++)
// 	{
// 		pInvDet = pInvDet->GetNewInvDet();	//从静态数组获取一个可用的CInvDet对象
// 		DBG_ASSERT_EXIT((pInvDet != NULL), (" pInvDet == NULL!"));
// 
// 		pInvDet->m_sphxh = i+1;
// 		pInvDet->m_spmc = "测试商品";	
// 		pInvDet->m_dj = 9.71;
// 		pInvDet->m_spsl = 1.0;	
// 		pInvDet->m_je = 971;	
// 		pInvDet->m_sl = 0.03;	
// 		pInvDet->m_spse = 29;
// 		pInvDet->m_spdj = 10;
// 		pInvDet->m_spje = 1000;	
// 		invHead.InsertNode(pInvDet);
// 		pInvDet = NULL;
// 	}
// 	invHead.m_kpje = 971*spnum;	
// 	invHead.m_kpse = 29*spnum;	
// 	invHead.m_kphjje = 1000*spnum;	
// 	invHead.m_backup1 = "1234567890";	
// 	invHead.m_sky = "主管";	
// 	invHead.m_kplx = 0;	
// 	invHead.m_yfpdm = "";	
// 	invHead.m_yfphm = 0;

// 	invHead.m_kplx = 1;
// 	invHead.m_yfpdm = "111000010025";	
// 	invHead.m_yfphm = 40105437;
// 	invHead.m_backup1 = "原正票代码:111000010025,号码:40105437";

// 	invHead.m_fpdm = "111000010025";
// 	invHead.m_fphm = 40105431;
// 	invHead.m_sky = "主管";	

// 	invVol.m_fplxdm = "025";
// 	invVol.m_code = "111000010025";
// 	invVol.m_isno = 20150611;
// 	invVol.m_fpzfs = 10;

// 	invVol.m_isno = 71010001;
// 	invVol.m_fpzfs = 99;

// 	manFunc.GetSksbbh(*g_YwXmlArg, str1, str1, str1, strErr);
// 	manFunc.GetTaxpayerInfo(*g_YwXmlArg, userInfo, strErr, strErr);
// 	manFunc.GetJKSJ(*g_YwXmlArg, invKind, strErr);
// 	invFunc.InvReadIn(*g_YwXmlArg, 2, strErr);
//	invFunc.ZJInvRecover(*g_YwXmlArg, &invVol, 2, strErr);
// 	salefunc.GetCurInvInfo(*g_YwXmlArg, &invVol, strErr);
//	salefunc.MakeNormalInv(*g_YwXmlArg, &invHead, strErr);
//	salefunc.MakeWasteInv(*g_YwXmlArg, &invHead, 1, strErr);
//	salefunc.InvoiceUpload(*g_YwXmlArg, strErr);
	salefunc.GetInvHeadInfo(*g_YwXmlArg, 0, "1110000100253486486334864863", invNum, &invHead, strErr);
//	manFunc.LXXXUpdatePro(*g_YwXmlArg, strErr);
//	decFunc.NetDeclareProc(*g_YwXmlArg, strErr);
//	decFunc.NetUpdateTaxProc(*g_YwXmlArg, strErr);
//	decFunc.DeclareProc(*g_YwXmlArg, 2, strErr);
//	invFunc.WLLQFPPro(*g_YwXmlArg, &invVol, strErr);
//	invFunc.WLLQFPJGQRPro(*g_YwXmlArg, &invVol, strErr);
// 	invFunc.InvReadIn(*g_YwXmlArg, 2, strErr);
// 	salefunc.GetCurInvInfo(*g_YwXmlArg, &invVol, strErr);

	DBG_PRINT(("strErr = %s", strErr.c_str()));

// 	int retval=0;
// 	string techMsg;
// 	techMsg.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
// 	techMsg.append("<tripTechnologyPackage version=\"1.0\">");
// 	techMsg.append("<identity>");
// 	techMsg.append("<applicationId>zzs_fp_cgl_cj</applicationId>");
// 	techMsg.append("<serviceId>jsp_dzdz_cb_zzszp</serviceId>");
// 	techMsg.append("<serviceURI>https://192.168.0.104:8008</serviceURI>");
// 	techMsg.append("<SSL>TA</SSL>");
// 	
// 	techMsg.append("<digigalCertPassword>88888888</digigalCertPassword>");
// 	techMsg.append("<showDigigalCertSelectDialog>FALSE</showDigigalCertSelectDialog>");
// 	techMsg.append("<logEnabled>TRUE</logEnabled>");
// 	techMsg.append("<password>x</password>");
// 	techMsg.append("<nsrsbh>00103434</nsrsbh>");
// 	techMsg.append("<senderName>zyc</senderName>");
// 	techMsg.append("</identity>");
// 	techMsg.append("</tripTechnologyPackage>");
// 	string bizMsg="hello,I am here";
// 	
// 	unsigned char responseBizMsg[2048];
// 	int responseBizMsgLength=sizeof(responseBizMsg);
// 	unsigned char errorMessage[1024];
// 	retval=aisino_ssl_transfer_call("htxx_test",(char*)techMsg.c_str(),
// 		techMsg.size(),(unsigned char*)bizMsg.c_str(),bizMsg.size(),responseBizMsg,&responseBizMsgLength,errorMessage);
// 	
// 	printf("aisino_ssl_transfer_call responseBizMsgLength=%d\n",responseBizMsgLength);
// 	printf("aisino_ssl_transfer_call errorMessage=%s\n",errorMessage);
// 	printf("aisino_ssl_transfer_call retval=%d\n",retval);
// 	if(retval==0) {
// 		string ret;
// 		char* pp=new char[responseBizMsgLength+1];
// 		memcpy(pp,responseBizMsg,responseBizMsgLength);
// 		*(pp+responseBizMsgLength)=0;
// 		ret.assign(pp);
// 		delete []pp;
// 		printf("\n--------------aisino_ssl_transfer_call:-------------\n%s",ret.c_str());
// 		printf("-------------------------------------------------------\n");
// 	}
// 	unsigned char* pOrg=(unsigned char*)"zhuyanchao ";
// 	unsigned char pOutSign[2048];
// 	int cbOutSign=sizeof(pOutSign);
// 	memset(pOutSign,0,sizeof(pOutSign));
// 	retval=aisino_Sign_pkcs7("88888888",pOrg,strlen((char*)pOrg),
// 		pOutSign,&cbOutSign,TRUE,TRUE);
// 	
// 	printf("\n\naisino_Sign_pkcs7 retval=%d,%s\n",retval,pOutSign);
// 	acceptFrameworkCleanup();

	DBG_PRINT(("===================main end====================="));
	DBG_PRINT(("%s", 1));

#endif
}

int main3()
{
	CDB *m_db = CDB::GetInstance();
	m_db->Open();
	m_db->Init();
	CommonSleep(300);
	
	CInvHead tmpInvHead;
	char sqlbuf[128];

	tmpInvHead.m_fpdm = "111000010025";
	tmpInvHead.m_fphm = 40105403;
	memset(sqlbuf, 0, sizeof(sqlbuf));
	sprintf(sqlbuf, "where FPDM='%s' and FPHM=%u", tmpInvHead.m_fpdm.c_str(), tmpInvHead.m_fphm);

	DBG_PRINT(("sqlbuf = %s", sqlbuf));

	tmpInvHead.m_kplx = 4;
	tmpInvHead.m_fpsyh = "12345";
	tmpInvHead.m_casign = "MIIBNgYJKoZIhvcNAQcCoIIBJzCCASMCAQExCzAJBgUrDgMCGgUAMAsGCSqGSIb3DQEHATGCAQIwgf8CAQEwXTBTMQswCQYDVQQGEwJDTjEbMBkGA1UECwwS5Zu95a6256iO5Yqh5oC75bGAMScwJQYDVQQDDB7nqI7liqHnlLXlrZDor4HkuabnrqHnkIbkuK3lv4MCBgEAAAAm0zAJBgUrDgMCGgUAMA0GCSqGSIb3DQEBAQUABIGAbCIOkwJx3UrXinMUDQETSY9gTcicE4Zis78HLJ9jJjw2WzP6C73lD4GGSUx7h+UK0TK54dp2boN5th0f45Mdy9sGfVcIiikt+duPtt+5+Uclq5/DnbG/7hfTUpAgXpRCqTPd0zKGanRJrgFU09kQ0F/8FsjtnKcabT0wb3pt7nM=";
	tmpInvHead.m_backup1 = "20150604122334";
	tmpInvHead.Update(sqlbuf, &tmpInvHead.m_kplx, &tmpInvHead.m_fpsyh, &tmpInvHead.m_backup1, &tmpInvHead.m_casign, NULL);
	
	DBG_PRINT(("here ============== success"));
	DBG_PRINT(("%s", 1));
	return 0;
}

//OperateDisk函数调用测试
int main2()
{
	string sInputInfo;
	string sOutputInfo;

	FILE *fp;
	INT8 tmpBuff[2048];
	
	//读取XML文件至BUFF
	if( (fp = fopen("wlcb.xml", "rb")) == NULL )
	{
		printf("open file error!!!\n");
		return FAILURE;
	}
	fseek( fp, 0L, SEEK_END );	
	int dataLen = ftell( fp );				
	printf("Req filelen: %d\n", dataLen);
	
	fseek( fp, 0L, SEEK_SET );	
	fread( (void *)tmpBuff, dataLen, 1, fp);
	fclose(fp);
	
	sInputInfo = tmpBuff;

	DBG_PRINT((" 1 读入的XML文件sInputInfo: "))
	printf("\n%s\n", sInputInfo.c_str());
	
	OperateDisk(sInputInfo, sOutputInfo);

	DBG_PRINT((" 6 输出的XML文件sOutputInfo: "))
	printf("\n%s\n", sOutputInfo.c_str());
}

//ServXml测试
int main1()
{
	struct NsrInfoData tmpData;
	strcpy(tmpData.nsrdzdah, "X111100000001");
	strcpy(tmpData.nsrmc, "AISINO");
	strcpy(tmpData.nsrsbh, "66667777888");
	strcpy(tmpData.password, "******");
	
	struct NsrInfoData outData;
	
	CStructOrganize test1_origanize;
	CNsrPara Test1Xml((ProtocolOrganize *)&test1_origanize);// = new Test1XML_YW((ProtocolOrganize *)&test1_origanize);
	INT32 ret=0;
	string strErr("");
	
	ret = Test1Xml.CommunicationProc(&tmpData, &outData, strErr);
	DBG_PRINT(("ret = %u", ret));
	DBG_PRINT(("pTest1Xml : %x", &Test1Xml));
	
	if (ret == SUCCESS)
	{
		DBG_PRINT(("nsrdzdah: %s", outData.nsrdzdah))
		DBG_PRINT(("nsrmc: %s", outData.nsrmc))
		DBG_PRINT(("nsrsbh: %s", outData.nsrsbh))
		DBG_PRINT(("password: %s", outData.password))
	}
	else
	{
		DBG_PRINT(("strErr: %s", strErr.c_str()))
	}
	
	
	DBG_PRINT(("main() finish."));
	return 1;
}

