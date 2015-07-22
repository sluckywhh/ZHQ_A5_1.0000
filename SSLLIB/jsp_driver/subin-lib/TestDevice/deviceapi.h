#ifndef __DEVICEAPI_H
#define __DEVICEAPI_H

#ifdef __cplusplus

#ifndef __stdcall
#define __stdcall
#endif
#include "typedef.h"

#define		BLOCK_LEN_LARGE_ENCRYPT			5600		//内部RAM为7680时
#define		BLOCK_LEN_FILE			2048		//读写大块二进制文件最大长度
#define		ONEVER			0x1000		//
#define		TWOVER			0x2000		//
#define		MAX_ECCLEN		1792		//一次SM2加解密的最大长度

class CDeviceEventLock
{
	HANDLE m_hEvent;
public:
	CDeviceEventLock(HANDLE hEvent)
	{
/*		if(NULL != hEvent)
		{
			m_hEvent = hEvent;
			WaitForSingleObjectEx(m_hEvent,0x1388,TRUE);
		}     */
	}; ///INFINITE
	void Lock(HANDLE hEvent)
	{
/*		if(NULL != hEvent)
		{
			m_hEvent = hEvent;
			WaitForSingleObjectEx(m_hEvent,0x1388,TRUE);
		}  */
	};
	void Unlock()
	{
/*		if(NULL != m_hEvent)
		{
			SetEvent(m_hEvent);
			m_hEvent = NULL;
		}  */
	};
	~CDeviceEventLock()
	{
//		if(NULL != m_hEvent)
//			SetEvent(m_hEvent);  
	}
};
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef		WAIT_FAILED
#define		WAIT_FAILED					0xFFFFFFFF 
#endif

#ifndef		WAIT_OBJECT_0
#define		WAIT_OBJECT_0				0x00000000 		
#endif

#ifndef		WAIT_TIMEOUT
#define		WAIT_TIMEOUT				0x00000102 
#endif

//macro definition of device type
#ifndef		DEVICETYPE
#define		DEVICETYPE
#define		DEVICETYPE_PCSC				0x00000001 		//PCSC设备
#define		DEVICETYPE_HID				0x00000002 		//HID设备
#define		DEVICETYPE_UKEY				0x00000004 		//UKey设备
//#define		DEVICETYPE_KEY_EX			0x00000008 		//带小存储的Key	
#endif

//macro definition of connect mode
#ifndef		CONNECTMODE
#define		CONNECTMODE
#define		CONNECT_MODE_SHARE			0x00000000 		//以共享方式打开端口
#define		CONNECT_MODE_EXCLUSIVE		0x00000001 		//以独占方式打开端口
#endif

//macro definition of status flag
//wanglei add 20090521	
#define     STATUS_FLAG_BASE			0x20002200 

#define		STATUS_FLAG_TOKEN_PRESENT	STATUS_FLAG_BASE+0x00000000 		//卡片是否存在
#define		STATUS_FLAG_CARD_ID			STATUS_FLAG_BASE+0x00000001 		//获取卡片序号
#define		STATUS_FLAG_ABILITY			STATUS_FLAG_BASE+0x00000002 		//获取设备能力
#define		STATUS_FLAG_FREESPACE		STATUS_FLAG_BASE+0x00000003 		//获取剩余空间的大小
#define		STATUS_FLAG_COS_VER			STATUS_FLAG_BASE+0x00000004 		//获取COS版本
#define		STATUS_FLAG_HARDWARE_VER	STATUS_FLAG_BASE+0x00000005 		//获取硬件版本
#define		STATUS_FLAG_FIRMWARE_VER	STATUS_FLAG_BASE+0x00000006 		//获取固件程序版本
#define		STATUS_FLAG_LIB_VER			STATUS_FLAG_BASE+0x00000007 		//获取API版本

#define		STATUS_FLAG_FREEERRORPIN	STATUS_FLAG_BASE+0x00000008L		//获取pin的错误尝试次数 subin 20130618

//macro definition of device ability
#define		DEVICE_ABILITY_RSA			0x00000001 		//是否具有RSA功能
#define		DEVICE_ABILITY_DES			0x00000002 		//是否具有DES/3DES功能
#define		DEVICE_ABILITY_RAND			0x00000004 		//是否具有生成随机数的能力
#define		DEVICE_ABILITY_SSF33		0x00000008 		//是否具有SSF33功能
#define		DEVICE_ABILITY_MD5			0x00000010 		//是否具有MD5功能
#define		DEVICE_ABILITY_SHA1			0x00000020 		//是否具有SHA-1功能
#define		DEVICE_ABILITY_SCB2			0x00000040 		//是否具有SCB2功能
		
//macro definition of file type
#define		FILE_TYPE_DATA				0x00000001 		//数据文件
#define		FILE_TYPE_RSAPUBKEY			0x00000002 		//RSA公钥文件
#define		FILE_TYPE_RSAPRIKEY			0x00000003 		//RSA私钥文件
#define		FILE_TYPE_KEY				0x00000004 		//对称密钥文件
#define		FILE_TYPE_LICENSE			0x00000008 		//授权文件
#define 	FILE_TYPE_PROGRAM			0x00000005 
#define 	FILE_TYPE_USERDATA			0x00000006 
//macro definition of access mode
#define		ACCESS_MODE_ALWAYS			0x00000000 		//权限永远满足
#define		ACCESS_MODE_NEVER			0xFFFFFFFF		//权限永远不满足
#define		ACCESS_MODE_USER			0x00000001 		//需要校验用户口令
#define		ACCESS_MODE_SO				0x00000002 		//需要校验管理员口令
#define		ACCESS_MODE_CERT			0x00000004 		//需要证书验证

//macro definition of login type
#define		LOGIN_TYPE_USER				0x00000001 		//普通用户
#define		LOGIN_TYPE_SO				0x00000002 		//管理员

//macro definition of alg
#define		ALGID_DES					0x00000001 		//DES/3DES算法
#define		ALGID_SSF33					0x00000002 		//SSF33算法
#define		ALGID_SHA1					0x00000003 		//SHA-1算法
#define		ALGID_MD5					0x00000004 		//MD5算法
#define		ALGID_SCB2					0x00000005 		//SCB2算法

#define		ALGID_SMS4					0x00000007 		//SMS4算法
#define		ALGID_AES					0x00000008 		//AES算法

#define		ALGID_P1					0x00000006 		//P1算法
#define		ALGID_PHUSH					0x00000032 		//PHUSH算法

//macro definition of rsa padding mode
//#define	RSA_PADDING_MODE_X509		0x00000001 		//纯RSA加密
//#define	RSA_PADDING_MODE_PKCS		0x00000002 		//符合PKCS V1.5规范的加密

//macro definition of device state
#define		DEVICE_STATUS_CARD_UNKNOWN	0x00000000 
#define		DEVICE_STATUS_CARD_ABSENT	0x00000001 
#define		DEVICE_STATUS_CARD_PRESENT	0x00000002 

#define MAX_PIN_LEN				0x10
#define MIN_PIN_LEN				8

//wanglei add 20090418
//#define CHANGERR 0xCE05A361
#define CHANGERR 0x0

