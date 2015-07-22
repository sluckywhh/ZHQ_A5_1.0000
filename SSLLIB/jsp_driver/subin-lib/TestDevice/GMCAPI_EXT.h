#ifndef _SCST_GMC_API_EXT_H_
#define _SCST_GMC_API_EXT_H_

#include "GMCAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

//#pragma pack(push, GMCAPI, 1)
typedef struct _FormatKeyParam
{
	BYTE  VersionMajor;         //���汾����ǰΪ1
	BYTE  VersionMinor;			//С�汾����ǰΪ0.
	ULONG ulAuthAlgID;          //��֤�㷨��
	ULONG ulDevAuthKeyLen;		//pbDevAuthKey����Ч���ȡ�
	BYTE  pbDevAuthKey[32];     //�豸��֤Key�����Ϊ32���ֽڡ�
	BYTE  pbDevLabel[64];       //�ַ��������Ϊ64���ֽڡ�
	BYTE  pbAuthCode[16];       //������֤�Ƿ���Ը�ʽ��Key����֤��.
	BYTE  bSupportRootCert;		//�Ƿ�ʶ���֤�顣(0��ʾ��ʶ��1��ʾʶ��). ��3��ϵͳ��ʹ�á�
								//����Ӧ���У���Ҫʶ�����ְ���Cert0���ļ�����Ϊ��֤�鱣�档P11��Ҫʹ�ø����ֽ���ʶ��
	BYTE  byCertStoreType;		//֤��洢���͡�0��ʾ�Զ�ʶ��1��ʾ�洢���ڲ���2��ʾ�洢��NAND�С�
	BYTE  byFileStoreType;		//�ļ��洢���͡�0��ʾ�Զ�ʶ��1��ʾ�洢���ڲ���2��ʾ�洢��NAND�С�
}__attribute__((packed)) FormatKeyParam, *PFormatKeyParam;
//#pragma pack(pop, GMCAPI)

#define ROOT_CERT 0			// ��֤��
#define SIGN_CERT 1         // ǩ��֤��
#define ENC_CERT  2			// ����֤��
#define NO_CERT   3			// ��֤��

#define MAX_CONTAINER_CERT_COUNT 3
#define MAX_CERT_CONTENT_LEN 4000

typedef struct tagCert 
{
	ULONG CertType;								// ֤������
	ULONG CertLen;								// ֤����Ч����
	BYTE  CertContent[MAX_CERT_CONTENT_LEN];	// ֤������
}Cert, *PCert;

typedef struct tagContainerRecordItem
{
	BOOL IsExist;										// ��¼���Ƿ����
	ULONG AppID;										// Ӧ��ID
	char AppName[MAX_FILE_NAME_SIZE];					// Ӧ������
	ULONG ContainerType;								// ��������
	char ContainerName[MAX_FILE_CONTAINER_NAME_SIZE];	// ��������
	Cert cert[MAX_CONTAINER_CERT_COUNT];				// ֤��ṹ
}ContainerRecordItem, *PContainerRecordItem;

//��ʽ��Key.
//��������:		��ʽ��Key��
//����: hDev 	[IN] �豸�����
//		pFkParam	[IN] ��ʽ��ʹ�õĲ�����
//		����ֵ	SAR_OK��	�ɹ���
//				������		�����롣
//��ע:	
ULONG DEVAPI SKFI_FormatKey(DEVHANDLE hDev,
							PFormatKeyParam pFkParam);

//��λ��
ULONG DEVAPI SKFI_CardReset(DEVHANDLE hDev);

// ��������    ʹ���ڲ�RSA����˽Կ�������������������㲢������
// ����        hContainer                   [IN] �������
// pbCipherText                 [IN] �����ܵ���������
// ulCipherTextLen              [IN] �������������ݳ���
// pbPlainText                  [OUT] ������������,����ò���ΪNULL������pulPlainTextLen�����������ݵ�ʵ�ʳ��ȡ�
// pulPlainTextLen              [IN��OUT] ����ʱ��ʾpbPlainText�������ĳ��ȣ�����ʱ��ʾ�������ݵ�ʵ�ʳ��ȡ�
// ����ֵ      SAR_OK:           �ɹ���
// ����:             �����롣

ULONG DEVAPI SKF_RSADecrypt(HCONTAINER hContainer, 
							BYTE *pbCipherText, 
							ULONG ulCipherTextLen, 
							BYTE *pbPlainText,
							ULONG *pulPlainTextLen);

//��������    ʹ���ڲ�ECC����˽Կ�������������������㲢������
// ����        hContainer                   [IN] �������
// pCipherText                  [IN] �����ܵ���������
// pbPlainText                  [OUT] ������������,����ò���ΪNULL������pulPlainTextLen�����������ݵ�ʵ�ʳ��ȡ�
// pulPlainTextLen              [IN��OUT] ����ʱ��ʾpbPlainText�������ĳ��ȣ�����ʱ��ʾ�������ݵ�ʵ�ʳ��ȡ�

