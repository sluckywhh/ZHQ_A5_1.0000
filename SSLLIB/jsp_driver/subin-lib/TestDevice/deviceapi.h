#ifndef __DEVICEAPI_H
#define __DEVICEAPI_H

#ifdef __cplusplus

#ifndef __stdcall
#define __stdcall
#endif
#include "typedef.h"

#define		BLOCK_LEN_LARGE_ENCRYPT			5600		//�ڲ�RAMΪ7680ʱ
#define		BLOCK_LEN_FILE			2048		//��д���������ļ���󳤶�
#define		ONEVER			0x1000		//
#define		TWOVER			0x2000		//
#define		MAX_ECCLEN		1792		//һ��SM2�ӽ��ܵ���󳤶�

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
#define		DEVICETYPE_PCSC				0x00000001 		//PCSC�豸
#define		DEVICETYPE_HID				0x00000002 		//HID�豸
#define		DEVICETYPE_UKEY				0x00000004 		//UKey�豸
//#define		DEVICETYPE_KEY_EX			0x00000008 		//��С�洢��Key	
#endif

//macro definition of connect mode
#ifndef		CONNECTMODE
#define		CONNECTMODE
#define		CONNECT_MODE_SHARE			0x00000000 		//�Թ���ʽ�򿪶˿�
#define		CONNECT_MODE_EXCLUSIVE		0x00000001 		//�Զ�ռ��ʽ�򿪶˿�
#endif

//macro definition of status flag
//wanglei add 20090521	
#define     STATUS_FLAG_BASE			0x20002200 

#define		STATUS_FLAG_TOKEN_PRESENT	STATUS_FLAG_BASE+0x00000000 		//��Ƭ�Ƿ����
#define		STATUS_FLAG_CARD_ID			STATUS_FLAG_BASE+0x00000001 		//��ȡ��Ƭ���
#define		STATUS_FLAG_ABILITY			STATUS_FLAG_BASE+0x00000002 		//��ȡ�豸����
#define		STATUS_FLAG_FREESPACE		STATUS_FLAG_BASE+0x00000003 		//��ȡʣ��ռ�Ĵ�С
#define		STATUS_FLAG_COS_VER			STATUS_FLAG_BASE+0x00000004 		//��ȡCOS�汾
#define		STATUS_FLAG_HARDWARE_VER	STATUS_FLAG_BASE+0x00000005 		//��ȡӲ���汾
#define		STATUS_FLAG_FIRMWARE_VER	STATUS_FLAG_BASE+0x00000006 		//��ȡ�̼�����汾
#define		STATUS_FLAG_LIB_VER			STATUS_FLAG_BASE+0x00000007 		//��ȡAPI�汾

#define		STATUS_FLAG_FREEERRORPIN	STATUS_FLAG_BASE+0x00000008L		//��ȡpin�Ĵ����Դ��� subin 20130618

//macro definition of device ability
#define		DEVICE_ABILITY_RSA			0x00000001 		//�Ƿ����RSA����
#define		DEVICE_ABILITY_DES			0x00000002 		//�Ƿ����DES/3DES����
#define		DEVICE_ABILITY_RAND			0x00000004 		//�Ƿ�������������������
#define		DEVICE_ABILITY_SSF33		0x00000008 		//�Ƿ����SSF33����
#define		DEVICE_ABILITY_MD5			0x00000010 		//�Ƿ����MD5����
#define		DEVICE_ABILITY_SHA1			0x00000020 		//�Ƿ����SHA-1����
#define		DEVICE_ABILITY_SCB2			0x00000040 		//�Ƿ����SCB2����
		
//macro definition of file type
#define		FILE_TYPE_DATA				0x00000001 		//�����ļ�
#define		FILE_TYPE_RSAPUBKEY			0x00000002 		//RSA��Կ�ļ�
#define		FILE_TYPE_RSAPRIKEY			0x00000003 		//RSA˽Կ�ļ�
#define		FILE_TYPE_KEY				0x00000004 		//�Գ���Կ�ļ�
#define		FILE_TYPE_LICENSE			0x00000008 		//��Ȩ�ļ�
#define 	FILE_TYPE_PROGRAM			0x00000005 
#define 	FILE_TYPE_USERDATA			0x00000006 
//macro definition of access mode
#define		ACCESS_MODE_ALWAYS			0x00000000 		//Ȩ����Զ����
#define		ACCESS_MODE_NEVER			0xFFFFFFFF		//Ȩ����Զ������
#define		ACCESS_MODE_USER			0x00000001 		//��ҪУ���û�����
#define		ACCESS_MODE_SO				0x00000002 		//��ҪУ�����Ա����
#define		ACCESS_MODE_CERT			0x00000004 		//��Ҫ֤����֤

//macro definition of login type
#define		LOGIN_TYPE_USER				0x00000001 		//��ͨ�û�
#define		LOGIN_TYPE_SO				0x00000002 		//����Ա

//macro definition of alg
#define		ALGID_DES					0x00000001 		//DES/3DES�㷨
#define		ALGID_SSF33					0x00000002 		//SSF33�㷨
#define		ALGID_SHA1					0x00000003 		//SHA-1�㷨
#define		ALGID_MD5					0x00000004 		//MD5�㷨
#define		ALGID_SCB2					0x00000005 		//SCB2�㷨

