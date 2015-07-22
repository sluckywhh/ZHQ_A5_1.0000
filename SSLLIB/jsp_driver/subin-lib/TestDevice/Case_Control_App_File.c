#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "Case_Control_App_File.h"

 
//#define DEVAPI	 __stdcall
//#define ADMIN_TYPE	0
//#define USER_TYPE	1

#include "GMCAPI.h"
#include "GMCAPI_EXT.h"
#include "GMCErr.h"

//#define NULL	0 
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

typedef struct  
{
	int id;
	char error[64];
}ErrorInfo;



ErrorInfo errorInfo[]=
{ 
	
	{ SAR_OK,/*0x00000000*/"成功"},
	{ SAR_FAIL,/*0x0A000001*/"失败"},
	{ SAR_UNKNOWNERR,/*0x0A000002*/"异常错误"},
	{ SAR_NOTSUPPORTYETERR,/*0x0A000003*/"不支持的服务"},
	{ SAR_FILEERR,/*0x0A000004*/"文件操作错误"},
	{ SAR_INVALIDHANDLEERR,/*0x0A000005*/"无效的句柄"},
	{ SAR_INVALIDPARAMERR,/*0x0A000006*/"无效的参数"},
	{ SAR_READFILEERR,/*0x0A000007*/"读文件错误"},
	{ SAR_WRITEFILEERR,/*0x0A000008*/"写文件错误"},
	{ SAR_NAMELENERR,/*0x0A000009*/"名称长度错误"},
	{ SAR_KEYUSAGEERR,/*0x0A00000A*/"密钥用途错误"},
	{ SAR_MODULUSLENERR,/*0x0A00000B*/"模的长度错误"},
	{ SAR_NOTINITIALIZEERR,/*0x0A00000C*/"未初始化"},
	{ SAR_OBJERR,/*0x0A00000D*/"对象错误"},
	{ SAR_MEMORYERR,/*0x0A00000E*/"内存错误"},
	{ SAR_TIMEOUTERR,/*0x0A00000F*/"超时"},
	{ SAR_INDATALENERR,/*0x0A000010*/"输入数据长度错误"},
	{ SAR_INDATAERR,/*0x0A000011*/"输入数据错误"},
	{ SAR_GENRANDERR,/*0x0A000012*/"生成随机数错误"},
	{ SAR_HASHOBJERR,/*0x0A000013*/"HASH对象错"},
	{ SAR_HASHERR,/*0x0A000014*/"HASH运算错误"},
	{ SAR_GENRSAKEYERR,/*0x0A000015*/"产生RSA密钥错"},
	{ SAR_RSAMODULUSLENERR,/*0x0A000016*/"RSA密钥模长错误"},
	{ SAR_CSPIMPRTPUBKEYERR,/*0x0A000017*/"CSP服务导入公钥错误"},
	{ SAR_RSAENCERR,/*0x0A000018*/"RSA加密错误"},
	{ SAR_RSADECERR,/*0x0A000019*/"RSA解密错误"},
	{ SAR_HASHNOTEQUALERR,/*0x0A00001A*/"HASH值不相等"},
	{ SAR_KEYNOTFOUNTERR,/*0x0A00001B*/"密钥未发现"},
	{ SAR_CERTNOTFOUNTERR,/*0x0A00001C*/"证书未发现"},
	{ SAR_NOTEXPORTERR,/*0x0A00001D*/"对象未导出"},
	{ SAR_DECRYPTPADERR,/*0x0A00001E*/"解密时做补丁错误"},
	{ SAR_MACLENERR,/*0x0A00001F*/"MAC长度错误"},
	{ SAR_BUFFER_TOO_SMALL,/*0x0A000020*/"缓冲区不足"},
	{ SAR_KEYINFOTYPEERR,/*0x0A000021*/"密钥类型错误"},
	{ SAR_NOT_EVENTERR,/*0x0A000022*/"无事件错误"},
	{ SAR_DEVICE_REMOVED,/*0x0A000023*/"设备已移除"},
	{ SAR_PIN_INCORRECT,/*0x0A000024*/"PIN不正确"},
	{ SAR_PIN_LOCKED,/*0x0A000025*/"PIN被锁死"},
	{ SAR_PIN_INVALID,/*0x0A000026*/"PIN无效"},
	{ SAR_PIN_LEN_RANGE,/*0x0A000027*/"PIN长度错误"},
	{ SAR_USER_ALREADY_LOGGED_IN,/*0x0A000028*/"用户已经登录"},
	{ SAR_USER_PIN_NOT_INITIALIZED,/*0x0A000029*/"没有初始化用户口令"},
	{ SAR_USER_TYPE_INVALID,/*0x0A00002A*/"PIN类型错误"},
	{ SAR_APPLICATION_NAME_INVALID,/*0x0A00002B*/"应用名称无效"},
	{ SAR_APPLICATION_EXISTS,/*0x0A00002C*/"应用已经存在"},
	{ SAR_USER_NOT_LOGGED_IN,/*0x0A00002D*/"用户没有登录"},
	{ SAR_APPLICATION_NOT_EXISTS,/*0x0A00002E*/"应用不存在"},
	{ SAR_FILE_ALREADY_EXIST,/*0x0A00002F*/"文件已经存在"},
	{ SAR_NO_ROOM,/*0x0A000030*/"空间不足"},
	{ SAR_FILE_NOT_EXIST,/*0x0A000031*/"文件不存在"},
	{ SAR_REACH_MAX_CONTAINER_COUNT,/*0x0A000032*/"已达到最大可管理容器数"}
};

#define DEVAPI  __stdcall
//#define DEVAPI

/*================================================================================
 *=================================DLL导入初始化==================================
 *===============================================================================*/
void Init()
{
}

void Init_Key()
{
/* 	DEVHANDLE hDev;
	DEVINFO DevInfo;
	FormatKeyParam pFkParam;	
	char *pLabel = "USBKEY"; 	
	char szDeviceName[100] = {0};
	unsigned int ulDeviceNameLen = 100;
	unsigned long lResult;
	int i;	

	memset(szDeviceName,0,100);
	ulDeviceNameLen = 100;
	printf("SKF_EnumDev Start!\n");
	lResult = SKF_EnumDev(1,szDeviceName,&ulDeviceNameLen);
	if(lResult!=0) {
		printf("SKF_EnumDev Error:%02x\n",lResult);
	}
	printf("SKF_ConnectDev Start!\n");	
	lResult = SKF_ConnectDev(szDeviceName,&hDev);
	if(lResult!=0) {
		printf("SKF_ConnectDev Error:%02x\n",lResult);
	}

	pFkParam.VersionMajor = 1;
	pFkParam.VersionMinor = 0;
	pFkParam.ulAuthAlgID = SGD_SM1_ECB;
	pFkParam.ulDevAuthKeyLen = 16;
	for(i=0;i<8;i++)
	{
		pFkParam.pbDevAuthKey[i] = 0x31 + i;
		pFkParam.pbDevAuthKey[8+i] = 0x31 + i;	
	}
	memset(pFkParam.pbDevLabel,0,sizeof(pFkParam.pbDevLabel));
	memcpy(pFkParam.pbDevLabel,pLabel,strlen(pLabel));
	pFkParam.bSupportRootCert= 1;
	pFkParam.byCertStoreType = 1;
	pFkParam.byFileStoreType = 1;
	lResult = SKFI_FormatKey(hDev,&pFkParam);
	if(lResult!=0) {
		printf("SKFI_FormatKey Error:%02x\n",lResult);
	}

	lResult = SKF_GetDevInfo(hDev,&DevInfo);
	if(lResult!=0) {
		printf("SKF_GetDevInfo Error:%02x\n",lResult);
	}

	lResult = SKF_DisConnectDev(hDev);
	if(lResult!=0) {
		printf("SKF_DisConnectDev Error:%02x\n",lResult);
	}
*/
}


