//#include "StdAfx.h"


#include <stdio.h>
#include "Case_Control_App_File.h"

#define MAX_LENGTH	128

typedef void (*DTestFunc)();

typedef struct _NAMEDISCAPP 
{
	char FuncName[MAX_LENGTH];
	char FuncDesc[MAX_LENGTH]; 
	DTestFunc TestFunc; 
}NAMEDISCAPP;

int g_FuncCount = 0;

NAMEDISCAPP testcase1[] = 
{
	{"SKF_EnumDev", "ö���豸", Test_SKF_EnumDev},
	{"SKF_ConnectDev", "�����豸", Test_SKF_ConnectDev_DisconnectDev},
	{"SKF_DisConnectDev", "�Ͽ��豸", Test_SKF_ConnectDev_DisconnectDev},
	{"SKF_GetDevState", "��ȡ�豸״̬", Test_SKF_GetDevState},
	{"SKF_GetDevInfo", "��ȡ�豸��Ϣ", Test_SKF_GetDevInfo},
	{"SKF_SetLabel", "�����豸��ǩ", Test_SKF_SetLabel},
	{"SKF_LockDev", "�����豸", Test_SKF_LockDev},
	{"SKF_UnlockDev", "�����豸", Test_SKF_UnlockDev},
	{"SKF_Transmit", "�豸�����", Test_SKF_Transmit},
	
	{"SKF_CreateContainer", "��������", Test_SKF_CreateContainer},
	{"SKF_DeleteContainer", "ɾ������", Test_SKF_DeleteContainer},
	{"SKF_EnumContainer", "ö������", Test_SKF_EnumContainer},
	{"SKF_OpenContainer", "������", Test_SKF_OpenContainer_CloseContainer},
	{"SKF_CloseContainer", "�ر�����", Test_SKF_OpenContainer_CloseContainer},
	{"SKF_GetContianerType", "�����������", Test_SKF_GetContianerType},
	{"SKF_ImportCertificate", "��������֤��", Test_SKF_ImportCertificate},
	{"SKF_ExportCertificate", "��������֤��", Test_SKF_ExportCertificate},

	//=======================================================//

	{"SKF_DevAuth","�豸��֤",Test_SKF_DevAuth},
	{"SKF_ChangePIN","�޸�PIN",Test_SKF_ChangePIN},
	{"SKF_VerifyPIN","У��PIN",Test_SKF_VerifyPIN},
	{"SKF_UnblockPIN","����PIN",Test_SKF_UnblockPIN},
	{"SKF_ChangeDevAuthKey","�޸��豸��֤��Կ",Test_SKF_ChangeDevAuthKey},
	{"SKF_ClearSecueState","���Ӧ�ð�ȫ״̬",Test_SKF_ClearSecueState},
	{"SKF_GetPINInfo","���PIN����Ϣ",Test_SKF_GetPINInfo},

	{"SKF_CreateApplication","����Ӧ��",Test_SKF_CreateApplication},
	{"SKF_EnumApplication","ö��Ӧ��",Test_SKF_EnumApplication},
	{"SKF_DeleteApplication","ɾ��Ӧ��",Test_SKF_DeleteApplication},
	{"SKF_OpenApplication","��Ӧ��",Test_SKF_OpenClose_Application},
	{"SKF_CloseApplication","�ر�Ӧ��",Test_SKF_OpenClose_Application},

	{"SKF_CreateFile","�����ļ�",Test_SKF_CreateFile},
	{"SKF_DeleteFile","ɾ���ļ�",Test_SKF_DeleteFile},
	{"SKF_ReadFile","���ļ�",Test_SKF_ReadFile},
	{"SKF_WriteFile","д�ļ�",Test_SKF_WriteFile},
	{"SKF_EnumFiles","ö���ļ�",Test_SKF_EnumFiles},
	{"SKF_GetFileInfo","��ȡ�ļ���Ϣ",Test_SKF_GetFileInfo},

	//////////////////�������//////////////////
	{"SKF_GenRSAKeyPair","RSA���ɵ���ǩ����ǩ",Test_SKF_GenRSAKeyPair},
	{"SKF_GenECCKeyPair","ECC���ɵ���ǩ����ǩ",Test_SKF_GenECCKeyPair},
	{"SKF_SetSymmKey","�Գ���Կ���ĵ��뼰�ӽ���",Test_SKF_SetSymmKey},
	{"SKF_RSAExportSessionKey","�Գ���Կ����RSA�������뼰�ӽ���",Test_SKF_RSAExportSessionKey},
	{"SKF_ECCExportSessionKey","�Գ���Կ����ECC�������뼰�ӽ���",Test_SKF_ECCExportSessionKey}

};