#define		ALGID_SMS4					0x00000007 		//SMS4�㷨
#define		ALGID_AES					0x00000008 		//AES�㷨

#define		ALGID_P1					0x00000006 		//P1�㷨
#define		ALGID_PHUSH					0x00000032 		//PHUSH�㷨

//macro definition of rsa padding mode
//#define	RSA_PADDING_MODE_X509		0x00000001 		//��RSA����
//#define	RSA_PADDING_MODE_PKCS		0x00000002 		//����PKCS V1.5�淶�ļ���

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
#define		AI_SUCCESS					0				//�ɹ�
#define		AI_UNKNOWN_ERROR			(CHANGERR^0xE0020001)		//δ֪����
#define		AI_INVALID_PARAMETER		(CHANGERR^0xE0020002)		//��������
#define		AI_BUFFER_NOT_ENOUGH		(CHANGERR^0xE0020003)		//�����ռ䲻��
#define		AI_HOST_MEMORY				(CHANGERR^0xE0020004)		//�����ڴ治��
#define		AI_FUNC_NOT_SUPPORT			(CHANGERR^0xE0020005)		//���ܲ�֧��
#define		AI_DEVICE_NUM_TOO_LARGE		(CHANGERR^0xE0020006)		//�豸��������
#define		AI_INVALID_HANDLE			(CHANGERR^0xE0020007)		//�����Ч
#define		AI_DEVICE_NO_RESPONSE		(CHANGERR^0xE0020008)		//�豸����Ӧ
#define		AI_NO_DEVICE				(CHANGERR^0xE0020009)		//û���豸
#define		AI_DEVICE_NOT_IDENTIFIED	(CHANGERR^0xE002000A)		//�豸����ʶ��(��λ��Ϣ����)
#define		AI_BAD_CHECKSUM				(CHANGERR^0xE002000B)		//ͨ��У�����
#define		AI_ERR_SEND_DATA			(CHANGERR^0xE002000C)		//�������ݹ����г���
#define		AI_ERR_READ_DATA			(CHANGERR^0xE002000D)		//��ȡ���ݹ����г���
#define		AI_COMM_TIMEOUT				(CHANGERR^0xE002000E)		//��ȡ���ݹ����з�����ʱ
#define		AI_BAD_DATA_FORMAT			(CHANGERR^0xE002000F)		//���ݸ�ʽ����ʶ��
#define		AI_NO_TOKEN					(CHANGERR^0xE0020010)		//û�����ܿ�
#define		AI_COS_NOT_RECOGNIZED		(CHANGERR^0xE0020011)		//����ʶ���COS
#define		AI_DEVICE_REMOVED			(CHANGERR^0xE0020012)		//�豸�ѱ��Ƴ�
//wangelei add 20090426
#define		AI_PORT_ALREADY_CONNECTED	(CHANGERR^0xE0021007)		//�˿��Ѿ����ӹ���
#define		AI_SSX45_EFLASH_ERROR		(CHANGERR^0xE0020013)		//45оƬ���Դ���
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
// parameter(s): ulDeviceType �豸����,��DEVICETYPE_XXX����. �ڸú�����,�����豸���Ϳ���
//								"��"����ʹ��,��Ӧλ��1���ʾ��Ҫö�ٸ��豸���͵��豸.
//				 szDeviceName ���ڴ���豸�����б�Ļ������׵�ַ,���ΪNULL,��pulDeviceNameLen
//							�������豸�����б��ʵ�ʳ���.
//				 pulDeviceNameLen ���뺯��ʱ,�ò��������ݱ�ʾ������szDeviceName�ĳ���,
//						��������ʱ,�ò���������ָʾ�������д�ŵ��豸�����б��ʵ�ʳ���.
//				 ulFlag ��־: ��ֵĿǰ����Ϊ1������ֵ������
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �ú���ö�ٵ�ǰϵͳ����֧�ֵ��豸�б�. ÿһ���豸����֮����'\0'��Ϊ�ָ���.
//				 ����,�ú������ص��豸�б��в������������豸.
*/
unsigned int __stdcall AI_Dev_EnumDev(OUT char *szDeviceName, 
							IN OUT unsigned int *pulDeviceNameLen,
							IN unsigned int ulDeviceType, 
							IN unsigned int ulFlag);


