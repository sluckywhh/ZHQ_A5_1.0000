#ifndef _CASE_CONTROL_APP_FILE_H_
#define _CASE_CONTROL_APP_FILE_H_


/*

INT8	有符号8位整数	
INT16	有符号16位整数	
INT32	有符号32位整数	
UINT8	无符号8位整数	
UINT16	无符号16位整数	
UINT32	无符号32位整数	
BOOL	布尔类型，取值为TRUE或FALSE	
BYTE	字节类型，无符号8位整数	typedef UINT8 BYTE
CHAR	字符类型，无符号8位整数	typedef UINT8 CHAR
SHORT	短整数，有符号16位	typedef INT16 SHORT
USHORT	无符号16位整数	typedef UINT16 USHORT
LONG 	长整数，有符号32位整数	typedef INT32 LONG
ULONG	长整数，无符号32位整数	typedef UINT32 ULONG
UINT	无符号32位整数	typedef UINT32 UINT
WORD	字类型，无符号16位整数	typedef UINT16 WORD
DWORD	双字类型，无符号32位整数	typedef UINT32 DWORD
FLAGS	标志类型，无符号32位整数	typedef UINT32 FLAGS
LPSTR	8位字符串指针，按照UTF8格式存储及交换	typedef CHAR * LPSTR
HANDLE 	句柄，指向任意数据对象的起始地址	typedef  void * HANDLE
DEVHANDLE	设备句柄	typedef HANDLE DEVHANDLE
HAPPLICATION	应用句柄	typedef HANDLE HAPPLICATION
HCONTAINER	容器句柄	typedef HANDLE HCONTAINER
*/

#if 0

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

typedef char			INT8;
typedef short			INT16;
typedef int				INT32;
typedef unsigned char	UINT8;
typedef unsigned short	UINT16;
typedef unsigned int	UINT32;

typedef long				BOOL;

typedef	UINT8			BYTE;
typedef UINT8			CHAR;

typedef INT16			SHORT;
typedef UINT16			USHORT;
typedef INT32			LONG;
typedef UINT32			ULONG;
typedef UINT32			UINT;
typedef UINT16			WORD;
typedef UINT32			DWORD;
typedef UINT32			FLAGS;
typedef CHAR *			LPSTR;
typedef void *			HANDLE;
typedef HANDLE			DEVHANDLE;
typedef HANDLE			HAPPLICATION;
typedef HANDLE			HCONTAINER;

typedef struct Struct_Version{
	BYTE major;
	BYTE minor;
}VERSION;

typedef struct Struct_DEVINFO{
	VERSION		Version;
	CHAR		Manufacturer[64];
	CHAR		Issuer[64];
	CHAR		Label[32];
	CHAR		SerialNumber[32];
	VERSION		HWVersion;
	VERSION		FirmwareVersion;
	ULONG		AlgSymCap;
	ULONG		AlgAsymCap;
	ULONG		AlgHashCap;
	ULONG		DevAuthAlgId;
	ULONG		TotalSpace;
	ULONG		FreeSpace;
	BYTE  		Reserved[64];
}DEVINFO,*PDEVINFO;




#define SAR_OK							0x00000000	 //成功
#define SAR_FAIL						0x0A000001	 //失败
#define SAR_UNKNOWNERR					0x0A000002	 //异常错误
#define SAR_NOTSUPPORTYETERR			0x0A000003	 //不支持的服务
#define SAR_FILEERR						0x0A000004	 //文件操作错误
#define SAR_INVALIDHANDLEERR			0x0A000005	 //无效的句柄
#define SAR_INVALIDPARAMERR				0x0A000006	 //无效的参数
#define SAR_READFILEERR					0x0A000007	 //读文件错误
#define SAR_WRITEFILEERR				0x0A000008	 //写文件错误
#define SAR_NAMELENERR					0x0A000009	 //名称长度错误
#define SAR_KEYUSAGEERR					0x0A00000A	 //密钥用途错误
#define SAR_MODULUSLENERR				0x0A00000B	 //模的长度错误
#define SAR_NOTINITIALIZEERR			0x0A00000C	 //未初始化
#define SAR_OBJERR						0x0A00000D	 //对象错误
#define SAR_MEMORYERR					0x0A00000E	 //内存错误
#define SAR_TIMEOUTERR					0x0A00000F	 //超时
#define SAR_INDATALENERR				0x0A000010	 //输入数据长度错误
#define SAR_INDATAERR					0x0A000011	 //输入数据错误
#define SAR_GENRANDERR					0x0A000012	 //生成随机数错误
#define SAR_HASHOBJERR					0x0A000013	 //HASH对象错
#define SAR_HASHERR						0x0A000014	 //HASH运算错误
#define SAR_GENRSAKEYERR				0x0A000015	 //产生RSA密钥错
#define SAR_RSAMODULUSLENERR			0x0A000016	 //RSA密钥模长错误
#define SAR_CSPIMPRTPUBKEYERR			0x0A000017	 //CSP服务导入公钥错误
#define SAR_RSAENCERR					0x0A000018	 //RSA加密错误
#define SAR_RSADECERR					0x0A000019	 //RSA解密错误
#define SAR_HASHNOTEQUALERR				0x0A00001A	 //HASH值不相等
#define SAR_KEYNOTFOUNTERR				0x0A00001B	 //密钥未发现
#define SAR_CERTNOTFOUNTERR				0x0A00001C	 //证书未发现
#define SAR_NOTEXPORTERR				0x0A00001D	 //对象未导出
#define SAR_DECRYPTPADERR				0x0A00001E	 //解密时做补丁错误
#define SAR_MACLENERR					0x0A00001F	 //MAC长度错误
#define SAR_BUFFER_TOO_SMALL			0x0A000020	 //缓冲区不足
#define SAR_KEYINFOTYPEERR				0x0A000021	 //密钥类型错误
#define SAR_NOT_EVENTERR				0x0A000022	 //无事件错误
#define SAR_DEVICE_REMOVED				0x0A000023	 //设备已移除
#define SAR_PIN_INCORRECT				0x0A000024	 //PIN不正确
#define SAR_PIN_LOCKED					0x0A000025	 //PIN被锁死
#define SAR_PIN_INVALID					0x0A000026	 //PIN无效
#define SAR_PIN_LEN_RANGE				0x0A000027	 //PIN长度错误
#define SAR_USER_ALREADY_LOGGED_IN		0x0A000028	 //用户已经登录
#define SAR_USER_PIN_NOT_INITIALIZED	0x0A000029	 //没有初始化用户口令
#define SAR_USER_TYPE_INVALID			0x0A00002A	 //PIN类型错误
#define SAR_APPLICATION_NAME_INVALID	0x0A00002B	 //应用名称无效
#define SAR_APPLICATION_EXISTS			0x0A00002C	 //应用已经存在
#define SAR_USER_NOT_LOGGED_IN			0x0A00002D	 //用户没有登录
#define SAR_APPLICATION_NOT_EXISTS		0x0A00002E	 //应用不存在
#define SAR_FILE_ALREADY_EXIST			0x0A00002F	 //文件已经存在
#define SAR_NO_ROOM						0x0A000030	 //空间不足
#define SAR_FILE_NOT_EXIST				0x0A000031	 //文件不存在
#define SAR_REACH_MAX_CONTAINER_COUNT	0x0A000032	 //已达到最大可管理容器数