ULONG _OpenDev(DEVHANDLE *phDev)
{
	ULONG result =0;
	CHAR *pBuffer = NULL;
	ULONG pulSize = 0;

	//枚举设备
	if ((result = SKF_EnumDev(TRUE,NULL,&pulSize)) != SAR_OK)
	{
		printf("SKF_EnumDev 1 ERROR:%s\n",errorInfo[result&0xff].error);
		return result;
	}

	pBuffer = (CHAR *)malloc(pulSize);
	if (!pBuffer)
	{
		return !SAR_OK;
	}

	memset(pBuffer,0,pulSize);
	if ((result = SKF_EnumDev(TRUE,pBuffer,&pulSize)) != SAR_OK)
	{
		printf("SKF_EnumDev 2 ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	//取第一个设备名称
	if(strlen((const char *)pBuffer)==0)
	{ 
		printf("没有发现设备\n");
		goto _ERRRET;
	}


	//打开设备
	if((result = SKF_ConnectDev(pBuffer,phDev))!=SAR_OK)
	{ 
		printf("SKF_ConnectDev   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}
 
	free(pBuffer);
	return SAR_OK;

_ERRRET:
	free(pBuffer);
	return result;
}


void _CloseDev(DEVHANDLE hDev)
{
	ULONG result =0;
	if((result = SKF_DisConnectDev(hDev))!=SAR_OK)
	{ 
		printf("SKF_ConnectDev   ERROR:%s\n",errorInfo[result&0xff].error);
	}
}

ULONG _DevAuth(DEVHANDLE hDev)
{
	DEVINFO hDevInfo;
	BYTE key[20] = {0};
	HANDLE  hKey;
	BLOCKCIPHERPARAM BlockParam;
	
	BYTE Random[8] = {0};
	ULONG RandomLen;
	BYTE paintData[32] = {0};
	ULONG paintDataLen;
	BYTE cryptData[128] = {0};
	ULONG cryptDataLen;
	ULONG result =0;
	
	/*
	 *根据 设备认证使用的分组密码算法标识 选择算法 然后加密随机数 最后认证
	 */

	//1.获取设备信息
	if ((result = SKF_GetDevInfo(hDev, &hDevInfo)) != SAR_OK)
	{
		printf("SKF_GetDevInfo   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//2.明文导入会话密钥
	printf("请输入16字节设备认证密钥:");
	scanf("%s", key);			//初始化密钥为1234567812345678
	if ((result = SKF_SetSymmKey(hDev, key, hDevInfo.DevAuthAlgId, &hKey)) != SAR_OK)
	{
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//3.取随机数
	RandomLen = 8;
	if ((result = SKF_GenRandom(hDev, Random, RandomLen)) != SAR_OK)
	{ 
		printf("SKF_GenRandom   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//4.单组密码初始化
	memset(&BlockParam, 0, sizeof(BLOCKCIPHERPARAM));
	if ((result = SKF_EncryptInit(hKey, BlockParam)) != SAR_OK)
	{ 
		printf("SKF_EncryptInit   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//5.单组密码加密
	memcpy(paintData, Random, 8);
	paintDataLen = 16;
	if ((result = SKF_Encrypt(hKey, paintData, paintDataLen, cryptData, &cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_Encrypt   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//6.认证
	if((result = SKF_DevAuth(hDev, cryptData, cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_DevAuth   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	return SAR_OK;
}

ULONG _OpenAPP_WithAUTH(DEVHANDLE *pDEV, HAPPLICATION* pAPP)
{
	ULONG result;
	char appName[36] = {0};

	if(_OpenDev(pDEV) != SAR_OK)
	{
		return !SAR_OK;
	}
	
	if(_DevAuth(*pDEV) != SAR_OK)
	{
		_CloseDev(*pDEV);
		return !SAR_OK;
	}
	
	printf("请输入要打开的应用名称:");
	scanf("%s", appName);
	
	result = SKF_OpenApplication(*pDEV, appName, pAPP);
	if (result != SAR_OK)
	{
		printf("SKF_OpenApplication  ERROR:%s\n", errorInfo[result&0xff].error);
		_CloseDev(*pDEV);
		return !SAR_OK;
	}

	return SAR_OK;
}

ULONG _OpenAPP_WithoutAUTH(DEVHANDLE *pDEV, HAPPLICATION* pAPP)
{
	ULONG result;
	char appName[36] = {0};
	
	if(_OpenDev(pDEV) != SAR_OK)
	{
		return !SAR_OK;
	}
	
	printf("请输入要打开的应用名称:");
	scanf("%s", appName);
	
	result = SKF_OpenApplication(*pDEV, appName, pAPP);
	if (result != SAR_OK)
	{
		printf("SKF_OpenApplication  ERROR:%s\n", errorInfo[result&0xff].error);
		_CloseDev(*pDEV);
		return !SAR_OK;
	}
	
	return SAR_OK;
}

ULONG _CheckPin(HAPPLICATION hAPP)
{
	ULONG result;
	ULONG remainretrycount;
	ULONG pintype;
	char arrPIN[10] = {0};

	printf("输入8字节PIN码:");
	scanf("%s", arrPIN);

_RETRYPIN:
	printf("\n输入PIN码类型(0--admin;1--user):");
	scanf("%d", &pintype);
	if (ADMIN_TYPE != pintype && USER_TYPE != pintype)
	{
		printf("输入类型不正确!");
		goto _RETRYPIN;
	}

	if ((result = SKF_VerifyPIN(hAPP, pintype, arrPIN, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_VerifyPIN  ERROR:%s  剩余重试次数=%d \n", errorInfo[result&0xff].error,remainretrycount);		
		return !SAR_OK;
	}

	return SAR_OK;
}

void _CloseAPP(HAPPLICATION hApp)
{
	ULONG result =0;
	if ((result = SKF_CloseApplication(hApp)) != SAR_OK)
	{
		printf("SKF_CloseApplication   ERROR:%s\n",errorInfo[result&0xff].error);
	}
}

void _CloseContain(HCONTAINER hCont)
{
	ULONG result =0;
	if ((result = SKF_CloseContainer(hCont)) != SAR_OK)
	{
		printf("SKF_CloseContainer   ERROR:%s\n",errorInfo[result&0xff].error);
	}
}

//访问控制系列
void Test_SKF_DevAuth()
{
	char *pDesc = "必须通过设备认证后才能在设备内创建和删除应用。\n"	\
	"设备认证使用分组密码算法和设备认证密钥进行。认证的流程如下：\n"	\
	"1)被认证方调用SKF_GenRandom函数从设备获取8字节随机数RND，并用0x00将其填充至密码算法的分块长度，组成数据块D0；\n"	\
	"2)被认证方对D0加密，得到加密结果D1，并调用SKF_DevAuth()，将D1发送至设备；\n"	\
	"3)设备收到D1后，验证D1是否正确。正确则通过设备认证，否则设备认证失败。\n";

	DEVHANDLE hDev;
	DEVINFO hDevInfo;
	BYTE key[16] = {0};
	HANDLE  hKey;
	BLOCKCIPHERPARAM BlockParam;

	BYTE Random[8] = {0};
	ULONG RandomLen;
	BYTE paintData[32] = {0};
	ULONG paintDataLen;
	BYTE cryptData[128] = {0};
	ULONG cryptDataLen;
	ULONG result =0;

	printf(pDesc);
	printf("=========================================\n");

	if(_OpenDev(&hDev) != SAR_OK)
	{
		return;
	}

	//获取设备信息
	if ((result = SKF_GetDevInfo(hDev, &hDevInfo)) != SAR_OK)
	{
		printf("SKF_GetDevInfo   ERROR:%s\n",errorInfo[result&0xff].error);
		_CloseDev(hDev);
		return ;
	}

	//根据 设备认证使用的分组密码算法标识 选择算法
	//明文导入会话密钥 
	//memset(key, 0, 16);
	//memcpy(key, "1234567812345678", 16);	//初始化密钥
	printf(" 请输入设备认证密钥(16字节):");
	scanf("%s", key);
	printf("\n");
	if ((result = SKF_SetSymmKey(hDev, key, hDevInfo.DevAuthAlgId, &hKey)) != SAR_OK)
	{ 
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		_CloseDev(hDev);
		return ;
	}
	
	//单组密码填充
	memset(&BlockParam, 0, sizeof(BLOCKCIPHERPARAM));
	//BlockParam.IV[MAX_IV_LEN];
	//BlockParam.IVLen = 8;
	//BlockParam.PaddingType = 0;
	//BlockParam.FeedBitLen = 0;
	RandomLen = 8;
	if ((result = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("SKF_GenRandom   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	memcpy(paintData, Random, 8);

	//单组密码初始化
	if ((result = SKF_EncryptInit(hKey, BlockParam)) != SAR_OK)
	{ 
		printf("SKF_EncryptInit   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	//单组密码加密
	paintDataLen = 16;
	if ((result = SKF_Encrypt(hKey, paintData, paintDataLen, cryptData, &cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_Encrypt   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	//认证
	if((result = SKF_DevAuth(hDev, cryptData, cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_DevAuth   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	else
	{
		printf(" 设备认证通过!\n");
	}
// 	if((result = SKF_CloseHandle(hKey))!=SAR_OK)
// 	{ 
// 		printf("SKF_CloseHandle  ERROR:%s\n",errorInfo[result&0xff].error);
// 		_CloseDev(hDev);
// 		return;
// 	}

	printf("测试完毕\n");
	
_ERRRET:	
	_CloseDev(hDev);
}

//测试修改PIN
void Test_SKF_ChangePIN()
{
	ULONG result;
	DEVHANDLE hDev;
	HAPPLICATION hApp;
	ULONG retrycount;
	ULONG pintype;
	char arrOldPIN[10] = {0};
	char arrNewPIN[10] = {0};

	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}

	printf("输入PIN码类型(0--admin;1--user):");
	scanf("%d", &pintype);

	printf("\n输入8字节旧PIN码:");
	scanf("%s", arrOldPIN);

	printf("\n输入8字节新PIN码:");
	scanf("%s", arrNewPIN);

	if ((result = SKF_ChangePIN(hApp, pintype, arrOldPIN, arrNewPIN, &retrycount)) != SAR_OK)
	{
		printf("SKF_ChangePIN  ERROR:%s  retrycount=%d\n",errorInfo[result&0xff].error,retrycount);
		goto _ERRRET;
	}
	else
	{	
		printf("使用管理员权限 修改成功\n");
	}
	
	printf("使用用户权限\n");
	if ((result = SKF_ChangePIN(hApp, USER_TYPE, "22222222", "aaaaaaaa", &retrycount)) != SAR_OK)
	{
		printf("SKF_ChangePIN  ERROR:%s  retrycount=%d\n",errorInfo[result&0xff].error,retrycount);		
		goto _ERRRET;
	}
	else
	{		
		printf("使用用户权限 修改成功\n");
	}

	printf("测试完毕\n");

_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//测试验证PIN
void Test_SKF_VerifyPIN()
{	
	ULONG result;
	DEVHANDLE hDev;
	HAPPLICATION hApp;

	ULONG remainretrycount;
	ULONG pintype;
	char arrPIN[10] = {0};

	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	printf("输入8字节PIN码:");
	scanf("%s", arrPIN);

	printf("\n输入PIN码类型(0--admin;1--user):");
	scanf("%d", &pintype);

	if ((result = SKF_VerifyPIN(hApp, pintype, arrPIN, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_VerifyPIN  ERROR:%s  剩余重试次数=%d \n", errorInfo[result&0xff].error,remainretrycount);		
		goto _ERRRET;
	}
	else
	{
		printf("校验PIN码成功!\n");
	}
	
	printf("测试完毕\n");
	
_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//测试解锁PIN
void Test_SKF_UnblockPIN()
{
	DEVHANDLE hDev;
	ULONG result; 
	HAPPLICATION hApp;
	
	ULONG remainretrycount;
	char arrADMPin[8] = {0};
	char arrUSRPin[8] = {0};

	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	printf("请输入管理员PIN:");
	scanf("%s", arrADMPin);
	printf("\n请输入新用户PIN:");
	scanf("%s", arrUSRPin);

	if ((result = SKF_UnblockPIN(hApp, arrADMPin, arrUSRPin, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_UnblockPIN  ERROR:%s  剩余重试次数=%d \n",errorInfo[result&0xff].error,remainretrycount);
	}
	else
	{
		printf("\n 解锁PIN成功!\n");
	}

	printf("测试完毕\n");

	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//测试修改设备认证密钥
void Test_SKF_ChangeDevAuthKey()
{
	ULONG result;
	DEVHANDLE hDev;
	CHAR  keyData[20] = {0};
	ULONG keyLen;

	if (_OpenDev(&hDev) != SAR_OK)
	{
		return;
	}
 
	//case1
	printf("没有认证，直接修改认证密钥:\n\n");
	printf("请输入密钥长度:");
	scanf("%d", &keyLen);
	printf("\n请输入新密钥:");
	scanf("%s", keyData);
	if ((result = SKF_ChangeDevAuthKey(hDev, (BYTE *)keyData, keyLen)) != SAR_OK)
	{ 
		printf(" SKF_ChangeDevAuthKey   ERROR:%s\n",errorInfo[result&0xff].error);
	} 
	else
	{		
		printf(" 修改认证密钥成功\n");
	}


	//case2	
	printf("\n认证后再修改认证密钥:\n");
	if (_DevAuth(&hDev) != SAR_OK)
	{
		goto _ERRRET;
	}

	memset(keyData, 0, sizeof(keyData));
	printf("请输入密钥长度:");
	scanf("%d", &keyLen);
	printf("\n请输入新密钥:");
	scanf("%s", keyData);
	if ((result = SKF_ChangeDevAuthKey(hDev, (BYTE *)keyData, keyLen)) != SAR_OK)
	{ 
		printf(" SKF_ChangeDevAuthKey   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	} 
	else
	{
		printf(" 修改认证密钥成功\n");
	}
	
	printf("测试完毕\n");

_ERRRET:
	_CloseDev(hDev);
}

//测试清除安全状态
void Test_SKF_ClearSecueState()
{
	ULONG result; 
	DEVHANDLE hDev;
	HAPPLICATION hApp;
	
	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	if ((result = SKF_ClearSecureState(hApp)) != SAR_OK)
	{
		printf("SKF_ClearSecureState  ERROR:%s  \n",errorInfo[result&0xff].error );
	}
	else
	{
		printf(" 清除安全状态成功!\n");
	}
	
	printf("测试完毕\n");
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//测试获取PIN信息
void Test_SKF_GetPINInfo()
{
	ULONG result; 	
	DEVHANDLE hDev;
	HAPPLICATION hApp;
	
	ULONG maxretrycount;
	ULONG remainretrycount;
	BOOL isdefaultPin;
	ULONG pintype = ADMIN_TYPE;
	
	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	if ((result = SKF_GetPINInfo(hApp, pintype, &maxretrycount, &remainretrycount, &isdefaultPin)) != SAR_OK)
	{
		printf("SKF_GetPINInfo  ERROR:%s \n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" PIN信息如下:\n");
		printf(" maxretrycount=%d\n remainretrycount=%d\n 是否默认pin=%s\n", maxretrycount,remainretrycount, (isdefaultPin ? "是" : "否"));
	}
	
	printf("测试完毕\n");
	_CloseAPP(hApp);
	_CloseDev(hDev);
}


//应用管理系列
//测试创建应用
void Test_SKF_CreateApplication()
{ 
	DEVHANDLE hDev;
	ULONG result;
	HAPPLICATION hApp0;
	HAPPLICATION hApp;
	char appName[64] = {0};
	ULONG rightType;
	int  quit;

	if (_OpenDev(&hDev)!=SAR_OK)
	{
		return;
	}

	//case1
	printf("测试不认证创建1组APP:\n");
	printf("权限类型：不允许创建; 应用名称:app0, 管理员pin:00000000, 最大重试:3; 用户pin:99999999, 最大重试5\n");
	if ((result = SKF_CreateApplication(hDev, "app0", "00000000", 3, "99999999", 5, SECURE_NEVER_ACCOUNT, &hApp0)) != SAR_OK)
	{ 
		printf("SKF_CreateApplication  ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{ 
		printf(" 创建app0执行成功\n");
		if ((result = SKF_CloseApplication(hApp0)) != SAR_OK)
		{ 
			printf("SKF_CloseApplication  ERROR:%s\n",errorInfo[result&0xff].error);
		}
		else
		{
			printf(" 关闭app0执行成功\n");
		}
	}

	//case2
	printf("测试认证后创建随意组APP[管理员PIN默认11111111,最多3次重试;用户PIN默认为22222222,最多5次重试]:\n");
	if (_DevAuth(hDev) != SAR_OK)
	{
		_CloseDev(hDev);
		return;
	}

_RETRY:
	printf("请输入应用名称:");
	memset(appName, 0, sizeof(appName));
	scanf("%s", appName);
	printf("\n请输入权限类型(0-不允许1-管理员权限16-用户权限255-任何人):");
	scanf("%d", &rightType);
	if ((result = SKF_CreateApplication(hDev, appName, "11111111", 3, "22222222", 5, rightType, &hApp)) != SAR_OK)
	{ 
		printf("SKF_CreateApplication  ERROR:%s\n", errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	else
	{ 
		if ((result = SKF_CloseApplication(hApp)) != SAR_OK)
		{ 
			printf("SKF_CloseApplication  ERROR:%s\n",errorInfo[result&0xff].error);
			goto _ERRRET;
		}
		printf("SKF_CreateApplication app执行成功\n");
	}
	printf("\n退出输入0，继续创建输入其它值:");
	scanf("%d", &quit);
	if (quit)
	{
		goto _RETRY;
	}

_ERRRET:
	_CloseDev(hDev);
	
	printf("测试完毕\n");
}

//测试枚举应用
void Test_SKF_EnumApplication()
{
	ULONG result =0;
	CHAR *pBuffer;
	ULONG pulSize = 0;

	DEVHANDLE hDev;
	CHAR *pStart = NULL;
	
	if (_OpenDev(&hDev) != SAR_OK)
	{
		return;
	}

	if ((result = SKF_EnumApplication(hDev, NULL, &pulSize)) != SAR_OK)
	{
		printf("SKF_EnumApplication 1 ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	
	pBuffer = (CHAR *)malloc(pulSize);
	memset(pBuffer, 0, pulSize);
	if ((result = SKF_EnumApplication(hDev, pBuffer, &pulSize)) != SAR_OK)
	{
		printf("SKF_EnumApplication 2 ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	
	//显示所有app列表
	printf("枚举应用:\n");
	pStart = pBuffer;
	while (*pStart)
	{
		printf("%s\n",pStart);
		pStart += (strlen(pStart) + 1);
	}
	free(pBuffer);

	printf("\n测试完毕\n");

_ERRRET:
	_CloseDev(hDev);
}

//测试删除应用
void Test_SKF_DeleteApplication()
{
	ULONG result =0; 
	ULONG pulSize = 0;
	DEVHANDLE hDev;  
	CHAR appName[128]={0};
	
	
	if (_OpenDev(&hDev) != SAR_OK)
	{
		return;
	}

	printf("请输入需要删除的应用名称:");
	scanf("%s", appName);
  
	//case1
	printf(" 没有认证，直接删除...\n");
	if ((result = SKF_DeleteApplication(hDev, appName)) != SAR_OK)
	{
		printf("SKF_DeleteApplication 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" 直接删除成功!\n");
	}
	 
	//case2
	printf(" 调用认证，删除应用..\n");
	if(_DevAuth(hDev) != SAR_OK)
	{
		_CloseDev(hDev);
		return;
	}

	if ((result = SKF_DeleteApplication(hDev, appName)) != SAR_OK)
	{
		printf("SKF_DeleteApplication 2 ERROR:%s\n",errorInfo[result&0xff].error);
	}
	else
	{
		printf(" 认证后删除应用成功!\n");
	}
	
	_CloseDev(hDev);
	
	printf("测试完毕\n");
	
	return;
}

//测试打开关闭应用
void Test_SKF_OpenClose_Application()
{
	ULONG result =0; 
	DEVHANDLE hDev;  
	HAPPLICATION hApp;
	
	CHAR appName[128]={0};
	
	if (_OpenDev(&hDev) != SAR_OK)
	{
		return;
	}

	printf("请输入需要打开的应用名称:");
	scanf("%s", appName);	
	
	if ((result = SKF_OpenApplication(hDev, appName, &hApp)) != SAR_OK)
	{
		printf("SKF_OpenApplication  ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	printf("\n打开应用成功\n");
	
	if ((result = SKF_CloseApplication(hApp)) != SAR_OK)
	{
		printf("SKF_CloseApplication  ERROR:%s\n",errorInfo[result&0xff].error);		
		goto _ERRRET;
	}
	
	printf("\n关闭应用成功\n");
	printf("测试完毕\n");

_ERRRET:
	_CloseDev(hDev);
}


//文件管理系列
//测试创建文件
void Test_SKF_CreateFile()
{
	DEVHANDLE hDev;
	ULONG result; 
	HAPPLICATION hApp;
	CHAR fileName[128]={0};
	ULONG fileSize, readRight, writeRight;
	int quit;

	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hApp) != SAR_OK)
	{
		return;
	}


_RETRY:
	printf("请输入文件名:");
	memset(fileName, 0, sizeof(fileName));
	scanf("%s", fileName);
	printf("\n请输入文件大小(<32K):");
	scanf("%d", &fileSize);
	printf("\n请输入读权限类型(0-不允许1-管理员权限16-用户权限255-任何人):");
	scanf("%d", &readRight);
	printf("\n请输入写权限类型(0-不允许1-管理员权限16-用户权限255-任何人):");
	scanf("%d", &writeRight);

	if ((result = SKF_CreateFile(hApp, fileName, fileSize, readRight, writeRight)) != SAR_OK)
	{ 
		printf(" SKF_CreateFile  ERROR:%s\n",errorInfo[result&0xff].error);
	}
	else
	{
		printf(" 创建file成功\n");
	}

	//
	printf("\n退出输入0，继续创建输入其它值:");
	scanf("%d", &quit);
	if (quit)
	{
		goto _RETRY;
	}


	_CloseAPP(hApp);
	_CloseDev(hDev);
	
	printf("测试完毕\n");
}

//测试删除文件
void Test_SKF_DeleteFile()
{
	ULONG result =0; 
	DEVHANDLE hDev;  
	HAPPLICATION hApp;
	CHAR fileName[128]={0};
	
	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}

	if (_CheckPin(hApp) != SAR_OK)
	{
		return;
	}

		
	printf("需要删除的文件名称:");
	scanf("%s", fileName);
	
	if ((result = SKF_DeleteFile(hApp, fileName)) != SAR_OK)
	{
		printf("SKF_DeleteFile  ERROR:%s\n",errorInfo[result&0xff].error);
	}
	
	_CloseAPP(hApp);
	_CloseDev(hDev);
	
	printf("测试完毕\n");
}

//测试读文件
static BYTE dataBuffer[32*1024];
void Test_SKF_ReadFile()
{
	ULONG result =0;	
	DEVHANDLE hDev; 
	HAPPLICATION hApp;
	CHAR fileName[64]={0};
	ULONG wantLen = 0;
	ULONG dataBufferLen, i;

	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hApp) != SAR_OK)
	{
		return;
	}

	printf("请输入要读取的文件名称:");
	scanf("%s", fileName);
	printf("请输入要读取的长度:");
	scanf("%d", &wantLen);
	dataBufferLen = 32*1024;
	if ((result = SKF_ReadFile(hApp, fileName,/*offset*/0, wantLen, dataBuffer, &dataBufferLen)) != SAR_OK)
	{
		printf(" SKF_ReadFile  ERROR:%s\n", errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	else
	{
		printf(" 读取%s的实际长度为%d,内容为:\n", fileName, dataBufferLen);
		for (i = 0; i < dataBufferLen; i++)
		{
			printf("%02x ", dataBuffer[i]);
		}
		printf("\n");
	}

	printf("测试完毕\n");
	
_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//测试写文件
static void GetRandomData(BYTE* pData, ULONG lDataLen)
{
	ULONG n;

	srand((int)time(0));	//由时间产生随机种子，使每次产生的数不一样
	for (n = 0; n < lDataLen; n++)
	{
		pData[n] = rand()%256;		//产生0-255数据
	}
}
void Test_SKF_WriteFile()
{
	ULONG result =0;
	DEVHANDLE hDev; 
	HAPPLICATION hApp;
	CHAR fileName[64]={0};
	ULONG wantLen, i;

	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hApp) != SAR_OK)
	{
		return;
	}

	printf("请输入要写入的文件名称:");
	scanf("%s", fileName);
	printf("\n请输入随机数据长度:");
	scanf("%d", &wantLen);

	memset(dataBuffer, 0, 32*1024);
	GetRandomData(dataBuffer, wantLen);

	if ((result = SKF_WriteFile(hApp, fileName,/*offset*/0, dataBuffer, wantLen)) != SAR_OK)
	{
		printf("SKF_WriteFile  ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" 在%s中写入%d字节数据成功:\n", fileName, wantLen);
		for (i = 0; i < wantLen; i++)
		{
			printf("%02x ", dataBuffer[i]);
		}
		printf("\n");
	}
	
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//测试枚举文件
void Test_SKF_EnumFiles()
{
	ULONG result =0; 
	CHAR *pBuffer;
	ULONG pulSize = 0;
	
	DEVHANDLE hDev; 
	HAPPLICATION hApp;
	CHAR *pStart = NULL;

	CHAR fileName[128]={0};
	CHAR appName[128]={0};

	
	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	if ((result = SKF_EnumFiles(hApp, NULL, &pulSize)) != SAR_OK)
	{
		printf("SKF_EnumFiles 1 ERROR:%s\n", errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	pBuffer = (CHAR *)malloc(pulSize);
	memset(pBuffer, 0, pulSize);	
	if ((result = SKF_EnumFiles(hApp, pBuffer, &pulSize)) != SAR_OK)
	{
		printf("SKF_EnumFiles 2 ERROR:%s\n", errorInfo[result&0xff].error);
		free(pBuffer);
		goto _ERRRET;
	}
	
	if (pulSize > 1)
	{
		//显示所有file列表
		printf(" 枚举文件:\n");
	}
	else
	{
		printf(" 没有发现文件!\n");
	}

	pStart = pBuffer;
	while(*pStart)
	{
		printf("%s\n", pStart);
		pStart += (strlen(pStart) +1);
	}
	free(pBuffer);
	printf("测试完毕\n");
	
_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);

}

//测试获取文件信息
void Test_SKF_GetFileInfo()
{
	ULONG result =0; 
	DEVHANDLE hDev; 
	HAPPLICATION hApp;
	
	CHAR fileName[128] = {0};
	FILEATTRIBUTE fileInfo;
	
	if (_OpenAPP_WithoutAUTH(&hDev, &hApp) != SAR_OK)
	{
		return;
	}
	
	printf("需要获取的文件名称:");
	scanf("%s", fileName);

	memset(&fileInfo, 0, sizeof(FILEATTRIBUTE));
	if((result = SKF_GetFileInfo(hApp, fileName, &fileInfo)) != SAR_OK)
	{
		printf("SKF_GetFileInfo  ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" 获取信息成功:\n");
		printf(" FileName:%s\n FileSize:%d \n ReadRights:%X\n WriteRights:%X\n",
				fileInfo.FileName, fileInfo.FileSize, fileInfo.ReadRights, fileInfo.WriteRights);
	}

	_CloseAPP(hApp);
	_CloseDev(hDev);
	
	printf("测试完毕\n");
	
	return;
}

//====================================================================================//
//====================================================================================//
//====================================================================================//

#define     LIB_EXIST				1
#define		NAME_BUFFER_SIZE		256
#define     DEFAULT_NAME_INDEX		1
static char m_NameBuffer[NAME_BUFFER_SIZE];

//测试枚举设备
void Test_SKF_EnumDev()
{
	ULONG ret;
	ULONG size;
	ULONG len;
	char* pName;

	printf("开始测试枚举设备函数:\n");
	
	//condition1.
	printf("测试获取当前设备状态为存在的设备列表...\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 返回设备列表长度为:%d\n", size);
		if (size > 0)
		{
			printf(" 返回设备列表名称为: \n");
			pName = m_NameBuffer;
			while (*pName)
			{
				printf(" %s \n", pName);
				len = strlen(pName);
				pName += (len + 1);
			}	
		}
	}
#endif

	//condition2.
	printf("测试获取当前驱动支持的设备列表...\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(FALSE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 返回设备列表长度为:%d\n", size);
		if (size > 0)
		{
			printf(" 返回设备列表名称为: \n");
			pName = m_NameBuffer;
			while (*pName)
			{
				printf(" %s \n", pName);
				len = strlen(pName);
				pName += (len + 1);
			}	
		}
	}
#endif

	printf("完成测试枚举设备函数!\n");
}


//测试连接设备与断开设备
void Test_SKF_ConnectDev_DisconnectDev()
{
	ULONG ret;
	ULONG size;
	char* pName;
	DEVHANDLE hDevice;

	printf("开始测试连接与断开设备函数:\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("枚举设备失败%08x\n", ret);
		return;
	}
	if (size < 1)
	{
		return;
	}

	pName = m_NameBuffer;
	ret = SKF_ConnectDev(pName, &hDevice);
	if (ret != SAR_OK)
	{
		printf("连接失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 返回设备句柄为: %08x\n", hDevice);
	}

	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("断开连接失败, 错误码为%08x!\n", ret);
		return;
	}
#endif

	printf("完成测试连接与断开设备函数!\n");
}

//测试获取设备状态
void Test_SKF_GetDevState()
{
	ULONG ret;
	ULONG size;
	ULONG status;
	char* pName;

	printf("开始测试获取设备状态函数:\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("枚举设备失败%08x\n", ret);
		return;
	}
	if (size < 1)
	{
		return;
	}
	
	pName = m_NameBuffer;
	ret = SKF_GetDevState(pName, &status);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		switch (status)
		{
		case DEV_ABSENT_STATE:
			printf(" 设备不存在\n");
			break;
		case DEV_PRESENT_STATE:
			printf(" 设备存在\n");
			break;
		case DEV_UNKNOW_STATE:
			printf(" 设备状态未知\n");
			break;
		default:
			printf(" 错误的状态码!\n");
			break;
		}
	}
#endif

	printf("完成测试获取设备状态函数!\n");
}

static BOOL GetDefaultDevHandle(DEVHANDLE *phDev)
{
	ULONG ret;
	ULONG size;
	char* pName;
	
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		return FALSE;
	}
	if (size < 1)
	{
		return FALSE; 
	}
	
	pName = m_NameBuffer;
	ret = SKF_ConnectDev(pName, phDev);
	if (ret != SAR_OK)
	{
		return FALSE;
	}
#endif
	
	return TRUE;
}

//测试获取设备信息
void Test_SKF_GetDevInfo()
{
	ULONG ret;
	DEVHANDLE hDevice;
	DEVINFO sDevInfo;
	
	printf("开始测试获取设备信息函数:\n");
	if (!GetDefaultDevHandle(&hDevice))
	{
		printf("连接设备失败!\n");
		return;
	}

#if LIB_EXIST	
	ret = SKF_GetDevInfo(hDevice, &sDevInfo);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 数据结构版本:Version %d.%d\n", sDevInfo.Version.major, sDevInfo.Version.minor);
		printf(" 设备厂商信息:%s\n", sDevInfo.Manufacturer);
		printf(" 发行厂商信息:%s\n", sDevInfo.Issuer);
		printf(" 设备标签:%s\n", sDevInfo.Label);
		printf(" 序列号:%s\n", sDevInfo.SerialNumber);
		printf(" 设备硬件版本:HWVer %d.%d\n", sDevInfo.HWVersion.major, sDevInfo.HWVersion.minor);
		printf(" 设备固件版本:FWVer %d.%d\n", sDevInfo.FirmwareVersion.major, sDevInfo.FirmwareVersion.minor);
		printf(" 分组密码算法标识:%08x\n", sDevInfo.AlgSymCap);
		printf(" 非对称密码算法标识:%08x\n", sDevInfo.AlgAsymCap);
		printf(" 密码杂凑算法标识:%08x\n", sDevInfo.AlgHashCap);
		printf(" 设备认证分组密码算法标识:%08x\n", sDevInfo.DevAuthAlgId);
		printf(" 设备总空间大小:%ld\n", sDevInfo.TotalSpace);
		printf(" 用户可用空间大小:%ld\n", sDevInfo.FreeSpace);
		printf(" 保留扩展:----------\n");
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("断开连接失败%08x!\n", ret);
		return;
	}
#endif
	
	printf("完成测试获取设备信息函数!\n");
}

//测试设置设备标签
void Test_SKF_SetLabel()
{
	ULONG ret;
	DEVHANDLE hDevice;
	char strLab[32] = {0};

	printf("开始测试设置设备标签函数:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("连接设备失败!\n");
		return;
	}

#if LIB_EXIST
	printf(" 请输入标签名:\n");
	scanf("%s", strLab);
	ret = SKF_SetLabel(hDevice, strLab);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 已设置设备标签码为%s!\n", strLab);
		// readback label
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("断开连接失败%08x!\n", ret);
		return;
	}
#endif
	
	printf("完成测试设置设备标签函数!\n");
}

//测试锁定设备
void Test_SKF_LockDev()
{
	ULONG ret;
	ULONG time;
	DEVHANDLE hDevice;

	printf("开始测试锁定设备函数:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("连接设备失败!\n");
		return;
	}

#if LIB_EXIST	
	time = 60000;	//一分钟
	ret = SKF_LockDev(hDevice, time);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 锁定设备%d秒!\n", time);
		//do other operation
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("断开连接失败%08x!\n", ret);
		return;
	}
#endif

	printf("完成测试锁定设备函数!\n");
}

//测试解锁设备
void Test_SKF_UnlockDev()
{
	ULONG ret;
	DEVHANDLE hDevice;

	printf("开始测试解锁设备函数:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("连接设备失败!\n");
		return;
	}

#if LIB_EXIST
	ret = SKF_UnlockDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 解锁设备成功!\n");
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("断开连接失败%08x!\n", ret);
		return;
	}
#endif
	
	printf("完成测试解锁设备函数!\n");
}

//测试设备命令传输
void Test_SKF_Transmit()
{
	ULONG ret;
	DEVHANDLE hDevice;
	BYTE cmd[10] = {0};
	BYTE data[40] = {0};
	ULONG dLen;

	printf("开始测试设备命令传输函数:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("连接设备失败!\n");
		return;
	}
	
#if LIB_EXIST	
	cmd[0] = 0x5A;
	cmd[1] = 0x11;
	cmd[2] = 0x22;
	cmd[3] = 0x33;
	ret = SKF_Transmit(hDevice, cmd, 10, data, &dLen);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
		return;
	}
	else
	{
		printf(" 命令返回长度%d!\n", dLen);
		printf(" 返回数据为%s\n", data);
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("断开连接失败%08x!\n", ret);
		return;
	}
#endif
	
	printf("完成测试设备命令传输函数!\n");
}


//=====================================================//
static BOOL GetDefaultAPPHandle(HAPPLICATION *phAPP)
{
	ULONG ret;
	DEVHANDLE hDevice;
	char strAppName[16] = {0};

	if (!GetDefaultDevHandle(&hDevice))
	{
		return FALSE;
	}

#if LIB_EXIST
	strAppName[0] = 'a';
	strAppName[1] = 'i';
	strAppName[2] = 's';
	strAppName[3] = 'i';
	strAppName[4] = 'n';
	strAppName[5] = 'o';
// 	if (_DevAuth(hDev) != SAR_OK)
// 	{
// 		_CloseDev(hDev);
// 		return;
// 	}
	//SKF_DevAuth();
	//SKF_VerifyPIN();
	ret = SKF_OpenApplication(hDevice, strAppName, phAPP);
	if (ret != SAR_OK)
	{
		return FALSE;
	}
#endif
	
	return TRUE;
}

//测试创建容器
void Test_SKF_CreateContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	printf("开始测试创建容器函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}

	if (_CheckPin(hAPP) != SAR_OK)
	{
		return;
	}

	printf("请输入容器名称:\n");
	scanf("%s", strContName);

#if LIB_EXIST
	ret = SKF_CreateContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" SKF_CreateContainer  ERROR:%s\n", errorInfo[ret&0xff].error);
		goto _ERRRET;
	}
	else
	{
		printf(" 容器创建成功，句柄为%08x!\n", hCont);
	}
#endif

	printf("完成测试创建容器函数!\n");
	_CloseContain(hCont);

_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//测试删除容器
void Test_SKF_DeleteContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	char strContName[64] = {0};

	printf("开始测试删除容器函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}

	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
	printf("请输入容器名称:\n");
	scanf("%s", strContName);
	
#if LIB_EXIST
	ret = SKF_DeleteContainer(hAPP, strContName);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
	}
	else
	{
		printf(" 容器删除成功!\n");
	}
#endif
	
	printf("完成测试删除容器函数!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//测试枚举容器
void Test_SKF_EnumContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	char strContName[64] = {0};
	ULONG size, len;
	char* pName;

	printf("开始测试枚举容器函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
	/*printf("请输入容器名称:\n");
	scanf("%s", strContName);*/
	
	//condition1.
	printf("测试只获取容器长度...\n");
#if LIB_EXIST
	ret = SKF_EnumContainer (hAPP, NULL, &size);
	if (ret != SAR_OK)
	{
		printf("测试CASE1失败, 错误码为%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" 返回设备列表长度为:%d\n", size);
	}
#endif

	//condition2.
	printf("测试获取指定长度的容器名称...\n");
#if LIB_EXIST
	if (size > NAME_BUFFER_SIZE)
	{
		printf("WARNING: buffer空间不足\n");
		goto _ERRRET;
	}
	memset(m_NameBuffer, 0, size);
	ret = SKF_EnumContainer (hAPP, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("测试CASE2失败, 错误码为%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" 返回设备列表长度为:%d\n", size);
		if (size > 0)
		{
			printf(" 返回设备列表名称为: \n");
			pName = m_NameBuffer;
			while (*pName)
			{
				printf(" %s \n", pName);
				len = strlen(pName);
				pName += (len + 1);
			}	
		}
	}
#endif
	
	printf("完成测试枚举容器函数!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//测试打开和关闭容器
void Test_SKF_OpenContainer_CloseContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	printf("开始测试打开关闭容器函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
	printf("请输入容器名称:\n");
	scanf("%s", strContName);

#if LIB_EXIST
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf("测试打开失败, 错误码为%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" 返回容器句柄为:%08x\n", hCont);
	}

	ret = SKF_CloseContainer(hCont);
	if (ret != SAR_OK)
	{
		printf("测试关闭失败, 错误码为%08x!\n", ret);
	}
#endif

	printf("完成测试打开关闭容器函数!\n");

_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//测试获取容器类型
void Test_SKF_GetContianerType()
{
	ULONG ret;
	ULONG type;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	printf("开始测试获取容器类型函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}

//	ret = SKF_GetContianerType(hCont, &type);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x!\n", ret);
	} 
	else
	{
		switch (type)
		{
		case 0:
			printf(" 未分配的容器\n");
			break;
		case 1:
			printf(" RSA容器\n");
			break;
		case 2:
			printf(" ECC容器\n");
			break;
		default:
			printf(" 错误的类型码!\n");
			break;
		}
	}
#endif

	printf("完成测试获取容器类型函数!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//测试导入证书
void Test_SKF_ImportCertificate()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	BYTE strCert[128] = {0};
	
	printf("开始测试导入证书函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}
	
	strCert[0] = 0x12;
	strCert[1] = 0x23;
	strCert[2] = 0x34;
	strCert[3] = 0x45;
	strCert[4] = 0x56;
	ret = SKF_ImportCertificate(hCont, TRUE,  strCert, 128);
	if (ret != SAR_OK)
	{
		printf("测试失败, 错误码为%08x\n", ret);
	} 
	else
	{
		printf("导入证书成功!");
	}
#endif
	
	printf("完成测试导入证书函数!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//测试导出证书
void Test_SKF_ExportCertificate()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	BYTE strCert[128] = {0};
	ULONG cLen;

	printf("开始测试导出证书函数:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
#if LIB_EXIST
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}
	
	//第一步：获取长度
	ret = SKF_ExportCertificate(hCont, TRUE,  NULL, &cLen);
	if (ret != SAR_OK)
	{
		printf("测试获取证书长度失败, 错误码为%08x\n", ret);
		_CloseContain(hCont);
		goto _ERRRET;
	} 
	else
	{
		printf(" 导出证书长度为%d!", cLen);
	}
	
	//第二步：获取内容
	if (cLen > 128)
	{
		printf("WARNING: 缓存空间不足!\n");
		_CloseContain(hCont);
		goto _ERRRET;
	}
	memset(strCert, 0, 128);
	ret = SKF_ExportCertificate(hCont, TRUE,  strCert, &cLen);
	if (ret != SAR_OK)
	{
		printf("测试获取证书内容失败, 错误码为%08x\n", ret);
	} 
	else
	{
		printf(" 导出证书内容为%s!", strCert);
	}
#endif
	
	printf("完成测试导出证书函数!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}



//测试RSA生成导出以及签名验签
void Test_SKF_GenRSAKeyPair()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	BYTE strCert[128] = {0};
	ULONG ucflag,ulBitsLen;

	RSAPUBLICKEYBLOB stRsaBlob1,stRsaBlob2;
	ULONG ulRsaBlobLen;
	BYTE Random[1024] = {0};
	BYTE Hash[32] = {0};
	ULONG RandomLen,ulHashLen;
	HANDLE hHash;
	BYTE sign[512];
	ULONG signLen=sizeof(sign);

	clock_t start_t, finish_t;
	double  duration = 0;
	char ucTime[32] = {0};

	printf("开始测试RSA公私钥对生成导出以及签名验签:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST
	//容器名称con1
	printf("请输入容器名称:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}

	//第一步：生成RSA签名公私钥对
	printf("请输入RSA算法长度(1-1024 2-2048):");
	scanf("%d", &ucflag);
	if(1 == ucflag)
		ulBitsLen = 1024;
	else
		ulBitsLen = 2048;
	
	memset(&stRsaBlob1,0,sizeof(stRsaBlob1));
	start_t = clock();
	ret = SKF_GenRSAKeyPair(hCont, ulBitsLen, &stRsaBlob1);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf(" 生成%dRSA公私钥对失败%08x!\n", ulBitsLen,ret);
		goto _ERRRET;
	}
	else
	{
		printf("生成%dRSA公私钥对成功!\n", ulBitsLen);
		printf("生成%dRSA公私钥对时长：\n",ulBitsLen);
		sprintf(ucTime,"%.3f",duration);
	}

	//第二步导出签名公钥，与生成输出的公钥比对
	memset(&stRsaBlob2,0,sizeof(stRsaBlob2));
	start_t = clock();
	ret = SKF_ExportPublicKey(hCont, TRUE, NULL, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得签名公钥长度失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 获得签名公钥长度成功!\n");

	ret = SKF_ExportPublicKey(hCont, TRUE, (BYTE *)&stRsaBlob2, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得签名公钥失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 获得签名公钥成功!\n");

	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	printf("获得签名公钥时长：\n");
	sprintf(ucTime,"%.3f",duration);


	//第三步签名验签测试
	//1.生成随机数
	RandomLen = 65;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("生成随机数失败%08x!\n",ret);
		goto _ERRRET;
	}

	//2.计算摘要
	start_t = clock();
	ret =  SKF_DigestInit(hDev, SGD_SHA1, NULL, NULL, 0, &hHash);
	if (ret != SAR_OK)
	{
		printf("摘要初始化失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 摘要初始化成功!\n");

	ulHashLen = sizeof(Hash);
	ret = SKF_Digest(hHash, Random, RandomLen,Hash,&ulHashLen);
	if (ret != SAR_OK)
	{
		printf("摘要失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 摘要成功!\n");

	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	printf("摘要计算时长：\n");
	sprintf(ucTime,"%.3f",duration);
	
	//3.签名验签
	start_t = clock();
	ret = SKF_RSASignData(hCont, Hash, ulHashLen, sign, &signLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("RSA签名失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("RSA签名成功!\n");

	printf("RSA签名时长：\n");
	sprintf(ucTime,"%.3f",duration);

	start_t = clock();
	ret = SKF_RSAVerify(hDev, &stRsaBlob2, Hash, ulHashLen, sign, signLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("RSA验签失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("RSA验签成功!\n");

	printf("RSA验签时长：\n");
	sprintf(ucTime,"%.3f",duration);


#endif
	
	printf("完成测试RSA公私钥对生成导出以及签名验签函数!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


//测试ECC生成导出以及签名验签
void Test_SKF_GenECCKeyPair()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	ECCPUBLICKEYBLOB stEccBlob1,stEccBlob2;
	ULONG ulEccBlobLen;
	BYTE DefID[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	BYTE Random[1024] = {0};
	BYTE Hash[32] = {0};
	ULONG RandomLen,ulHashLen;
	HANDLE hHash;
	BYTE sign[512];
	ULONG signLen=sizeof(sign);
	ECCSIGNATUREBLOB stEccSign;

	clock_t start_t, finish_t;
	double  duration = 0;
	char ucTime[32] = {0};

	printf("开始测试ecc公私钥对生成导出以及签名验签:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST
	//容器名称con2
	printf("请输入容器名称:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}

	//第一步：生成ECC签名公私钥对
	memset(&stEccBlob1,0,sizeof(stEccBlob1));
	start_t = clock();
	ret = SKF_GenECCKeyPair(hCont, SGD_SM2_1, &stEccBlob1);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf(" 生成ECC公私钥对失败%08x!\n",ret);
		goto _ERRRET;
	}
	else
	{
		printf("生成ECC公私钥对成功!\n");
		printf("生成ECC公私钥对时长：\n");
		sprintf(ucTime,"%.3f",duration);
	}

	//第二步导出签名公钥，与生成输出的公钥比对
	memset(&stEccBlob2,0,sizeof(stEccBlob2));
	ret = SKF_ExportPublicKey(hCont, TRUE, NULL, &ulEccBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得签名公钥长度失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" 获得签名公钥长度成功!\n");
	}

	start_t = clock();
	ret = SKF_ExportPublicKey(hCont, TRUE, (BYTE *)&stEccBlob2, &ulEccBlobLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf(" 获得签名公钥失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" 获得签名公钥成功!\n");
		printf("获得签名公钥时长：\n");
		sprintf(ucTime,"%.3f",duration);
	}

	//第三步签名验签测试
	//1.生成随机数
	RandomLen = 56;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("生成随机数失败%08x!\n",ret);
		goto _ERRRET;
	}

	//2.计算摘要
	start_t = clock();
	ret =  SKF_DigestInit(hDev, SGD_SM3, &stEccBlob2, DefID, sizeof(DefID), &hHash);
	if (ret != SAR_OK)
	{
		printf("SM3摘要初始化失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 摘要初始化成功!\n");

	ulHashLen = sizeof(Hash);
	ret = SKF_Digest(hHash, Random, RandomLen,Hash,&ulHashLen);
	if (ret != SAR_OK)
	{
		printf("SM3摘要失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 摘要成功!\n");

	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	printf("SM3摘要计算时长：\n");
	sprintf(ucTime,"%.3f",duration);

	//3.签名验签
	start_t = clock();
	ret = SKF_ECCSignData(hCont, Hash, ulHashLen, &stEccSign);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECC签名失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("ECC签名成功!\n");
	
	printf("ECC签名时长：\n");
	sprintf(ucTime,"%.3f",duration);

	start_t = clock();
	ret = SKF_ECCVerify(hDev, &stEccBlob1, Hash, ulHashLen, &stEccSign);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECC验签失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("ECC验签成功!\n");
	printf("ECC验签时长：\n");
	sprintf(ucTime,"%.3f",duration);


#endif
	
	printf("完成测试ECC公私钥对生成导出以及签名验签函数!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


ULONG En_DewithoutUpdate(DEVHANDLE hDev,HANDLE hkey) 
{
	ULONG ret;
	BYTE Random[1024] = {0};
	ULONG RandomLen;

	BYTE encryptedData[1024] = {0},pulDataBytes[1024] = {0};
	ULONG ulEncryptedLen,dataLen;
	BLOCKCIPHERPARAM encrptPara;

	clock_t start_t, finish_t;
	double  duration = 0;
	char ucTime[32] = {0};


	memset((void *)&encrptPara, 0x00, sizeof(BLOCKCIPHERPARAM));
	printf(" =================>单步数据加解密!\n");
	//1.生成随机数
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("生成随机数失败%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" 生成随机数成功!\n");

	//ECB加密
	start_t = clock();
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB加密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB加密初始化成功!\n");

	ret = SKF_Encrypt(hkey, Random, 256, NULL, &ulEncryptedLen);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密长度成功!\n");

	ret = SKF_Encrypt(hkey, Random, 256, encryptedData, &ulEncryptedLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECB加密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB加密成功!\n");
	printf("ECB加密时长：\n");
	sprintf(ucTime,"%.3f",duration);

	//ECB解密
	start_t = clock();
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB解密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB解密初始化成功!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, NULL, &dataLen);
	if (ret != SAR_OK)
	{
		printf("获得ECB解密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB解密长度成功!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, pulDataBytes, &dataLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECB解密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB解密成功!\n");

	printf("ECB解密时长：\n");
	sprintf(ucTime,"%.3f",duration);

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB单步数据加解密失败!\n");
			return !SAR_OK;
		}
	}else {
		printf("ECB单步数据加解密成功!\n");
	}

	return SAR_OK;
}

ULONG En_DeUpdate(DEVHANDLE hDev,HANDLE hkey)
{
	ULONG ret;
	BYTE Random[1024] = {0};
	ULONG RandomLen;

	BYTE encryptedData[1024] = {0},pulDataBytes[1024] = {0};
	ULONG ulEncryptedLen,dataLen;
	ULONG templen, outlen1,outlen2,finallen;
	BLOCKCIPHERPARAM encrptPara;
	memset((void *)&encrptPara, 0x00, sizeof(BLOCKCIPHERPARAM));

	printf(" =================>单步数据加密多步数据解密!\n");

	//1.生成随机数
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("生成随机数失败%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" 生成随机数成功!\n");


	//ECB加密
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB加密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB加密初始化成功!\n");

	ret = SKF_Encrypt(hkey, Random, 256, NULL, &ulEncryptedLen);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密长度成功!\n");

	ret = SKF_Encrypt(hkey, Random, 256, encryptedData, &ulEncryptedLen);
	if (ret != SAR_OK)
	{
		printf("ECB加密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB加密成功!\n");

	//ECB解密
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB解密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB解密初始化成功!\n");

	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("获得ECB解密部分长度失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB解密部分长度成功1!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, pulDataBytes, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB部分解密失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分解密成功1!\n");


	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("获得ECB解密部分长度失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB解密部分长度成功2!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, pulDataBytes+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB部分解密失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分解密成功2!\n");

	ret = SKF_DecryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("获得ECB结束解密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB结束解密长度成功!\n");
	ret = SKF_DecryptFinal(hkey, pulDataBytes+outlen1+outlen2, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB结束解密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB结束解密成功!\n");

	dataLen = outlen1+outlen2+finallen;

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB单步数据加密多步数据解密失败!\n");
			return !SAR_OK;
		}
		else {
			printf("ECB单步数据加密多步数据解密成功!\n");
		}
	}
			
	return SAR_OK;
}


ULONG EnUpdate_De(DEVHANDLE hDev, HANDLE hkey)
{
	ULONG ret;
	BYTE Random[1024] = {0};
	ULONG RandomLen;

	BYTE encryptedData[1024] = {0},pulDataBytes[1024] = {0};
	ULONG ulEncryptedLen,dataLen;
	ULONG inlen1, outlen1,outlen2,outlen3,finallen;
	BLOCKCIPHERPARAM encrptPara;
	memset((void *)&encrptPara, 0x00, sizeof(BLOCKCIPHERPARAM));

	printf(" =================>多步数据加密单步数据解密!\n");

	//1.生成随机数
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("生成随机数失败%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" 生成随机数成功!\n");

	//ECB加密
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB加密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB加密初始化成功!\n");

	
	inlen1 = 256/3;
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密部分长度失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密部分长度成功1!\n");
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, encryptedData, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB部分加密失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分加密成功1!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密部分长度失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密部分长度成功2!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, encryptedData+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB部分加密失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分加密成功2!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, NULL, &outlen3);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密部分长度失败3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密部分长度成功3!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, encryptedData+outlen1+outlen2, &outlen3);
	if (ret != SAR_OK)
	{
		printf("ECB部分加密失败3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分加密成功3!\n");

	ret = SKF_EncryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("获得ECB结束加密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB结束加密长度成功!\n");
	ret = SKF_EncryptFinal(hkey, encryptedData+outlen1+outlen2+outlen3, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB结束加密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB结束加密成功!\n");
	ulEncryptedLen = outlen1+outlen2+outlen3+finallen;


	//ECB解密
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB解密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB解密初始化成功!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, NULL, &dataLen);
	if (ret != SAR_OK)
	{
		printf("获得ECB解密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB解密长度成功!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, pulDataBytes, &dataLen);
	if (ret != SAR_OK)
	{
		printf("ECB解密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB解密成功!\n");

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB多步数据加密单步数据解密失败!\n");
			return !SAR_OK;
		}
		else {
			printf("ECB多步数据加密单步数据解密成功!\n");
		}
	}
	return TRUE;
}

ULONG EnUpdate_DeUpdate(DEVHANDLE hDev, HANDLE hkey)
{
	ULONG ret;
	BYTE Random[1024] = {0};
	ULONG RandomLen;

	BYTE encryptedData[1024] = {0},pulDataBytes[1024] = {0};
	ULONG ulEncryptedLen,dataLen;
	ULONG templen,inlen1, outlen1,outlen2,outlen3,finallen;
	BLOCKCIPHERPARAM encrptPara;
	memset((void *)&encrptPara, 0x00, sizeof(BLOCKCIPHERPARAM));

	printf(" =================>多步数据加密解密!\n");

	//1.生成随机数
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("生成随机数失败%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" 生成随机数成功!\n");

	//ECB加密
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB加密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB加密初始化成功!\n");

	
	inlen1 = 256/3;
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密部分长度失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密部分长度成功1!\n");
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, encryptedData, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB部分加密失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分加密成功1!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密部分长度失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密部分长度成功2!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, encryptedData+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB部分加密失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分加密成功2!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, NULL, &outlen3);
	if (ret != SAR_OK)
	{
		printf("获得ECB加密部分长度失败3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB加密部分长度成功3!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, encryptedData+outlen1+outlen2, &outlen3);
	if (ret != SAR_OK)
	{
		printf("ECB部分加密失败3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分加密成功3!\n");

	ret = SKF_EncryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("获得ECB结束加密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB结束加密长度成功!\n");
	ret = SKF_EncryptFinal(hkey, encryptedData+outlen1+outlen2+outlen3, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB结束加密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB结束加密成功!\n");
	ulEncryptedLen = outlen1+outlen2+outlen3+finallen;


	//ECB解密
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB解密初始化失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB解密初始化成功!\n");

	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("获得ECB解密部分长度失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB解密部分长度成功1!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, pulDataBytes, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB部分解密失败1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分解密成功1!\n");


	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("获得ECB解密部分长度失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB解密部分长度成功2!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, pulDataBytes+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB部分解密失败2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB部分解密成功2!\n");

	ret = SKF_DecryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("获得ECB结束解密长度失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("获得ECB结束解密长度成功!\n");
	ret = SKF_DecryptFinal(hkey, pulDataBytes+outlen1+outlen2, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB结束解密失败%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB结束解密成功!\n");

	dataLen = outlen1+outlen2+finallen;

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB多步数据加密解密失败!\n");
			return !SAR_OK;
		}
		else {
			printf("ECB多步数据加密解密成功!\n");
		}
	}
	
	return SAR_OK;
}


//对称密钥明文导入及加解密
void Test_SKF_SetSymmKey()
{
	ULONG ret,i;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;

	ULONG ulAlgIDs[] = {SGD_SM1_ECB, SGD_SMS4_ECB, SGD_SSF33_ECB};
	HANDLE hkey;
	BYTE Random[16] = {0};
	ULONG RandomLen,len;
	
	clock_t start_t, finish_t;
	double  duration = 0;
	char ucTime[32] = {0};

	printf("开始测试对称密钥明文导入及加解密:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST

	GET_ARRAY_LEN(ulAlgIDs, len);

	for(i=0; i<len; i++)
	{
		//第一步生成随机数
		RandomLen =	16;
		if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
		{ 
			printf("生成随机数失败%08x!\n",ret);
			goto _ERRRET;
		}

		//第二步导入对称密钥
		start_t = clock();
		ret = SKF_SetSymmKey(hDev, Random, ulAlgIDs[i], &hkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf("导入第%d个对称密钥失败%08x!\n",i, ret);
			goto _ERRRET;
		}
		else
			printf(" 导入第%d个对称密钥成功!\n",i);

		printf(" 导入第%d个对称密钥时长：\n",i);
		sprintf(ucTime,"%.3f",duration);

		//第三步加解密测试
		ret = En_DewithoutUpdate(hDev,hkey);
		ret = En_DeUpdate(hDev,hkey);
		ret = EnUpdate_De(hDev,hkey);
		ret = EnUpdate_DeUpdate(hDev,hkey);

		ret = SKF_CloseHandle(hkey);
		if (ret != SAR_OK)
		{
			printf("关闭密钥句柄失败%08x!\n",ret);
			goto _ERRRET;
		}
		else
			printf("关闭密钥句柄成功!\n");
	}
#endif
	
	printf("完成测试对称密钥明文导入及加解密函数!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


//对称密钥生成RSA导出及加解密
void Test_SKF_RSAExportSessionKey()
{
	ULONG ret,i;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	RSAPUBLICKEYBLOB stRsaBlob;
	ULONG ulRsaBlobLen;

	ULONG ulAlgIDs[] = {SGD_SM1_ECB, SGD_SMS4_ECB, SGD_SSF33_ECB};
	HANDLE hkey,hImkey;
	BYTE Random[16] = {0};
	ULONG len;
	BYTE ucEnkeyData[512];
	ULONG ulDataLen=sizeof(ucEnkeyData);

	clock_t start_t, finish_t;
	double  duration = 0;
	char ucTime[32] = {0};
	

	printf("开始测试对称密钥生成RSA导出导入及加解密:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST

	//容器名称con1
	printf("请输入容器名称:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}


	//导出加密公钥
	memset(&stRsaBlob,0,sizeof(stRsaBlob));
	ret = SKF_ExportPublicKey(hCont, FALSE, NULL, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得加密公钥长度失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 获得加密公钥长度成功!\n");


	ret = SKF_ExportPublicKey(hCont, FALSE, (BYTE *)&stRsaBlob, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得加密公钥失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 获得加密公钥成功!\n");

	GET_ARRAY_LEN(ulAlgIDs, len);

	for(i=0; i<len; i++)
	{
		memset(ucEnkeyData,0,sizeof(ucEnkeyData));
		//第一步生成对称密钥
		start_t = clock();
		ret = SKF_RSAExportSessionKey(hCont, ulAlgIDs[i], &stRsaBlob, NULL, &ulDataLen, &hkey);
		if (ret != SAR_OK)
		{
			printf(" 获得第%d个导出对称密钥长度失败%08x!\n",i, ret);
			goto _ERRRET;
		}
		else
			printf(" 获得第%d个导出对称密钥长度成功!\n",i);
		ret = SKF_RSAExportSessionKey(hCont, ulAlgIDs[i], &stRsaBlob, ucEnkeyData, &ulDataLen, &hkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf(" 获得第%d个导出对称密钥失败%08x!\n", i,ret);
			goto _ERRRET;
		}
		else
			printf(" 获得第%d个导出对称密钥成功!\n",i);

		printf(" 第%d个对称密钥生成导出时长:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//第二步导入对称密钥
		start_t = clock();
		ret = SKF_ImportSessionKey(hCont, ulAlgIDs[i], ucEnkeyData, ulDataLen, &hImkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf("导入第%d个加密对称密钥失败%08x!\n",i, ret);
			SKF_CloseHandle(hkey);
			goto _ERRRET;
		}
		else
			printf(" 导入第%d个加密对称密钥成功!\n",i);

		printf(" 第%d个对称密钥加密导入时长:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//第三步加解密测试
		ret = En_DewithoutUpdate(hDev,hkey);
		ret = En_DeUpdate(hDev,hImkey);
		ret = EnUpdate_De(hDev,hImkey);
		ret = EnUpdate_DeUpdate(hDev,hkey);

		SKF_CloseHandle(hkey);
		ret = SKF_CloseHandle(hImkey);
		if (ret != SAR_OK)
		{
			printf("关闭密钥句柄失败%08x!\n",ret);
			goto _ERRRET;
		}
		else
			printf("关闭密钥句柄成功!\n");
	}
#endif
	
	printf("完成测试对称密钥生成RSA导出导入及加解密!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


//对称密钥生成ECC导出及加解密
void Test_SKF_ECCExportSessionKey()
{
	ULONG ret,i;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	ECCPUBLICKEYBLOB stEccBlob;
	ECCCIPHERBLOB stEccCipherBlob;
	ULONG ulEccBlobLen;

	ULONG ulAlgIDs[] = {SGD_SM1_ECB, SGD_SMS4_ECB, SGD_SSF33_ECB};
	HANDLE hkey,hImkey;
	BYTE Random[16] = {0};
	ULONG len;
	BYTE ucEnkeyData[512];
	ULONG ulDataLen=sizeof(ucEnkeyData);

	clock_t start_t, finish_t;
	double  duration = 0;
	char ucTime[32] = {0};
	

	printf("开始测试对称密钥生成ECC导出导入及加解密:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST

	//容器名称con2
	printf("请输入容器名称:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" 打开容器失败%08x!\n", ret);
		goto _ERRRET;
	}

	//导出ECC加密公钥
	memset(&stEccBlob,0,sizeof(stEccBlob));
	ret = SKF_ExportPublicKey(hCont, FALSE, NULL, &ulEccBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得ECC加密公钥长度失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 获得ECC加密公钥长度成功!\n");


	ret = SKF_ExportPublicKey(hCont, FALSE, (BYTE *)&stEccBlob, &ulEccBlobLen);
	if (ret != SAR_OK)
	{
		printf(" 获得ECC加密公钥失败%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" 获得ECC加密公钥成功!\n");

	GET_ARRAY_LEN(ulAlgIDs, len);

	for(i=0; i<len; i++)
	{
		memset(&stEccCipherBlob,0,sizeof(stEccCipherBlob));
		//第一步生成对称密钥
		start_t = clock();
		ret = SKF_ECCExportSessionKey(hCont, ulAlgIDs[i], &stEccBlob, &stEccCipherBlob, &hkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf(" 获得ECC第%d个导出对称密钥失败%08x!\n", i,ret);
			goto _ERRRET;
		}
		else
			printf(" 获得ECC第%d个导出对称密钥成功!\n",i);

		printf(" 第%d个对称密钥生成ECC导出时长:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//第二步导入对称密钥
		start_t = clock();
		ret = SKF_ImportSessionKey(hCont, ulAlgIDs[i], (BYTE *)&stEccCipherBlob, sizeof(stEccCipherBlob), &hImkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf("导入第%d个加密对称密钥失败%08x!\n",i, ret);
			SKF_CloseHandle(hkey);
			goto _ERRRET;
		}
		else
			printf(" 导入第%d个加密对称密钥成功!\n",i);

		printf(" 第%d个对称密钥ECC导入时长:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//第三步加解密测试
		ret = En_DewithoutUpdate(hDev,hkey);
		ret = En_DeUpdate(hDev,hImkey);
		ret = EnUpdate_De(hDev,hImkey);
		ret = EnUpdate_DeUpdate(hDev,hkey);

		SKF_CloseHandle(hkey);
		ret = SKF_CloseHandle(hImkey);
		if (ret != SAR_OK)
		{
			printf("关闭密钥句柄失败%08x!\n",ret);
			goto _ERRRET;
		}
		else
			printf("关闭密钥句柄成功!\n");
	}
#endif
	
	printf("完成测试对称密钥生成ECC导出导入及加解密!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


/*================================================================================
 *=================================流程测试用例===================================
 *===============================================================================*/
DEVHANDLE  m_hDevice = NULL;
HAPPLICATION m_hApp = NULL;
HCONTAINER	 m_hContainer = NULL;
//HSESSION;

UINT8 m_DataforEn[] = {
	0x12, 0x6a, 0x59, 0xf8, 0x73, 0x28, 0xbc, 0x66, 0x2b, 0x3f, 0x93, 0x12, 0xb3, 0x5c, 0x7d, 0x4e,
	0x9e, 0x7c, 0x3b, 0x00, 0xd7, 0x19, 0x60, 0x93, 0x27, 0xd3, 0x04, 0xae, 0xa2, 0xde, 0xd8, 0xa5,
	0x54, 0x03, 0x7e, 0x5d, 0x9d, 0x46, 0x61, 0xe9, 0xba, 0x85, 0xcc, 0xc5, 0x03, 0x34, 0x8f, 0xd7,
	0x40, 0xc6, 0x67, 0x95, 0xc8, 0x0e, 0x0b, 0xc4, 0xe4, 0xaf, 0xb8, 0xf1, 0x08, 0x39, 0x3a, 0xa8,
	0xa1, 0x84, 0x15, 0x61, 0x5c, 0x5b, 0x02, 0xa6, 0x42, 0x5e, 0x47, 0xa5, 0x56, 0xb9, 0xcb, 0xc6,
	0x8b, 0xb9, 0x9c, 0x05, 0xf8, 0x32, 0x42, 0x2d, 0x65, 0xaf, 0xb3, 0xe9, 0xa9, 0x0b, 0xd6, 0xaa,
	0xb6, 0x4c, 0x26, 0x96, 0xa7, 0x89, 0x9e, 0xdf, 0xff, 0x1d, 0x21, 0xc9, 0xb8, 0x59, 0x34, 0x64,
	0x65, 0xc8, 0xb6, 0xf1, 0x6c, 0xc4, 0x4e, 0xa7, 0xab, 0x37, 0x9e, 0x79, 0x7c, 0xfe, 0xf8, 0x38,
	0x62, 0x98, 0x49, 0x1f, 0xdd, 0xc3, 0x70, 0x56, 0x48, 0x69, 0x12, 0xae, 0x1f, 0x77, 0xb5, 0x98,
	0x24, 0x0f, 0x93, 0x33, 0x62, 0x98, 0x49, 0x1f, 0xdd, 0xc3, 0x70, 0x56, 0x62, 0x98, 0x49, 0x1f,
	0x9e, 0x7c, 0x3b, 0x00, 0xd7, 0x19, 0x60, 0x93, 0x27, 0xd3, 0x04, 0xae, 0xa2, 0xde, 0xd8, 0xa5,
	0x54, 0x03, 0x7e, 0x5d, 0x9d, 0x46, 0x61, 0xe9, 0xba, 0x85, 0xcc, 0xc5, 0x03, 0x34, 0x8f, 0xd7,
	0x40, 0xc6, 0x67, 0x95, 0xc8, 0x0e, 0x0b, 0xc4, 0xe4, 0xaf, 0xb8, 0xf1, 0x08, 0x39, 0x3a, 0xa8,
	0xa1, 0x84, 0x15, 0x61, 0x5c, 0x5b, 0x02, 0xa6, 0x42, 0x5e, 0x47, 0xa5, 0x56, 0xb9, 0xcb, 0xc6,
	0x8b, 0xb9, 0x9c, 0x05, 0xf8, 0x32, 0x42, 0x2d, 0x65, 0xaf, 0xb3, 0xe9, 0xa9, 0x0b, 0xd6, 0xaa,
	0xb6, 0x4c, 0x26, 0x96, 0xa7, 0x89, 0x9e, 0xdf, 0xff, 0x1d, 0x21, 0xc9, 0xb8, 0x59, 0x34, 0x64,
	0x65, 0xc8, 0xb6, 0xf1, 0x6c, 0xc4, 0x4e, 0xa7, 0xab, 0x37, 0x9e, 0x79, 0x7c, 0xfe, 0xf8, 0x38	
};

UINT8 m_DataforSign[] = {
	0x05, 0xab, 0x60, 0x76, 0x2e, 0x05, 0x9e, 0x88, 0x58, 0x84, 0x1e, 0x3c, 0x3f, 0x2a, 0xe3, 0x7b,
	0xb0, 0x21, 0x93, 0x56, 0xff, 0xf9, 0x17, 0xdf, 0x26, 0xd6, 0x49, 0x94, 0xed, 0x76, 0x47, 0xc1,
	0x12, 0x74, 0x62, 0xd7, 0x71, 0xc2, 0x06, 0x36, 0x76, 0xee, 0xa2, 0x8f, 0x82, 0x6d, 0x37, 0x6c,
	0xd7, 0x69, 0x48, 0x9f, 0x0c, 0xb7, 0x9d, 0x67, 0x34, 0x50, 0xe9, 0x57, 0x70, 0x89, 0xda, 0xb7,
	0x04, 0x47, 0xb5, 0x9a, 0x71, 0x14, 0x7a, 0x00, 0x57, 0xf9, 0xa5, 0xbd, 0xf6, 0x1d, 0xca, 0x93,
	0x9e, 0x7c, 0x3b
};

UINT8 m_SignData[512] = {0};
UINT8 m_EnData[512] = {0};
static ULONG mSignLen,mEnLen;

BYTE m_IV[32] = {0};
BYTE m_EnDataforSym[512] = {0};
static ULONG mIVLen, mEnDataLen;

BYTE m_randKey[16] = {0};
void EnwithSymKey(DEVHANDLE hDev, HANDLE hkey, BYTE flag, BYTE * pbData, ULONG ulDataLen) 
{
	ULONG ret;
	ULONG cLen, i;
	BYTE* pDst;
	BLOCKCIPHERPARAM encryptPara;

	ulDataLen = ulDataLen/16*16;

	//设置加密参数
	memset((void *)&encryptPara, 0x00, sizeof(BLOCKCIPHERPARAM));
	if(flag)
	{
		memcpy(encryptPara.IV, m_IV, mIVLen);
		encryptPara.IVLen = mIVLen;
		//encryptPara.PaddingType = 1;
		//IV
		pDst = m_IV;
		cLen = mIVLen;
		printf("IV =");
		for (i = 0; i < cLen; i++)
		{
			printf("%02x", *pDst++);
		}
		printf("\n");
	}


	//打印
	//Data
	pDst = pbData;
	cLen = ulDataLen;
	printf("DataBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//加密
	ret = SKF_EncryptInit(hkey, encryptPara);
	if (ret != SAR_OK)
	{
		printf("SKF_EncryptInit ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}

	ret = SKF_Encrypt(hkey, pbData, ulDataLen, NULL, &mEnDataLen);
	if (ret != SAR_OK)
	{
		printf("SKF_Encrypt get length ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}

	ret = SKF_Encrypt(hkey, pbData, ulDataLen, m_EnDataforSym, &mEnDataLen);
	if (ret != SAR_OK)
	{
		printf("SKF_Encrypt ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}
	
	//打印
	pDst = m_EnDataforSym;
	cLen = mEnDataLen;
	printf("EncryptDataBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	printf("SKF_Encrypt OK.\n");
	return;
	
}

void DewithSymKey(DEVHANDLE hDev, HANDLE hkey, BYTE flag)
{
	ULONG ret;

	BYTE DataBytes[1024] = {0};
	ULONG dataLen;
	BLOCKCIPHERPARAM encryptPara;

	ULONG cLen, i;
	BYTE* pDst;

	//设置解密参数
	memset((void *)&encryptPara, 0x00, sizeof(BLOCKCIPHERPARAM));
	if(flag)
	{
		memcpy(encryptPara.IV, m_IV, mIVLen);
		encryptPara.IVLen = mIVLen;
		//encryptPara.PaddingType = 1;

		//IV
		pDst = m_IV;
		cLen = mIVLen;
		printf("IV =");
		for (i = 0; i < cLen; i++)
		{
			printf("%02x", *pDst++);
		}
		printf("\n");
	}

	//打印
	//EncryptDataBlob
	pDst = m_EnDataforSym;
	cLen = mEnDataLen;
	printf("EncryptDataBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");


	//ECB解密
	ret = SKF_DecryptInit(hkey, encryptPara);
	if (ret != SAR_OK)
	{
		printf("SKF_DecryptInit ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}

	ret = SKF_Decrypt(hkey, m_EnDataforSym, mEnDataLen, NULL, &dataLen);
	if (ret != SAR_OK)
	{
		printf("SKF_Decrypt get length ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}

	ret = SKF_Decrypt(hkey, m_EnDataforSym, mEnDataLen, DataBytes, &dataLen);
	if (ret != SAR_OK)
	{
		printf("SKF_Decrypt ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}


	//打印
	pDst = DataBytes;
	cLen = dataLen;
	printf("DeDataBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	printf("SKF_Decrypt OK.\n");

	return;
}

void Test_Flow_EncryptwithSymKey()
{
	BYTE randPaint[64] = {0};
	HANDLE  hKey;

	ULONG ulAlgID;
	int choose;
	ULONG result;

	ULONG cLen, i;
	BYTE* pDst;

	if (m_hDevice == NULL)
	{
		printf("No device opened, please open device first!\n");
		return;
	}

	//
	printf("请选则算法: \n");
	printf("0-SM1_ECB, 1-SM1_CBC, 2-SSF33_ECB, 3-SSF33_CBC, 4-SM4_ECB, 5-SM4_CBC\n");
	scanf("%d", &choose);

	switch (choose)
	{
	case 0:
		ulAlgID = SGD_SM1_ECB;
		break;
	case 1:
		ulAlgID = SGD_SM1_CBC;
		break;
	case 2:
		ulAlgID = SGD_SSF33_ECB;
		break;
	case 3:
		ulAlgID = SGD_SSF33_CBC;
		break;
	case 4:
		ulAlgID = SGD_SMS4_ECB;
		break;
	case 5:
		ulAlgID = SGD_SMS4_CBC;
		break;
	default:
		printf("算法选择错误!\n");
		return;
	}

	//填充IV
	if ((result = SKF_GenRandom(m_hDevice, m_IV, 16)) != SAR_OK)
	{
		printf("SKF_GenRandom 0 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	mIVLen = 16;

	//产生16字节随机密钥并保存
	if ((result = SKF_GenRandom(m_hDevice, m_randKey, 16)) != SAR_OK)
	{
		printf("SKF_GenRandom 1 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	
	//生成密钥句柄
	if ((result = SKF_SetSymmKey(m_hDevice, m_randKey, ulAlgID, &hKey)) != SAR_OK)
	{
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		return;
	}

	//产生64字节明文
	if ((result = SKF_GenRandom(m_hDevice, randPaint, 64)) != SAR_OK)
	{ 
		printf("SKF_GenRandom 2 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	printf("开始执行64字节明文加密:\n");

	//打印
	pDst = m_randKey;
	cLen = 16;
	printf("SYMKEY =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	EnwithSymKey(m_hDevice, hKey, choose%2, randPaint, 64);
}

void Test_Flow_DecryptwithSymKey()
{
	HANDLE  hKey;
	ULONG ulAlgID;
	int choose;
	ULONG result;

	ULONG cLen, i;
	BYTE* pDst;
	
	if (m_hDevice == NULL)
	{
		printf("No device opened, please open device first!\n");
		return;
	}
	
	//
	printf("请选则算法: \n");
	printf("0-SM1_ECB, 1-SM1_CBC, 2-SSF33_ECB, 3-SSF33_CBC, 4-SM4_ECB, 5-SM4_CBC\n");
	scanf("%d", &choose);
	
	switch (choose)
	{
	case 0:
		ulAlgID = SGD_SM1_ECB;
		break;
	case 1:
		ulAlgID = SGD_SM1_CBC;
		break;
	case 2:
		ulAlgID = SGD_SSF33_ECB;
		break;
	case 3:
		ulAlgID = SGD_SSF33_CBC;
		break;
	case 4:
		ulAlgID = SGD_SMS4_ECB;
		break;
	case 5:
		ulAlgID = SGD_SMS4_CBC;
		break;
	default:
		printf("算法选择错误!\n");
		return;
	}
	
	//生成密钥句柄
	if ((result = SKF_SetSymmKey(m_hDevice, m_randKey, ulAlgID, &hKey)) != SAR_OK)
	{
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		return;
	}
	
	printf("开始执行64字节密文解密:\n");

	//打印
	pDst = m_randKey;
	cLen = 16;
	printf("SYMKEY =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	DewithSymKey(m_hDevice, hKey, choose%2);
}

void Test_Flow_EnumOpenCloseDev()
{
	ULONG ret;
	ULONG size;
	ULONG len;
	char* pName;
	
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);

#if LIB_EXIST
	//枚举设备
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("SKF_EnumDev ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}
	else
	{
		printf("SKF_EnumDev OK.\n");
		if (size > 0)
		{
			pName = m_NameBuffer;
			while (*pName)
			{
				printf("caDevName:%s\n", pName);
				len = strlen(pName);
				pName += (len + 1);
			}	
		}
	}

	//打开设备
	ret = SKF_ConnectDev(m_NameBuffer, &m_hDevice);
	if(ret != SAR_OK)
	{
		printf("SKF_ConnectDev ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}
	else
	{
		printf("SKF_ConnectDev OK.\n");
	}

	//关闭设备不打印
	ret = SKF_DisConnectDev(m_hDevice);
	if (ret != SAR_OK)
	{
		printf("SKF_DisConnectDev ERROR:%s\n", errorInfo[ret&0xff].error);
	}

	//再次打开设备不打印
	ret = SKF_ConnectDev(m_NameBuffer, &m_hDevice);
	if(ret != SAR_OK)
	{
		printf("SKF_ConnectDev ERROR:%s\n", errorInfo[ret&0xff].error);
	}

#endif
}


void Test_Flow_GetDevInfo()
{
	ULONG ret;
	DEVINFO sDevInfo;
	
	if (m_hDevice == NULL)
	{
		printf("No device opened, Please Open Device first!");
		return;
	}

#if LIB_EXIST	
	ret = SKF_GetDevInfo(m_hDevice, &sDevInfo);
	if (ret != SAR_OK)
	{
		printf("SKF_GetDevInfo ERROR:%s\n", errorInfo[ret&0xff].error);
		return;
	}
	else
	{
		printf("SKF_GetDevInfo OK.\n");
		printf(" 数据结构版本:Version %d.%d\n", sDevInfo.Version.major, sDevInfo.Version.minor);
		printf(" 设备厂商信息:%s\n", sDevInfo.Manufacturer);
		printf(" 发行厂商信息:%s\n", sDevInfo.Issuer);
		printf(" 设备标签:%s\n", sDevInfo.Label);
		printf(" 序列号:%s\n", sDevInfo.SerialNumber);
		printf(" 设备硬件版本:HWVer %d.%d\n", sDevInfo.HWVersion.major, sDevInfo.HWVersion.minor);
		printf(" 设备固件版本:FWVer %d.%d\n", sDevInfo.FirmwareVersion.major, sDevInfo.FirmwareVersion.minor);
		printf(" 分组密码算法标识:%08x\n", sDevInfo.AlgSymCap);
		printf(" 非对称密码算法标识:%08x\n", sDevInfo.AlgAsymCap);
		printf(" 密码杂凑算法标识:%08x\n", sDevInfo.AlgHashCap);
		printf(" 设备认证分组密码算法标识:%08x\n", sDevInfo.DevAuthAlgId);
		printf(" 设备总空间大小:%ld\n", sDevInfo.TotalSpace);
		printf(" 用户可用空间大小:%ld\n", sDevInfo.FreeSpace);
		printf(" 保留扩展:----------\n");
	}
#endif
}


void Test_Flow_EnumApp()
{
	ULONG result = 0;
	CHAR *pBuffer = NULL;
	ULONG pulSize = 0;
	CHAR *pStart = NULL;
	
	if (m_hDevice == NULL)
	{
		printf("No device opened, Please Open Device first!\n");
		return;
	}

#if LIB_EXIST
	if ((result = SKF_EnumApplication(m_hDevice, NULL, &pulSize)) != SAR_OK)
	{
		printf("SKF_EnumApplication 1 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	
	pBuffer = (CHAR *)malloc(pulSize);
	memset(pBuffer, 0, pulSize);
	if ((result = SKF_EnumApplication(m_hDevice, pBuffer, &pulSize)) != SAR_OK)
	{
		printf("SKF_EnumApplication 2 ERROR:%s\n", errorInfo[result&0xff].error);
		free(pBuffer);
		return;
	}
	
	//显示所有app列表
	printf("SKF_EnumApplication OK.");
	pStart = pBuffer;
	while (*pStart)
	{
		printf("%s,",pStart);
		pStart += (strlen(pStart) + 1);
	}
	free(pBuffer);
	
	printf("\n");
#endif
}


static void _OpenAPPContainer(char* appNamp, char* contName)
{
	ULONG result;
	char* pBuffer = NULL;
	ULONG size;
	char* pStart;

#if LIB_EXIST
	//打开应用
	result = SKF_OpenApplication(m_hDevice, appNamp, &m_hApp);
	if (result != SAR_OK)
	{
		printf("SKF_OpenApplication  ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
	{
		printf("SKF_OpenApplication ok.\n");
	}

	//枚举容器
	result = SKF_EnumContainer(m_hApp, NULL, &size);
	if (result != SAR_OK)
	{
		printf("SKF_EnumContainer  ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	pBuffer = (CHAR *)malloc(size);
	memset(pBuffer, 0, size);	
	result = SKF_EnumContainer(m_hApp, m_NameBuffer, &size);
	if (result != SAR_OK)
	{
		printf("SKF_EnumContainer  ERROR:%s\n", errorInfo[result&0xff].error);
		free(pBuffer);
		return;
	}
	else
	{
		//显示所有container列表	
		printf("SKF_EnumContainer ok.\n");
		pStart = pBuffer;
		while (*pStart)
		{
			printf("caCntName:%s\n", pStart);
			pStart += (strlen(pStart) + 1);
		}
		free(pBuffer);
	}

	//打开容器
	result = SKF_OpenContainer(m_hApp, contName, &m_hContainer);
	if (result != SAR_OK)
	{
		printf("SKF_OpenContainer  ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
	{
		printf("SKF_OpenContainer ok.\n");
	}
#endif
}


void Test_Flow_OpenSM2AppCont()
{
	char* appName = "SM2";
	char* contName = "SM2CONTAINER";
	_OpenAPPContainer(appName, contName);
}


void Test_Flow_OpenRSA2048appCont()
{
	char* appName = "RSA2048";
	char* contName = "RSA2048CONTAINER";
	_OpenAPPContainer(appName, contName);
}


void Test_Flow_OpenRSA1024appCont()
{
	char* appName = "RSA1024";
	char* contName = "RSA1024CONTAINER";
	_OpenAPPContainer(appName, contName);
}


void Test_Flow_VerifyPIN()
{
	ULONG result;
	ULONG remainretrycount;
	ULONG pintype;
	char arrPIN[10] = {0};
	
	printf("Please input user's pin:");
	scanf("%s", arrPIN);
	
	pintype = USER_TYPE;
	
	if ((result = SKF_VerifyPIN(m_hApp, pintype, arrPIN, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_VerifyPIN  ERROR:%s  剩余重试次数=%d \n", errorInfo[result&0xff].error, remainretrycount);
	}
	else
	{
		printf("VerifyPIN OK.\n");
	}
}


void Test_Flow_ChangeUserPIN()
{
	ULONG result;
	ULONG retrycount;
	ULONG pintype;
	char arrOldPIN[10] = {0};
	char arrNewPIN[10] = {0};
	
	printf("Please input user's old pin:");
	scanf("%s", arrOldPIN);
	
	printf("Please input user's new pin:");
	scanf("%s", arrNewPIN);
	
	pintype = USER_TYPE;
	if ((result = SKF_ChangePIN(m_hApp, pintype, arrOldPIN, arrNewPIN, &retrycount)) != SAR_OK)
	{
		printf("SKF_ChangePIN  ERROR:%s  retrycount=%d\n", errorInfo[result&0xff].error, retrycount);
	}
	else
	{	
		printf("SKF_ChangePIN ok.\n");
	}
}


void Test_Flow_ExportCertificate()
{
	ULONG result;
	BYTE* pBuffer = NULL;
	ULONG cLen = 4096*2, i;
	BYTE* pDst;
	
	if (m_hContainer == NULL)
	{
		printf("No container opened, Please Open first!\n");
		return;
	}

#if LIB_EXIST	//导出签名证书
	//第一步：获取长度
	result = SKF_ExportCertificate(m_hContainer, TRUE,  NULL, &cLen);
	printf("SKF_ExportCertificate cLen = %x\n",cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCertificate Signed 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	
	//第二步：获取内容
	pBuffer = (BYTE*)malloc(cLen);
	memset(pBuffer, 0, cLen);
	result = SKF_ExportCertificate(m_hContainer, TRUE,  pBuffer, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCertificate Signed 2 ERROR:%s\n", errorInfo[result&0xff].error);
		free(pBuffer);
		return;
	} 
	else
	{
		printf("SKF_ExportCertificate Signed ok.\n");
	}

	//打印
	pDst = pBuffer;
	printf("sign data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	free(pBuffer);
	pBuffer = NULL;
#endif
	
#if LIB_EXIST	//导出加密证书
	//第一步：获取长度
	result = SKF_ExportCertificate(m_hContainer, FALSE,  NULL, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCertificate Encrypt 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	
	//第二步：获取内容
	pBuffer = (BYTE*)malloc(cLen);
	memset(pBuffer, 0, cLen);
	result = SKF_ExportCertificate(m_hContainer, FALSE,  pBuffer, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCertificate Encrypt 2 ERROR:%s\n", errorInfo[result&0xff].error);
		free(pBuffer);
		return;
	} 
	else
	{
		printf("SKF_ExportCertificate Encrypt ok.\n");
	}
	
	//打印
	pDst = pBuffer;
	printf("encrypt data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	free(pBuffer);
#endif

#if LIB_EXIST	//导出ca证书
	//第一步：获取长度
	result = SKF_ExportCACertificate(m_hContainer, NULL, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCACertificate 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	
	//第二步：获取内容
	pBuffer = (BYTE*)malloc(cLen);
	memset(pBuffer, 0, cLen);
	result = SKF_ExportCACertificate(m_hContainer, pBuffer, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCACertificate 2 ERROR:%s\n", errorInfo[result&0xff].error);
		free(pBuffer);
		return;
	} 
	else
	{
		printf("SKF_ExportCertificate Signed ok.\n");
	}

	//打印
	pDst = pBuffer;
	printf("sign data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	free(pBuffer);
	pBuffer = NULL;
#endif

}


void Test_Flow_ExitTest()
{
	if (m_hContainer)
	{
		SKF_CloseContainer(m_hContainer);
		m_hContainer = NULL;
	}

	if (m_hApp)
	{
		SKF_CloseApplication(m_hApp);
		m_hApp = NULL;
	}

	if (m_hDevice)
	{
		SKF_DisConnectDev(m_hDevice);
		SKF_CloseHandle(m_hDevice);
		m_hDevice = NULL;
	}
}

void Test_Flow_ExportPublickey()
{
	ULONG result;

	BYTE* pBuffer = NULL;
	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST
	//第一步：获取签名公钥
	result = SKF_ExportPublicKey(m_hContainer, TRUE, NULL, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Sign Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	pBuffer = (BYTE*)malloc(cLen);
	memset(pBuffer, 0, cLen);
	result = SKF_ExportPublicKey(m_hContainer, TRUE, pBuffer, &cLen);
	if (result != SAR_OK)
	{
		free(pBuffer);
		printf("SKF_ExportPublicKey Sign ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
		printf("SKF_ExportPublicKey Sign ok.\n");

	//打印
	pDst = pBuffer;
	printf("Sign pubkey data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");
	free(pBuffer);
	pBuffer = NULL;

#endif
	
#if LIB_EXIST
	//第二步：获取加密公钥
	result = SKF_ExportPublicKey(m_hContainer, FALSE, NULL, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Encrypt Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	pBuffer = (BYTE*)malloc(cLen);
	memset(pBuffer, 0, cLen);
	result = SKF_ExportPublicKey(m_hContainer, FALSE, pBuffer, &cLen);
	if (result != SAR_OK)
	{
		free(pBuffer);
		printf("SKF_ExportPublicKey Encrypt ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
		printf("SKF_ExportPublicKey Encrypt ok.\n");

	//打印
	pDst = pBuffer;
	printf("Encrypt pubkey data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	free(pBuffer);
	pBuffer = NULL;
#endif	

}
void Test_Flow_RsaSignData()
{
	ULONG result;

	BYTE Hash[32] = {0};
	ULONG ulDataLen,ulHashLen;
	HANDLE hHash;
	ULONG signLen;


	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST

	ulDataLen = sizeof(m_DataforSign);
	
	//打印
	pDst = m_DataforSign;
	cLen = ulDataLen;
	printf("orData=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第一步：计算摘要
	result =  SKF_DigestInit(m_hDevice, SGD_SHA1, NULL, NULL, 0, &hHash);
	if (result != SAR_OK)
	{
		printf("SKF_DigestInit ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
//	printf("SKF_DigestInit result = %x\n",result);
	ulHashLen = sizeof(Hash);
//	printf("SKF_Digest len = %x\n",ulHashLen);
	result = SKF_Digest(hHash, m_DataforSign, ulDataLen,Hash,&ulHashLen);
	if (result != SAR_OK)
	{
		printf("SKF_Digest ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
//	printf("SKF_Digest result = %x\n",result);

	//第二步：签名
	result = SKF_RSASignData(m_hContainer, Hash, ulHashLen, NULL, &signLen);
	if (result != SAR_OK)
	{
		printf("SKF_RSASignData get Sign length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
//	printf("SKF_RSASignData Len result = %x signLen = %x\n",result,signLen);
		
	result = SKF_RSASignData(m_hContainer, Hash, ulHashLen, m_SignData, &signLen);
	if (result != SAR_OK)
	{
		printf("SKF_RSASignData ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
	{
		mSignLen = signLen;
		printf("SKF_RSASignData ok.\n");
	}
	//打印
	pDst = m_SignData;
	cLen = mSignLen;
	printf("SignBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");	
#endif

}

void Test_Flow_RSAVerify()
{
	ULONG result;

	BYTE Hash[32] = {0};
	ULONG ulDataLen,ulHashLen;
	HANDLE hHash;
	RSAPUBLICKEYBLOB stRsaBlob;
	ULONG ulRsaBlobLen;

	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST
	//第一步：导出验签公钥
	memset(&stRsaBlob,0,sizeof(stRsaBlob));
	result = SKF_ExportPublicKey(m_hContainer, TRUE, NULL, &ulRsaBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Sign Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	result = SKF_ExportPublicKey(m_hContainer, TRUE, (BYTE *)&stRsaBlob, &ulRsaBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey Sign ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
		printf("SKF_ExportPublicKey Sign ok.\n");

	//打印
	pDst = (BYTE *)&stRsaBlob;
	cLen = ulRsaBlobLen;
	printf("Sign pubkey data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第二步：计算摘要
	result =  SKF_DigestInit(m_hDevice, SGD_SHA1, NULL, NULL, 0, &hHash);
	if (result != SAR_OK)
	{
		printf("SKF_DigestInit ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	ulHashLen = sizeof(Hash);
	ulDataLen = sizeof(m_DataforSign);
	result = SKF_Digest(hHash, m_DataforSign, ulDataLen,Hash,&ulHashLen);
	if (result != SAR_OK)
	{
		printf("SKF_Digest ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	
	//第三步：验签
	result = SKF_RSAVerify(m_hDevice, &stRsaBlob, Hash, ulHashLen, m_SignData, mSignLen);
	if (result != SAR_OK)
	{
		printf("SKF_RSAVerify ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
	{
		printf("SKF_RSAVerify ok.\n");
	}
	
#endif


}
void Test_Flow_ECCSignData()
{
	ULONG result;

	BYTE DefID[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	BYTE Hash[32] = {0};
	ULONG ulDataLen,ulHashLen;
	HANDLE hHash;
	ECCPUBLICKEYBLOB stEccBlob;
	ULONG ulEccBlobLen;
	//ECCSIGNATUREBLOB stEccSign;


	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST

	ulDataLen = sizeof(m_DataforSign);
	
	//打印
	pDst = m_DataforSign;
	cLen = ulDataLen;
	printf("orData=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第一步：导出签名公钥
	memset(&stEccBlob,0,sizeof(stEccBlob));
	result = SKF_ExportPublicKey(m_hContainer, TRUE, NULL, &ulEccBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Sign Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	result = SKF_ExportPublicKey(m_hContainer, TRUE, (BYTE *)&stEccBlob, &ulEccBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey Sign ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}


	//第一步：计算摘要
	result =  SKF_DigestInit(m_hDevice, SGD_SM3, &stEccBlob, DefID, sizeof(DefID), &hHash);
	if (result != SAR_OK)
	{
		printf("SKF_DigestInit ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	ulHashLen = sizeof(Hash);
	result = SKF_Digest(hHash, m_DataforSign, ulDataLen,Hash,&ulHashLen);
	if (result != SAR_OK)
	{
		printf("SKF_Digest ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	//第二步：签名
	result = SKF_ECCSignData(m_hContainer, Hash, ulHashLen, (PECCSIGNATUREBLOB)m_SignData);
	if (result != SAR_OK)
	{
		printf("SKF_ECCSignData ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
	{
		printf("SKF_ECCSignData ok.\n");
	}
	//打印
	pDst = m_SignData;
	cLen = sizeof(ECCSIGNATUREBLOB);
	printf("SignBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");	
#endif

}
void Test_Flow_ECCVerify()
{
	ULONG result;

	BYTE DefID[] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};
	BYTE Hash[32] = {0};
	ULONG ulDataLen,ulHashLen;
	HANDLE hHash;
	ECCPUBLICKEYBLOB stEccBlob;
	ULONG ulEccBlobLen;

	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST
	//第一步：导出验签公钥
	memset(&stEccBlob,0,sizeof(stEccBlob));
	result = SKF_ExportPublicKey(m_hContainer, TRUE, NULL, &ulEccBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Sign Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	result = SKF_ExportPublicKey(m_hContainer, TRUE, (BYTE *)&stEccBlob, &ulEccBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey Sign ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
		printf("SKF_ExportPublicKey Sign ok.\n");

	//打印
	pDst = (BYTE *)&stEccBlob;
	cLen = ulEccBlobLen;
	printf("Sign pubkey data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第二步：计算摘要
	result =  SKF_DigestInit(m_hDevice, SGD_SM3, &stEccBlob, DefID, sizeof(DefID), &hHash);
	if (result != SAR_OK)
	{
		printf("SKF_DigestInit ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	ulHashLen = sizeof(Hash);
	ulDataLen = sizeof(m_DataforSign);
	result = SKF_Digest(hHash, m_DataforSign, ulDataLen,Hash,&ulHashLen);
	if (result != SAR_OK)
	{
		printf("SKF_Digest ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	
	//第三步：验签
	result = SKF_ECCVerify(m_hDevice, &stEccBlob, Hash, ulHashLen, (PECCSIGNATUREBLOB)m_SignData);
	if (result != SAR_OK)
	{
		printf("SKF_ECCVerify ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
	{
		printf("SKF_ECCVerify ok.\n");
	}
	
#endif

}
void Test_Flow_ExtRSAOperatDecrypt()
{

	ULONG result;
	RSAPUBLICKEYBLOB stRsaBlob;
	ULONG ulRsaBlobLen;
	ULONG ulDataLen;
	BYTE ucOutData[512],ucDeData[512];
	ULONG uloutLen = 512;

	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST

	//第一步：导出加密公钥
	memset(&stRsaBlob,0,sizeof(stRsaBlob));
	result = SKF_ExportPublicKey(m_hContainer, FALSE, NULL, &ulRsaBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Sign Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	result = SKF_ExportPublicKey(m_hContainer, FALSE, (BYTE *)&stRsaBlob, &ulRsaBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey Sign ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	else
		printf("SKF_ExportPublicKey Sign ok.\n");

	//打印
	pDst = (BYTE *)&stRsaBlob;
	cLen = ulRsaBlobLen;
	printf("En pubkey =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第二步：外部公钥加密
	//ulDataLen = sizeof(m_DataforEn);
//	ulDataLen = stRsaBlob.BitLen/8;
	ulDataLen = 112;

	//打印
	pDst = m_DataforEn;
	cLen = ulDataLen;
	printf("DataToRSAEncrpt=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//result = SKF_ExtRSAPubKeyOperation(m_hDevice, &stRsaBlob, m_DataforEn, ulDataLen, NULL, &uloutLen);
	//if (result != SAR_OK)
	//{
	//	printf("uloutlen = %d,ulDataLen = %d\n",uloutLen,ulDataLen);
	//	printf("SKF_ExtRSAPubKeyOperation get EnData length ERROR:%s\n", errorInfo[result&0xff].error);
	//	return;
	//}
	memset(ucOutData,0,sizeof(ucOutData));
	result = SKF_ExtRSAPubKeyOperation(m_hDevice, &stRsaBlob, m_DataforEn, ulDataLen, ucOutData, &uloutLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExtRSAPubKeyOperation ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	//打印
	pDst = ucOutData;
	cLen = uloutLen;
	printf("EncryResult =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第三步：私钥解密
	ulDataLen = stRsaBlob.BitLen/8;
	memset(ucDeData,0,sizeof(ucDeData));
	result = SKF_RSADecrypt(m_hContainer, ucOutData, uloutLen, ucDeData, &ulDataLen);
	if (result != SAR_OK)
	{
		printf("oloutLen = %d,ulDataLen = %d,result = %08x\n",uloutLen,ulDataLen,result);
		printf("SKF_RSADecrypt ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	//打印
	pDst = ucDeData;
	cLen = ulDataLen;
	printf("DecryResult =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");	
#endif

}
void Test_Flow_ExtECCEncryptDecrypt()
{
	ULONG result;

	ULONG ulDataLen;
	BYTE ucDeData[512];
	BYTE pCipher;
	
	BYTE pTempCipher[2048] = {0};

	ECCPUBLICKEYBLOB stEccBlob;
	ULONG ulEccBlobLen;
	ECCCIPHERBLOB  *stEccCipherBlob = (ECCCIPHERBLOB *)pTempCipher;

	ULONG cLen, i;
	BYTE* pDst;

	if (m_hContainer == NULL)
	{
		printf("No container open,Please Open App&Container!");
		return;
	}
	
#if LIB_EXIST
	//第一步：导出加密公钥
	memset(&stEccBlob,0,sizeof(stEccBlob));
	result = SKF_ExportPublicKey(m_hContainer, FALSE, NULL, &ulEccBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey get Sign Publickey Length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	result = SKF_ExportPublicKey(m_hContainer, FALSE, (BYTE *)&stEccBlob, &ulEccBlobLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportPublicKey Sign ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	
	//打印
	pDst = (BYTE *)&stEccBlob;
	cLen = ulEccBlobLen;
	printf("En pubkey =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//第二步：外部公钥加密
	ulDataLen = sizeof(m_DataforEn);
//	ulDataLen = 32;
	
	//打印
	pDst = m_DataforEn;
	cLen = ulDataLen;
	printf("baDataToEccEncrpt= len = %x",ulDataLen);
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

//	memset(&stEccCipherBlob,0,sizeof(stEccCipherBlob));
	result = SKF_ExtECCEncrypt(m_hDevice, &stEccBlob, m_DataforEn, ulDataLen, stEccCipherBlob);
	if (result != SAR_OK)
	{
		printf("SKF_ExtECCEncrypt ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	//打印
	pDst = (BYTE *)stEccCipherBlob;
	cLen = sizeof(ECCCIPHERBLOB) + ulDataLen;
	printf("EncryResult =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	ulDataLen = 2048;
	//第三步：私钥解密
	result = SKF_ECCDecrypt(m_hContainer, stEccCipherBlob, NULL, &ulDataLen);
	if (result != SAR_OK)
	{
		printf("SKF_ECCDecrypt get EnData length ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	memset(ucDeData,0,sizeof(ucDeData));
	result = SKF_ECCDecrypt(m_hContainer, stEccCipherBlob, ucDeData, &ulDataLen);
	if (result != SAR_OK)
	{
		printf("SKF_ECCDecrypt ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	//打印
	pDst = ucDeData;
	cLen = ulDataLen;
	printf("DecryResult =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");
#endif

}