//error code
#define		AI_SUCCESS					0				//成功
#define		AI_UNKNOWN_ERROR			(CHANGERR^0xE0020001)		//未知错误
#define		AI_INVALID_PARAMETER		(CHANGERR^0xE0020002)		//参数错误
#define		AI_BUFFER_NOT_ENOUGH		(CHANGERR^0xE0020003)		//参数空间不足
#define		AI_HOST_MEMORY				(CHANGERR^0xE0020004)		//主机内存不足
#define		AI_FUNC_NOT_SUPPORT			(CHANGERR^0xE0020005)		//功能不支持
#define		AI_DEVICE_NUM_TOO_LARGE		(CHANGERR^0xE0020006)		//设备个数超限
#define		AI_INVALID_HANDLE			(CHANGERR^0xE0020007)		//句柄无效
#define		AI_DEVICE_NO_RESPONSE		(CHANGERR^0xE0020008)		//设备无响应
#define		AI_NO_DEVICE				(CHANGERR^0xE0020009)		//没有设备
#define		AI_DEVICE_NOT_IDENTIFIED	(CHANGERR^0xE002000A)		//设备不能识别(复位信息不对)
#define		AI_BAD_CHECKSUM				(CHANGERR^0xE002000B)		//通信校验错误
#define		AI_ERR_SEND_DATA			(CHANGERR^0xE002000C)		//发送数据过程中出错
#define		AI_ERR_READ_DATA			(CHANGERR^0xE002000D)		//读取数据过程中出错
#define		AI_COMM_TIMEOUT				(CHANGERR^0xE002000E)		//读取数据过程中发生超时
#define		AI_BAD_DATA_FORMAT			(CHANGERR^0xE002000F)		//数据格式不能识别
#define		AI_NO_TOKEN					(CHANGERR^0xE0020010)		//没有智能卡
#define		AI_COS_NOT_RECOGNIZED		(CHANGERR^0xE0020011)		//不能识别的COS
#define		AI_DEVICE_REMOVED			(CHANGERR^0xE0020012)		//设备已被移除
//wangelei add 20090426
#define		AI_PORT_ALREADY_CONNECTED	(CHANGERR^0xE0021007)		//端口已经连接过了
#define		AI_SSX45_EFLASH_ERROR		(CHANGERR^0xE0020013)		//45芯片测试错误
#define     AI_PLEASE_REINSET_KEY		(CHANGERR^0xE0020014)		//

#define MAX_RSA_MODULUS_BITS 2048
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN ((MAX_RSA_PRIME_BITS + 7) / 8)

//#pragma pack(push, 8)

typedef struct 
{
	unsigned short int bits;						// length in bits of modulus 
	unsigned char modulus[MAX_RSA_MODULUS_LEN];		// modulus 
	unsigned char exponent[MAX_RSA_MODULUS_LEN];	// public exponent 
}/*__attribute__((aligned(8)))*/ RSA_PUBLIC_KEY;

typedef struct 
{
	unsigned short int bits;							// length in bits of modulus
	unsigned char modulus[MAX_RSA_MODULUS_LEN];			// modulus
	unsigned char publicExponent[MAX_RSA_MODULUS_LEN];	// public exponent 
	unsigned char exponent[MAX_RSA_MODULUS_LEN];		// private exponent
	unsigned char prime[2][MAX_RSA_PRIME_LEN];			// prime factors 
	unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];	// exponents for CRT
	unsigned char coefficient[MAX_RSA_PRIME_LEN];		// CRT coefficient
}/*__attribute__((aligned(8)))*/ RSA_PRIVATE_KEY;

//#pragma pack(pop)

void printerr(char *fun, int input);
/*
// C prototype : unsigned int __stdcall AI_Dev_EnumDev( IN unsigned int ulDeviceType, 
//											OUT char *szDeviceName, 
//											IN OUT unsigned int *pulDeviceNameLen,
//											IN ulFlag);
// parameter(s): ulDeviceType 设备类型,见DEVICETYPE_XXX定义. 在该函数中,各种设备类型可以
//								"或"起来使用,相应位置1则表示需要枚举该设备类型的设备.
//				 szDeviceName 用于存放设备名称列表的缓冲区首地址,如果为NULL,则pulDeviceNameLen
//							将返回设备名称列表的实际长度.
//				 pulDeviceNameLen 进入函数时,该参数的内容表示缓冲区szDeviceName的长度,
//						函数返回时,该参数的内容指示缓冲区中存放的设备名称列表的实际长度.
//				 ulFlag 标志: 该值目前必须为1，其它值保留。
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 该函数枚举当前系统上所支持的设备列表. 每一个设备名称之间以'\0'作为分隔符.
//				 另外,该函数返回的设备列表中并不包含串口设备.
*/
unsigned int __stdcall AI_Dev_EnumDev(OUT char *szDeviceName, 
							IN OUT unsigned int *pulDeviceNameLen,
							IN unsigned int ulDeviceType, 
							IN unsigned int ulFlag);


/*
// C prototype : unsigned int __stdcall AI_Dev_ConnectDev(IN const char *szDeviceName, 
//										IN unsigned int ulMode, 
//										OUT unsigned int *pulDevHandle);
// parameter(s): szDeviceName 设备名称
//				 ulMode 连接模式,最低字节表示以共享打开端口还是以独占方式打开端口,见CONNECT_MODE_XXX定义.
//						如果是串口设备,高3字节表示波特率(目前支持9600和115200,如果设为0,则内部将默认以
//						最高波特率连接设备以获取最高通信速率),对于其它设备类型高3字节必须为0.
//				 pulDevHandle 设备句柄.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 建立与Token(智能卡)的连接. 对于串口设备,设备名称为"COM1", "COM2"等. 对于其它设备类型,
//				 设备名称可以由AI_Dev_EnumDev返回. 调用该函数时一个容易引起歧义的地方是该函数的功能是
//				 建立与智能卡的连接,而不仅是设备,也就是对于读卡器这种类型的设备,如果当前没有插入卡片,
//				 调用该函数则不能成功. 如果该函数被成功调用后,用户曾经拔出过卡片之后又重新插入了卡片,
//				 除非重新调用本函数,否则也将不能对新的卡片进行操作.
*/
unsigned int __stdcall AI_Dev_Transmit(IN unsigned int ulDevHandle, BYTE *pbCDB, BYTE *pbData, ULONG ulLen, BYTE bDir);

unsigned int __stdcall AI_Dev_TestDeviceState(OUT char *szDeviceList, IN OUT unsigned int *ulDeviceLen);

unsigned int __stdcall AI_Dev_ConnectDev(IN const char *szDeviceName, 
						 OUT unsigned int *pulDevHandle,
						 IN unsigned int ulMode);

unsigned int __stdcall AI_Dev_ReadFingerReg(IN unsigned int ulDevHandle, BYTE addr,BYTE *data);

unsigned int __stdcall AI_Dev_WriteFingerReg(IN unsigned int ulDevHandle, BYTE addr,BYTE data);

unsigned int __stdcall AI_Dev_ReadFingerImg(IN unsigned int ulDevHandle,BYTE *img);
/*
// C prototype : unsigned int __stdcall AI_Dev_DisconnectDev(IN unsigned int ulDevHandle);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 断开与设备的连接.
*/
unsigned int __stdcall AI_Dev_DisconnectDev(IN unsigned int ulDevHandle);

/*
// C prototype : unsigned int __stdcall AI_Dev_TransportCmd(IN unsigned int ulDevHandle, 
//											IN const unsigned char *pbSendBuff, 
//											IN unsigned int ulSendLen, 
//											OUT unsigned char *pbRecBuff, 
//											IN OUT unsigned int *pulRecLen,
//											IN unsigned int ulFlag);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pbSendBuff 命令数据.
//				 ulSendLen 命令数据的长度.
//				 pbRecBuff 接收响应数据的缓冲区起始地址.
//				 pulRecLen 进入函数时,表示接收缓冲区的长度; 函数返回时表示响应数据的实际长度.
//				 ulFlag 标志,如果设备有数据需要返回,是否直接取出. 如果值为0则直接取出,否则不取.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 该函数用于直接向IC卡发送APDU命令. 当函数返回AI_BUFFER_NOT_ENOUGH时,pulRecLen
//				 的内容指示实际需要的输出缓冲区的字节数.
*/
unsigned int __stdcall AI_Dev_TransportCmd(IN unsigned int ulDevHandle, 
						  IN unsigned int ulSendLen, 
						  IN const unsigned char *pbSendBuff, 
						  IN OUT unsigned int *pulRecLen,
						  OUT unsigned char *pbRecBuff, 
						  IN unsigned int ulFlag);


