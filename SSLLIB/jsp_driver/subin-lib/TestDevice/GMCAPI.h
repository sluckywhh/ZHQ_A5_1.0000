#ifndef _SCST_GMC_API_H_
#define _SCST_GMC_API_H_

#include "GMCErr.h"
#include "deviceapi.h"

#ifdef __cplusplus
extern "C" {
#endif

//**********************************************************************
//�������Ͷ���

/////////////////////////////////////////////////////////////////////////
//�㷨��ʶ
//**�����㷨��
#define SGD_SM1_ECB		0x00000101   //SM1�㷨ECB����ģʽ��
#define SGD_SM1_CBC		0x00000102   //SM1�㷨CBC����ģʽ��
#define SGD_SM1_CFB		0x00000104   //SM1�㷨CFB����ģʽ��
#define SGD_SM1_OFB		0x00000108   //SM1�㷨OFB����ģʽ��
#define SGD_SM1_MAC		0x00000110   //SM1�㷨MAC����

#define SGD_SSF33_ECB   0x00000201   //SSF33�㷨ECB����ģʽ��
#define SGD_SSF33_CBC   0x00000202   //SSF33�㷨CBC����ģʽ��
#define SGD_SSF33_CFB   0x00000204   //SSF33�㷨CFB����ģʽ��
#define SGD_SSF33_OFB   0x00000208   //SSF33�㷨OFB����ģʽ��
#define SGD_SSF33_MAC   0x00000210   //SSF33�㷨MAC����

#define SGD_SMS4_ECB	0x00000401   //SM4�㷨ECB����ģʽ��
#define SGD_SMS4_CBC	0x00000402   //SM4�㷨CBC����ģʽ��
#define SGD_SMS4_CFB	0x00000404   //SM4�㷨CFB����ģʽ��
#define SGD_SMS4_OFB	0x00000408   //SM4�㷨OFB����ģʽ��
#define SGD_SMS4_MAC	0x00000410   //SM4�㷨MAC���㡣

//**�ǶԳ��㷨
#define SGD_RSA			0x00010000   //RSA�㷨��
#define SGD_SM2_1		0x00020100   //��Բ����ǩ���㷨��
#define SGD_SM2_2		0x00020200   //��Բ������Կ����Э�顣
#define SGD_SM2_3		0x00020400   //��Բ���߼����㷨��

//**�����Ӵ��㷨��ʶ
#define SGD_SM3			0x00000001	//SM3�����Ӵ��㷨��
#define SGD_SHA1		0x00000002	//SHA1�����Ӵ��㷨��
#define SGD_SHA256		0x00000004	//SHA256�����Ӵ��㷨��

//////////////////////////////////////////////////////////////////////////
//�����������Ͷ���
#ifndef WIN32
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed int          INT32;
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
#define BOOL int
typedef UINT8 BYTE;
//typedef UINT8 CHAR;
typedef char CHAR;

typedef INT16 SHORT;
typedef UINT16 USHORT;
//typedef INT32 LONG;
//typedef UINT32 ULONG;
typedef UINT32 UINT;
typedef UINT16 WORD;
//typedef UINT32 DWORD;
typedef UINT32 FLAGS;
typedef CHAR * LPSTR;
/*typedef void * HANDLE;*/
#endif
typedef void * HANDLE;
typedef void * DEVHANDLE;
typedef void * HAPPLICATION;
typedef void * HSESSION;
typedef void * HCONTAINER;

//////////////////////////////////////////////////////////////////////////
//�������塣
#ifndef FALSE
#define FALSE            0x00000000
#endif

#ifndef TRUE
#define TRUE              0x00000001
#endif

#ifdef WIN32
	#ifdef GMCAPI_EXPORT
	#define DEVAPI  __stdcall
	#else
	#define DEVAPI  __stdcall
	#endif
#else
    #define DEVAPI
#endif

#ifndef ADMIN_TYPE
#define ADMIN_TYPE						0
#endif

#ifndef USER_TYPE
#define USER_TYPE						1
#endif

//#define MAX_RSA_MODULUS_LEN				256
#define MAX_RSA_EXPONENT_LEN			4
#define ECC_MAX_XCOORDINATE_BITS_LEN	512
#define ECC_MAX_YCOORDINATE_BITS_LEN	512

#define ECC_MAX_MODULUS_BITS_LEN		512


#define MAX_IV_LEN						32

#define MAX_FILE_NAME_SIZE				32
#define MAX_FILE_CONTAINER_NAME_SIZE    64

//�ļ���д��Ȩ�޶���
#define SECURE_NEVER_ACCOUNT			0x00000000  //������
#define SECURE_ADM_ACCOUNT				0x00000001  //����ԱȨ��
#define SECURE_USER_ACCOUNT				0x00000010  //�û�Ȩ��
#define SECURE_ANYONE_ACCOUNT			0x000000FF  //�κ���

//�豸״̬����
#define DEV_ABSENT_STATE				0x00000000  //�豸������
#define DEV_PRESENT_STATE				0x00000001  //�豸����
#define DEV_UNKNOW_STATE				0x00000010  //�豸״̬δ֪

//////////////////////////////////////////////////////////////////////////
//�����������͡�

//#pragma pack(push, GMCAPI, 1)

//�汾
typedef struct Struct_Version{
	BYTE major;   //���汾�� 
	BYTE minor;   //�ΰ汾��
}__attribute__((packed)) VERSION1;

//�豸��Ϣ
typedef struct Struct_DEVINFO{
	VERSION1	Version;           //�汾��. ���ṹ�İ汾��Ϊ1.0
	CHAR		Manufacturer[64];  //�豸������Ϣ
	CHAR		Issuer[64];		   //���г�����Ϣ
	CHAR		Label[32];         //�豸��ǩ
	CHAR		SerialNumber[32];  //���к�
	VERSION1	HWVersion;         //�豸Ӳ���汾 
	VERSION1	FirmwareVersion;   //�豸����̼��汾
	ULONG		AlgSymCap;		   //���������㷨��ʶ
	ULONG		AlgAsymCap;		   //�ǶԳ������㷨��ʶ
	ULONG		AlgHashCap;		   //�����Ӵ��㷨��ʶ
	ULONG		DevAuthAlgId;	   //�豸��֤ʹ�õķ��������㷨��ʶ
	ULONG		TotalSpace;		   //�豸�ܿռ��С
	ULONG		FreeSpace;		   //�û����ÿռ��С
	ULONG		MaxECCBufferSize;  //�ܹ������ECC�������ݴ�С
	ULONG		MaxBufferSize;	   //�ܹ�����ķ���������Ӵ���������ݴ�С
	BYTE  		Reserved[64];	   //������չ
}__attribute__((packed)) DEVINFO,*PDEVINFO;

//RSA��Կ���ݽṹ��
typedef struct Struct_RSAPUBLICKEYBLOB{
	ULONG	AlgID;									//�㷨��ʶ��
	ULONG	BitLen;									//ģ����ʵ��λ����
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];			//ģ��n = p * q
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];	//������Կe
}__attribute__((packed)) RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;

