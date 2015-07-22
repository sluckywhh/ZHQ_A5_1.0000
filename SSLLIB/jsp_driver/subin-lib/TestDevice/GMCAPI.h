#ifndef _SCST_GMC_API_H_
#define _SCST_GMC_API_H_

#include "GMCErr.h"
#include "deviceapi.h"

#ifdef __cplusplus
extern "C" {
#endif

//**********************************************************************
//数据类型定义

/////////////////////////////////////////////////////////////////////////
//算法标识
//**分组算法。
#define SGD_SM1_ECB		0x00000101   //SM1算法ECB加密模式。
#define SGD_SM1_CBC		0x00000102   //SM1算法CBC加密模式。
#define SGD_SM1_CFB		0x00000104   //SM1算法CFB加密模式。
#define SGD_SM1_OFB		0x00000108   //SM1算法OFB加密模式。
#define SGD_SM1_MAC		0x00000110   //SM1算法MAC运算

#define SGD_SSF33_ECB   0x00000201   //SSF33算法ECB加密模式。
#define SGD_SSF33_CBC   0x00000202   //SSF33算法CBC加密模式。
#define SGD_SSF33_CFB   0x00000204   //SSF33算法CFB加密模式。
#define SGD_SSF33_OFB   0x00000208   //SSF33算法OFB加密模式。
#define SGD_SSF33_MAC   0x00000210   //SSF33算法MAC运算

#define SGD_SMS4_ECB	0x00000401   //SM4算法ECB加密模式。
#define SGD_SMS4_CBC	0x00000402   //SM4算法CBC加密模式。
#define SGD_SMS4_CFB	0x00000404   //SM4算法CFB加密模式。
#define SGD_SMS4_OFB	0x00000408   //SM4算法OFB加密模式。
#define SGD_SMS4_MAC	0x00000410   //SM4算法MAC运算。

//**非对称算法
#define SGD_RSA			0x00010000   //RSA算法。
#define SGD_SM2_1		0x00020100   //椭圆曲线签名算法。
#define SGD_SM2_2		0x00020200   //椭圆曲线密钥交换协议。
#define SGD_SM2_3		0x00020400   //椭圆曲线加密算法。

//**密码杂凑算法标识
#define SGD_SM3			0x00000001	//SM3密码杂凑算法。
#define SGD_SHA1		0x00000002	//SHA1密码杂凑算法。
#define SGD_SHA256		0x00000004	//SHA256密码杂凑算法。

//////////////////////////////////////////////////////////////////////////
//基本数据类型定义
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
//常量定义。
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

//文件读写的权限定义
#define SECURE_NEVER_ACCOUNT			0x00000000  //不允许
#define SECURE_ADM_ACCOUNT				0x00000001  //管理员权限
#define SECURE_USER_ACCOUNT				0x00000010  //用户权限
#define SECURE_ANYONE_ACCOUNT			0x000000FF  //任何人

//设备状态定义
#define DEV_ABSENT_STATE				0x00000000  //设备不存在
#define DEV_PRESENT_STATE				0x00000001  //设备存在
#define DEV_UNKNOW_STATE				0x00000010  //设备状态未知

//////////////////////////////////////////////////////////////////////////
//复合数据类型。

//#pragma pack(push, GMCAPI, 1)

//版本
typedef struct Struct_Version{
	BYTE major;   //主版本号 
	BYTE minor;   //次版本号
}__attribute__((packed)) VERSION1;

//设备信息
typedef struct Struct_DEVINFO{
	VERSION1	Version;           //版本号. 本结构的版本号为1.0
	CHAR		Manufacturer[64];  //设备厂商信息
	CHAR		Issuer[64];		   //发行厂商信息
	CHAR		Label[32];         //设备标签
	CHAR		SerialNumber[32];  //序列号
	VERSION1	HWVersion;         //设备硬件版本 
	VERSION1	FirmwareVersion;   //设备本身固件版本
	ULONG		AlgSymCap;		   //分组密码算法标识
	ULONG		AlgAsymCap;		   //非对称密码算法标识
	ULONG		AlgHashCap;		   //密码杂凑算法标识
	ULONG		DevAuthAlgId;	   //设备认证使用的分组密码算法标识
	ULONG		TotalSpace;		   //设备总空间大小
	ULONG		FreeSpace;		   //用户可用空间大小
	ULONG		MaxECCBufferSize;  //能够处理的ECC加密数据大小
	ULONG		MaxBufferSize;	   //能够处理的分组运算和杂凑运算的数据大小
	BYTE  		Reserved[64];	   //保留扩展
}__attribute__((packed)) DEVINFO,*PDEVINFO;

//RSA公钥数据结构。
typedef struct Struct_RSAPUBLICKEYBLOB{
	ULONG	AlgID;									//算法标识号
	ULONG	BitLen;									//模数的实际位长度
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];			//模数n = p * q
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];	//公开密钥e
}__attribute__((packed)) RSAPUBLICKEYBLOB, *PRSAPUBLICKEYBLOB;