unsigned int __stdcall AI_Dev_ImportRsaSK(IN unsigned int    hToken,
										   IN unsigned short   nPrvKeyID,
										   IN BYTE             *pEncDerPrvData,
										   IN unsigned int     nEncDerPrvLen,
										   IN BYTE             *pPubEncKeySymData,
										   IN unsigned int     nPubEncKeySymLen,
										   IN unsigned short   nDecryptPrvKeyID,
										   IN unsigned int    symAlgoType);

/*
// C prototype : unsigned int __stdcall AI_Dev_IoControl(IN unsigned int ulDevHandle, 
//						 IN unsigned int ulControlCode, 
//						 IN const unsigned char *pbInBuff, 
//						 IN unsigned int ulInLen, 
//						 OUT unsigned char *pbOutBuff, 
//						 IN OUT unsigned int *pulOutLen);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulControlCode 操作代码.
//				 pbInBuff 操作需要的命令数据.
//				 ulInLen 命令数据的长度.
//				 pbOutBuff 接收响应数据的缓冲区起始地址.
//				 pulOutLen 进入函数时,表示接收缓冲区的长度; 函数返回时表示响应数据的实际长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 该函数用于直接向设备发送控制命令. 为了保证应用程序的兼容性,建议用户不要直接调用该函数.
*/
unsigned int __stdcall AI_Dev_IoControl(IN unsigned int ulDevHandle, 
						 IN unsigned int ulControlCode, 
						 IN unsigned int ulInLen, 
						 IN const unsigned char *pbInBuff, 
						 IN OUT unsigned int *pulOutLen,
						 OUT unsigned char *pbOutBuff);

/*
// C prototype : unsigned int __stdcall AI_Dev_GetState(IN unsigned int ulDevHandle, 
//						   IN unsigned int ulFlag, 
//						   OUT void *pbOut, 
//						   IN OUT unsigned int *pulOutLen);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulFlag 标志. 
//					STATUS_FLAG_TOKEN_PRESENT,获取当前Token(卡片)存在的状态,将返回4字节的unsigned
//						int型整数. 可能为如下值:
//						1: Token一直存在;
//						0: 表示当前没有Token存在或者自从上次成功调用AI_Dev_ConnectDev函数后Token曾经被移除;
//					STATUS_FLAG_CARD_ID,获取卡片序号,一般情况下将返回8字节的卡片序列号.
//					STATUS_FLAG_ABILITY,获取设备能力,将返回4字节的unsigned int型整数.其
//						每一位的定义见DEVICE_ABILITY_XXX定义.如果相应为置1,则表示具有该能力.
//					STATUS_FLAG_FREESPACE,获取剩余空间的大小,返回4字节的unsigned int型整数.
//					STATUS_FLAG_COS_VER,获取COS版本,返回2字节的unsigned short型整数.
//					STATUS_FLAG_HARDWARE_VER,获取硬件版本,返回2字节unsigned short型整数.
//					STATUS_FLAG_FIRMWARE_VER,获取固件程序版本,返回2字节unsigned short型整数.
//					STATUS_FLAG_LIB_VER,获取API版本,返回2字节unsigned short型整数.
//				 pbOut 接收返回数据的缓冲区起始地址.
//				 pulOutLen 进入函数时,表示接收缓冲区的长度; 函数返回时表示返回数据的实际长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 该函数用于获取设备的当前状态. 对于STATUS_FLAG_TOKEN_PRESENT参数,如果返回值
//				 为0,说明从上次连接端口到当前查询状态的期间,Token曾经被移除过,即使移除后又重
//				 新插入了原始Token,返回值都将为0. 如果返回值为1,则表明卡片自从连接端口到现在
//				 从来没有被移除过. 如果更换了Token,除非重新连接端口,否则返回状态值将一直是0.
*/
unsigned int __stdcall AI_Dev_GetState(IN unsigned int ulDevHandle, 
						   IN unsigned int ulFlag, 
						   IN OUT unsigned int *pulOutLen,
						   OUT void *pbOut);


/*
// C prototype : unsigned int __stdcall AI_Dev_GetErrs(IN unsigned int ulErrCode, 
//						   OUT char *szErrMsg, 
//						   IN OUT unsigned int *pulMsgLen);
// parameter(s): ulErrCode 由本库返回的错误码.
//				 szErrMsg 返回的错误信息.
//				 pulMsgLen 进入函数时表示缓冲区szErrMsg的长度,函数返回时表示返回
//						的错误信息的实际长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 根据错误码获取错误信息.
*/
unsigned int __stdcall AI_Dev_GetErrs(IN unsigned int ulErrCode, 
						   IN OUT unsigned int *pulMsgLen,	
						   OUT char *szErrMsg);



/*
// C prototype : unsigned int __stdcall AI_Dev_LockDev(IN unsigned int ulDevHandle,
//							IN unsigned int ulTimeout);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulTimeout 等待时间,单位为毫秒.如果值为0xFFFFFFFF,表示一直等到事件发生为止.
// return value: WAIT_OBJECT_0 - 成功;
//				 WAIT_FAILED - 函数执行失败;
//				 WAIT_TIMEOUT - 函数超时返回;
//				 其它值 - 错误码;
// remarks     : 同步设备访问.如果一个线程通过调用该函数获得了对设备的访问控制权限,
//				 直到该线程通过调用AI_Dev_UnlockDev函数释放自己的访问控制权限之前,
//				 其它也调用AI_Dev_LockDev函数希望获取对设备的访问权限的线程将被阻塞.
//				 为了保障对设备的一个"操作事务"能顺利完成,而中间不会因为其它线程对
//				 设备的访问而中断,我们就必须在"操作事务"的最前面调用该函数,而在事务
//				 确认已经完成后,再调用AI_Dev_UnlockDev函数释放控制权限,让其它线程也有
//				 获取对设备访问的机会. 另外在调用该函数时,必须保证与AI_Dev_UnlockDev
//				 配对使用.
*/
unsigned int __stdcall AI_Dev_LockDev(IN unsigned int ulDevHandle,
							IN unsigned int ulTimeout);


/*
// C prototype : unsigned int __stdcall AI_Dev_UnlockDev(IN unsigned int ulDevHandle);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 释放当前线程对设备的访问控制权限. 该函数必须与AI_Dev_LockDev函数
//				 配对使用.
*/
unsigned int __stdcall AI_Dev_UnlockDev(IN unsigned int ulDevHandle);



// C prototype : unsigned int __stdcall AI_CreateApplication(IN unsigned int ulDevHandle,
//								   IN unsigned short usAppID,
//								   IN const unsigned char * pbUserPin,
//								   IN unsigned int ulUserPinLen,
//								   IN unsigned int ulUserPinRetryCount,
//								   IN const unsigned char * pbSOPin,
//								   IN unsigned int ulSOPinLen,
//								   IN unsigned int ulSOPinRetryCount,
//								   IN unsigned int ulFlag);								   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usAppID 用来唯一标识一个应用,其数值范围在0x1000到0xEFFF之间.
//				 pbUserPin 用户口令,用以保护文件的读写控制或密钥的使用控制.
//				 ulUserPinLen 用户口令的长度.
//				 ulUserPinRetryCount 用户口令允许的最大尝试次数. 如果为0,则系统内部将设为默认值.
//				 pbSOPin 管理员口令,用以解锁用户口令或特定的权限控制.
//				 ulSOPinLen 管理员口令的长度.
//				 ulSOPinRetryCount 管理员口令允许的最大尝试次数. 如果为0,则系统内部将设为默认值.
//				 ulFlag 标志,可能值如下:
//					0 - 用户口令和管理员口令安装到当前应用下;
//					1 - 用户口令和管理员口令安装到卡片根目录下,但是卡片必须为空,否则返回错误;
//					2 - 用户口令和管理员口令安装到卡片根目录下,如果根目录下已经存在密钥文件,则
//						跳过安装口令的步骤.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 建立应用.
//				 如果参数pbUserPin和参数pbSOPin为NULL,则函数内部将不安装用户口令以及管理员口令,
//				 如果其它应用在卡片的根目录下安装了全局PIN,则可能会如此调用. 
//
/*
unsigned int __stdcall AI_CreateApplication(IN unsigned int ulDevHandle,
								   IN unsigned short usAppID,
								   IN const unsigned char * pbUserPin,
								   IN unsigned int ulUserPinLen,
								   IN unsigned int ulUserPinRetryCount,
								   IN const unsigned char * pbSOPin,
								   IN unsigned int ulSOPinLen,
								   IN unsigned int ulSOPinRetryCount,
								   IN unsigned int ulFlag);
*/								   