//RSA˽Կ���ݽṹ
typedef struct Struct_RSAPRIVATEKEYBLOB{
	ULONG	AlgID;									 //�㷨��ʶ��
	ULONG	BitLen;									 //ģ����ʵ��λ����
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];			 //ģ��n = p * q
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];	 //������Կe
	BYTE	PrivateExponent[MAX_RSA_MODULUS_LEN];	 //˽����Կd
	BYTE	Prime1[MAX_RSA_MODULUS_LEN/2];			 //����p
	BYTE	Prime2[MAX_RSA_MODULUS_LEN/2];			 //����q
	BYTE	Prime1Exponent[MAX_RSA_MODULUS_LEN/2];	 //d mod (p-1)��ֵ
	BYTE	Prime2Exponent[MAX_RSA_MODULUS_LEN/2];	 //d mod (q -1)��ֵ
	BYTE	Coefficient[MAX_RSA_MODULUS_LEN/2];		 //qģp�ĳ˷���Ԫ
}__attribute__((packed)) RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;

//ECC��Կ���ݽṹ
typedef struct Struct_ECCPUBLICKEYBLOB{
	ULONG	BitLen;											//ģ����ʵ��λ����
	BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];    //�����ϵ��X����
	BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];	//�����ϵ��Y����
}__attribute__((packed)) ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;

