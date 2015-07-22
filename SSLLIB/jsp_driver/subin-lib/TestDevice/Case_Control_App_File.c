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
	
	{ SAR_OK,/*0x00000000*/"�ɹ�"},
	{ SAR_FAIL,/*0x0A000001*/"ʧ��"},
	{ SAR_UNKNOWNERR,/*0x0A000002*/"�쳣����"},
	{ SAR_NOTSUPPORTYETERR,/*0x0A000003*/"��֧�ֵķ���"},
	{ SAR_FILEERR,/*0x0A000004*/"�ļ���������"},
	{ SAR_INVALIDHANDLEERR,/*0x0A000005*/"��Ч�ľ��"},
	{ SAR_INVALIDPARAMERR,/*0x0A000006*/"��Ч�Ĳ���"},
	{ SAR_READFILEERR,/*0x0A000007*/"���ļ�����"},
	{ SAR_WRITEFILEERR,/*0x0A000008*/"д�ļ�����"},
	{ SAR_NAMELENERR,/*0x0A000009*/"���Ƴ��ȴ���"},
	{ SAR_KEYUSAGEERR,/*0x0A00000A*/"��Կ��;����"},
	{ SAR_MODULUSLENERR,/*0x0A00000B*/"ģ�ĳ��ȴ���"},
	{ SAR_NOTINITIALIZEERR,/*0x0A00000C*/"δ��ʼ��"},
	{ SAR_OBJERR,/*0x0A00000D*/"�������"},
	{ SAR_MEMORYERR,/*0x0A00000E*/"�ڴ����"},
	{ SAR_TIMEOUTERR,/*0x0A00000F*/"��ʱ"},
	{ SAR_INDATALENERR,/*0x0A000010*/"�������ݳ��ȴ���"},
	{ SAR_INDATAERR,/*0x0A000011*/"�������ݴ���"},
	{ SAR_GENRANDERR,/*0x0A000012*/"�������������"},
	{ SAR_HASHOBJERR,/*0x0A000013*/"HASH�����"},
	{ SAR_HASHERR,/*0x0A000014*/"HASH�������"},
	{ SAR_GENRSAKEYERR,/*0x0A000015*/"����RSA��Կ��"},
	{ SAR_RSAMODULUSLENERR,/*0x0A000016*/"RSA��Կģ������"},
	{ SAR_CSPIMPRTPUBKEYERR,/*0x0A000017*/"CSP�����빫Կ����"},
	{ SAR_RSAENCERR,/*0x0A000018*/"RSA���ܴ���"},
	{ SAR_RSADECERR,/*0x0A000019*/"RSA���ܴ���"},
	{ SAR_HASHNOTEQUALERR,/*0x0A00001A*/"HASHֵ�����"},
	{ SAR_KEYNOTFOUNTERR,/*0x0A00001B*/"��Կδ����"},
	{ SAR_CERTNOTFOUNTERR,/*0x0A00001C*/"֤��δ����"},
	{ SAR_NOTEXPORTERR,/*0x0A00001D*/"����δ����"},
	{ SAR_DECRYPTPADERR,/*0x0A00001E*/"����ʱ����������"},
	{ SAR_MACLENERR,/*0x0A00001F*/"MAC���ȴ���"},
	{ SAR_BUFFER_TOO_SMALL,/*0x0A000020*/"����������"},
	{ SAR_KEYINFOTYPEERR,/*0x0A000021*/"��Կ���ʹ���"},
	{ SAR_NOT_EVENTERR,/*0x0A000022*/"���¼�����"},
	{ SAR_DEVICE_REMOVED,/*0x0A000023*/"�豸���Ƴ�"},
	{ SAR_PIN_INCORRECT,/*0x0A000024*/"PIN����ȷ"},
	{ SAR_PIN_LOCKED,/*0x0A000025*/"PIN������"},
	{ SAR_PIN_INVALID,/*0x0A000026*/"PIN��Ч"},
	{ SAR_PIN_LEN_RANGE,/*0x0A000027*/"PIN���ȴ���"},
	{ SAR_USER_ALREADY_LOGGED_IN,/*0x0A000028*/"�û��Ѿ���¼"},
	{ SAR_USER_PIN_NOT_INITIALIZED,/*0x0A000029*/"û�г�ʼ���û�����"},
	{ SAR_USER_TYPE_INVALID,/*0x0A00002A*/"PIN���ʹ���"},
	{ SAR_APPLICATION_NAME_INVALID,/*0x0A00002B*/"Ӧ��������Ч"},
	{ SAR_APPLICATION_EXISTS,/*0x0A00002C*/"Ӧ���Ѿ�����"},
	{ SAR_USER_NOT_LOGGED_IN,/*0x0A00002D*/"�û�û�е�¼"},
	{ SAR_APPLICATION_NOT_EXISTS,/*0x0A00002E*/"Ӧ�ò�����"},
	{ SAR_FILE_ALREADY_EXIST,/*0x0A00002F*/"�ļ��Ѿ�����"},
	{ SAR_NO_ROOM,/*0x0A000030*/"�ռ䲻��"},
	{ SAR_FILE_NOT_EXIST,/*0x0A000031*/"�ļ�������"},
	{ SAR_REACH_MAX_CONTAINER_COUNT,/*0x0A000032*/"�Ѵﵽ���ɹ���������"}
};

#define DEVAPI  __stdcall
//#define DEVAPI