//RSA私钥数据结构
typedef struct Struct_RSAPRIVATEKEYBLOB{
	ULONG	AlgID;									 //算法标识号
	ULONG	BitLen;									 //模数的实际位长度
	BYTE	Modulus[MAX_RSA_MODULUS_LEN];			 //模数n = p * q
	BYTE	PublicExponent[MAX_RSA_EXPONENT_LEN];	 //公开密钥e
	BYTE	PrivateExponent[MAX_RSA_MODULUS_LEN];	 //私有密钥d
	BYTE	Prime1[MAX_RSA_MODULUS_LEN/2];			 //素数p
	BYTE	Prime2[MAX_RSA_MODULUS_LEN/2];			 //素数q
	BYTE	Prime1Exponent[MAX_RSA_MODULUS_LEN/2];	 //d mod (p-1)的值
	BYTE	Prime2Exponent[MAX_RSA_MODULUS_LEN/2];	 //d mod (q -1)的值
	BYTE	Coefficient[MAX_RSA_MODULUS_LEN/2];		 //q模p的乘法逆元
}__attribute__((packed)) RSAPRIVATEKEYBLOB, *PRSAPRIVATEKEYBLOB;

//ECC公钥数据结构
typedef struct Struct_ECCPUBLICKEYBLOB{
	ULONG	BitLen;											//模数的实际位长度
	BYTE	XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];    //曲线上点的X坐标
	BYTE	YCoordinate[ECC_MAX_YCOORDINATE_BITS_LEN/8];	//曲线上点的Y坐标
}__attribute__((packed)) ECCPUBLICKEYBLOB, *PECCPUBLICKEYBLOB;

//ECC私钥数据结构
typedef struct Struct_ECCPRIVATEKEYBLOB{
	ULONG	BitLen;										//模数的实际位长度
	BYTE	PrivateKey[ECC_MAX_MODULUS_BITS_LEN/8];		//私有密钥
}__attribute__((packed)) ECCPRIVATEKEYBLOB, *PECCPRIVATEKEYBLOB;

//ECC密文数据结构
typedef struct Struct_ECCCIPHERBLOB{
	BYTE  XCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];	//与y组成椭圆曲线上的点（x，y）
	BYTE  YCoordinate[ECC_MAX_XCOORDINATE_BITS_LEN/8];  //与x组成椭圆曲线上的点（x，y）
	BYTE  HASH[32];										//明文的杂凑值
	ULONG CipherLen;									//密文数据长度
	BYTE  Cipher[1];									//密文数据
}__attribute__((packed))  ECCCIPHERBLOB, *PECCCIPHERBLOB;

//ECC签名数据结构
typedef struct Struct_ECCSIGNATUREBLOB{
	BYTE r[ECC_MAX_XCOORDINATE_BITS_LEN/8];			//签名结果的r部分
	BYTE s[ECC_MAX_XCOORDINATE_BITS_LEN/8];			//签名结果的s部分
}__attribute__((packed))  ECCSIGNATUREBLOB, *PECCSIGNATUREBLOB;

//分组密码参数
typedef struct Struct_BLOCKCIPHERPARAM{
	BYTE	IV[MAX_IV_LEN];						//初始向量
	ULONG	IVLen;								//初始向量实际长度（按字节计算）
	ULONG	PaddingType;						//填充方式，0表示不填充，1表示按照PKCS#5方式进行填充
	ULONG	FeedBitLen;							//反馈值的位长度（按位计算），只针对OFB、CFB模式
}__attribute__((packed))  BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;

//ECC加密密钥对保护结构
typedef struct SKF_ENVELOPEDKEYBLOB{
	ULONG Version;                  //当前版本为 1
	ULONG ulSymmAlgID;              //对称算法标识，限定ECB模式
	ULONG ulBits;					//加密密钥对的密钥位长度
	BYTE  cbEncryptedPriKey[64];    //加密密钥对私钥的密文
	ECCPUBLICKEYBLOB PubKey;        //加密密钥对的公钥
	ECCCIPHERBLOB	ECCCipherBlob;  // 用保护公钥加密的对称密钥密文。
}__attribute__((packed)) ENVELOPEDKEYBLOB, *PENVELOPEDKEYBLOB;

//文件属性
typedef struct Struct_FILEATTRIBUTE{
	CHAR	FileName[MAX_FILE_NAME_SIZE];			//文件名
	ULONG	FileSize;				//文件大小
	ULONG	ReadRights;				//读取权限
	ULONG	WriteRights;            //写入权限
}__attribute__((packed))  FILEATTRIBUTE, *PFILEATTRIBUTE;


//#pragma pack(pop, GMCAPI)

//**********************************************************************
//接口函数定义


//////////////////////////////////////////////////////////////////////////
//设备管理函数
//功能描述:	该函数等待设备插入或者拔除事件。szDevName返回发生事件的设备名称。
//参数: szDevName 	[OUT] 发生事件的设备名称。
//		pulDevNameLen	[IN/OUT] 输入/输出参数，当输入时表示缓冲区长度，输出时表示设备名称的有效长度,长度包含字符串结束符。
//		pulEvent	[OUT]事件类型。1表示插入，2表示拔出。
//		返回值	SAR_OK：	成功。
//				其他：		错误码。
//备注:	本函数为阻塞函数。
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
//访问控制函数
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
//应用管理函数
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
//文件管理函数
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
//容器管理函数
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
//密码服务函数。

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