//ECC˽Կ���ݽṹ
typedef struct Struct_ECCPRIVATEKEYBLOB{
	ULONG	BitLen;										//ģ����ʵ��λ����
	BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];		//˽����Կ
}__attribute__((packed)) ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;

//ECC�������ݽṹ
typedef struct Struct_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];	//��y�����Բ�����ϵĵ㣨x��y��
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];  //��x�����Բ�����ϵĵ㣨x��y��
	BYTE  HASH[32];										//���ĵ��Ӵ�ֵ
	ULONG CipherLen;									//�������ݳ���
	BYTE  Cipher[1];									//��������
}__attribute__((packed))  ECCCIPHERBLOB, *PECCCIPHERBLOB;

//ECCǩ�����ݽṹ
typedef struct Struct_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];			//ǩ�������r����
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];			//ǩ�������s����
}__attribute__((packed))  ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

//�����������
typedef struct Struct_BLOCKCIPHERPARAM{
	BYTE	IV[MAX_IV_LEN];						//��ʼ����
	ULONG	IVLen;								//��ʼ����ʵ�ʳ��ȣ����ֽڼ��㣩
	ULONG	PaddingType;						//��䷽ʽ��0��ʾ����䣬1��ʾ����PKCS#5��ʽ�������
	ULONG	FeedBitLen;							//����ֵ��λ���ȣ���λ���㣩��ֻ���OFB��CFBģʽ
}__attribute__((packed))  BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;

//ECC������Կ�Ա����ṹ
typedef struct SKF_ENVELOPEDKEYBLOB{
	ULONG Version;                  //��ǰ�汾Ϊ 1
	ULONG ulSymmAlgID;              //�Գ��㷨��ʶ���޶�ECBģʽ
	ULONG ulBits;					//������Կ�Ե���Կλ����
	BYTE  cbEncryptedPriKey[64];    //������Կ��˽Կ������
	ECCPUBLICKEYBLOB PubKey;        //������Կ�ԵĹ�Կ
	ECCCIPHERBLOB	ECCCipherBlob;  // �ñ�����Կ���ܵĶԳ���Կ���ġ�
}__attribute__((packed)) ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

//�ļ�����
typedef struct Struct_FILEATTRIBUTE{
	CHAR	FileName[MAX_FILE_NAME_SIZE];			//�ļ���
	ULONG	FileSize;				//�ļ���С
	ULONG	ReadRights;				//��ȡȨ��
	ULONG	WriteRights;            //д��Ȩ��
}__attribute__((packed))  FILEATTRIBUTE, *PFILEATTRIBUTE;


//#pragma pack(pop, GMCAPI)

//**********************************************************************
//�ӿں�������


//////////////////////////////////////////////////////////////////////////
//�豸������
//��������:	�ú����ȴ��豸������߰γ��¼���szDevName���ط����¼����豸���ơ�
//����: szDevName 	[OUT] �����¼����豸���ơ�
//		pulDevNameLen	[IN/OUT] ����/���������������ʱ��ʾ���������ȣ����ʱ��ʾ�豸���Ƶ���Ч����,���Ȱ����ַ�����������
//		pulEvent	[OUT]�¼����͡�1��ʾ���룬2��ʾ�γ���
//		����ֵ	SAR_OK��	�ɹ���
//				������		�����롣
//��ע:	������Ϊ����������
ULONG DEVAPI SKF_WaitForDevEvent(LPSTR szDevName,
				ULONG *pulDevNameLen, 
				ULONG *pulEvent);