/*
// C prototype : unsigned int __stdcall AI_Dev_ConnectDev(IN const char *szDeviceName, 
//										IN unsigned int ulMode, 
//										OUT unsigned int *pulDevHandle);
// parameter(s): szDeviceName �豸����
//				 ulMode ����ģʽ,����ֽڱ�ʾ�Թ���򿪶˿ڻ����Զ�ռ��ʽ�򿪶˿�,��CONNECT_MODE_XXX����.
//						����Ǵ����豸,��3�ֽڱ�ʾ������(Ŀǰ֧��9600��115200,�����Ϊ0,���ڲ���Ĭ����
//						��߲����������豸�Ի�ȡ���ͨ������),���������豸���͸�3�ֽڱ���Ϊ0.
//				 pulDevHandle �豸���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ������Token(���ܿ�)������. ���ڴ����豸,�豸����Ϊ"COM1", "COM2"��. ���������豸����,
//				 �豸���ƿ�����AI_Dev_EnumDev����. ���øú���ʱһ��������������ĵط��Ǹú����Ĺ�����
//				 ���������ܿ�������,���������豸,Ҳ���Ƕ��ڶ������������͵��豸,�����ǰû�в��뿨Ƭ,
//				 ���øú������ܳɹ�. ����ú������ɹ����ú�,�û������γ�����Ƭ֮�������²����˿�Ƭ,
//				 �������µ��ñ�����,����Ҳ�����ܶ��µĿ�Ƭ���в���.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �Ͽ����豸������.
*/
unsigned int __stdcall AI_Dev_DisconnectDev(IN unsigned int ulDevHandle);

/*
// C prototype : unsigned int __stdcall AI_Dev_TransportCmd(IN unsigned int ulDevHandle, 
//											IN const unsigned char *pbSendBuff, 
//											IN unsigned int ulSendLen, 
//											OUT unsigned char *pbRecBuff, 
//											IN OUT unsigned int *pulRecLen,
//											IN unsigned int ulFlag);
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pbSendBuff ��������.
//				 ulSendLen �������ݵĳ���.
//				 pbRecBuff ������Ӧ���ݵĻ�������ʼ��ַ.
//				 pulRecLen ���뺯��ʱ,��ʾ���ջ������ĳ���; ��������ʱ��ʾ��Ӧ���ݵ�ʵ�ʳ���.
//				 ulFlag ��־,����豸��������Ҫ����,�Ƿ�ֱ��ȡ��. ���ֵΪ0��ֱ��ȡ��,����ȡ.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �ú�������ֱ����IC������APDU����. ����������AI_BUFFER_NOT_ENOUGHʱ,pulRecLen
//				 ������ָʾʵ����Ҫ��������������ֽ���.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulControlCode ��������.
//				 pbInBuff ������Ҫ����������.
//				 ulInLen �������ݵĳ���.
//				 pbOutBuff ������Ӧ���ݵĻ�������ʼ��ַ.
//				 pulOutLen ���뺯��ʱ,��ʾ���ջ������ĳ���; ��������ʱ��ʾ��Ӧ���ݵ�ʵ�ʳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �ú�������ֱ�����豸���Ϳ�������. Ϊ�˱�֤Ӧ�ó���ļ�����,�����û���Ҫֱ�ӵ��øú���.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulFlag ��־. 
//					STATUS_FLAG_TOKEN_PRESENT,��ȡ��ǰToken(��Ƭ)���ڵ�״̬,������4�ֽڵ�unsigned
//						int������. ����Ϊ����ֵ:
//						1: Tokenһֱ����;
//						0: ��ʾ��ǰû��Token���ڻ����Դ��ϴγɹ�����AI_Dev_ConnectDev������Token�������Ƴ�;
//					STATUS_FLAG_CARD_ID,��ȡ��Ƭ���,һ������½�����8�ֽڵĿ�Ƭ���к�.
//					STATUS_FLAG_ABILITY,��ȡ�豸����,������4�ֽڵ�unsigned int������.��
//						ÿһλ�Ķ����DEVICE_ABILITY_XXX����.�����ӦΪ��1,���ʾ���и�����.
//					STATUS_FLAG_FREESPACE,��ȡʣ��ռ�Ĵ�С,����4�ֽڵ�unsigned int������.
//					STATUS_FLAG_COS_VER,��ȡCOS�汾,����2�ֽڵ�unsigned short������.
//					STATUS_FLAG_HARDWARE_VER,��ȡӲ���汾,����2�ֽ�unsigned short������.
//					STATUS_FLAG_FIRMWARE_VER,��ȡ�̼�����汾,����2�ֽ�unsigned short������.
//					STATUS_FLAG_LIB_VER,��ȡAPI�汾,����2�ֽ�unsigned short������.
//				 pbOut ���շ������ݵĻ�������ʼ��ַ.
//				 pulOutLen ���뺯��ʱ,��ʾ���ջ������ĳ���; ��������ʱ��ʾ�������ݵ�ʵ�ʳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �ú������ڻ�ȡ�豸�ĵ�ǰ״̬. ����STATUS_FLAG_TOKEN_PRESENT����,�������ֵ
//				 Ϊ0,˵�����ϴ����Ӷ˿ڵ���ǰ��ѯ״̬���ڼ�,Token�������Ƴ���,��ʹ�Ƴ�������
//				 �²�����ԭʼToken,����ֵ����Ϊ0. �������ֵΪ1,�������Ƭ�Դ����Ӷ˿ڵ�����
//				 ����û�б��Ƴ���. ���������Token,�����������Ӷ˿�,���򷵻�״ֵ̬��һֱ��0.
*/
unsigned int __stdcall AI_Dev_GetState(IN unsigned int ulDevHandle, 
						   IN unsigned int ulFlag, 
						   IN OUT unsigned int *pulOutLen,
						   OUT void *pbOut);