// C prototype : unsigned int __stdcall AI_DeleteApplication(IN unsigned int ulDevHandle,
//								   IN unsigned short usAppID);								   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usAppID 用来唯一标识一个应用.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 删除应用. 只有以管理员身份登录设备后才能执行该操作,详见AI_Dev_Login函数.


unsigned int __stdcall AI_Dev_DeleteApplication(IN unsigned int ulDevHandle,
								   IN unsigned short usAppID);

unsigned int __stdcall AI_Dev_BlankKey(unsigned int ulDevHandle);

// C prototype : unsigned int __stdcall AI_SelectApplication(IN unsigned int ulDevHandle,
//								   IN unsigned short usAppID);							   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usAppID 用来唯一标识一个应用.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 选择应用.

unsigned int __stdcall AI_Dev_SelectApplication(IN unsigned int ulDevHandle,
								   IN unsigned short usAppID);

/*
// C prototype : unsigned int __stdcall AI_Dev_CreateFile(IN unsigned int ulDevHandle,
//							 IN unsigned short usFileID,
//							 IN unsigned int ulFileType,
//							 IN unsigned short usSize,
//							 IN unsigned int ulReadSec,
//							 IN unsigned int ulUpdateSec,
//							 IN unsigned int ulUseSec);						   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usFileID 用来唯一标识一个文件,其数值范围在0x1000到0xEFFF之间.
//				 ulFileType 文件类型,见FILE_TYPE_XXX定义.
//				 usSize 文件大小参数. 对于FILE_TYPE_RSAPUBKEY和FILE_TYPE_RSAPRIKEY,该参数为模长(bits).
//				 ulReadSec 对于FILE_TYPE_DATA,FILE_TYPE_LICENSE文件类型适用,表示读取文件需要满足的权限.
//					对于FILE_TYPE_LICENSE文件类型,该参数必须设为ACCESS_MODE_CERT.
//				 ulUpdateSec 对于FILE_TYPE_DATA,FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY,FILE_TYPE_LICENSE
//					文件类型适用,表示更新文件内容需要满足的权限.
//					对于FILE_TYPE_LICENSE文件类型,该参数必须设为ACCESS_MODE_CERT.
//				 ulUseSec 对于FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY文件类型适用. 
//					对于FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY两种文件,其表示使用密钥时需要满足的权限; 
//					对于其它类型的文件,该参数无意义.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 建立文件. 
//				 关于文件的权限设置说明如下:
//				 如果权限设置为ACCESS_MODE_ALWAYS,表示权限永远满足,无需普通用户或管理员登录即可操作.
//				 如果权限设置为ACCESS_MODE_NEVER,表示权限永远不满足,即指定的操作用户不允许被执行.
//				 如果权限设置为ACCESS_MODE_USER,表示需要校验用户口令后,才能执行相应的操作.
//				 如果权限设置为ACCESS_MODE_SO,表示需要校验管理员口令后,才能执行相应的操作.
//				 如果权限设置为ACCESS_MODE_CERT,表示需要校验证书合法性后,才能执行相应的操作.
//				 注意,对于文件的权限设置只有在调用AI_ActivateFile之后才开始生效.
*/
unsigned int __stdcall AI_Dev_CreateFile(IN unsigned int ulDevHandle,
							 IN unsigned int ulFileType,
							 IN unsigned short usFileID,
							 IN unsigned short usSize,
							 IN unsigned int ulReadSec,
							 IN unsigned int ulUpdateSec,
							 IN unsigned int ulUseSec);

/*
// C prototype : unsigned int __stdcall AI_ActivateFile(IN unsigned int ulDevHandle,
//							  IN unsigned short usFileID);				   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usFileID 用来唯一标识一个文件.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 激活文件, 即让文件的所有权限设置开始生效. 
*/
unsigned int __stdcall AI_Dev_ActivateFile(IN unsigned int ulDevHandle,
							  IN unsigned short usFileID);
/*
// C prototype : unsigned int __stdcall AI_Dev_SelectFile(IN unsigned int ulDevHandle,
//							IN const unsigned short *pusPath,
//							IN unsigned int ulPathLen);			   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pusPath  文件路径,路径是由应用的标识和文件的标识组成. 如果当前已经
//					选择过应用,只需传入要选择的文件标识即可.
//				 ulPathLen 路径中包含的标识的个数(而不是路径中包含的字符的字节数).
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 选择文件. 在连接设备成功后, 如果需要操作某个应用下的某个文件,可以
//				 直接调用该函数进行选择,如果选择成功,路径中包含的应用即成为了当前
//				 应用, 该过程会比先选择应用,然后选择文件效率更高.
*/
unsigned int __stdcall AI_Dev_SelectFile(IN unsigned int ulDevHandle,
							IN unsigned int ulPathLen,
							IN const unsigned short *pusPath);
							
/*
// C prototype : unsigned int __stdcall AI_Dev_DeleteFile(IN unsigned int ulDevHandle,
//							IN const unsigned short *pusPath,
//							IN unsigned int ulPathLen);			   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pusPath  文件路径,路径是由应用的标识和文件的标识组成. 如果当前已经
//					选择过应用,只需传入要删除的文件标识即可.
//				 ulPathLen 路径中包含的标识的个数(而不是路径中包含的字符的字节数).
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 删除文件.
*/
unsigned int __stdcall AI_Dev_DeleteFile(IN unsigned int ulDevHandle,
							IN unsigned int ulPathLen,
							IN const unsigned short *pusPath);


/*
// C prototype : unsigned int __stdcall AI_Dev_ReadFile(IN unsigned int ulDevHandle,
//						  IN const unsigned short *pusPath,
//						  IN unsigned int ulPathLen,
//						  IN unsigned int ulOffset,
//						  IN unsigned int ulReadLen,
//						  OUT unsigned char *pbOut);		   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pusPath  文件路径,路径是由应用的标识和文件的标识组成. 如果已经选择过
//					目标文件,可以直接传入NULL.
//				 ulPathLen 路径中包含的标识的个数(而不是路径中包含的字符的字节数).如果
//					已经选择过目标文件,可以设为0.
//				 ulOffset 偏移地址.
//				 ulReadLen 要读取数据的字节数.
//				 pbOut 接收数据的缓冲区首地址.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 读文件. 该函数适用于FILE_TYPE_DATA,FILE_TYPE_RSAPUBKEY,FILE_TYPE_USERDATA文件类型.
*/
unsigned int __stdcall AI_Dev_ReadFile(IN unsigned int ulDevHandle,
						  IN unsigned int ulPathLen,
						  IN const unsigned short *pusPath,
						  IN unsigned int ulOffset,
						  IN unsigned int ulReadLen,
						  OUT unsigned char *pbOut);


/*
// C prototype : unsigned int __stdcall AI_Dev_UpdateFile(IN unsigned int ulDevHandle,
//							IN const unsigned short *pusPath,
//							IN unsigned int ulPathLen,
//							IN unsigned int ulOffset,
//							IN unsigned int ulUpdateLen,
//							IN const unsigned char *pbBuff);		   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pusPath  文件路径,路径是由应用的标识和文件的标识组成. 如果已经选择过
//					目标文件,可以直接传入NULL.
//				 ulPathLen 路径中包含的标识的个数(而不是路径中包含的字符的字节数).如果
//					已经选择过目标文件,可以设为0.
//				 ulOffset 偏移地址.
//				 ulUpdateLen 需要更新的字节数.
//				 pbBuff 需要更新的数据.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 更新文件内容. 该函数适用于FILE_TYPE_DATA,FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY,
//				 FILE_TYPE_PROGRAM,FILE_TYPE_USERDATA文件类型.
*/
unsigned int __stdcall AI_Dev_UpdateFile(IN unsigned int ulDevHandle,
							IN unsigned int ulPathLen,
							IN const unsigned short *pusPath,
							IN unsigned int ulOffset,
							IN unsigned int ulUpdateLen,
							IN const unsigned char *pbBuff);