ULONG DEVAPI SKF_CancelWaitForDevEvent();

ULONG DEVAPI SKF_EnumDev(BOOL bPresent, 
				LPSTR szNameList, 
				ULONG *pulSize);

ULONG DEVAPI SKF_ConnectDev (LPSTR szName, 
				DEVHANDLE *phDev);

ULONG DEVAPI SKF_DisConnectDev (DEVHANDLE hDev);

ULONG DEVAPI SKF_GetDevState(LPSTR szDevName, 
				ULONG *pulDevState);

ULONG DEVAPI SKF_SetLabel (DEVHANDLE hDev, 
				LPSTR szLabel);

ULONG DEVAPI SKF_GetDevInfo (DEVHANDLE hDev, 
				DEVINFO *pDevInfo);

ULONG DEVAPI SKF_LockDev (DEVHANDLE hDev, 
				ULONG ulTimeOut);

ULONG DEVAPI SKF_UnlockDev (DEVHANDLE hDev);

ULONG DEVAPI SKF_Transmit(DEVHANDLE hDev, 
				BYTE* pbCommand, 
				ULONG ulCommandLen,
				BYTE* pbData, 
				ULONG* pulDataLen);

//////////////////////////////////////////////////////////////////////////
//���ʿ��ƺ���
ULONG DEVAPI SKF_ChangeDevAuthKey (DEVHANDLE hDev, 
				BYTE *pbKeyValue,
				ULONG ulKeyLen);

ULONG DEVAPI SKF_DevAuth (DEVHANDLE hDev, 
				BYTE *pbAuthData, 
				ULONG ulLen);

ULONG DEVAPI SKF_ChangePIN (HAPPLICATION hApplication, 
				ULONG ulPINType, 
				LPSTR szOldPin, 
				LPSTR szNewPin, 
				ULONG *pulRetryCount);

LONG DEVAPI SKF_GetPINInfo(HAPPLICATION hApplication, 
				ULONG  ulPINType, 
				ULONG *pulMaxRetryCount, 
				ULONG *pulRemainRetryCount, 
				BOOL *pbDefaultPin);

ULONG DEVAPI SKF_VerifyPIN (HAPPLICATION hApplication, 
				ULONG  ulPINType, 
				LPSTR szPIN, 
				ULONG *pulRetryCount);

ULONG DEVAPI SKF_UnblockPIN (HAPPLICATION hApplication, 
				LPSTR szAdminPIN, 
				LPSTR szNewUserPIN,  
				ULONG *pulRetryCount);

ULONG DEVAPI SKF_ClearSecureState (HAPPLICATION hApplication);

//////////////////////////////////////////////////////////////////////////
//Ӧ�ù�����
ULONG DEVAPI SKF_CreateApplication(DEVHANDLE hDev, 
				LPSTR szAppName, 
				LPSTR szAdminPin, 
				DWORD dwAdminPinRetryCount,
				LPSTR szUserPin, 
				DWORD dwUserPinRetryCount,
				DWORD dwCreateFileRights, 
				HAPPLICATION *phApplication);

ULONG DEVAPI SKF_EnumApplication(DEVHANDLE hDev,
				LPSTR szAppName,
				ULONG *pulSize);

ULONG DEVAPI SKF_DeleteApplication(DEVHANDLE hDev, 
								   LPSTR szAppName);

ULONG DEVAPI SKF_OpenApplication(DEVHANDLE hDev, 
				LPSTR szAppName, 
				HAPPLICATION *phApplication);

ULONG DEVAPI SKF_CloseApplication(HAPPLICATION hApplication);

//////////////////////////////////////////////////////////////////////////
//�ļ�������
ULONG DEVAPI SKF_CreateFile (HAPPLICATION hApplication,
				LPSTR szFileName, 
				ULONG ulFileSize, 
				ULONG ulReadRights,
				ULONG ulWriteRights);