/*
// C prototype : unsigned int __stdcall AI_Dev_GetErrs(IN unsigned int ulErrCode, 
//						   OUT char *szErrMsg, 
//						   IN OUT unsigned int *pulMsgLen);
// parameter(s): ulErrCode �ɱ��ⷵ�صĴ�����.
//				 szErrMsg ���صĴ�����Ϣ.
//				 pulMsgLen ���뺯��ʱ��ʾ������szErrMsg�ĳ���,��������ʱ��ʾ����
//						�Ĵ�����Ϣ��ʵ�ʳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ���ݴ������ȡ������Ϣ.
*/
unsigned int __stdcall AI_Dev_GetErrs(IN unsigned int ulErrCode, 
						   IN OUT unsigned int *pulMsgLen,	
						   OUT char *szErrMsg);



/*
// C prototype : unsigned int __stdcall AI_Dev_LockDev(IN unsigned int ulDevHandle,
//							IN unsigned int ulTimeout);
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulTimeout �ȴ�ʱ��,��λΪ����.���ֵΪ0xFFFFFFFF,��ʾһֱ�ȵ��¼�����Ϊֹ.
// return value: WAIT_OBJECT_0 - �ɹ�;
//				 WAIT_FAILED - ����ִ��ʧ��;
//				 WAIT_TIMEOUT - ������ʱ����;
//				 ����ֵ - ������;
// remarks     : ͬ���豸����.���һ���߳�ͨ�����øú�������˶��豸�ķ��ʿ���Ȩ��,
//				 ֱ�����߳�ͨ������AI_Dev_UnlockDev�����ͷ��Լ��ķ��ʿ���Ȩ��֮ǰ,
//				 ����Ҳ����AI_Dev_LockDev����ϣ����ȡ���豸�ķ���Ȩ�޵��߳̽�������.
//				 Ϊ�˱��϶��豸��һ��"��������"��˳�����,���м䲻����Ϊ�����̶߳�
//				 �豸�ķ��ʶ��ж�,���Ǿͱ�����"��������"����ǰ����øú���,��������
//				 ȷ���Ѿ���ɺ�,�ٵ���AI_Dev_UnlockDev�����ͷſ���Ȩ��,�������߳�Ҳ��
//				 ��ȡ���豸���ʵĻ���. �����ڵ��øú���ʱ,���뱣֤��AI_Dev_UnlockDev
//				 ���ʹ��.
*/
unsigned int __stdcall AI_Dev_LockDev(IN unsigned int ulDevHandle,
							IN unsigned int ulTimeout);


/*
// C prototype : unsigned int __stdcall AI_Dev_UnlockDev(IN unsigned int ulDevHandle);
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �ͷŵ�ǰ�̶߳��豸�ķ��ʿ���Ȩ��. �ú���������AI_Dev_LockDev����
//				 ���ʹ��.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usAppID ����Ψһ��ʶһ��Ӧ��,����ֵ��Χ��0x1000��0xEFFF֮��.
//				 pbUserPin �û�����,���Ա����ļ��Ķ�д���ƻ���Կ��ʹ�ÿ���.
//				 ulUserPinLen �û�����ĳ���.
//				 ulUserPinRetryCount �û��������������Դ���. ���Ϊ0,��ϵͳ�ڲ�����ΪĬ��ֵ.
//				 pbSOPin ����Ա����,���Խ����û�������ض���Ȩ�޿���.
//				 ulSOPinLen ����Ա����ĳ���.
//				 ulSOPinRetryCount ����Ա�������������Դ���. ���Ϊ0,��ϵͳ�ڲ�����ΪĬ��ֵ.
//				 ulFlag ��־,����ֵ����:
//					0 - �û�����͹���Ա���װ����ǰӦ����;
//					1 - �û�����͹���Ա���װ����Ƭ��Ŀ¼��,���ǿ�Ƭ����Ϊ��,���򷵻ش���;
//					2 - �û�����͹���Ա���װ����Ƭ��Ŀ¼��,�����Ŀ¼���Ѿ�������Կ�ļ�,��
//						������װ����Ĳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ����Ӧ��.
//				 �������pbUserPin�Ͳ���pbSOPinΪNULL,�����ڲ�������װ�û������Լ�����Ա����,
//				 �������Ӧ���ڿ�Ƭ�ĸ�Ŀ¼�°�װ��ȫ��PIN,����ܻ���˵���. 
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usAppID ����Ψһ��ʶһ��Ӧ��.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ɾ��Ӧ��. ֻ���Թ���Ա��ݵ�¼�豸�����ִ�иò���,���AI_Dev_Login����.


unsigned int __stdcall AI_Dev_DeleteApplication(IN unsigned int ulDevHandle,
								   IN unsigned short usAppID);

unsigned int __stdcall AI_Dev_BlankKey(unsigned int ulDevHandle);

// C prototype : unsigned int __stdcall AI_SelectApplication(IN unsigned int ulDevHandle,
//								   IN unsigned short usAppID);							   
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usAppID ����Ψһ��ʶһ��Ӧ��.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ѡ��Ӧ��.

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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usFileID ����Ψһ��ʶһ���ļ�,����ֵ��Χ��0x1000��0xEFFF֮��.
//				 ulFileType �ļ�����,��FILE_TYPE_XXX����.
//				 usSize �ļ���С����. ����FILE_TYPE_RSAPUBKEY��FILE_TYPE_RSAPRIKEY,�ò���Ϊģ��(bits).
//				 ulReadSec ����FILE_TYPE_DATA,FILE_TYPE_LICENSE�ļ���������,��ʾ��ȡ�ļ���Ҫ�����Ȩ��.
//					����FILE_TYPE_LICENSE�ļ�����,�ò���������ΪACCESS_MODE_CERT.
//				 ulUpdateSec ����FILE_TYPE_DATA,FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY,FILE_TYPE_LICENSE
//					�ļ���������,��ʾ�����ļ�������Ҫ�����Ȩ��.
//					����FILE_TYPE_LICENSE�ļ�����,�ò���������ΪACCESS_MODE_CERT.
//				 ulUseSec ����FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY�ļ���������. 
//					����FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY�����ļ�,���ʾʹ����Կʱ��Ҫ�����Ȩ��; 
//					�����������͵��ļ�,�ò���������.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �����ļ�. 
//				 �����ļ���Ȩ������˵������:
//				 ���Ȩ������ΪACCESS_MODE_ALWAYS,��ʾȨ����Զ����,������ͨ�û������Ա��¼���ɲ���.
//				 ���Ȩ������ΪACCESS_MODE_NEVER,��ʾȨ����Զ������,��ָ���Ĳ����û�������ִ��.
//				 ���Ȩ������ΪACCESS_MODE_USER,��ʾ��ҪУ���û������,����ִ����Ӧ�Ĳ���.
//				 ���Ȩ������ΪACCESS_MODE_SO,��ʾ��ҪУ�����Ա�����,����ִ����Ӧ�Ĳ���.
//				 ���Ȩ������ΪACCESS_MODE_CERT,��ʾ��ҪУ��֤��Ϸ��Ժ�,����ִ����Ӧ�Ĳ���.
//				 ע��,�����ļ���Ȩ������ֻ���ڵ���AI_ActivateFile֮��ſ�ʼ��Ч.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usFileID ����Ψһ��ʶһ���ļ�.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �����ļ�, �����ļ�������Ȩ�����ÿ�ʼ��Ч. 
*/
unsigned int __stdcall AI_Dev_ActivateFile(IN unsigned int ulDevHandle,
							  IN unsigned short usFileID);