/*
// C prototype : unsigned int __stdcall AI_Dev_AddKey(IN unsigned int ulDevHandle,
//						IN unsigned char bKeyID,
//						IN unsigned int ulAlgID,
//						IN const unsigned char *pbValue,
//						IN unsigned int ulValueLen,
//						IN unsigned int ulUseSec,
//						IN unsigned int ulUpdateSec);		   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulAlgID 密钥算法,可以为ALGID_DES或ALGID_SSF33.
//				 bKeyID 密钥标识,用于唯一标识一条密钥.范围在0x10到0xEF之间.
//				 pbValue 密钥值.
//				 ulValueLen 密钥长度.
//				 ulUseSec 密钥使用的权限.
//				 ulUpdateSec 更新密钥的权限.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 往密钥文件中安装一条对称密钥. 该操作必须在管理员登录后才能执行.
//				 ulUseSec和ulUpdateSec可能值为ACCESS_MODE_ALWAYS,ACCESS_MODE_NEVER,
//				 ACCESS_MODE_USER或ACCESS_MODE_SO.
*/
unsigned int __stdcall AI_Dev_AddKey(IN unsigned int ulDevHandle,
						IN unsigned char bKeyID,
						IN unsigned int ulAlgID,
						IN const unsigned char *pbValue,
						IN unsigned int ulValueLen,
						IN unsigned int ulUseSec,
						IN unsigned int ulUpdateSec);


/*
// C prototype : unsigned int __stdcall AI_Dev_UpdateKey(IN unsigned int ulDevHandle,
//						IN unsigned char bKeyID,
//						IN unsigned int ulAlgID,
//						IN const unsigned char *pbValue,
//						IN unsigned int ulValueLen,
//						IN unsigned int ulUseSec,
//						IN unsigned int ulUpdateSec);		   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulAlgID 密钥算法,可以为ALGID_DES或ALGID_SSF33.
//				 bKeyID 密钥标识,用于唯一标识一条密钥.
//				 pbValue 密钥值.
//				 ulValueLen 密钥长度.
//				 ulUseSec 密钥使用的权限.参见ACCESS_MODE_XXX定义
//				 ulUpdateSec 更新密钥的权限.参见ACCESS_MODE_XXX定义
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 修改密钥文件中的一条对称密钥.
*/
unsigned int __stdcall AI_Dev_UpdateKey(IN unsigned int ulDevHandle,
						IN unsigned char bKeyID,
						IN unsigned int ulAlgID,
						IN const unsigned char *pbValue,
						IN unsigned int ulValueLen,
						IN unsigned int ulUseSec,
						IN unsigned int ulUpdateSec);


/*
// C prototype : unsigned int __stdcall AI_Dev_Login(IN unsigned int ulDevHandle,
//					   IN const unsigned char *pbPin,
//					   IN unsigned int ulPinLen,
//					   IN unsigned int ulType);	   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pbPin 用户口令或管理员口令.
//				 ulPinLen 口令的长度.
//				 ulType 登录类型. LOGIN_TYPE_USER或LOGIN_TYPE_SO.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 以普通用户或管理员身份登录设备.
*/
unsigned int __stdcall AI_Dev_Login(IN unsigned int ulDevHandle,
					   IN unsigned int ulPinLen,
					   IN const unsigned char *pbPin,
					   IN unsigned int ulType);

/*
// C prototype : unsigned int __stdcall AI_Dev_ChangePwd(IN unsigned int ulDevHandle,
//						   IN const unsigned char *pbOldPin,
//						   IN unsigned int ulOldPinLen,
//						   IN const unsigned char *pbNewPin,
//						   IN unsigned int ulNewPinlen,
//						   IN unsigned int ulType);	   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pbOldPin 原始口令.
//				 ulOldPinLen 原始口令的长度.
//				 pbNewPin 新口令.
//				 ulNewPinLen 新口令的长度.
//				 ulType 口令类型. LOGIN_TYPE_USER或LOGIN_TYPE_SO.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 修改口令.
*/
unsigned int __stdcall AI_Dev_ChangePwd(IN unsigned int ulDevHandle,
						   IN unsigned int ulOldPinLen,
						   IN const unsigned char *pbOldPin,
						   IN unsigned int ulNewPinlen,
						   IN const unsigned char *pbNewPin,
						   IN unsigned int ulType);


/*
// C prototype : unsigned int __stdcall AI_Dev_UnblockPwd(IN unsigned int ulDevHandle,
//							IN const unsigned char *pbSOPin,
//							IN unsigned int ulSOPinLen,
//							IN const unsigned char *pbNewUserPin,
//							IN unsigned int ulNewUserPinLen);	   
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pbSOPin 管理员口令.
//				 ulSOPinLen 管理员口令的长度.
//				 pbNewUserPin 新的用户口令.
//				 ulNewUserPinLen 新用户口令的长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 使用管理员口令重设用户口令.
*/
unsigned int __stdcall AI_Dev_UnblockPwd(IN unsigned int ulDevHandle,
							IN unsigned int ulSOPinLen,
							IN const unsigned char *pbSOPin,
							IN unsigned int ulNewUserPinLen,
							IN const unsigned char *pbNewUserPin);


/*
// C prototype : unsigned int __stdcall AI_Dev_GenerateRsaKeyPair(IN unsigned int ulDevHandle,
//									IN unsigned int ulModulusBits,
//									IN unsigned short usPubKeyFileID,
//									IN unsigned short usPriKeyFileID);  
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulModulusBits RSA密钥的模数位数.
//				 usPubKeyFileID 公钥文件标识.
//				 usPriKeyFileID 私钥文件标识.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 生成RSA密钥对.
*/
unsigned int __stdcall AI_Dev_GenerateRsaKeyPair(IN unsigned int ulDevHandle,
									IN unsigned int ulModulusBits,
									IN unsigned short usPriKeyFileID,
									IN unsigned short usPubKeyFileID);
//
unsigned int __stdcall AI_Dev_GenerateEccKeyPair(IN unsigned int ulDevHandle,
												  IN unsigned int ulModulusBits,
												  IN unsigned short usPriKeyFileID,
									IN unsigned short usPubKeyFileID,
									IN OUT unsigned char *pbkey);

/*
// C prototype : unsigned int __stdcall AI_Dev_ImportRsaKey(IN unsigned int ulDevHandle,
//										   IN unsigned short usPubKeyFileID,
//										   IN unsigned short usPriKeyFileID,
//										   IN RSA_PRIVATE_KEY *pstRsaPriKey);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usPubKeyFileID 公钥文件标识. 如果等于0,则忽略导入公钥的步骤.
//				 usPriKeyFileID 私钥文件标识. 如果等于0,则忽略导入私钥的步骤.
//				 pstRsaPriKey RSA私钥结构(其中同时包含了公钥元素).
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 导入RSA密钥到设备内部已经存在的密钥文件中. 当usPubKeyFileID不等于0时,
//				 在pstRsaPriKey结构体中必须具备合法的bits,modulus,publicExponent等3个元素.
//				 当usPriKeyFileID不等于0时,在pstRsaPriKey结构体中必须具备合法的bits,
//				 prime, primeExponent, coefficient等4个元素.
//				 注意,RSA_PRIVATE_KEY结构中密钥元素格式必须是高字节在前,低字节在后.
*/
unsigned int __stdcall AI_Dev_ImportRsaKey(IN unsigned int ulDevHandle,
										IN unsigned short usPriKeyFileID,
										IN unsigned short usPubKeyFileID,
										IN RSA_PRIVATE_KEY *pstRsaPriKey);