ULONG DEVAPI SKF_DeleteFile (HAPPLICATION hApplication,
				LPSTR szFileName);

ULONG DEVAPI SKF_EnumFiles (HAPPLICATION hApplication, 
				LPSTR szFileList, 
				ULONG *pulSize);

ULONG DEVAPI SKF_GetFileInfo (HAPPLICATION hApplication,
				LPSTR szFileName, 
				FILEATTRIBUTE *pFileInfo);

ULONG DEVAPI SKF_ReadFile (HAPPLICATION hApplication,
				LPSTR szFileName, 
				ULONG ulOffset, 
				ULONG ulSize, 
				BYTE * pbOutData, 
				ULONG *pulOutLen);

ULONG DEVAPI SKF_WriteFile (HAPPLICATION hApplication, 
				LPSTR szFileName, 
				ULONG  ulOffset, 
				BYTE *pbData, 
				ULONG ulSize);


//////////////////////////////////////////////////////////////////////////
//����������
ULONG DEVAPI SKF_CreateContainer (HAPPLICATION hApplication,
				LPSTR szContainerName,
				HCONTAINER *phContainer);


ULONG DEVAPI SKF_DeleteContainer(HAPPLICATION hApplication, 
				LPSTR szContainerName);

ULONG DEVAPI SKF_EnumContainer (HAPPLICATION hApplication,
				LPSTR szContainerName,
				ULONG *pulSize);

ULONG DEVAPI SKF_OpenContainer(HAPPLICATION hApplication,
				LPSTR szContainerName,
				HCONTAINER *phContainer);

ULONG DEVAPI SKF_CloseContainer(HCONTAINER hContainer);

ULONG DEVAPI SKF_GetContainerType(HCONTAINER hContainer,
				ULONG *pulContainerType);

ULONG DEVAPI SKF_ImportCertificate(HCONTAINER hContainer, 
				BOOL bSignFlag,  
				BYTE* pbCert, 
				ULONG ulCertLen);

ULONG DEVAPI SKF_ExportCertificate(HCONTAINER hContainer,
				BOOL bSignFlag,  
				BYTE* pbCert, 
				ULONG *pulCertLen);

//////////////////////////////////////////////////////////////////////////
//�����������

ULONG DEVAPI SKF_GenRandom (DEVHANDLE hDev, 
				BYTE *pbRandom,
				ULONG ulRandomLen);

ULONG DEVAPI SKF_GenExtRSAKey (DEVHANDLE hDev, 
				ULONG ulBitsLen, 
				RSAPRIVATEKEYBLOB *pBlob);

ULONG DEVAPI SKF_GenRSAKeyPair (HCONTAINER hContainer, 
				ULONG ulBitsLen, 
				RSAPUBLICKEYBLOB *pBlob);

ULONG DEVAPI SKF_ImportRSAKeyPair(HCONTAINER hContainer, 
				ULONG ulSymAlgId, 
				BYTE *pbWrappedKey, 
				ULONG ulWrappedKeyLen,
				BYTE *pbEncryptedData, 
				ULONG ulEncryptedDataLen);

ULONG DEVAPI SKF_RSASignData(HCONTAINER hContainer, 
				BYTE *pbData, 
				ULONG  ulDataLen, 
				BYTE *pbSignature, 
				ULONG *pulSignLen);

ULONG DEVAPI SKF_RSAVerify(DEVHANDLE hDev, 
			    RSAPUBLICKEYBLOB* pRSAPubKeyBlob, 
				BYTE *pbData, 
				ULONG  ulDataLen, 
				BYTE *pbSignature, 
				ULONG ulSignLen);

ULONG DEVAPI SKF_RSAExportSessionKey(HCONTAINER hContainer, 
				ULONG ulAlgId, 
				RSAPUBLICKEYBLOB *pPubKey, 
				BYTE *pbData, 
				ULONG  *pulDataLen, 
				HANDLE *phSessionKey);