/*
// C prototype : unsigned int __stdcall AI_Dev_SelectFile(IN unsigned int ulDevHandle,
//							IN const unsigned short *pusPath,
//							IN unsigned int ulPathLen);			   
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pusPath  �ļ�·��,·������Ӧ�õı�ʶ���ļ��ı�ʶ���. �����ǰ�Ѿ�
//					ѡ���Ӧ��,ֻ�贫��Ҫѡ����ļ���ʶ����.
//				 ulPathLen ·���а����ı�ʶ�ĸ���(������·���а������ַ����ֽ���).
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ѡ���ļ�. �������豸�ɹ���, �����Ҫ����ĳ��Ӧ���µ�ĳ���ļ�,����
//				 ֱ�ӵ��øú�������ѡ��,���ѡ��ɹ�,·���а�����Ӧ�ü���Ϊ�˵�ǰ
//				 Ӧ��, �ù��̻����ѡ��Ӧ��,Ȼ��ѡ���ļ�Ч�ʸ���.
*/
unsigned int __stdcall AI_Dev_SelectFile(IN unsigned int ulDevHandle,
							IN unsigned int ulPathLen,
							IN const unsigned short *pusPath);
							
/*
// C prototype : unsigned int __stdcall AI_Dev_DeleteFile(IN unsigned int ulDevHandle,
//							IN const unsigned short *pusPath,
//							IN unsigned int ulPathLen);			   
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pusPath  �ļ�·��,·������Ӧ�õı�ʶ���ļ��ı�ʶ���. �����ǰ�Ѿ�
//					ѡ���Ӧ��,ֻ�贫��Ҫɾ�����ļ���ʶ����.
//				 ulPathLen ·���а����ı�ʶ�ĸ���(������·���а������ַ����ֽ���).
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ɾ���ļ�.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pusPath  �ļ�·��,·������Ӧ�õı�ʶ���ļ��ı�ʶ���. ����Ѿ�ѡ���
//					Ŀ���ļ�,����ֱ�Ӵ���NULL.
//				 ulPathLen ·���а����ı�ʶ�ĸ���(������·���а������ַ����ֽ���).���
//					�Ѿ�ѡ���Ŀ���ļ�,������Ϊ0.
//				 ulOffset ƫ�Ƶ�ַ.
//				 ulReadLen Ҫ��ȡ���ݵ��ֽ���.
//				 pbOut �������ݵĻ������׵�ַ.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ���ļ�. �ú���������FILE_TYPE_DATA,FILE_TYPE_RSAPUBKEY,FILE_TYPE_USERDATA�ļ�����.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pusPath  �ļ�·��,·������Ӧ�õı�ʶ���ļ��ı�ʶ���. ����Ѿ�ѡ���
//					Ŀ���ļ�,����ֱ�Ӵ���NULL.
//				 ulPathLen ·���а����ı�ʶ�ĸ���(������·���а������ַ����ֽ���).���
//					�Ѿ�ѡ���Ŀ���ļ�,������Ϊ0.
//				 ulOffset ƫ�Ƶ�ַ.
//				 ulUpdateLen ��Ҫ���µ��ֽ���.
//				 pbBuff ��Ҫ���µ�����.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �����ļ�����. �ú���������FILE_TYPE_DATA,FILE_TYPE_RSAPUBKEY,FILE_TYPE_RSAPRIKEY,
//				 FILE_TYPE_PROGRAM,FILE_TYPE_USERDATA�ļ�����.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulAlgID ��Կ�㷨,����ΪALGID_DES��ALGID_SSF33.
//				 bKeyID ��Կ��ʶ,����Ψһ��ʶһ����Կ.��Χ��0x10��0xEF֮��.
//				 pbValue ��Կֵ.
//				 ulValueLen ��Կ����.
//				 ulUseSec ��Կʹ�õ�Ȩ��.
//				 ulUpdateSec ������Կ��Ȩ��.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ����Կ�ļ��а�װһ���Գ���Կ. �ò��������ڹ���Ա��¼�����ִ��.
//				 ulUseSec��ulUpdateSec����ֵΪACCESS_MODE_ALWAYS,ACCESS_MODE_NEVER,
//				 ACCESS_MODE_USER��ACCESS_MODE_SO.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulAlgID ��Կ�㷨,����ΪALGID_DES��ALGID_SSF33.
//				 bKeyID ��Կ��ʶ,����Ψһ��ʶһ����Կ.
//				 pbValue ��Կֵ.
//				 ulValueLen ��Կ����.
//				 ulUseSec ��Կʹ�õ�Ȩ��.�μ�ACCESS_MODE_XXX����
//				 ulUpdateSec ������Կ��Ȩ��.�μ�ACCESS_MODE_XXX����
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �޸���Կ�ļ��е�һ���Գ���Կ.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pbPin �û���������Ա����.
//				 ulPinLen ����ĳ���.
//				 ulType ��¼����. LOGIN_TYPE_USER��LOGIN_TYPE_SO.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ����ͨ�û������Ա��ݵ�¼�豸.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pbOldPin ԭʼ����.
//				 ulOldPinLen ԭʼ����ĳ���.
//				 pbNewPin �¿���.
//				 ulNewPinLen �¿���ĳ���.
//				 ulType ��������. LOGIN_TYPE_USER��LOGIN_TYPE_SO.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �޸Ŀ���.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pbSOPin ����Ա����.
//				 ulSOPinLen ����Ա����ĳ���.
//				 pbNewUserPin �µ��û�����.
//				 ulNewUserPinLen ���û�����ĳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ʹ�ù���Ա���������û�����.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulModulusBits RSA��Կ��ģ��λ��.
//				 usPubKeyFileID ��Կ�ļ���ʶ.
//				 usPriKeyFileID ˽Կ�ļ���ʶ.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ����RSA��Կ��.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usPubKeyFileID ��Կ�ļ���ʶ. �������0,����Ե��빫Կ�Ĳ���.
//				 usPriKeyFileID ˽Կ�ļ���ʶ. �������0,����Ե���˽Կ�Ĳ���.
//				 pstRsaPriKey RSA˽Կ�ṹ(����ͬʱ�����˹�ԿԪ��).
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ����RSA��Կ���豸�ڲ��Ѿ����ڵ���Կ�ļ���. ��usPubKeyFileID������0ʱ,
//				 ��pstRsaPriKey�ṹ���б���߱��Ϸ���bits,modulus,publicExponent��3��Ԫ��.
//				 ��usPriKeyFileID������0ʱ,��pstRsaPriKey�ṹ���б���߱��Ϸ���bits,
//				 prime, primeExponent, coefficient��4��Ԫ��.
//				 ע��,RSA_PRIVATE_KEY�ṹ����ԿԪ�ظ�ʽ�����Ǹ��ֽ���ǰ,���ֽ��ں�.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usPubKeyFileID ��Կ�ļ���ʶ. �������0,����Ե�����Կ�Ĳ���.
//				 usPriKeyFileID ˽Կ�ļ���ʶ. �������0,����Ե���˽Կ�Ĳ���.Ŀǰ�ò�������Ϊ0.
//				 pstRsaPriKey RSA˽Կ�ṹ(����ͬʱ�����˹�ԿԪ��).
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ��ָ����RSA��Կ�ļ��е�����Կ. ���usPubKeyFileID������0,�����ɹ�����ʱ,
//				 ��pstRsaPriKey�ṹ���л᷵��bits,modulus,publicExponent��3��Ԫ��.
//				 Ŀǰ,��ʱ��֧�ֵ���˽Կ�����,����usPriKeyFileID����Ϊ0.
//				 ע��,RSA_PRIVATE_KEY�ṹ����ԿԪ�ظ�ʽ�Ǹ��ֽ���ǰ,���ֽ��ں�.
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
							IN const unsigned char *pbPlainText,   //����ECC����
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usPubKeyFileID ��Կ�ļ���ʶ.
//				 pbPlainText ��������.
//				 ulPlainTextLen �������ݵĳ���.
//				 pbCipherText ��������.
//				 pulCipherTextLen ���뺯��ʱ��ʾ����������ݵĻ������Ĵ�С,��������ʱ
//					��ʾ������������ݵ�ʵ�ʳ���.
//				 ulFlag Ŀǰ������Ϊ0.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : RSA��Կ����. �ü��ܲ������漰���κα���.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 usPriKeyFileID ˽Կ�ļ���ʶ.
//				 pbPlainText ��������.
//				 ulPlainTextLen �������ݵĳ���.
//				 pbCipherText ��������.
//				 pulCipherTextLen ���뺯��ʱ��ʾ����������ݵĻ������Ĵ�С,��������ʱ
//					��ʾ������������ݵ�ʵ�ʳ���.
//				 ulFlag Ŀǰ������Ϊ0.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : RSA˽Կ����. �ý��ܲ������漰���κα���.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulRandomlen ��Ҫ���ɵ�������ĳ���.
//				 pbRandom �����.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ���������. ��ִ����֤����ǰ,�����ȵ��øú�����Ӳ����ȡ�����,���ҳ���
//				 ����Ϊ4��8�ֽ�.
*/
unsigned int __stdcall AI_Dev_GenerateRandom(IN unsigned int ulDevHandle,
							IN unsigned int ulRandomLen,
							OUT unsigned char *pbRandom);