#define SECURE_NEVER_ACCOUNT	0x00000000	//不允许
#define SECURE_ADM_ACCOUNT		0x00000001	//管理员权限
#define SECURE_USER_ACCOUNT		0x00000010	//用户权限
#define SECURE_ANYONE_ACCOUNT	0x000000FF	//任何人



typedef struct  
{
	int id;
	char error[64];
}ErrorInfo;



typedef struct Struct_FILEATTRIBUTE{
	CHAR	FileName[32];
	ULONG	FileSize;
	ULONG	ReadRights;
	ULONG	WriteRights; 
} FILEATTRIBUTE, *PFILEATTRIBUTE;

#endif


void Init();


void Test_SKF_DevAuth();
void Test_SKF_ChangePIN();
void Test_SKF_VerifyPIN();
void Test_SKF_UnblockPIN();
void Test_SKF_ChangeDevAuthKey();
void Test_SKF_ClearSecueState();
void Test_SKF_GetPINInfo();


void Test_SKF_CreateApplication();
void Test_SKF_EnumApplication();
void Test_SKF_DeleteApplication();
//void Test_SKF_OpenApplication();
//void Test_SKF_CloseApplication();
void Test_SKF_OpenClose_Application();

void Test_SKF_CreateFile();
void Test_SKF_DeleteFile();
void Test_SKF_ReadFile();
void Test_SKF_WriteFile();
void Test_SKF_EnumFiles();
void Test_SKF_GetFileInfo();



//==========================//
void Test_SKF_EnumDev();
//void Test_SKF_ConnectDev();
//void Test_SKF_DisConnectDev();
void Test_SKF_ConnectDev_DisconnectDev();
void Test_SKF_GetDevState();
void Test_SKF_GetDevInfo();
void Test_SKF_SetLabel();
void Test_SKF_LockDev();
void Test_SKF_UnlockDev();
void Test_SKF_Transmit();

void Test_SKF_CreateContainer();
void Test_SKF_DeleteContainer();
void Test_SKF_EnumContainer();
//void Test_SKF_OpenContainer();
//void Test_SKF_CloseContainer();
void Test_SKF_OpenContainer_CloseContainer();
void Test_SKF_GetContianerType();
void Test_SKF_ImportCertificate();
void Test_SKF_ExportCertificate();

void Test_SKF_GenRSAKeyPair();
void Test_SKF_GenECCKeyPair();
void Test_SKF_SetSymmKey();
void Test_SKF_RSAExportSessionKey();
void Test_SKF_ECCExportSessionKey();


//=============================//
void Test_Flow_EnumOpenCloseDev();
void Test_Flow_GetDevInfo();
void Test_Flow_EnumApp();
void Test_Flow_OpenSM2AppCont();
void Test_Flow_OpenRSA2048appCont();
void Test_Flow_OpenRSA1024appCont();
void Test_Flow_VerifyPIN();
void Test_Flow_ChangeUserPIN();
void Test_Flow_ExportPublickey();
void Test_Flow_ExportCertificate();
void Test_Flow_RsaSignData();
void Test_Flow_RSAVerify();
void Test_Flow_ECCSignData();
void Test_Flow_ECCVerify();
void Test_Flow_ExtRSAOperatDecrypt();
void Test_Flow_ExtECCEncryptDecrypt();
void Test_Flow_ExitTest();

void Test_Flow_EncryptwithSymKey();
void Test_Flow_DecryptwithSymKey();
#endif