ULONG DEVAPI SKF_ExtRSAPubKeyOperation (DEVHANDLE hDev, 
				RSAPUBLICKEYBLOB* pRSAPubKeyBlob,
				BYTE* pbInput, 
				ULONG ulInputLen, 
				BYTE* pbOutput, 
				ULONG* pulOutputLen);

ULONG DEVAPI SKF_ExtRSAPriKeyOperation (DEVHANDLE hDev,
				RSAPRIVATEKEYBLOB* pRSAPriKeyBlob,
				BYTE* pbInput, 
				ULONG ulInputLen, 
				BYTE* pbOutput, 
				ULONG* pulOutputLen);

ULONG DEVAPI SKF_GenECCKeyPair (HCONTAINER hContainer, 
								ULONG ulAlgId,
								ECCPUBLICKEYBLOB *pBlob);

ULONG DEVAPI SKF_ImportECCKeyPair (HCONTAINER hContainer, 
				PENVELOPEDKEYBLOB pEnvelopedKeyBlob);

ULONG DEVAPI SKF_ECCSignData (HCONTAINER hContainer,
				BYTE *pbData, 
				ULONG  ulDataLen, 
				PECCSIGNATUREBLOB pSignature);

ULONG DEVAPI SKF_ECCVerify(DEVHANDLE hDev, 
				ECCPUBLICKEYBLOB* pECCPubKeyBlob, 
				BYTE *pbData, 
				ULONG  ulDataLen, 
				PECCSIGNATUREBLOB pSignature);

ULONG DEVAPI SKF_ECCExportSessionKey (HCONTAINER hContainer, 
				ULONG ulAlgId, 
				ECCPUBLICKEYBLOB *pPubKey, 
				PECCCIPHERBLOB pData, 
				HANDLE *phSessionKey);

ULONG DEVAPI SKF_ExtECCEncrypt (DEVHANDLE hDev, 
				ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
				BYTE* pbPlainText, 
				ULONG ulPlainTextLen, 
				PECCCIPHERBLOB pCipherText);

ULONG DEVAPI SKF_ExtECCDecrypt (DEVHANDLE hDev,
				ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, 
				PECCCIPHERBLOB pCipherText, 
				BYTE* pbPlainText, 
				ULONG* pulPlainTextLen);

ULONG DEVAPI SKF_ExtECCSign (DEVHANDLE hDev, 
				ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, 
				BYTE* pbData, 
				ULONG ulDataLen, 
				PECCSIGNATUREBLOB pSignature);

ULONG DEVAPI SKF_ExtECCVerify (DEVHANDLE hDev, 
				ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
				BYTE* pbData, 
				ULONG ulDataLen, 
				PECCSIGNATUREBLOB pSignature);

ULONG DEVAPI SKF_GenerateAgreementDataWithECC (HCONTAINER hContainer,
				ULONG ulAlgId,
				ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
				BYTE* pbID, 
				ULONG ulIDLen,
				HANDLE *phAgreementHandle);

ULONG DEVAPI SKF_GenerateAgreementDataAndKeyWithECC(HANDLE hContainer, 
				ULONG ulAlgId,
				ECCPUBLICKEYBLOB*  pSponsorECCPubKeyBlob,
				ECCPUBLICKEYBLOB*  pSponsorTempECCPubKeyBlob,
				ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
				BYTE* pbID, 
				ULONG ulIDLen, 
				BYTE *pbSponsorID, 
				ULONG ulSponsorIDLen,
				HANDLE *phKeyHandle);

ULONG DEVAPI SKF_GenerateKeyWithECC (HANDLE hAgreementHandle,
				ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
				ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
				BYTE* pbID, 
				ULONG ulIDLen, 
				HANDLE *phKeyHandle);

ULONG DEVAPI SKF_ExportPublicKey (HCONTAINER hContainer, 
				BOOL bSignFlag, 
				BYTE* pbBlob, 
				ULONG* pulBlobLen);