unsigned int __stdcall AI_Dev_P2Hash(IN unsigned int ulDevHandle,
									  IN unsigned char *bkey,
									  IN unsigned char key_len, 					  
									  IN unsigned int ulTextLen,
									  IN const unsigned char *pbText,
									  IN unsigned int num,        // ��ʼ���
									  IN unsigned int total_len,  // �ܳ��ȣ����һ����Ч
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 bKeyID �Գ���Կ�ı�ʶ��.
//				 ulAlgID �Գ���Կ�㷨,����ΪALGID_DES��ALGID_SSF33.
//				 pbKeyValue ��Կֵ,���������NULL,��ʹ�ø���Կֱ�Ӽ���,
//							����,ʹ�ô洢���豸�ڲ��ı�ʶΪbKeyID����Կ����.
//				 ulKeyValueLen ��Կ����.
//				 pbPlainText ��������.
//				 ulPlainTextLen �������ݵĳ���.
//				 pbCipherText ��������.
//				 pulCipherTextLen ���뺯��ʱ��ʾ����������ݵĻ���������,��������ʱ
//					��ʾ���ص��������ݵ�ʵ�ʳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ʹ�ô洢���豸�ڲ��ĶԳ���Կ��������.
*/
//unsigned int __stdcall AI_Dev_DEVRESET(IN unsigned int ulDevHandle);

unsigned int __stdcall AI_Dev_Encrypt(IN unsigned int ulDevHandle,
						 IN unsigned char bKeyID,
						 IN unsigned int ulAlgID,
						 IN unsigned char    bAlgMode,		// �㷨ģʽ addbysubin 20090528
						 IN unsigned int ulKeyValueLen,
						 IN unsigned char *pbKeyValue,
						 IN unsigned char*   pbIV,			// ��ʼ���� addbysubin 20090528
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 bKeyID �Գ���Կ�ı�ʶ��.
//				 ulAlgID �Գ���Կ�㷨,����ΪALGID_DES��ALGID_SSF33.
//				 pbKeyValue ��Կֵ,���������NULL,��ʹ�ø���Կֱ�ӽ���,
//							����,ʹ�ô洢���豸�ڲ��ı�ʶΪbKeyID����Կ����.
//				 ulKeyValueLen ��Կ����.
//				 pbCipherText ��������.
//				 ulCipherTextLen �������ݵĳ���.
//				 pbPlainText ��������.
//				 pulPlainTextLen ���뺯��ʱ��ʾ����������ݵĻ���������,��������ʱ
//					��ʾ���ص��������ݵ�ʵ�ʳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ʹ�ô洢���豸�ڲ��ĶԳ���Կ��������.
*/
unsigned int __stdcall AI_Dev_Decrypt(IN unsigned int ulDevHandle,
						 IN unsigned char bKeyID,
						 IN unsigned int ulAlgID,
						 IN unsigned char    bAlgMode,		// �㷨ģʽ addbysubin 20090528
						 IN unsigned int ulKeyValueLen,
						 IN unsigned char *pbKeyValue,
						 IN unsigned char*   pbIV,			// ��ʼ���� addbysubin 20090528
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 ulAlgID ժҪ�㷨,����ΪALGID_SHA1��ALGID_MD5.
//				 pbText ��Ҫ����ժҪ��ԭʼ����.
//				 ulTextLen ԭʼ���ݵĳ���.
//				 pbDigest ժҪֵ.
//				 pulDegestLen ���뺯��ʱ��ʾ���ժҪ�㷨����Ļ���������,��������ʱ
//					��ʾ���ص�ժҪ���ݵ�ʵ�ʳ���.
//				 ulFlag ��־,Ŀǰ������Ϊ0.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �����ݽ���ժҪ����.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pbServerRandCipher �豸��Կ�Է�����������ļ��ܽ��.
//				 ulServerRandCipherLen �豸��Կ�Է�����������ļ��ܺ����ĵĳ���,����Ϊ128.
//				 pusUserCertPriKeyFilePath �豸˽Կ�ļ���·��.
//				 ulFileIDsInPath pusUserCertPriKeyFilePath�����а������ļ���ʶ�ĸ���.
//				 pbDeviceRandCipher ���ڴ�ŷ�������Կ���豸������ļ��ܽ��,����ò���ΪNULL,
//					��pulDeviceRandCipherLen����������pbDeviceRandCipher����������С�ռ�.
//				 pulDeviceRandCipherLen ��������Կ���豸������ļ��ܺ����ĵĳ���;��Ϊ�������ʱ
//					ָʾpbDeviceRandCipher�������Ĵ�С;��Ϊ�������ʱָʾ���ĵ�ʵ�ʳ���;
//				 ulServerFlag �ò�����������Կʱ��Ч,������Կʱ��������. ���Ϊ0��ʾ�����豸
//					��Կ�����������;���Ϊ1��ʾ�����豸��Կ��Ӧ�÷�����.
//				 ulReserved ��������,������Ϊ0.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : ������ȫͨ��.
//				 �ú�������������Ѿ�������AI_Dev_LockDevִ�����߳�ͬ��.
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
// parameter(s): pbSessionKey �Ự��Կ.
//				 ulSessionKeyLen �Ự��Կ���ֽ���,Ŀǰ������Ϊ16.
//				 pbInitValue ����MAC��ĳ�ʼֵ.
//				 pbRawCmd ԭʼ��������.
//				 ulRawCmdLen ԭʼ�������ݵĳ���.
//				 pbSecChannelCmd ���ڱ��氲ȫͨ������Ļ������׵�ַ,����ò���ΪNULL,��pulSecChannelCmdLen
//					����������ʵ������Ҫ�Ļ�������С.
//				 pulSecChannelCmdLen ��Ϊ�������ʱ,ָʾpbSecChannelCmd�������Ĵ�С;��Ϊ�������ʱָʾ��
//					����İ�ȫͨ�������ʵ�ʳ���.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     :���찲ȫͨ������.
//				�ڵ��øú���ǰ,�����߱��뱣֤�Ѿ����豸������4�ֽ������,��ͬ4�ֽ�0���8�ֽ�,��Ϊ
//				����MAC�ĳ�ʼֵ,Ҳ����pbInitValue������ֵ.
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
// parameter(s): ulDevHandle �豸���. ��AI_Dev_ConnectDev��������.
//				 pbData �Գ���Կ�ļ��ܽ��,��������Կʱ,��������Ϊ�豸��Կ�ԶԳ���Կ�ļ��ܽ��,
//					��ʱ�ò���Ϊ�������; �������Գ���Կʱ,��������Ϊ�ⲿ��Կ�ԶԳ���Կ��
//					���ܽ��,��ʱ�ò���Ϊ�������. ��������Կʱ,���pbData=NULL,��pulDataLen
//					������ʵ�ʷ������ݵĳ���.
//				 pulDataLen pbData���������������ݳ���. ������Գ���Կʱ,�ò���Ϊ�������;
//					�������Գ���Կʱ,�ò���Ϊ�������.
//				 pusRsaKeyFilePath ��������Կʱ,Ϊ�豸˽Կ�ļ���·��. ��������Կʱ,Ϊ������
//					��Կ�ļ���·��.
//				 ulFileIDsInPath pusUserCertPriKeyFilePath�����а������ļ���ʶ�ĸ���.
//				 ulImportFlag ���ڱ�ʶ�ǵ�����Կ���ǵ�����Կ�ı�־.���Ϊ1���ʾ������Կ,Ϊ0
//					���ʶ������Կ.
//				 ulReserved ��������,������Ϊ0.
// return value: 0 - �ɹ�;
//				 ����ֵ - ������;
// remarks     : �Գ���Կ����/����.
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
		IN int lTokenHandle,				//�豸���
		IN unsigned short	usFileID,
		IN	void* pbData,					// д�������
		IN	unsigned short wOffset,			// �ļ�ƫ����
		IN	unsigned short wLen	);

unsigned int AI_ImportRSAPubkeyActive(
		IN int lTokenHandle,				//�豸���
		IN unsigned short usFileID,			//��Կ�ļ���ʶ
		IN	unsigned char* pbData,					// д��Ĺ�Կ����
		IN	unsigned short wLen				// ��Կ���ݳ���
		);

unsigned int AI_ImportRSAPrikeyActive(
		IN int lTokenHandle,				//�豸���
		IN unsigned short usFileID,			//˽Կ�ļ���ʶ
		IN	unsigned char* pbData,					// д��Ĺ�Կ����
		IN	unsigned short wLen				// ��Կ���ݳ���
	);

*/

unsigned int __stdcall AI_Dev_AddRealKey(
						IN unsigned int ulDevHandle,
						IN unsigned char bKeyID,
						IN unsigned int ulAlgID,
						IN unsigned int ulType,			//��Կ����,���Ϊ0,��Ĭ��Ϊ����/������Կ
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