unsigned int __stdcall AI_Dev_ImportEccKey(IN unsigned int ulDevHandle,
											IN unsigned short usPriKeyFileID,
 											IN unsigned char *pstEccPriKey);

/*
// C prototype : unsigned int __stdcall AI_Dev_ExportRsaKey(IN unsigned int ulDevHandle,
//										IN unsigned short usPubKeyFileID,
//										IN unsigned short usPriKeyFileID,
//										OUT RSA_PRIVATE_KEY *pstRsaPriKey);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usPubKeyFileID 公钥文件标识. 如果等于0,则忽略导出公钥的步骤.
//				 usPriKeyFileID 私钥文件标识. 如果等于0,则忽略导出私钥的步骤.目前该参数必须为0.
//				 pstRsaPriKey RSA私钥结构(其中同时包含了公钥元素).
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 从指定的RSA密钥文件中导出密钥. 如果usPubKeyFileID不等于0,函数成功返回时,
//				 在pstRsaPriKey结构体中会返回bits,modulus,publicExponent等3个元素.
//				 目前,暂时不支持导出私钥的情况,所以usPriKeyFileID必须为0.
//				 注意,RSA_PRIVATE_KEY结构中密钥元素格式是高字节在前,低字节在后.
*/
unsigned int __stdcall AI_Dev_ExportRsaKey(IN unsigned int ulDevHandle,
										IN unsigned short usPriKeyFileID,
										IN unsigned short usPubKeyFileID,
										OUT RSA_PRIVATE_KEY *pstRsaPriKey);


unsigned int __stdcall AI_Dev_EccVer(IN unsigned int ulDevHandle,							
								IN unsigned char bMode, 
								  IN const unsigned char *pbPlainText,
							OUT unsigned char *pbVerR);

unsigned int __stdcall AI_Dev_EccSig(IN unsigned int ulDevHandle,							
										IN unsigned char bMode, 
									  IN const unsigned char *pbPlainText,   //P
							OUT unsigned char *pbSigRS);


unsigned int __stdcall AI_Dev_EccFit(IN unsigned int ulDevHandle,							
							IN const unsigned char *pbPlainText,   //设置ECC参数
							IN unsigned int ulPlainTextLen
							);

/*unsigned int __stdcall AI_Dev_EccSig(IN unsigned int ulDevHandle,							
							IN const unsigned char *pbPlainText,
							OUT const unsigned char *pbSigR,
							OUT const unsigned char *pbSigS,
							OUT unsigned char *pbVerR);	*/						
							
/*
// C prototype : unsigned int __stdcall AI_Dev_RsaEncrypt(IN unsigned int ulDevHandle,
//							IN unsigned short usPubKeyFileID,
//							IN const unsigned char *pbPlainText,
//							IN unsigned int ulPlainTextLen,
//							OUT unsigned char *pbCipherText,
//							IN OUT unsigned int *pulCipherTextLen,
//							IN unsigned int ulFlag);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usPubKeyFileID 公钥文件标识.
//				 pbPlainText 明文数据.
//				 ulPlainTextLen 明文数据的长度.
//				 pbCipherText 密文数据.
//				 pulCipherTextLen 进入函数时表示存放密文数据的缓冲区的大小,函数返回时
//					表示输出的密文数据的实际长度.
//				 ulFlag 目前必须设为0.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : RSA公钥加密. 该加密操作不涉及到任何编码.
*/

unsigned int __stdcall AI_Dev_EccEncrypt(IN unsigned int ulDevHandle,
										  IN unsigned short usPubKeyFileID,
										  IN unsigned int ulPlainTextLen,
										  IN const unsigned char *pbPlainText,
										  IN OUT unsigned int *pulCipherTextLen,
										  OUT unsigned char *pbCipherText,
										  IN unsigned int ulFlag);

unsigned int __stdcall AI_Dev_EccDecrypt(IN unsigned int ulDevHandle,
										  IN unsigned short usPriKeyFileID,
										  IN unsigned int ulCipherTextLen,
										  IN const unsigned char *pbCipherText,
										  IN OUT unsigned int *pulPlainTextLen,
										  OUT unsigned char *pbPlainText,
										  IN unsigned int ulFlag);
										  
unsigned int __stdcall AI_Dev_EccSignature(IN unsigned int ulDevHandle,
										  IN unsigned short usPriKeyFileID,
										  IN unsigned int ulCipherTextLen,
										  IN const unsigned char *pbCipherText,
										  IN OUT unsigned int *pulPlainTextLen,
										  OUT unsigned char *pbPlainText,
										  IN unsigned int ulFlag);
										  
unsigned int __stdcall AI_Dev_EccVerify(IN unsigned int ulDevHandle,
										  IN unsigned short usPubKeyFileID,
										  IN unsigned int ulPlainTextLen,
										  IN const unsigned char *pbPlainText,
										  IN OUT unsigned int *pulCipherTextLen,
										  OUT unsigned char *pbCipherText,
										  IN unsigned int ulFlag);


unsigned int __stdcall AI_Dev_ImportEccKey(IN unsigned int ulDevHandle,
											IN unsigned short usPriKeyFileID,
 											IN unsigned char *pstEccPriKey);

unsigned int __stdcall AI_Dev_ExportEccKey(IN unsigned int ulDevHandle,
											IN unsigned short usPubKeyFileID,
											OUT unsigned char *pstEccPubKey);
 

unsigned int __stdcall AI_Dev_RsaEncrypt(IN unsigned int ulDevHandle,
							IN unsigned short usPubKeyFileID,
							IN unsigned int ulPlainTextLen,
							IN const unsigned char *pbPlainText,
							IN OUT unsigned int *pulCipherTextLen,
							OUT unsigned char *pbCipherText,
							IN unsigned int ulFlag);

/*
// C prototype : unsigned int __stdcall AI_Dev_RsaDecrypt(IN unsigned int ulDevHandle,
//							IN unsigned short usPriKeyFileID,
//							IN const unsigned char *pbCipherText,
//							IN unsigned int ulCipherTextLen,
//							OUT unsigned char *pbPlainText,
//							IN OUT unsigned int *pulPlainTextLen,
//							IN unsigned int ulFlag);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 usPriKeyFileID 私钥文件标识.
//				 pbPlainText 密文数据.
//				 ulPlainTextLen 密文数据的长度.
//				 pbCipherText 明文数据.
//				 pulCipherTextLen 进入函数时表示存放明文数据的缓冲区的大小,函数返回时
//					表示输出的明文数据的实际长度.
//				 ulFlag 目前必须设为0.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : RSA私钥解密. 该解密操作不涉及到任何编码.
*/
unsigned int __stdcall AI_Dev_RsaDecrypt(IN unsigned int ulDevHandle,
							IN unsigned short usPriKeyFileID,
							IN unsigned int ulCipherTextLen,
							IN const unsigned char *pbCipherText,
							IN OUT unsigned int *pulPlainTextLen,
							OUT unsigned char *pbPlainText,
							IN unsigned int ulFlag);


/*
// C prototype : unsigned int __stdcall AI_Dev_GenerateRandom(IN unsigned int ulDevHandle,
//								IN unsigned int ulRandomLen,
//								OUT unsigned char *pbRandom);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulRandomlen 需要生成的随机数的长度.
//				 pbRandom 随机数.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 生成随机数. 当执行认证过程前,必须先调用该函数从硬件获取随机数,而且长度
//				 必须为4或8字节.
*/
unsigned int __stdcall AI_Dev_GenerateRandom(IN unsigned int ulDevHandle,
							IN unsigned int ulRandomLen,
							OUT unsigned char *pbRandom);

