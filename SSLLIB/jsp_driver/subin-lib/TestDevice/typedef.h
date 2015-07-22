#ifndef __TYPEDEF_H
#define __TYPEDEF_H
//#include "winerr.h"
#ifndef WIN32
#define	__stdcall
#endif
   
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef UCHAR
typedef unsigned char UCHAR;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef BOOLEAN
typedef BYTE  BOOLEAN;
#endif

#ifndef BOOL
typedef int	BOOL;
#endif

#ifndef DWORD
typedef unsigned int DWORD;
#endif

#ifndef LONG_PTR
typedef void * LONG_PTR;
#endif

#ifndef ULONG_PTR
typedef void * ULONG_PTR;
#endif

#ifndef DWORD_PTR
typedef ULONG_PTR DWORD_PTR;
#endif

#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef HANDLE
typedef void * HANDLE;
#endif

#ifndef LONG
typedef int LONG;
#endif

#ifndef ULONG
typedef unsigned int ULONG;
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#endif

#ifndef		MAX_PATH
#define		MAX_PATH		260
#endif

#ifndef		MAX_DEVICE_NUM
#define		MAX_DEVICE_NUM				0x00000008		//最大支持的设备个数
#endif

#ifndef MAXIMUM_ATTR_STRING_LENGTH
#define MAXIMUM_ATTR_STRING_LENGTH		32
#endif

#pragma pack(push,1)


typedef struct  
{
	DWORD	dwState;				// 设备状态: 0 - 未连接; 1 - 已连接
	//char	szDevicePath[MAX_PATH];
	char	szDevicePath[200];
}/*__attribute__((packed))*/ DEVICE_LIST;

//共享内存管理器
typedef struct 
{
	DEVICE_LIST stDeviceList_Hid[MAX_DEVICE_NUM];
	DEVICE_LIST stDeviceList_UKey[MAX_DEVICE_NUM];
	DEVICE_LIST stDeviceList_KeyEx[MAX_DEVICE_NUM];
	DEVICE_LIST stDeviceList_PCSC[MAX_DEVICE_NUM];//其实本库中是不需要维护PCSC设备列表的
}/*__attribute__((packed))*/ SHM_CONTEXT;

typedef unsigned int (__stdcall PFN_TRANSMIT)(IN void *pstDeviceManager, 
						  IN const unsigned char *pbSendBuff, 
						  IN unsigned int ulSendLen, 
						  OUT unsigned char *pbRecBuff, 
						  IN OUT unsigned int *pulRecLen,
						  IN unsigned int ulFlag);


//设备管理器
typedef struct  
{
	void *			hDevice;				// 真正的设备句柄,由CreateFile返回
//	long				hDevice;	
	DWORD			dwShareMode;			// 对于PCSC设备来说,当卡被拔出时,原来的句柄就不能直接使用了,必须调用
											// SCardReconnect函数重新连接端口,该函数需要这个参数.
	DWORD			dwDeviceType;			// 设备类型
	char			szDevicePath[MAX_PATH];	// 设备路径(CreateFile传入的名称)
	BYTE			abSerialNO[16];			// 8字节的卡片序列号
	BYTE			abAtrInfo[MAXIMUM_ATTR_STRING_LENGTH];//卡片复位信息
	BYTE			bAtrLen;				// 复位信息的长度
	DWORD			dwCosType;				// COS类型
	WORD			wCosVersion;			// COS版本
	DWORD			dwAbility;				// COS能力
	DWORD			dwConnectState;			// 设备连接状态
	DWORD			dwIndex;				// 设备序号
	DWORD			dwConnectCount;			// 连接计数
	PFN_TRANSMIT	*pfnTransmit;			// 发送命令的函数指针
//	PFN_TRANSMIT	*pfnTransmit1;			// 发送简单命令的函数指针
	HANDLE			hMutex;					// 同步对象的句柄
//	HANDLE			hEvent;					// 同步事件的句柄
}/*__attribute__((packed))*/ DEVICE_MANAGER;


#pragma pack(pop)

#endif // __TYPEDEF_H