ULONG DEVAPI SKF_ImportSessionKey (HCONTAINER hContainer, 
				ULONG ulAlgId,
				BYTE *pbWrapedData,
				ULONG ulWrapedLen,
				HANDLE *phKey);

ULONG DEVAPI SKF_SetSymmKey (DEVHANDLE hDev, 
				BYTE* pbKey, 
				ULONG ulAlgID, 
				HANDLE* phKey);

ULONG DEVAPI SKF_EncryptInit (HANDLE hKey, 
				BLOCKCIPHERPARAM EncryptParam);

ULONG DEVAPI SKF_Encrypt(HANDLE hKey, 
				BYTE * pbData, 
				ULONG ulDataLen, 
				BYTE *pbEncryptedData, 
				ULONG *pulEncryptedLen);

ULONG DEVAPI SKF_EncryptUpdate(HANDLE hKey,
				BYTE * pbData, 
				ULONG ulDataLen, 
				BYTE *pbEncryptedData, 
				ULONG *pulEncryptedLen);

ULONG DEVAPI SKF_EncryptFinal (HANDLE hKey, 
				BYTE *pbEncryptedData, 
				ULONG *pulEncryptedDataLen);

ULONG DEVAPI SKF_DecryptInit (HANDLE hKey, 
				BLOCKCIPHERPARAM DecryptParam);

ULONG DEVAPI SKF_Decrypt(HANDLE hKey, 
				BYTE * pbEncryptedData, 
				ULONG ulEncryptedLen, 
				BYTE * pbData, 
				ULONG * pulDataLen);

ULONG DEVAPI SKF_DecryptUpdate(HANDLE hKey, 
				BYTE * pbEncryptedData, 
				ULONG ulEncryptedLen, 
				BYTE * pbData, 
				ULONG * pulDataLen);

ULONG DEVAPI SKF_DecryptFinal (HANDLE hKey, 
				BYTE *pbDecryptedData, 
				ULONG *pulDecryptedDataLen);

ULONG DEVAPI SKF_DigestInit(DEVHANDLE hDev, 
				ULONG ulAlgID,  
				ECCPUBLICKEYBLOB *pPubKey, 
				unsigned char *pucID, 
				ULONG ulIDLen, 
				HANDLE *phHash);

ULONG DEVAPI SKF_Digest (HANDLE hHash, 
				BYTE *pbData, 
				ULONG ulDataLen, 
				BYTE *pbHashData, 
				ULONG *pulHashLen);

ULONG DEVAPI SKF_DigestUpdate (HANDLE hHash, 
				BYTE *pbData, 
				ULONG  ulDataLen);

ULONG DEVAPI SKF_DigestFinal (HANDLE hHash,
				BYTE *pHashData, 
				ULONG  *pulHashLen);

ULONG DEVAPI SKF_MacInit (HANDLE hKey, 
				BLOCKCIPHERPARAM* pMacParam, 
				HANDLE *phMac);

ULONG DEVAPI SKF_Mac(HANDLE hMac,
				BYTE* pbData, 
				ULONG ulDataLen, 
				BYTE *pbMacData, 
				ULONG *pulMacLen);

ULONG DEVAPI SKF_MacUpdate(HANDLE hMac, 
				BYTE * pbData, 
				ULONG ulDataLen);

ULONG DEVAPI SKF_MacFinal (HANDLE hMac, 
				BYTE *pbMacData, 
				ULONG *pulMacDataLen);

ULONG DEVAPI SKF_CloseHandle(HANDLE hHandle);

//DefaultApplication
ULONG DEVAPI SKF_DefaultSelectApplication(DEVHANDLE hDev,HAPPLICATION *phApplication);

ULONG DEVAPI SKF_DefaultGetCertInfo(HAPPLICATION hApplication,BYTE* pbCert,ULONG *pulCertLen);
//done subin 20141215

#ifdef __cplusplus
}
#endif

#endif //_SCST_GMC_API_H_