unsigned int __stdcall AI_Dev_P2Hash(IN unsigned int ulDevHandle,
									  IN unsigned char *bkey,
									  IN unsigned char key_len, 					  
									  IN unsigned int ulTextLen,
									  IN const unsigned char *pbText,
									  IN unsigned int num,        // 起始块号
									  IN unsigned int total_len,  // 总长度，最后一块有效
									  IN OUT unsigned char *pbDigest,  //H COMPRESS
									  IN unsigned char ulFlag);
 
unsigned int __stdcall AI_Dev_P1EcbCrypt(IN unsigned int ulDevHandle,
						 IN unsigned char *bkey,
						 IN unsigned char key_len,
						 IN unsigned char *in,		//  
						 IN unsigned char *out,		// 
						 IN unsigned int  len,
						 IN unsigned char  flag);
 
unsigned int __stdcall AI_Dev_P1CbcCrypt(IN unsigned int ulDevHandle,
						 IN unsigned char *bkey,
						 IN unsigned char key_len,
						 IN unsigned char *in,		//  
						 IN unsigned char *out,		// 
						 IN unsigned int  len,
						 IN unsigned char *iv,		// 
						 IN unsigned char  flag);
/*
// C prototype : unsigned int __stdcall AI_Dev_Encrypt(IN unsigned int ulDevHandle,
//						 IN unsigned char bKeyID,
//						 IN unsigned int ulAlgID,
//						 IN unsigned char *pbKeyValue,
//						 IN unsigned int ulKeyValueLen,
//						 IN const unsigned char *pbPlainText,
//						 IN unsigned int ulPlainTextLen,
//						 OUT unsigned char *pbCipherText,
//						 IN OUT unsigned int *pulCipherTextLen);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 bKeyID 对称密钥的标识符.
//				 ulAlgID 对称密钥算法,可以为ALGID_DES或ALGID_SSF33.
//				 pbKeyValue 密钥值,如果不等于NULL,则使用该密钥直接加密,
//							否则,使用存储在设备内部的标识为bKeyID的密钥加密.
//				 ulKeyValueLen 密钥长度.
//				 pbPlainText 明文数据.
//				 ulPlainTextLen 明文数据的长度.
//				 pbCipherText 密文数据.
//				 pulCipherTextLen 进入函数时表示存放密文数据的缓冲区长度,函数返回时
//					表示返回的密文数据的实际长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 使用存储在设备内部的对称密钥加密数据.
*/
//unsigned int __stdcall AI_Dev_DEVRESET(IN unsigned int ulDevHandle);

unsigned int __stdcall AI_Dev_Encrypt(IN unsigned int ulDevHandle,
						 IN unsigned char bKeyID,
						 IN unsigned int ulAlgID,
						 IN unsigned char    bAlgMode,		// 算法模式 addbysubin 20090528
						 IN unsigned int ulKeyValueLen,
						 IN unsigned char *pbKeyValue,
						 IN unsigned char*   pbIV,			// 初始向量 addbysubin 20090528
						 IN unsigned int ulPlainTextLen,
						 IN const unsigned char *pbPlainText,
						 IN OUT unsigned int *pulCipherTextLen,
						 OUT unsigned char *pbCipherText);

unsigned int __stdcall AI_Dev_EccEnc(IN unsigned int ulDevHandle,
						 IN unsigned char bMode,
						 IN unsigned int ulPlainTextLen,
						 IN const unsigned char *pbPlainText,
						 IN OUT unsigned int *pulCipherTextLen,
						 OUT unsigned char *pbCipherText);

unsigned int __stdcall AI_Dev_EccDec(IN unsigned int ulDevHandle,
						 IN unsigned char bMode,
						 IN unsigned int ulPlainTextLen,
						 IN const unsigned char *pbPlainText,
						 IN OUT unsigned int *pulCipherTextLen,
						 OUT unsigned char *pbCipherText);

unsigned int __stdcall AI_Dev_Keygen(IN unsigned int ulDevHandle,
						 IN unsigned char mode,
						 IN unsigned int ulPlainTextLen,
						 IN const unsigned char *pbPlainText,
						 IN OUT unsigned int *pulCipherTextLen,
						 OUT unsigned char *pbCipherText);						 

						 
/*
// C prototype : unsigned int __stdcall AI_Dev_Decrypt(IN unsigned int ulDevHandle,
//						 IN unsigned char bKeyID,
//						 IN unsigned int ulAlgID,
//						 IN unsigned char *pbKeyValue,
//						 IN unsigned int ulKeyValueLen,
//						 IN const unsigned char *pbCipherText,
//						 IN unsigned int ulCipherTextLen,
//						 OUT unsigned char *pbPlainText,
//						 IN OUT unsigned int *pulPlainTextLen);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 bKeyID 对称密钥的标识符.
//				 ulAlgID 对称密钥算法,可以为ALGID_DES或ALGID_SSF33.
//				 pbKeyValue 密钥值,如果不等于NULL,则使用该密钥直接解密,
//							否则,使用存储在设备内部的标识为bKeyID的密钥解密.
//				 ulKeyValueLen 密钥长度.
//				 pbCipherText 密文数据.
//				 ulCipherTextLen 密文数据的长度.
//				 pbPlainText 明文数据.
//				 pulPlainTextLen 进入函数时表示存放明文数据的缓冲区长度,函数返回时
//					表示返回的明文数据的实际长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 使用存储在设备内部的对称密钥解密数据.
*/
unsigned int __stdcall AI_Dev_Decrypt(IN unsigned int ulDevHandle,
						 IN unsigned char bKeyID,
						 IN unsigned int ulAlgID,
						 IN unsigned char    bAlgMode,		// 算法模式 addbysubin 20090528
						 IN unsigned int ulKeyValueLen,
						 IN unsigned char *pbKeyValue,
						 IN unsigned char*   pbIV,			// 初始向量 addbysubin 20090528
						 IN unsigned int ulCipherTextLen,
						 IN const unsigned char *pbCipherText,
						 IN OUT unsigned int *pulPlainTextLen,	
						 OUT unsigned char *pbPlainText);


/*
// C prototype : unsigned int __stdcall AI_Dev_Hash(IN unsigned int ulDevHandle,
//					  IN unsigned int ulAlgID,
//					  IN const unsigned char *pbText,
//					  IN unsigned int ulTextLen,
//					  OUT unsigned char *pbDigest,
//					  IN OUT unsigned int *pulDegistLen,
//					  IN unsigned int ulFlag);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 ulAlgID 摘要算法,可以为ALGID_SHA1或ALGID_MD5.
//				 pbText 需要计算摘要的原始数据.
//				 ulTextLen 原始数据的长度.
//				 pbDigest 摘要值.
//				 pulDegestLen 进入函数时表示存放摘要算法结果的缓冲区长度,函数返回时
//					表示返回的摘要数据的实际长度.
//				 ulFlag 标志,目前必须设为0.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 对数据进行摘要计算.
*/
unsigned int __stdcall AI_Dev_Hash(IN unsigned int ulDevHandle,
					  IN unsigned int ulAlgID,
					  IN unsigned int ulTextLen,
					  IN const unsigned char *pbText,
					  IN OUT unsigned int *pulDigestLen,
					  OUT unsigned char *pbDigest,
					  IN unsigned int ulFlag);


unsigned int __stdcall AI_Dev_CHash(IN unsigned int ulDevHandle,
					  IN unsigned int ulTextLen,
					  IN const unsigned char *pbText,
					  IN OUT unsigned int *pulDigestLen,
					  OUT unsigned char *pbDigest);


unsigned int __stdcall AI_Dev_RunProgram(IN unsigned int ulDevHandle,
										IN const unsigned short usFileID,
										IN const unsigned char *pbParam,
										IN const unsigned int ulParamLen,
										OUT unsigned char *pbOut,
										IN OUT unsigned int *pulOutLen);