/*================================================================================
 *=================================DLL�����ʼ��==================================
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

	//ö���豸
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

	//ȡ��һ���豸����
	if(strlen((const char *)pBuffer)==0)
	{ 
		printf("û�з����豸\n");
		goto _ERRRET;
	}


	//���豸
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
	 *���� �豸��֤ʹ�õķ��������㷨��ʶ ѡ���㷨 Ȼ���������� �����֤
	 */

	//1.��ȡ�豸��Ϣ
	if ((result = SKF_GetDevInfo(hDev, &hDevInfo)) != SAR_OK)
	{
		printf("SKF_GetDevInfo   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//2.���ĵ���Ự��Կ
	printf("������16�ֽ��豸��֤��Կ:");
	scanf("%s", key);			//��ʼ����ԿΪ1234567812345678
	if ((result = SKF_SetSymmKey(hDev, key, hDevInfo.DevAuthAlgId, &hKey)) != SAR_OK)
	{
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//3.ȡ�����
	RandomLen = 8;
	if ((result = SKF_GenRandom(hDev, Random, RandomLen)) != SAR_OK)
	{ 
		printf("SKF_GenRandom   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//4.���������ʼ��
	memset(&BlockParam, 0, sizeof(BLOCKCIPHERPARAM));
	if ((result = SKF_EncryptInit(hKey, BlockParam)) != SAR_OK)
	{ 
		printf("SKF_EncryptInit   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//5.�����������
	memcpy(paintData, Random, 8);
	paintDataLen = 16;
	if ((result = SKF_Encrypt(hKey, paintData, paintDataLen, cryptData, &cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_Encrypt   ERROR:%s\n",errorInfo[result&0xff].error);
		return !SAR_OK;
	}
	
	//6.��֤
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
	
	printf("������Ҫ�򿪵�Ӧ������:");
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
	
	printf("������Ҫ�򿪵�Ӧ������:");
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

	printf("����8�ֽ�PIN��:");
	scanf("%s", arrPIN);

_RETRYPIN:
	printf("\n����PIN������(0--admin;1--user):");
	scanf("%d", &pintype);
	if (ADMIN_TYPE != pintype && USER_TYPE != pintype)
	{
		printf("�������Ͳ���ȷ!");
		goto _RETRYPIN;
	}

	if ((result = SKF_VerifyPIN(hAPP, pintype, arrPIN, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_VerifyPIN  ERROR:%s  ʣ�����Դ���=%d \n", errorInfo[result&0xff].error,remainretrycount);		
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

//���ʿ���ϵ��
void Test_SKF_DevAuth()
{
	char *pDesc = "����ͨ���豸��֤��������豸�ڴ�����ɾ��Ӧ�á�\n"	\
	"�豸��֤ʹ�÷��������㷨���豸��֤��Կ���С���֤���������£�\n"	\
	"1)����֤������SKF_GenRandom�������豸��ȡ8�ֽ������RND������0x00��������������㷨�ķֿ鳤�ȣ�������ݿ�D0��\n"	\
	"2)����֤����D0���ܣ��õ����ܽ��D1��������SKF_DevAuth()����D1�������豸��\n"	\
	"3)�豸�յ�D1����֤D1�Ƿ���ȷ����ȷ��ͨ���豸��֤�������豸��֤ʧ�ܡ�\n";

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

	//��ȡ�豸��Ϣ
	if ((result = SKF_GetDevInfo(hDev, &hDevInfo)) != SAR_OK)
	{
		printf("SKF_GetDevInfo   ERROR:%s\n",errorInfo[result&0xff].error);
		_CloseDev(hDev);
		return ;
	}

	//���� �豸��֤ʹ�õķ��������㷨��ʶ ѡ���㷨
	//���ĵ���Ự��Կ 
	//memset(key, 0, 16);
	//memcpy(key, "1234567812345678", 16);	//��ʼ����Կ
	printf(" �������豸��֤��Կ(16�ֽ�):");
	scanf("%s", key);
	printf("\n");
	if ((result = SKF_SetSymmKey(hDev, key, hDevInfo.DevAuthAlgId, &hKey)) != SAR_OK)
	{ 
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		_CloseDev(hDev);
		return ;
	}
	
	//�����������
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

	//���������ʼ��
	if ((result = SKF_EncryptInit(hKey, BlockParam)) != SAR_OK)
	{ 
		printf("SKF_EncryptInit   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	//�����������
	paintDataLen = 16;
	if ((result = SKF_Encrypt(hKey, paintData, paintDataLen, cryptData, &cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_Encrypt   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	//��֤
	if((result = SKF_DevAuth(hDev, cryptData, cryptDataLen)) != SAR_OK)
	{ 
		printf("SKF_DevAuth   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	else
	{
		printf(" �豸��֤ͨ��!\n");
	}
// 	if((result = SKF_CloseHandle(hKey))!=SAR_OK)
// 	{ 
// 		printf("SKF_CloseHandle  ERROR:%s\n",errorInfo[result&0xff].error);
// 		_CloseDev(hDev);
// 		return;
// 	}

	printf("�������\n");
	
_ERRRET:	
	_CloseDev(hDev);
}

//�����޸�PIN
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

	printf("����PIN������(0--admin;1--user):");
	scanf("%d", &pintype);

	printf("\n����8�ֽھ�PIN��:");
	scanf("%s", arrOldPIN);

	printf("\n����8�ֽ���PIN��:");
	scanf("%s", arrNewPIN);

	if ((result = SKF_ChangePIN(hApp, pintype, arrOldPIN, arrNewPIN, &retrycount)) != SAR_OK)
	{
		printf("SKF_ChangePIN  ERROR:%s  retrycount=%d\n",errorInfo[result&0xff].error,retrycount);
		goto _ERRRET;
	}
	else
	{	
		printf("ʹ�ù���ԱȨ�� �޸ĳɹ�\n");
	}
	
	printf("ʹ���û�Ȩ��\n");
	if ((result = SKF_ChangePIN(hApp, USER_TYPE, "22222222", "aaaaaaaa", &retrycount)) != SAR_OK)
	{
		printf("SKF_ChangePIN  ERROR:%s  retrycount=%d\n",errorInfo[result&0xff].error,retrycount);		
		goto _ERRRET;
	}
	else
	{		
		printf("ʹ���û�Ȩ�� �޸ĳɹ�\n");
	}

	printf("�������\n");

_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//������֤PIN
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
	
	printf("����8�ֽ�PIN��:");
	scanf("%s", arrPIN);

	printf("\n����PIN������(0--admin;1--user):");
	scanf("%d", &pintype);

	if ((result = SKF_VerifyPIN(hApp, pintype, arrPIN, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_VerifyPIN  ERROR:%s  ʣ�����Դ���=%d \n", errorInfo[result&0xff].error,remainretrycount);		
		goto _ERRRET;
	}
	else
	{
		printf("У��PIN��ɹ�!\n");
	}
	
	printf("�������\n");
	
_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//���Խ���PIN
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
	
	printf("���������ԱPIN:");
	scanf("%s", arrADMPin);
	printf("\n���������û�PIN:");
	scanf("%s", arrUSRPin);

	if ((result = SKF_UnblockPIN(hApp, arrADMPin, arrUSRPin, &remainretrycount)) != SAR_OK)
	{
		printf("SKF_UnblockPIN  ERROR:%s  ʣ�����Դ���=%d \n",errorInfo[result&0xff].error,remainretrycount);
	}
	else
	{
		printf("\n ����PIN�ɹ�!\n");
	}

	printf("�������\n");

	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//�����޸��豸��֤��Կ
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
	printf("û����֤��ֱ���޸���֤��Կ:\n\n");
	printf("��������Կ����:");
	scanf("%d", &keyLen);
	printf("\n����������Կ:");
	scanf("%s", keyData);
	if ((result = SKF_ChangeDevAuthKey(hDev, (BYTE *)keyData, keyLen)) != SAR_OK)
	{ 
		printf(" SKF_ChangeDevAuthKey   ERROR:%s\n",errorInfo[result&0xff].error);
	} 
	else
	{		
		printf(" �޸���֤��Կ�ɹ�\n");
	}


	//case2	
	printf("\n��֤�����޸���֤��Կ:\n");
	if (_DevAuth(&hDev) != SAR_OK)
	{
		goto _ERRRET;
	}

	memset(keyData, 0, sizeof(keyData));
	printf("��������Կ����:");
	scanf("%d", &keyLen);
	printf("\n����������Կ:");
	scanf("%s", keyData);
	if ((result = SKF_ChangeDevAuthKey(hDev, (BYTE *)keyData, keyLen)) != SAR_OK)
	{ 
		printf(" SKF_ChangeDevAuthKey   ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	} 
	else
	{
		printf(" �޸���֤��Կ�ɹ�\n");
	}
	
	printf("�������\n");

_ERRRET:
	_CloseDev(hDev);
}

//���������ȫ״̬
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
		printf(" �����ȫ״̬�ɹ�!\n");
	}
	
	printf("�������\n");
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//���Ի�ȡPIN��Ϣ
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
		printf(" PIN��Ϣ����:\n");
		printf(" maxretrycount=%d\n remainretrycount=%d\n �Ƿ�Ĭ��pin=%s\n", maxretrycount,remainretrycount, (isdefaultPin ? "��" : "��"));
	}
	
	printf("�������\n");
	_CloseAPP(hApp);
	_CloseDev(hDev);
}


//Ӧ�ù���ϵ��
//���Դ���Ӧ��
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
	printf("���Բ���֤����1��APP:\n");
	printf("Ȩ�����ͣ���������; Ӧ������:app0, ����Աpin:00000000, �������:3; �û�pin:99999999, �������5\n");
	if ((result = SKF_CreateApplication(hDev, "app0", "00000000", 3, "99999999", 5, SECURE_NEVER_ACCOUNT, &hApp0)) != SAR_OK)
	{ 
		printf("SKF_CreateApplication  ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{ 
		printf(" ����app0ִ�гɹ�\n");
		if ((result = SKF_CloseApplication(hApp0)) != SAR_OK)
		{ 
			printf("SKF_CloseApplication  ERROR:%s\n",errorInfo[result&0xff].error);
		}
		else
		{
			printf(" �ر�app0ִ�гɹ�\n");
		}
	}

	//case2
	printf("������֤�󴴽�������APP[����ԱPINĬ��11111111,���3������;�û�PINĬ��Ϊ22222222,���5������]:\n");
	if (_DevAuth(hDev) != SAR_OK)
	{
		_CloseDev(hDev);
		return;
	}

_RETRY:
	printf("������Ӧ������:");
	memset(appName, 0, sizeof(appName));
	scanf("%s", appName);
	printf("\n������Ȩ������(0-������1-����ԱȨ��16-�û�Ȩ��255-�κ���):");
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
		printf("SKF_CreateApplication appִ�гɹ�\n");
	}
	printf("\n�˳�����0������������������ֵ:");
	scanf("%d", &quit);
	if (quit)
	{
		goto _RETRY;
	}

_ERRRET:
	_CloseDev(hDev);
	
	printf("�������\n");
}

//����ö��Ӧ��
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
	
	//��ʾ����app�б�
	printf("ö��Ӧ��:\n");
	pStart = pBuffer;
	while (*pStart)
	{
		printf("%s\n",pStart);
		pStart += (strlen(pStart) + 1);
	}
	free(pBuffer);

	printf("\n�������\n");

_ERRRET:
	_CloseDev(hDev);
}

//����ɾ��Ӧ��
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

	printf("��������Ҫɾ����Ӧ������:");
	scanf("%s", appName);
  
	//case1
	printf(" û����֤��ֱ��ɾ��...\n");
	if ((result = SKF_DeleteApplication(hDev, appName)) != SAR_OK)
	{
		printf("SKF_DeleteApplication 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" ֱ��ɾ���ɹ�!\n");
	}
	 
	//case2
	printf(" ������֤��ɾ��Ӧ��..\n");
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
		printf(" ��֤��ɾ��Ӧ�óɹ�!\n");
	}
	
	_CloseDev(hDev);
	
	printf("�������\n");
	
	return;
}

//���Դ򿪹ر�Ӧ��
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

	printf("��������Ҫ�򿪵�Ӧ������:");
	scanf("%s", appName);	
	
	if ((result = SKF_OpenApplication(hDev, appName, &hApp)) != SAR_OK)
	{
		printf("SKF_OpenApplication  ERROR:%s\n",errorInfo[result&0xff].error);
		goto _ERRRET;
	}

	printf("\n��Ӧ�óɹ�\n");
	
	if ((result = SKF_CloseApplication(hApp)) != SAR_OK)
	{
		printf("SKF_CloseApplication  ERROR:%s\n",errorInfo[result&0xff].error);		
		goto _ERRRET;
	}
	
	printf("\n�ر�Ӧ�óɹ�\n");
	printf("�������\n");

_ERRRET:
	_CloseDev(hDev);
}


//�ļ�����ϵ��
//���Դ����ļ�
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
	printf("�������ļ���:");
	memset(fileName, 0, sizeof(fileName));
	scanf("%s", fileName);
	printf("\n�������ļ���С(<32K):");
	scanf("%d", &fileSize);
	printf("\n�������Ȩ������(0-������1-����ԱȨ��16-�û�Ȩ��255-�κ���):");
	scanf("%d", &readRight);
	printf("\n������дȨ������(0-������1-����ԱȨ��16-�û�Ȩ��255-�κ���):");
	scanf("%d", &writeRight);

	if ((result = SKF_CreateFile(hApp, fileName, fileSize, readRight, writeRight)) != SAR_OK)
	{ 
		printf(" SKF_CreateFile  ERROR:%s\n",errorInfo[result&0xff].error);
	}
	else
	{
		printf(" ����file�ɹ�\n");
	}

	//
	printf("\n�˳�����0������������������ֵ:");
	scanf("%d", &quit);
	if (quit)
	{
		goto _RETRY;
	}


	_CloseAPP(hApp);
	_CloseDev(hDev);
	
	printf("�������\n");
}

//����ɾ���ļ�
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

		
	printf("��Ҫɾ�����ļ�����:");
	scanf("%s", fileName);
	
	if ((result = SKF_DeleteFile(hApp, fileName)) != SAR_OK)
	{
		printf("SKF_DeleteFile  ERROR:%s\n",errorInfo[result&0xff].error);
	}
	
	_CloseAPP(hApp);
	_CloseDev(hDev);
	
	printf("�������\n");
}

//���Զ��ļ�
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

	printf("������Ҫ��ȡ���ļ�����:");
	scanf("%s", fileName);
	printf("������Ҫ��ȡ�ĳ���:");
	scanf("%d", &wantLen);
	dataBufferLen = 32*1024;
	if ((result = SKF_ReadFile(hApp, fileName,/*offset*/0, wantLen, dataBuffer, &dataBufferLen)) != SAR_OK)
	{
		printf(" SKF_ReadFile  ERROR:%s\n", errorInfo[result&0xff].error);
		goto _ERRRET;
	}
	else
	{
		printf(" ��ȡ%s��ʵ�ʳ���Ϊ%d,����Ϊ:\n", fileName, dataBufferLen);
		for (i = 0; i < dataBufferLen; i++)
		{
			printf("%02x ", dataBuffer[i]);
		}
		printf("\n");
	}

	printf("�������\n");
	
_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//����д�ļ�
static void GetRandomData(BYTE* pData, ULONG lDataLen)
{
	ULONG n;

	srand((int)time(0));	//��ʱ�����������ӣ�ʹÿ�β���������һ��
	for (n = 0; n < lDataLen; n++)
	{
		pData[n] = rand()%256;		//����0-255����
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

	printf("������Ҫд����ļ�����:");
	scanf("%s", fileName);
	printf("\n������������ݳ���:");
	scanf("%d", &wantLen);

	memset(dataBuffer, 0, 32*1024);
	GetRandomData(dataBuffer, wantLen);

	if ((result = SKF_WriteFile(hApp, fileName,/*offset*/0, dataBuffer, wantLen)) != SAR_OK)
	{
		printf("SKF_WriteFile  ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" ��%s��д��%d�ֽ����ݳɹ�:\n", fileName, wantLen);
		for (i = 0; i < wantLen; i++)
		{
			printf("%02x ", dataBuffer[i]);
		}
		printf("\n");
	}
	
	_CloseAPP(hApp);
	_CloseDev(hDev);
}

//����ö���ļ�
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
		//��ʾ����file�б�
		printf(" ö���ļ�:\n");
	}
	else
	{
		printf(" û�з����ļ�!\n");
	}

	pStart = pBuffer;
	while(*pStart)
	{
		printf("%s\n", pStart);
		pStart += (strlen(pStart) +1);
	}
	free(pBuffer);
	printf("�������\n");
	
_ERRRET:
	_CloseAPP(hApp);
	_CloseDev(hDev);

}

//���Ի�ȡ�ļ���Ϣ
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
	
	printf("��Ҫ��ȡ���ļ�����:");
	scanf("%s", fileName);

	memset(&fileInfo, 0, sizeof(FILEATTRIBUTE));
	if((result = SKF_GetFileInfo(hApp, fileName, &fileInfo)) != SAR_OK)
	{
		printf("SKF_GetFileInfo  ERROR:%s\n", errorInfo[result&0xff].error);
	}
	else
	{
		printf(" ��ȡ��Ϣ�ɹ�:\n");
		printf(" FileName:%s\n FileSize:%d \n ReadRights:%X\n WriteRights:%X\n",
				fileInfo.FileName, fileInfo.FileSize, fileInfo.ReadRights, fileInfo.WriteRights);
	}

	_CloseAPP(hApp);
	_CloseDev(hDev);
	
	printf("�������\n");
	
	return;
}

//====================================================================================//
//====================================================================================//
//====================================================================================//

#define     LIB_EXIST				1
#define		NAME_BUFFER_SIZE		256
#define     DEFAULT_NAME_INDEX		1
static char m_NameBuffer[NAME_BUFFER_SIZE];

//����ö���豸
void Test_SKF_EnumDev()
{
	ULONG ret;
	ULONG size;
	ULONG len;
	char* pName;

	printf("��ʼ����ö���豸����:\n");
	
	//condition1.
	printf("���Ի�ȡ��ǰ�豸״̬Ϊ���ڵ��豸�б�...\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" �����豸�б���Ϊ:%d\n", size);
		if (size > 0)
		{
			printf(" �����豸�б�����Ϊ: \n");
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
	printf("���Ի�ȡ��ǰ����֧�ֵ��豸�б�...\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(FALSE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" �����豸�б���Ϊ:%d\n", size);
		if (size > 0)
		{
			printf(" �����豸�б�����Ϊ: \n");
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

	printf("��ɲ���ö���豸����!\n");
}


//���������豸��Ͽ��豸
void Test_SKF_ConnectDev_DisconnectDev()
{
	ULONG ret;
	ULONG size;
	char* pName;
	DEVHANDLE hDevice;

	printf("��ʼ����������Ͽ��豸����:\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("ö���豸ʧ��%08x\n", ret);
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
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" �����豸���Ϊ: %08x\n", hDevice);
	}

	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("�Ͽ�����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
#endif

	printf("��ɲ���������Ͽ��豸����!\n");
}

//���Ի�ȡ�豸״̬
void Test_SKF_GetDevState()
{
	ULONG ret;
	ULONG size;
	ULONG status;
	char* pName;

	printf("��ʼ���Ի�ȡ�豸״̬����:\n");
	size = NAME_BUFFER_SIZE;
	memset(m_NameBuffer, 0, size);
#if LIB_EXIST
	ret = SKF_EnumDev(TRUE, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("ö���豸ʧ��%08x\n", ret);
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
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		switch (status)
		{
		case DEV_ABSENT_STATE:
			printf(" �豸������\n");
			break;
		case DEV_PRESENT_STATE:
			printf(" �豸����\n");
			break;
		case DEV_UNKNOW_STATE:
			printf(" �豸״̬δ֪\n");
			break;
		default:
			printf(" �����״̬��!\n");
			break;
		}
	}
#endif

	printf("��ɲ��Ի�ȡ�豸״̬����!\n");
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

//���Ի�ȡ�豸��Ϣ
void Test_SKF_GetDevInfo()
{
	ULONG ret;
	DEVHANDLE hDevice;
	DEVINFO sDevInfo;
	
	printf("��ʼ���Ի�ȡ�豸��Ϣ����:\n");
	if (!GetDefaultDevHandle(&hDevice))
	{
		printf("�����豸ʧ��!\n");
		return;
	}

#if LIB_EXIST	
	ret = SKF_GetDevInfo(hDevice, &sDevInfo);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" ���ݽṹ�汾:Version %d.%d\n", sDevInfo.Version.major, sDevInfo.Version.minor);
		printf(" �豸������Ϣ:%s\n", sDevInfo.Manufacturer);
		printf(" ���г�����Ϣ:%s\n", sDevInfo.Issuer);
		printf(" �豸��ǩ:%s\n", sDevInfo.Label);
		printf(" ���к�:%s\n", sDevInfo.SerialNumber);
		printf(" �豸Ӳ���汾:HWVer %d.%d\n", sDevInfo.HWVersion.major, sDevInfo.HWVersion.minor);
		printf(" �豸�̼��汾:FWVer %d.%d\n", sDevInfo.FirmwareVersion.major, sDevInfo.FirmwareVersion.minor);
		printf(" ���������㷨��ʶ:%08x\n", sDevInfo.AlgSymCap);
		printf(" �ǶԳ������㷨��ʶ:%08x\n", sDevInfo.AlgAsymCap);
		printf(" �����Ӵ��㷨��ʶ:%08x\n", sDevInfo.AlgHashCap);
		printf(" �豸��֤���������㷨��ʶ:%08x\n", sDevInfo.DevAuthAlgId);
		printf(" �豸�ܿռ��С:%ld\n", sDevInfo.TotalSpace);
		printf(" �û����ÿռ��С:%ld\n", sDevInfo.FreeSpace);
		printf(" ������չ:----------\n");
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("�Ͽ�����ʧ��%08x!\n", ret);
		return;
	}
#endif
	
	printf("��ɲ��Ի�ȡ�豸��Ϣ����!\n");
}

//���������豸��ǩ
void Test_SKF_SetLabel()
{
	ULONG ret;
	DEVHANDLE hDevice;
	char strLab[32] = {0};

	printf("��ʼ���������豸��ǩ����:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("�����豸ʧ��!\n");
		return;
	}

#if LIB_EXIST
	printf(" �������ǩ��:\n");
	scanf("%s", strLab);
	ret = SKF_SetLabel(hDevice, strLab);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" �������豸��ǩ��Ϊ%s!\n", strLab);
		// readback label
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("�Ͽ�����ʧ��%08x!\n", ret);
		return;
	}
#endif
	
	printf("��ɲ��������豸��ǩ����!\n");
}

//���������豸
void Test_SKF_LockDev()
{
	ULONG ret;
	ULONG time;
	DEVHANDLE hDevice;

	printf("��ʼ���������豸����:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("�����豸ʧ��!\n");
		return;
	}

#if LIB_EXIST	
	time = 60000;	//һ����
	ret = SKF_LockDev(hDevice, time);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" �����豸%d��!\n", time);
		//do other operation
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("�Ͽ�����ʧ��%08x!\n", ret);
		return;
	}
#endif

	printf("��ɲ��������豸����!\n");
}

//���Խ����豸
void Test_SKF_UnlockDev()
{
	ULONG ret;
	DEVHANDLE hDevice;

	printf("��ʼ���Խ����豸����:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("�����豸ʧ��!\n");
		return;
	}

#if LIB_EXIST
	ret = SKF_UnlockDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" �����豸�ɹ�!\n");
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("�Ͽ�����ʧ��%08x!\n", ret);
		return;
	}
#endif
	
	printf("��ɲ��Խ����豸����!\n");
}

//�����豸�����
void Test_SKF_Transmit()
{
	ULONG ret;
	DEVHANDLE hDevice;
	BYTE cmd[10] = {0};
	BYTE data[40] = {0};
	ULONG dLen;

	printf("��ʼ�����豸����亯��:\n");
	if ( !GetDefaultDevHandle(&hDevice) )
	{
		printf("�����豸ʧ��!\n");
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
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
		return;
	}
	else
	{
		printf(" ����س���%d!\n", dLen);
		printf(" ��������Ϊ%s\n", data);
	}
	
	ret = SKF_DisConnectDev(hDevice);
	if (ret != SAR_OK)
	{
		printf("�Ͽ�����ʧ��%08x!\n", ret);
		return;
	}
#endif
	
	printf("��ɲ����豸����亯��!\n");
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

//���Դ�������
void Test_SKF_CreateContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	printf("��ʼ���Դ�����������:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}

	if (_CheckPin(hAPP) != SAR_OK)
	{
		return;
	}

	printf("��������������:\n");
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
		printf(" ���������ɹ������Ϊ%08x!\n", hCont);
	}
#endif

	printf("��ɲ��Դ�����������!\n");
	_CloseContain(hCont);

_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//����ɾ������
void Test_SKF_DeleteContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	char strContName[64] = {0};

	printf("��ʼ����ɾ����������:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}

	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
	printf("��������������:\n");
	scanf("%s", strContName);
	
#if LIB_EXIST
	ret = SKF_DeleteContainer(hAPP, strContName);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
	}
	else
	{
		printf(" ����ɾ���ɹ�!\n");
	}
#endif
	
	printf("��ɲ���ɾ����������!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//����ö������
void Test_SKF_EnumContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	char strContName[64] = {0};
	ULONG size, len;
	char* pName;

	printf("��ʼ����ö����������:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
	/*printf("��������������:\n");
	scanf("%s", strContName);*/
	
	//condition1.
	printf("����ֻ��ȡ��������...\n");
#if LIB_EXIST
	ret = SKF_EnumContainer (hAPP, NULL, &size);
	if (ret != SAR_OK)
	{
		printf("����CASE1ʧ��, ������Ϊ%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" �����豸�б���Ϊ:%d\n", size);
	}
#endif

	//condition2.
	printf("���Ի�ȡָ�����ȵ���������...\n");
#if LIB_EXIST
	if (size > NAME_BUFFER_SIZE)
	{
		printf("WARNING: buffer�ռ䲻��\n");
		goto _ERRRET;
	}
	memset(m_NameBuffer, 0, size);
	ret = SKF_EnumContainer (hAPP, m_NameBuffer, &size);
	if (ret != SAR_OK)
	{
		printf("����CASE2ʧ��, ������Ϊ%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" �����豸�б���Ϊ:%d\n", size);
		if (size > 0)
		{
			printf(" �����豸�б�����Ϊ: \n");
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
	
	printf("��ɲ���ö����������!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//���Դ򿪺͹ر�����
void Test_SKF_OpenContainer_CloseContainer()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	printf("��ʼ���Դ򿪹ر���������:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}
	
	printf("��������������:\n");
	scanf("%s", strContName);

#if LIB_EXIST
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf("���Դ�ʧ��, ������Ϊ%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" �����������Ϊ:%08x\n", hCont);
	}

	ret = SKF_CloseContainer(hCont);
	if (ret != SAR_OK)
	{
		printf("���Թر�ʧ��, ������Ϊ%08x!\n", ret);
	}
#endif

	printf("��ɲ��Դ򿪹ر���������!\n");

_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//���Ի�ȡ��������
void Test_SKF_GetContianerType()
{
	ULONG ret;
	ULONG type;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};

	printf("��ʼ���Ի�ȡ�������ͺ���:\n");
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
		printf(" ������ʧ��%08x!\n", ret);
		goto _ERRRET;
	}

//	ret = SKF_GetContianerType(hCont, &type);
	if (ret != SAR_OK)
	{
		printf("����ʧ��, ������Ϊ%08x!\n", ret);
	} 
	else
	{
		switch (type)
		{
		case 0:
			printf(" δ���������\n");
			break;
		case 1:
			printf(" RSA����\n");
			break;
		case 2:
			printf(" ECC����\n");
			break;
		default:
			printf(" �����������!\n");
			break;
		}
	}
#endif

	printf("��ɲ��Ի�ȡ�������ͺ���!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//���Ե���֤��
void Test_SKF_ImportCertificate()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	BYTE strCert[128] = {0};
	
	printf("��ʼ���Ե���֤�麯��:\n");
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
		printf(" ������ʧ��%08x!\n", ret);
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
		printf("����ʧ��, ������Ϊ%08x\n", ret);
	} 
	else
	{
		printf("����֤��ɹ�!");
	}
#endif
	
	printf("��ɲ��Ե���֤�麯��!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}

//���Ե���֤��
void Test_SKF_ExportCertificate()
{
	ULONG ret;
	DEVHANDLE hDev;
	HAPPLICATION hAPP;
	HCONTAINER hCont;
	char strContName[64] = {0};
	BYTE strCert[128] = {0};
	ULONG cLen;

	printf("��ʼ���Ե���֤�麯��:\n");
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
		printf(" ������ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	
	//��һ������ȡ����
	ret = SKF_ExportCertificate(hCont, TRUE,  NULL, &cLen);
	if (ret != SAR_OK)
	{
		printf("���Ի�ȡ֤�鳤��ʧ��, ������Ϊ%08x\n", ret);
		_CloseContain(hCont);
		goto _ERRRET;
	} 
	else
	{
		printf(" ����֤�鳤��Ϊ%d!", cLen);
	}
	
	//�ڶ�������ȡ����
	if (cLen > 128)
	{
		printf("WARNING: ����ռ䲻��!\n");
		_CloseContain(hCont);
		goto _ERRRET;
	}
	memset(strCert, 0, 128);
	ret = SKF_ExportCertificate(hCont, TRUE,  strCert, &cLen);
	if (ret != SAR_OK)
	{
		printf("���Ի�ȡ֤������ʧ��, ������Ϊ%08x\n", ret);
	} 
	else
	{
		printf(" ����֤������Ϊ%s!", strCert);
	}
#endif
	
	printf("��ɲ��Ե���֤�麯��!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}



//����RSA���ɵ����Լ�ǩ����ǩ
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

	printf("��ʼ����RSA��˽Կ�����ɵ����Լ�ǩ����ǩ:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST
	//��������con1
	printf("��������������:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" ������ʧ��%08x!\n", ret);
		goto _ERRRET;
	}

	//��һ��������RSAǩ����˽Կ��
	printf("������RSA�㷨����(1-1024 2-2048):");
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
		printf(" ����%dRSA��˽Կ��ʧ��%08x!\n", ulBitsLen,ret);
		goto _ERRRET;
	}
	else
	{
		printf("����%dRSA��˽Կ�Գɹ�!\n", ulBitsLen);
		printf("����%dRSA��˽Կ��ʱ����\n",ulBitsLen);
		sprintf(ucTime,"%.3f",duration);
	}

	//�ڶ�������ǩ����Կ������������Ĺ�Կ�ȶ�
	memset(&stRsaBlob2,0,sizeof(stRsaBlob2));
	start_t = clock();
	ret = SKF_ExportPublicKey(hCont, TRUE, NULL, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ���ǩ����Կ����ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ���ǩ����Կ���ȳɹ�!\n");

	ret = SKF_ExportPublicKey(hCont, TRUE, (BYTE *)&stRsaBlob2, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ���ǩ����Կʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ���ǩ����Կ�ɹ�!\n");

	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	printf("���ǩ����Կʱ����\n");
	sprintf(ucTime,"%.3f",duration);


	//������ǩ����ǩ����
	//1.���������
	RandomLen = 65;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("���������ʧ��%08x!\n",ret);
		goto _ERRRET;
	}

	//2.����ժҪ
	start_t = clock();
	ret =  SKF_DigestInit(hDev, SGD_SHA1, NULL, NULL, 0, &hHash);
	if (ret != SAR_OK)
	{
		printf("ժҪ��ʼ��ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ժҪ��ʼ���ɹ�!\n");

	ulHashLen = sizeof(Hash);
	ret = SKF_Digest(hHash, Random, RandomLen,Hash,&ulHashLen);
	if (ret != SAR_OK)
	{
		printf("ժҪʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ժҪ�ɹ�!\n");

	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	printf("ժҪ����ʱ����\n");
	sprintf(ucTime,"%.3f",duration);
	
	//3.ǩ����ǩ
	start_t = clock();
	ret = SKF_RSASignData(hCont, Hash, ulHashLen, sign, &signLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("RSAǩ��ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("RSAǩ���ɹ�!\n");

	printf("RSAǩ��ʱ����\n");
	sprintf(ucTime,"%.3f",duration);

	start_t = clock();
	ret = SKF_RSAVerify(hDev, &stRsaBlob2, Hash, ulHashLen, sign, signLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("RSA��ǩʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("RSA��ǩ�ɹ�!\n");

	printf("RSA��ǩʱ����\n");
	sprintf(ucTime,"%.3f",duration);


#endif
	
	printf("��ɲ���RSA��˽Կ�����ɵ����Լ�ǩ����ǩ����!\n");

	_CloseContain(hCont);
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


//����ECC���ɵ����Լ�ǩ����ǩ
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

	printf("��ʼ����ecc��˽Կ�����ɵ����Լ�ǩ����ǩ:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST
	//��������con2
	printf("��������������:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" ������ʧ��%08x!\n", ret);
		goto _ERRRET;
	}

	//��һ��������ECCǩ����˽Կ��
	memset(&stEccBlob1,0,sizeof(stEccBlob1));
	start_t = clock();
	ret = SKF_GenECCKeyPair(hCont, SGD_SM2_1, &stEccBlob1);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf(" ����ECC��˽Կ��ʧ��%08x!\n",ret);
		goto _ERRRET;
	}
	else
	{
		printf("����ECC��˽Կ�Գɹ�!\n");
		printf("����ECC��˽Կ��ʱ����\n");
		sprintf(ucTime,"%.3f",duration);
	}

	//�ڶ�������ǩ����Կ������������Ĺ�Կ�ȶ�
	memset(&stEccBlob2,0,sizeof(stEccBlob2));
	ret = SKF_ExportPublicKey(hCont, TRUE, NULL, &ulEccBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ���ǩ����Կ����ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" ���ǩ����Կ���ȳɹ�!\n");
	}

	start_t = clock();
	ret = SKF_ExportPublicKey(hCont, TRUE, (BYTE *)&stEccBlob2, &ulEccBlobLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf(" ���ǩ����Կʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
	{
		printf(" ���ǩ����Կ�ɹ�!\n");
		printf("���ǩ����Կʱ����\n");
		sprintf(ucTime,"%.3f",duration);
	}

	//������ǩ����ǩ����
	//1.���������
	RandomLen = 56;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("���������ʧ��%08x!\n",ret);
		goto _ERRRET;
	}

	//2.����ժҪ
	start_t = clock();
	ret =  SKF_DigestInit(hDev, SGD_SM3, &stEccBlob2, DefID, sizeof(DefID), &hHash);
	if (ret != SAR_OK)
	{
		printf("SM3ժҪ��ʼ��ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ժҪ��ʼ���ɹ�!\n");

	ulHashLen = sizeof(Hash);
	ret = SKF_Digest(hHash, Random, RandomLen,Hash,&ulHashLen);
	if (ret != SAR_OK)
	{
		printf("SM3ժҪʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ժҪ�ɹ�!\n");

	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	printf("SM3ժҪ����ʱ����\n");
	sprintf(ucTime,"%.3f",duration);

	//3.ǩ����ǩ
	start_t = clock();
	ret = SKF_ECCSignData(hCont, Hash, ulHashLen, &stEccSign);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECCǩ��ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("ECCǩ���ɹ�!\n");
	
	printf("ECCǩ��ʱ����\n");
	sprintf(ucTime,"%.3f",duration);

	start_t = clock();
	ret = SKF_ECCVerify(hDev, &stEccBlob1, Hash, ulHashLen, &stEccSign);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECC��ǩʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf("ECC��ǩ�ɹ�!\n");
	printf("ECC��ǩʱ����\n");
	sprintf(ucTime,"%.3f",duration);


#endif
	
	printf("��ɲ���ECC��˽Կ�����ɵ����Լ�ǩ����ǩ����!\n");

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
	printf(" =================>�������ݼӽ���!\n");
	//1.���������
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("���������ʧ��%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" ����������ɹ�!\n");

	//ECB����
	start_t = clock();
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	ret = SKF_Encrypt(hkey, Random, 256, NULL, &ulEncryptedLen);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܳ��ȳɹ�!\n");

	ret = SKF_Encrypt(hkey, Random, 256, encryptedData, &ulEncryptedLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECB����ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳɹ�!\n");
	printf("ECB����ʱ����\n");
	sprintf(ucTime,"%.3f",duration);

	//ECB����
	start_t = clock();
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, NULL, &dataLen);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܳ��ȳɹ�!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, pulDataBytes, &dataLen);
	finish_t = clock();
	duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
	if (ret != SAR_OK)
	{
		printf("ECB����ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳɹ�!\n");

	printf("ECB����ʱ����\n");
	sprintf(ucTime,"%.3f",duration);

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB�������ݼӽ���ʧ��!\n");
			return !SAR_OK;
		}
	}else {
		printf("ECB�������ݼӽ��ܳɹ�!\n");
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

	printf(" =================>�������ݼ��ܶಽ���ݽ���!\n");

	//1.���������
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("���������ʧ��%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" ����������ɹ�!\n");


	//ECB����
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	ret = SKF_Encrypt(hkey, Random, 256, NULL, &ulEncryptedLen);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܳ��ȳɹ�!\n");

	ret = SKF_Encrypt(hkey, Random, 256, encryptedData, &ulEncryptedLen);
	if (ret != SAR_OK)
	{
		printf("ECB����ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳɹ�!\n");

	//ECB����
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�1!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, pulDataBytes, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB���ֽ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ֽ��ܳɹ�1!\n");


	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�2!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, pulDataBytes+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB���ֽ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ֽ��ܳɹ�2!\n");

	ret = SKF_DecryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("���ECB�������ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB�������ܳ��ȳɹ�!\n");
	ret = SKF_DecryptFinal(hkey, pulDataBytes+outlen1+outlen2, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB��������ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB�������ܳɹ�!\n");

	dataLen = outlen1+outlen2+finallen;

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB�������ݼ��ܶಽ���ݽ���ʧ��!\n");
			return !SAR_OK;
		}
		else {
			printf("ECB�������ݼ��ܶಽ���ݽ��ܳɹ�!\n");
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

	printf(" =================>�ಽ���ݼ��ܵ������ݽ���!\n");

	//1.���������
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("���������ʧ��%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" ����������ɹ�!\n");

	//ECB����
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	
	inlen1 = 256/3;
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�1!\n");
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, encryptedData, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB���ּ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ּ��ܳɹ�1!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�2!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, encryptedData+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB���ּ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ּ��ܳɹ�2!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, NULL, &outlen3);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�3!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, encryptedData+outlen1+outlen2, &outlen3);
	if (ret != SAR_OK)
	{
		printf("ECB���ּ���ʧ��3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ּ��ܳɹ�3!\n");

	ret = SKF_EncryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("���ECB�������ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB�������ܳ��ȳɹ�!\n");
	ret = SKF_EncryptFinal(hkey, encryptedData+outlen1+outlen2+outlen3, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB��������ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB�������ܳɹ�!\n");
	ulEncryptedLen = outlen1+outlen2+outlen3+finallen;


	//ECB����
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, NULL, &dataLen);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܳ��ȳɹ�!\n");

	ret = SKF_Decrypt(hkey, encryptedData, ulEncryptedLen, pulDataBytes, &dataLen);
	if (ret != SAR_OK)
	{
		printf("ECB����ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳɹ�!\n");

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB�ಽ���ݼ��ܵ������ݽ���ʧ��!\n");
			return !SAR_OK;
		}
		else {
			printf("ECB�ಽ���ݼ��ܵ������ݽ��ܳɹ�!\n");
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

	printf(" =================>�ಽ���ݼ��ܽ���!\n");

	//1.���������
	RandomLen = 364;
	if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
	{ 
		printf("���������ʧ��%08x!\n",ret);
		return !SAR_OK;
	}
	else
		printf(" ����������ɹ�!\n");

	//ECB����
	ret = SKF_EncryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	
	inlen1 = 256/3;
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�1!\n");
	ret = SKF_EncryptUpdate(hkey, Random, inlen1, encryptedData, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB���ּ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ּ��ܳɹ�1!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�2!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1, inlen1, encryptedData+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB���ּ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ּ��ܳɹ�2!\n");

	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, NULL, &outlen3);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�3!\n");
	ret = SKF_EncryptUpdate(hkey, Random+inlen1+inlen1, 256-inlen1-inlen1, encryptedData+outlen1+outlen2, &outlen3);
	if (ret != SAR_OK)
	{
		printf("ECB���ּ���ʧ��3%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ּ��ܳɹ�3!\n");

	ret = SKF_EncryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("���ECB�������ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB�������ܳ��ȳɹ�!\n");
	ret = SKF_EncryptFinal(hkey, encryptedData+outlen1+outlen2+outlen3, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB��������ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB�������ܳɹ�!\n");
	ulEncryptedLen = outlen1+outlen2+outlen3+finallen;


	//ECB����
	ret = SKF_DecryptInit(hkey, encrptPara);
	if (ret != SAR_OK)
	{
		printf("ECB���ܳ�ʼ��ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ܳ�ʼ���ɹ�!\n");

	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, NULL, &outlen1);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�1!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData, templen, pulDataBytes, &outlen1);
	if (ret != SAR_OK)
	{
		printf("ECB���ֽ���ʧ��1%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ֽ��ܳɹ�1!\n");


	templen = ulEncryptedLen/2;
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, NULL, &outlen2);
	if (ret != SAR_OK)
	{
		printf("���ECB���ܲ��ֳ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB���ܲ��ֳ��ȳɹ�2!\n");
	ret = SKF_DecryptUpdate(hkey, encryptedData+templen, ulEncryptedLen - templen, pulDataBytes+outlen1, &outlen2);
	if (ret != SAR_OK)
	{
		printf("ECB���ֽ���ʧ��2%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB���ֽ��ܳɹ�2!\n");

	ret = SKF_DecryptFinal(hkey, NULL, &finallen);
	if (ret != SAR_OK)
	{
		printf("���ECB�������ܳ���ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("���ECB�������ܳ��ȳɹ�!\n");
	ret = SKF_DecryptFinal(hkey, pulDataBytes+outlen1+outlen2, &finallen);
	if (ret != SAR_OK)
	{
		printf("ECB��������ʧ��%08x!\n", ret);
		return !SAR_OK;
	}
	else
		printf("ECB�������ܳɹ�!\n");

	dataLen = outlen1+outlen2+finallen;

	if (256 == dataLen)
	{
		if (0 != memcmp((void *)Random, (void *)pulDataBytes, dataLen))
		{
			printf("ECB�ಽ���ݼ��ܽ���ʧ��!\n");
			return !SAR_OK;
		}
		else {
			printf("ECB�ಽ���ݼ��ܽ��ܳɹ�!\n");
		}
	}
	
	return SAR_OK;
}


//�Գ���Կ���ĵ��뼰�ӽ���
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

	printf("��ʼ���ԶԳ���Կ���ĵ��뼰�ӽ���:\n");
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
		//��һ�����������
		RandomLen =	16;
		if ((ret = SKF_GenRandom(hDev, Random, RandomLen))!=SAR_OK)
		{ 
			printf("���������ʧ��%08x!\n",ret);
			goto _ERRRET;
		}

		//�ڶ�������Գ���Կ
		start_t = clock();
		ret = SKF_SetSymmKey(hDev, Random, ulAlgIDs[i], &hkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf("�����%d���Գ���Կʧ��%08x!\n",i, ret);
			goto _ERRRET;
		}
		else
			printf(" �����%d���Գ���Կ�ɹ�!\n",i);

		printf(" �����%d���Գ���Կʱ����\n",i);
		sprintf(ucTime,"%.3f",duration);

		//�������ӽ��ܲ���
		ret = En_DewithoutUpdate(hDev,hkey);
		ret = En_DeUpdate(hDev,hkey);
		ret = EnUpdate_De(hDev,hkey);
		ret = EnUpdate_DeUpdate(hDev,hkey);

		ret = SKF_CloseHandle(hkey);
		if (ret != SAR_OK)
		{
			printf("�ر���Կ���ʧ��%08x!\n",ret);
			goto _ERRRET;
		}
		else
			printf("�ر���Կ����ɹ�!\n");
	}
#endif
	
	printf("��ɲ��ԶԳ���Կ���ĵ��뼰�ӽ��ܺ���!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


//�Գ���Կ����RSA�������ӽ���
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
	

	printf("��ʼ���ԶԳ���Կ����RSA�������뼰�ӽ���:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST

	//��������con1
	printf("��������������:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" ������ʧ��%08x!\n", ret);
		goto _ERRRET;
	}


	//�������ܹ�Կ
	memset(&stRsaBlob,0,sizeof(stRsaBlob));
	ret = SKF_ExportPublicKey(hCont, FALSE, NULL, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ��ü��ܹ�Կ����ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ��ü��ܹ�Կ���ȳɹ�!\n");


	ret = SKF_ExportPublicKey(hCont, FALSE, (BYTE *)&stRsaBlob, &ulRsaBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ��ü��ܹ�Կʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ��ü��ܹ�Կ�ɹ�!\n");

	GET_ARRAY_LEN(ulAlgIDs, len);

	for(i=0; i<len; i++)
	{
		memset(ucEnkeyData,0,sizeof(ucEnkeyData));
		//��һ�����ɶԳ���Կ
		start_t = clock();
		ret = SKF_RSAExportSessionKey(hCont, ulAlgIDs[i], &stRsaBlob, NULL, &ulDataLen, &hkey);
		if (ret != SAR_OK)
		{
			printf(" ��õ�%d�������Գ���Կ����ʧ��%08x!\n",i, ret);
			goto _ERRRET;
		}
		else
			printf(" ��õ�%d�������Գ���Կ���ȳɹ�!\n",i);
		ret = SKF_RSAExportSessionKey(hCont, ulAlgIDs[i], &stRsaBlob, ucEnkeyData, &ulDataLen, &hkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf(" ��õ�%d�������Գ���Կʧ��%08x!\n", i,ret);
			goto _ERRRET;
		}
		else
			printf(" ��õ�%d�������Գ���Կ�ɹ�!\n",i);

		printf(" ��%d���Գ���Կ���ɵ���ʱ��:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//�ڶ�������Գ���Կ
		start_t = clock();
		ret = SKF_ImportSessionKey(hCont, ulAlgIDs[i], ucEnkeyData, ulDataLen, &hImkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf("�����%d�����ܶԳ���Կʧ��%08x!\n",i, ret);
			SKF_CloseHandle(hkey);
			goto _ERRRET;
		}
		else
			printf(" �����%d�����ܶԳ���Կ�ɹ�!\n",i);

		printf(" ��%d���Գ���Կ���ܵ���ʱ��:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//�������ӽ��ܲ���
		ret = En_DewithoutUpdate(hDev,hkey);
		ret = En_DeUpdate(hDev,hImkey);
		ret = EnUpdate_De(hDev,hImkey);
		ret = EnUpdate_DeUpdate(hDev,hkey);

		SKF_CloseHandle(hkey);
		ret = SKF_CloseHandle(hImkey);
		if (ret != SAR_OK)
		{
			printf("�ر���Կ���ʧ��%08x!\n",ret);
			goto _ERRRET;
		}
		else
			printf("�ر���Կ����ɹ�!\n");
	}
#endif
	
	printf("��ɲ��ԶԳ���Կ����RSA�������뼰�ӽ���!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


//�Գ���Կ����ECC�������ӽ���
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
	

	printf("��ʼ���ԶԳ���Կ����ECC�������뼰�ӽ���:\n");
	if (_OpenAPP_WithoutAUTH(&hDev, &hAPP) != SAR_OK)
	{
		return;
	}
	
	if (_CheckPin(hAPP) != SAR_OK)
	{
		goto _ERRRET;
	}

#if LIB_EXIST

	//��������con2
	printf("��������������:\n");
	scanf("%s", strContName);
	ret = SKF_OpenContainer(hAPP, strContName, &hCont);
	if (ret != SAR_OK)
	{
		printf(" ������ʧ��%08x!\n", ret);
		goto _ERRRET;
	}

	//����ECC���ܹ�Կ
	memset(&stEccBlob,0,sizeof(stEccBlob));
	ret = SKF_ExportPublicKey(hCont, FALSE, NULL, &ulEccBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ���ECC���ܹ�Կ����ʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ���ECC���ܹ�Կ���ȳɹ�!\n");


	ret = SKF_ExportPublicKey(hCont, FALSE, (BYTE *)&stEccBlob, &ulEccBlobLen);
	if (ret != SAR_OK)
	{
		printf(" ���ECC���ܹ�Կʧ��%08x!\n", ret);
		goto _ERRRET;
	}
	else
		printf(" ���ECC���ܹ�Կ�ɹ�!\n");

	GET_ARRAY_LEN(ulAlgIDs, len);

	for(i=0; i<len; i++)
	{
		memset(&stEccCipherBlob,0,sizeof(stEccCipherBlob));
		//��һ�����ɶԳ���Կ
		start_t = clock();
		ret = SKF_ECCExportSessionKey(hCont, ulAlgIDs[i], &stEccBlob, &stEccCipherBlob, &hkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf(" ���ECC��%d�������Գ���Կʧ��%08x!\n", i,ret);
			goto _ERRRET;
		}
		else
			printf(" ���ECC��%d�������Գ���Կ�ɹ�!\n",i);

		printf(" ��%d���Գ���Կ����ECC����ʱ��:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//�ڶ�������Գ���Կ
		start_t = clock();
		ret = SKF_ImportSessionKey(hCont, ulAlgIDs[i], (BYTE *)&stEccCipherBlob, sizeof(stEccCipherBlob), &hImkey);
		finish_t = clock();
		duration = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
		if (ret != SAR_OK)
		{
			printf("�����%d�����ܶԳ���Կʧ��%08x!\n",i, ret);
			SKF_CloseHandle(hkey);
			goto _ERRRET;
		}
		else
			printf(" �����%d�����ܶԳ���Կ�ɹ�!\n",i);

		printf(" ��%d���Գ���ԿECC����ʱ��:\n",i);
		sprintf(ucTime,"%.3f",duration);

		//�������ӽ��ܲ���
		ret = En_DewithoutUpdate(hDev,hkey);
		ret = En_DeUpdate(hDev,hImkey);
		ret = EnUpdate_De(hDev,hImkey);
		ret = EnUpdate_DeUpdate(hDev,hkey);

		SKF_CloseHandle(hkey);
		ret = SKF_CloseHandle(hImkey);
		if (ret != SAR_OK)
		{
			printf("�ر���Կ���ʧ��%08x!\n",ret);
			goto _ERRRET;
		}
		else
			printf("�ر���Կ����ɹ�!\n");
	}
#endif
	
	printf("��ɲ��ԶԳ���Կ����ECC�������뼰�ӽ���!\n");
	
_ERRRET:
	_CloseAPP(hAPP);
	_CloseDev(hDev);
}


/*================================================================================
 *=================================���̲�������===================================
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

	//���ü��ܲ���
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


	//��ӡ
	//Data
	pDst = pbData;
	cLen = ulDataLen;
	printf("DataBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//����
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
	
	//��ӡ
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

	//���ý��ܲ���
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

	//��ӡ
	//EncryptDataBlob
	pDst = m_EnDataforSym;
	cLen = mEnDataLen;
	printf("EncryptDataBlob =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");


	//ECB����
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


	//��ӡ
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
	printf("��ѡ���㷨: \n");
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
		printf("�㷨ѡ�����!\n");
		return;
	}

	//���IV
	if ((result = SKF_GenRandom(m_hDevice, m_IV, 16)) != SAR_OK)
	{
		printf("SKF_GenRandom 0 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	mIVLen = 16;

	//����16�ֽ������Կ������
	if ((result = SKF_GenRandom(m_hDevice, m_randKey, 16)) != SAR_OK)
	{
		printf("SKF_GenRandom 1 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}
	
	//������Կ���
	if ((result = SKF_SetSymmKey(m_hDevice, m_randKey, ulAlgID, &hKey)) != SAR_OK)
	{
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		return;
	}

	//����64�ֽ�����
	if ((result = SKF_GenRandom(m_hDevice, randPaint, 64)) != SAR_OK)
	{ 
		printf("SKF_GenRandom 2 ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	printf("��ʼִ��64�ֽ����ļ���:\n");

	//��ӡ
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
	printf("��ѡ���㷨: \n");
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
		printf("�㷨ѡ�����!\n");
		return;
	}
	
	//������Կ���
	if ((result = SKF_SetSymmKey(m_hDevice, m_randKey, ulAlgID, &hKey)) != SAR_OK)
	{
		printf("SKF_SetSymmKey   ERROR:%s\n",errorInfo[result&0xff].error);
		return;
	}
	
	printf("��ʼִ��64�ֽ����Ľ���:\n");

	//��ӡ
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
	//ö���豸
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

	//���豸
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

	//�ر��豸����ӡ
	ret = SKF_DisConnectDev(m_hDevice);
	if (ret != SAR_OK)
	{
		printf("SKF_DisConnectDev ERROR:%s\n", errorInfo[ret&0xff].error);
	}

	//�ٴδ��豸����ӡ
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
		printf(" ���ݽṹ�汾:Version %d.%d\n", sDevInfo.Version.major, sDevInfo.Version.minor);
		printf(" �豸������Ϣ:%s\n", sDevInfo.Manufacturer);
		printf(" ���г�����Ϣ:%s\n", sDevInfo.Issuer);
		printf(" �豸��ǩ:%s\n", sDevInfo.Label);
		printf(" ���к�:%s\n", sDevInfo.SerialNumber);
		printf(" �豸Ӳ���汾:HWVer %d.%d\n", sDevInfo.HWVersion.major, sDevInfo.HWVersion.minor);
		printf(" �豸�̼��汾:FWVer %d.%d\n", sDevInfo.FirmwareVersion.major, sDevInfo.FirmwareVersion.minor);
		printf(" ���������㷨��ʶ:%08x\n", sDevInfo.AlgSymCap);
		printf(" �ǶԳ������㷨��ʶ:%08x\n", sDevInfo.AlgAsymCap);
		printf(" �����Ӵ��㷨��ʶ:%08x\n", sDevInfo.AlgHashCap);
		printf(" �豸��֤���������㷨��ʶ:%08x\n", sDevInfo.DevAuthAlgId);
		printf(" �豸�ܿռ��С:%ld\n", sDevInfo.TotalSpace);
		printf(" �û����ÿռ��С:%ld\n", sDevInfo.FreeSpace);
		printf(" ������չ:----------\n");
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
	
	//��ʾ����app�б�
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
	//��Ӧ��
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

	//ö������
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
		//��ʾ����container�б�	
		printf("SKF_EnumContainer ok.\n");
		pStart = pBuffer;
		while (*pStart)
		{
			printf("caCntName:%s\n", pStart);
			pStart += (strlen(pStart) + 1);
		}
		free(pBuffer);
	}

	//������
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
		printf("SKF_VerifyPIN  ERROR:%s  ʣ�����Դ���=%d \n", errorInfo[result&0xff].error, remainretrycount);
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

#if LIB_EXIST	//����ǩ��֤��
	//��һ������ȡ����
	result = SKF_ExportCertificate(m_hContainer, TRUE,  NULL, &cLen);
	printf("SKF_ExportCertificate cLen = %x\n",cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCertificate Signed 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	
	//�ڶ�������ȡ����
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

	//��ӡ
	pDst = pBuffer;
	printf("sign data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	free(pBuffer);
	pBuffer = NULL;
#endif
	
#if LIB_EXIST	//��������֤��
	//��һ������ȡ����
	result = SKF_ExportCertificate(m_hContainer, FALSE,  NULL, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCertificate Encrypt 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	
	//�ڶ�������ȡ����
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
	
	//��ӡ
	pDst = pBuffer;
	printf("encrypt data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	free(pBuffer);
#endif

#if LIB_EXIST	//����ca֤��
	//��һ������ȡ����
	result = SKF_ExportCACertificate(m_hContainer, NULL, &cLen);
	if (result != SAR_OK)
	{
		printf("SKF_ExportCACertificate 1 ERROR:%s\n", errorInfo[result&0xff].error);
	}
	
	//�ڶ�������ȡ����
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

	//��ӡ
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
	//��һ������ȡǩ����Կ
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

	//��ӡ
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
	//�ڶ�������ȡ���ܹ�Կ
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

	//��ӡ
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
	
	//��ӡ
	pDst = m_DataforSign;
	cLen = ulDataLen;
	printf("orData=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//��һ��������ժҪ
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

	//�ڶ�����ǩ��
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
	//��ӡ
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
	//��һ����������ǩ��Կ
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

	//��ӡ
	pDst = (BYTE *)&stRsaBlob;
	cLen = ulRsaBlobLen;
	printf("Sign pubkey data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//�ڶ���������ժҪ
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

	
	//����������ǩ
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
	
	//��ӡ
	pDst = m_DataforSign;
	cLen = ulDataLen;
	printf("orData=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//��һ��������ǩ����Կ
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


	//��һ��������ժҪ
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

	//�ڶ�����ǩ��
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
	//��ӡ
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
	//��һ����������ǩ��Կ
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

	//��ӡ
	pDst = (BYTE *)&stEccBlob;
	cLen = ulEccBlobLen;
	printf("Sign pubkey data=");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//�ڶ���������ժҪ
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

	
	//����������ǩ
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

	//��һ�����������ܹ�Կ
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

	//��ӡ
	pDst = (BYTE *)&stRsaBlob;
	cLen = ulRsaBlobLen;
	printf("En pubkey =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//�ڶ������ⲿ��Կ����
	//ulDataLen = sizeof(m_DataforEn);
//	ulDataLen = stRsaBlob.BitLen/8;
	ulDataLen = 112;

	//��ӡ
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

	//��ӡ
	pDst = ucOutData;
	cLen = uloutLen;
	printf("EncryResult =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//��������˽Կ����
	ulDataLen = stRsaBlob.BitLen/8;
	memset(ucDeData,0,sizeof(ucDeData));
	result = SKF_RSADecrypt(m_hContainer, ucOutData, uloutLen, ucDeData, &ulDataLen);
	if (result != SAR_OK)
	{
		printf("oloutLen = %d,ulDataLen = %d,result = %08x\n",uloutLen,ulDataLen,result);
		printf("SKF_RSADecrypt ERROR:%s\n", errorInfo[result&0xff].error);
		return;
	}

	//��ӡ
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
	//��һ�����������ܹ�Կ
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
	
	//��ӡ
	pDst = (BYTE *)&stEccBlob;
	cLen = ulEccBlobLen;
	printf("En pubkey =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	//�ڶ������ⲿ��Կ����
	ulDataLen = sizeof(m_DataforEn);
//	ulDataLen = 32;
	
	//��ӡ
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

	//��ӡ
	pDst = (BYTE *)stEccCipherBlob;
	cLen = sizeof(ECCCIPHERBLOB) + ulDataLen;
	printf("EncryResult =");
	for (i = 0; i < cLen; i++)
	{
		printf("%02x", *pDst++);
	}
	printf("\n");

	ulDataLen = 2048;
	//��������˽Կ����
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

	//��ӡ
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