typedef struct _NAMEANDAPP 
{
	char FuncName[MAX_LENGTH];
	DTestFunc TestFunc; 
}NAMEANDAPP;


NAMEANDAPP testcase2[] = 
{
	{"enum,open,close device", Test_Flow_EnumOpenCloseDev},
	{"get device info",  Test_Flow_GetDevInfo},
	{"enum app",  Test_Flow_EnumApp},
	{"open SM2 app&Container",  Test_Flow_OpenSM2AppCont},
	{"open RSA2048 app&Container",  Test_Flow_OpenRSA2048appCont},
	{"open RSA1024 app&Container", Test_Flow_OpenRSA1024appCont},
	{"VerifyPIN", Test_Flow_VerifyPIN},
	{"ChangeUserPIN", Test_Flow_ChangeUserPIN},
	{"ExportPublickey", Test_Flow_ExportPublickey},
	{"ExportCertificate", Test_Flow_ExportCertificate},
	{"RsaSignData", Test_Flow_RsaSignData},
	{"RSAVerify", Test_Flow_RSAVerify},
	{"ECCSignData", Test_Flow_ECCSignData},
	{"ECCVerify", Test_Flow_ECCVerify},
	{"ExtRSAPubKeyOperation & RSADecrypt", Test_Flow_ExtRSAOperatDecrypt},
	{"ExtECCEncrypt & ECCDecrypt", Test_Flow_ExtECCEncryptDecrypt},
	{"symmetry Encypt Test", Test_Flow_EncryptwithSymKey},
	{"symmetry Decrypt Test", Test_Flow_DecryptwithSymKey}
};


static void PrintMenu()
{
	int i = 0;
	
//	Init_Key();
#if 0
	g_FuncCount = sizeof(testcase1)/sizeof(NAMEDISCAPP);
	printf("%-30s%-30s%-30s\n\n", "�ӿ�����", "�ӿ�����", "�����������");
	for(i = 0; i < g_FuncCount; i++)
	{
		printf("%-30s%-30s		%d\n",testcase1[i].FuncName, testcase1[i].FuncDesc, i+1);
	}
#else
	g_FuncCount = sizeof(testcase2)/sizeof(NAMEANDAPP);
	printf("\n<========================MENU========================>\n");
	for(i = 0; i < g_FuncCount; i++)
	{
		printf("%-2d: %-33s  ", i+1, testcase2[i].FuncName);
		if (0 == (i+1)%2)
		{
			printf("\n");
		}
	}
	printf("0 : exit\n--------------------------\n");
	
#endif
}

static void DoTestLoop()
{
	int nTesterIndex = 0;

#if 0
	while(1)
	{
		printf("\n\n�������������� [0Ϊ�˳�] :");
		scanf("%d", &nTesterIndex); 
		if (nTesterIndex == 0)
		{
			return;
		}
		
		if ((nTesterIndex <0) || (nTesterIndex > g_FuncCount))
		{
			printf("��������������\n");
			continue;
		}
		else
		{
			printf("\n");
			if (testcase1[nTesterIndex-1].TestFunc)
			{
				testcase1[nTesterIndex-1].TestFunc();
			}
		}
	}
#else
	while(1)
	{
		printf("input your choice:");
		scanf("%d", &nTesterIndex); 
		if (nTesterIndex == 0)
		{
			Test_Flow_ExitTest();
			return;
		}
		
		if ((nTesterIndex <0) || (nTesterIndex > g_FuncCount))
		{
			printf("input invalid, repress.\n");
			continue;
		}
		else
		{
			if (testcase2[nTesterIndex-1].TestFunc)
			{
				testcase2[nTesterIndex-1].TestFunc();
			}
			PrintMenu();
		}
	}
#endif
}


int main()
{
	Init();
	PrintMenu();
	DoTestLoop();
	
	return 0;
}