/*
// C prototype : unsigned int __stdcall AI_Dev_CreateSecureChannel(IN unsigned int ulDevHandle,
//							IN unsigned char *pbServerRandCipher,
//							IN unsigned int ulServerRandCipherLen,
//							IN unsigned short *pusUserCertPriKeyFilePath,
//							IN unsigned int ulFileIDsInPath,
//							OUT unsigned char *pbDeviceRandCipher,
//							IN OUT unsigned int *pulDeviceRandCipherLen,
//							IN unsigned int ulServerFlag,
//							IN unsigned int ulReserved);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pbServerRandCipher 设备公钥对服务器随机数的加密结果.
//				 ulServerRandCipherLen 设备公钥对服务器随机数的加密后密文的长度,必须为128.
//				 pusUserCertPriKeyFilePath 设备私钥文件的路径.
//				 ulFileIDsInPath pusUserCertPriKeyFilePath参数中包含的文件标识的个数.
//				 pbDeviceRandCipher 用于存放服务器公钥对设备随机数的加密结果,如果该参数为NULL,
//					则pulDeviceRandCipherLen参数将返回pbDeviceRandCipher缓冲区的最小空间.
//				 pulDeviceRandCipherLen 服务器公钥对设备随机数的加密后密文的长度;作为输入参数时
//					指示pbDeviceRandCipher缓冲区的大小;作为输出参数时指示密文的实际长度;
//				 ulServerFlag 该参数当导出密钥时有效,导入密钥时将被忽略. 如果为0表示导出设备
//					密钥到管理服务器;如果为1表示导出设备密钥到应用服务器.
//				 ulReserved 保留参数,必须设为0.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 创建安全通道.
//				 该函数假设调用者已经调用了AI_Dev_LockDev执行了线程同步.
*/
unsigned int __stdcall AI_Dev_CreateSecureChannel(IN unsigned int ulDevHandle,
							IN unsigned char *pbServerRandCipher,
							IN unsigned int ulServerRandCipherLen,
							IN unsigned short *pusUserCertPriKeyFilePath,
							IN unsigned int ulFileIDsInPath,
							OUT unsigned char *pbDeviceRandCipher,
							IN OUT unsigned int *pulDeviceRandCipherLen,
							IN unsigned int ulServerFlag,
							IN unsigned int ulReserved);

/*
// C prototype : unsigned int __stdcall AI_Dev_BuildSecureChannelCommand(IN unsigned char *pbSessionKey,
//													 IN unsigned int ulSessionKeyLen,
//								`					 IN unsigned char *pbInitValue,
//													 IN unsigned char *pbRawCmd,
//													 IN unsigned int ulRawCmdLen,
//													 OUT unsigned char *pbSecChannelCmd,
//													 IN OUT unsigned int *pulSecChannelCmdLen);
// parameter(s): pbSessionKey 会话密钥.
//				 ulSessionKeyLen 会话密钥的字节数,目前必须设为16.
//				 pbInitValue 计算MAC码的初始值.
//				 pbRawCmd 原始命令数据.
//				 ulRawCmdLen 原始命令数据的长度.
//				 pbSecChannelCmd 用于保存安全通道命令的缓冲区首地址,如果该参数为NULL,则pulSecChannelCmdLen
//					参数将返回实际所需要的缓冲区大小.
//				 pulSecChannelCmdLen 作为输入参数时,指示pbSecChannelCmd缓冲区的大小;作为输出参数时指示所
//					构造的安全通道命令的实际长度.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     :构造安全通道命令.
//				在调用该函数前,调用者必须保证已经从设备生成了4字节随机数,连同4字节0填补至8字节,作为
//				计算MAC的初始值,也就是pbInitValue参数的值.
*/
unsigned int __stdcall AI_Dev_BuildSecureChannelCommand(IN unsigned char *pbSessionKey,
													 IN unsigned int ulSessionKeyLen,
													 IN unsigned char *pbInitValue,
													 IN unsigned char *pbRawCmd,
													 IN unsigned int ulRawCmdLen,
													 OUT unsigned char *pbSecChannelCmd,
													 IN OUT unsigned int *pulSecChannelCmdLen);


/*
// C prototype : AI_Dev_WrapKey(IN unsigned int ulDevHandle,
//							IN OUT unsigned char *pbData,
//							IN OUT unsigned int *pulDataLen,
//							IN unsigned short *pusRsaKeyFilePath,
//							IN unsigned int ulFileIDsInPath,
//							IN unsigned int ulImportFlag,
//							IN unsigned int ulReserved);
// parameter(s): ulDevHandle 设备句柄. 由AI_Dev_ConnectDev函数返回.
//				 pbData 对称密钥的加密结果,当导入密钥时,数据内容为设备公钥对对称密钥的加密结果,
//					此时该参数为输入参数; 当导出对称密钥时,数据内容为外部公钥对对称密钥的
//					加密结果,此时该参数为输出参数. 当导出密钥时,如果pbData=NULL,则pulDataLen
//					将返回实际返回数据的长度.
//				 pulDataLen pbData参数所包含的数据长度. 当导入对称密钥时,该参数为输入参数;
//					当导出对称密钥时,该参数为输出参数.
//				 pusRsaKeyFilePath 当导入密钥时,为设备私钥文件的路径. 当导出密钥时,为调用者
//					公钥文件的路径.
//				 ulFileIDsInPath pusUserCertPriKeyFilePath参数中包含的文件标识的个数.
//				 ulImportFlag 用于标识是导入密钥还是导出密钥的标志.如果为1则表示导入密钥,为0
//					则标识导出密钥.
//				 ulReserved 保留参数,必须设为0.
// return value: 0 - 成功;
//				 其它值 - 错误码;
// remarks     : 对称密钥导入/导出.
*/
unsigned int __stdcall AI_Dev_WrapKey(IN unsigned int ulDevHandle,
							IN OUT unsigned char *pbData,
							IN OUT unsigned int *pulDataLen,
							IN unsigned short *pusRsaKeyFilePath,
							IN unsigned int ulFileIDsInPath,
							IN unsigned int ulImportFlag,
							IN unsigned int ulReserved);


/*

unsigned int AI_Dev_UpdateFileActive(
		IN int lTokenHandle,				//设备句柄
		IN unsigned short	usFileID,
		IN	void* pbData,					// 写入的数据
		IN	unsigned short wOffset,			// 文件偏移量
		IN	unsigned short wLen	);

unsigned int AI_ImportRSAPubkeyActive(
		IN int lTokenHandle,				//设备句柄
		IN unsigned short usFileID,			//公钥文件标识
		IN	unsigned char* pbData,					// 写入的公钥数据
		IN	unsigned short wLen				// 公钥数据长度
		);

unsigned int AI_ImportRSAPrikeyActive(
		IN int lTokenHandle,				//设备句柄
		IN unsigned short usFileID,			//私钥文件标识
		IN	unsigned char* pbData,					// 写入的公钥数据
		IN	unsigned short wLen				// 公钥数据长度
	);

*/

unsigned int __stdcall AI_Dev_AddRealKey(
						IN unsigned int ulDevHandle,
						IN unsigned char bKeyID,
						IN unsigned int ulAlgID,
						IN unsigned int ulType,			//密钥类型,如果为0,则默认为加密/解密密钥
						IN unsigned int ulValueLen,
						IN const unsigned char *pbValue,
						IN unsigned int ulUseSec,
						IN unsigned int ulUpdateSec,
						IN unsigned int ulRetryCount);

unsigned int __stdcall  AI_Dev_IsAisinoCOS(IN unsigned int ulDevHandle);

unsigned int __stdcall  AI_Dev_TestEflash(unsigned int ulDevHandle);

unsigned int __stdcall AI_Dev_SHAinit(IN unsigned int ulDevHandle);

unsigned int __stdcall AI_Dev_SHAupdate(IN unsigned int ulDevHandle,unsigned char  *pbData,unsigned int dwDataLen);

unsigned int __stdcall AI_Dev_SHAdigest(IN unsigned int ulDevHandle,unsigned int *pHash);

#ifdef __cplusplus
}
#endif

#endif // __DEVICEAPI_H