ULONG DEVAPI SKF_ECCDecrypt(HCONTAINER hContainer, 
							PECCCIPHERBLOB pCipherText, 
							BYTE *pbPlainText,
							ULONG *pulPlainTextLen);




//---------------------����֤�鹲���ڴ��������----------------------------------//

//��������   ������֤��ʱ�������ڴ������Ӽ�¼
// ����  
// pDevSerialNum		[IN] �豸���к�
// ulSerialNumLen		[IN] �豸���кų���
// ulAppID				[IN] Ӧ��ID
// lpszContainerName    [IN] ������
// pbCert				[IN] ֤������
// ulCertLen            [IN] ֤�鳤��
// nCertType		    [IN] ֤������

ULONG DEVAPI SKFC_AddCertRecord(const BYTE* pDevSerialNum, 
								ULONG ulSerialNumLen, 
								ULONG ulAppID, 
								LPSTR lpszContainerName, 
								BYTE* pbCert, 
								ULONG ulCertLen, 
								int nCertType);


//��������   ��ɾ��֤��ʱ���ڹ����ڴ���ɾ����Ӧ��¼
// ����  
// pDevSerialNum		[IN] �豸���к�
// ulSerialNumLen		[IN] �豸���кų���
// ulAppID				[IN] Ӧ��ID
// lpszContainerName    [IN] ������
// nCertType		    [IN] ֤������
ULONG DEVAPI SKFC_DeleteCertRecord(const BYTE* pDevSerialNum, 
								   ULONG ulSerialNumLen, 
								   ULONG ulAppID, 
								   LPSTR lpszContainerName, 
								   int nCertType);

//��������   ��ɾ������ʱ���ڹ����ڴ���ɾ��������¼
// ����  
// pDevSerialNum		[IN] �豸���к�
// ulSerialNumLen		[IN] �豸���кų���
// ulAppID				[IN] Ӧ��ID
// lpszContainerName    [IN] ������
ULONG DEVAPI SKF_DeleteContainerRecord(const BYTE* pDevSerialNum, 
									   ULONG ulSerialNumLen, 
									   ULONG ulAppID, 
									   LPSTR lpszContainerName);


//��������   ����������ʱ���ڹ����ڴ��д���������¼
// ����  
// pDevSerialNum		[IN] �豸���к�
// ulSerialNumLen		[IN] �豸���кų���
// ulAppID				[IN] Ӧ��ID
// lpszContainerName    [IN] ������

ULONG DEVAPI SKFC_AddContainerRecord(const BYTE* pDevSerialNum, 
									 ULONG ulSerialNumLen, 
									 ULONG ulAppID, 
									 LPSTR lpszContainerName);


//��������   ���ع����ڴ��е����м�¼
// ����  
// pDevSerialNum		[IN] �豸���к�
// ulSerialNumLen		[IN] �豸���кų���
// pRecordItem		    [OUT] ContainerRecordItem�ṹָ�룬pRecordItemΪ��ʱ��nRecordItemCount��������Ҫ��ContainerRecordItem�ṹ����
// pnRecordItemCount     [IN\OUT] ����ʱ����ʾContainerRecordItem�ṹ���������ʱ����ʾʵ�ʵ�ContainerRecordItem�ṹ������
//								 ContainerRecordItem�е�IsExist����Ϊ�棬���Կ��Ժ���
ULONG DEVAPI SKFC_GetContainerRecordItem(const BYTE* pDevSerialNum, 
										 ULONG ulSerialNumLen, 
										 ContainerRecordItem *pRecordItem, 
										 ULONG* pulRecordItemCount);

ULONG DEVAPI SKFC_CleanMemeory(const BYTE* pDevSerialNum, 
							   ULONG ulSerialNumLen);

//---------------------���������֤�麯��----------------------------------//
//  ��������	�������ڵ���CA����֤�顣
//  ����	    hContainer	[IN] ���������
//  pbCert		[IN] ָ��֤�����ݻ�������
//  ulCertLen	[IN] ֤�鳤�ȡ�
//  ����ֵ	    SAR_OK��	�ɹ���
ULONG DEVAPI SKF_ImportCACertificate(HCONTAINER hContainer, 
									 BYTE* pbCert, 
									 ULONG ulCertLen);

// ��������			�������ڵ���CA����֤�顣
// ����	hContainer	[IN] ���������
// pbCert			[OUT] ָ��֤�����ݻ�����������˲���ΪNULLʱ��pulCertLen��ʾ������������Ҫ�������ĳ��ȣ�����˲�����ΪNULLʱ����������֤�����ݡ�
// pulCertLen		[IN/OUT] ����ʱ��ʾpbCert�������ĳ��ȣ����ʱ��ʾ֤�����ݵĳ��ȡ�
// ����ֵ			SAR_OK��	�ɹ���
// ������			�����롣
ULONG DEVAPI SKF_ExportCACertificate(HCONTAINER hContainer,
									 BYTE* pbCert, 
									 ULONG *pulCertLen);	

#ifdef __cplusplus
}


#endif

#endif //_SCST_GMC_API_H_
