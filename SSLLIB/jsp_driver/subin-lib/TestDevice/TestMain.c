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
	{"SKF_EnumDev", "枚举设备", Test_SKF_EnumDev},
	{"SKF_ConnectDev", "连接设备", Test_SKF_ConnectDev_DisconnectDev},
	{"SKF_DisConnectDev", "断开设备", Test_SKF_ConnectDev_DisconnectDev},
	{"SKF_GetDevState", "获取设备状态", Test_SKF_GetDevState},
	{"SKF_GetDevInfo", "获取设备信息", Test_SKF_GetDevInfo},
	{"SKF_SetLabel", "设置设备标签", Test_SKF_SetLabel},
	{"SKF_LockDev", "锁定设备", Test_SKF_LockDev},
	{"SKF_UnlockDev", "解锁设备", Test_SKF_UnlockDev},
	{"SKF_Transmit", "设备命令传输", Test_SKF_Transmit},
	
	{"SKF_CreateContainer", "创建容器", Test_SKF_CreateContainer},
	{"SKF_DeleteContainer", "删除容器", Test_SKF_DeleteContainer},
	{"SKF_EnumContainer", "枚举容器", Test_SKF_EnumContainer},
	{"SKF_OpenContainer", "打开容器", Test_SKF_OpenContainer_CloseContainer},
	{"SKF_CloseContainer", "关闭容器", Test_SKF_OpenContainer_CloseContainer},
	{"SKF_GetContianerType", "获得容器类型", Test_SKF_GetContianerType},
	{"SKF_ImportCertificate", "导入数字证书", Test_SKF_ImportCertificate},
	{"SKF_ExportCertificate", "导出数字证书", Test_SKF_ExportCertificate},

	//=======================================================//

	{"SKF_DevAuth","设备认证",Test_SKF_DevAuth},
	{"SKF_ChangePIN","修改PIN",Test_SKF_ChangePIN},
	{"SKF_VerifyPIN","校验PIN",Test_SKF_VerifyPIN},
	{"SKF_UnblockPIN","解锁PIN",Test_SKF_UnblockPIN},
	{"SKF_ChangeDevAuthKey","修改设备认证密钥",Test_SKF_ChangeDevAuthKey},
	{"SKF_ClearSecueState","清除应用安全状态",Test_SKF_ClearSecueState},
	{"SKF_GetPINInfo","获得PIN码信息",Test_SKF_GetPINInfo},

	{"SKF_CreateApplication","创建应用",Test_SKF_CreateApplication},
	{"SKF_EnumApplication","枚举应用",Test_SKF_EnumApplication},
	{"SKF_DeleteApplication","删除应用",Test_SKF_DeleteApplication},
	{"SKF_OpenApplication","打开应用",Test_SKF_OpenClose_Application},
	{"SKF_CloseApplication","关闭应用",Test_SKF_OpenClose_Application},

	{"SKF_CreateFile","创建文件",Test_SKF_CreateFile},
	{"SKF_DeleteFile","删除文件",Test_SKF_DeleteFile},
	{"SKF_ReadFile","读文件",Test_SKF_ReadFile},
	{"SKF_WriteFile","写文件",Test_SKF_WriteFile},
	{"SKF_EnumFiles","枚举文件",Test_SKF_EnumFiles},
	{"SKF_GetFileInfo","获取文件信息",Test_SKF_GetFileInfo},

	//////////////////密码服务//////////////////
	{"SKF_GenRSAKeyPair","RSA生成导出签名验签",Test_SKF_GenRSAKeyPair},
	{"SKF_GenECCKeyPair","ECC生成导出签名验签",Test_SKF_GenECCKeyPair},
	{"SKF_SetSymmKey","对称密钥明文导入及加解密",Test_SKF_SetSymmKey},
	{"SKF_RSAExportSessionKey","对称密钥生成RSA导出导入及加解密",Test_SKF_RSAExportSessionKey},
	{"SKF_ECCExportSessionKey","对称密钥生成ECC导出导入及加解密",Test_SKF_ECCExportSessionKey}

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
	printf("%-30s%-30s%-30s\n\n", "接口名称", "接口描述", "测试用例编号");
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
		printf("\n\n输入测试用例编号 [0为退出] :");
		scanf("%d", &nTesterIndex); 
		if (nTesterIndex == 0)
		{
			return;
		}
		
		if ((nTesterIndex <0) || (nTesterIndex > g_FuncCount))
		{
			printf("输入有误，请重试\n");
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
