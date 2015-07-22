#ifndef _SCST_GMC_API_EXT_H_
#define _SCST_GMC_API_EXT_H_

#include "GMCAPI.h"

#ifdef __cplusplus
extern "C" {
#endif

//#pragma pack(push, GMCAPI, 1)
typedef struct _FormatKeyParam
{
	BYTE  VersionMajor;         //主版本。当前为1
	BYTE  VersionMinor;			//小版本。当前为0.
	ULONG ulAuthAlgID;          //认证算法。
	ULONG ulDevAuthKeyLen;		//pbDevAuthKey的有效长度。
	BYTE  pbDevAuthKey[32];     //设备认证Key。最大为32个字节。
	BYTE  pbDevLabel[64];       //字符串，最大为64个字节。
	BYTE  pbAuthCode[16];       //用于验证是否可以格式化Key的认证码.
	BYTE  bSupportRootCert;		//是否识别根证书。(0表示不识别。1表示识别). 在3部系统中使用。
								//三部应用中，需要识别名字包含Cert0的文件。作为根证书保存。P11需要使用该名字进行识别。
	BYTE  byCertStoreType;		//证书存储类型。0表示自动识别。1表示存储在内部。2表示存储在NAND中。
	BYTE  byFileStoreType;		//文件存储类型。0表示自动识别。1表示存储在内部。2表示存储在NAND中。
}__attribute__((packed)) FormatKeyParam, *PFormatKeyParam;
//#pragma pack(pop, GMCAPI)

#define ROOT_CERT 0			// 根证书
#define SIGN_CERT 1         // 签名证书
#define ENC_CERT  2			// 加密证书
#define NO_CERT   3			// 无证书

#define MAX_CONTAINER_CERT_COUNT 3
#define MAX_CERT_CONTENT_LEN 4000

typedef struct tagCert 
{
	ULONG CertType;								// 证书类型
	ULONG CertLen;								// 证书有效长度
	BYTE  CertContent[MAX_CERT_CONTENT_LEN];	// 证书内容
}Cert, *PCert;

typedef struct tagContainerRecordItem
{
	BOOL IsExist;										// 记录项是否存在
	ULONG AppID;										// 应用ID
	char AppName[MAX_FILE_NAME_SIZE];					// 应用名称
	ULONG ContainerType;								// 容器类型
	char ContainerName[MAX_FILE_CONTAINER_NAME_SIZE];	// 容器名称
	Cert cert[MAX_CONTAINER_CERT_COUNT];				// 证书结构
}ContainerRecordItem, *PContainerRecordItem;

//格式化Key.
//功能描述:		格式化Key。
//参数: hDev 	[IN] 设备句柄。
//		pFkParam	[IN] 格式化使用的参数。
//		返回值	SAR_OK：	成功。
//				其他：		错误码。
//备注:	
ULONG DEVAPI SKFI_FormatKey(DEVHANDLE hDev,
							PFormatKeyParam pFkParam);

//软复位。
ULONG DEVAPI SKFI_CardReset(DEVHANDLE hDev);

// 功能描述    使用内部RSA加密私钥对输入数据做解密运算并输出结果
// 参数        hContainer                   [IN] 容器句柄
// pbCipherText                 [IN] 待解密的密文数据
// ulCipherTextLen              [IN] 待解密密文数据长度
// pbPlainText                  [OUT] 返回明文数据,如果该参数为NULL，则由pulPlainTextLen返回明文数据的实际长度。
// pulPlainTextLen              [IN，OUT] 输入时表示pbPlainText缓冲区的长度，输入时表示明文数据的实际长度。
// 返回值      SAR_OK:           成功。
// 其他:             错误码。

ULONG DEVAPI SKF_RSADecrypt(HCONTAINER hContainer, 
							BYTE *pbCipherText, 
							ULONG ulCipherTextLen, 
							BYTE *pbPlainText,
							ULONG *pulPlainTextLen);

//功能描述    使用内部ECC加密私钥对输入数据做解密运算并输出结果
// 参数        hContainer                   [IN] 容器句柄
// pCipherText                  [IN] 待解密的密文数据
// pbPlainText                  [OUT] 返回明文数据,如果该参数为NULL，则由pulPlainTextLen返回明文数据的实际长度。
// pulPlainTextLen              [IN，OUT] 输入时表示pbPlainText缓冲区的长度，输入时表示明文数据的实际长度。

ULONG DEVAPI SKF_ECCDecrypt(HCONTAINER hContainer, 
							PECCCIPHERBLOB pCipherText, 
							BYTE *pbPlainText,
							ULONG *pulPlainTextLen);




//---------------------关于证书共享内存操作函数----------------------------------//

//功能描述   当增加证书时，向共享内存中增加记录
// 参数  
// pDevSerialNum		[IN] 设备序列号
// ulSerialNumLen		[IN] 设备序列号长度
// ulAppID				[IN] 应用ID
// lpszContainerName    [IN] 容器名
// pbCert				[IN] 证书内容
// ulCertLen            [IN] 证书长度
// nCertType		    [IN] 证书类型

ULONG DEVAPI SKFC_AddCertRecord(const BYTE* pDevSerialNum, 
								ULONG ulSerialNumLen, 
								ULONG ulAppID, 
								LPSTR lpszContainerName, 
								BYTE* pbCert, 
								ULONG ulCertLen, 
								int nCertType);


//功能描述   当删除证书时，在共享内存中删除对应记录
// 参数  
// pDevSerialNum		[IN] 设备序列号
// ulSerialNumLen		[IN] 设备序列号长度
// ulAppID				[IN] 应用ID
// lpszContainerName    [IN] 容器名
// nCertType		    [IN] 证书类型
ULONG DEVAPI SKFC_DeleteCertRecord(const BYTE* pDevSerialNum, 
								   ULONG ulSerialNumLen, 
								   ULONG ulAppID, 
								   LPSTR lpszContainerName, 
								   int nCertType);

//功能描述   当删除容器时，在共享内存中删除容器记录
// 参数  
// pDevSerialNum		[IN] 设备序列号
// ulSerialNumLen		[IN] 设备序列号长度
// ulAppID				[IN] 应用ID
// lpszContainerName    [IN] 容器名
ULONG DEVAPI SKF_DeleteContainerRecord(const BYTE* pDevSerialNum, 
									   ULONG ulSerialNumLen, 
									   ULONG ulAppID, 
									   LPSTR lpszContainerName);


//功能描述   当创建容器时，在共享内存中创建容器记录
// 参数  
// pDevSerialNum		[IN] 设备序列号
// ulSerialNumLen		[IN] 设备序列号长度
// ulAppID				[IN] 应用ID
// lpszContainerName    [IN] 容器名

ULONG DEVAPI SKFC_AddContainerRecord(const BYTE* pDevSerialNum, 
									 ULONG ulSerialNumLen, 
									 ULONG ulAppID, 
									 LPSTR lpszContainerName);


//功能描述   返回共享内存中的所有记录
// 参数  
// pDevSerialNum		[IN] 设备序列号
// ulSerialNumLen		[IN] 设备序列号长度
// pRecordItem		    [OUT] ContainerRecordItem结构指针，pRecordItem为空时，nRecordItemCount返回所需要的ContainerRecordItem结构数量
// pnRecordItemCount     [IN\OUT] 输入时，表示ContainerRecordItem结构个数，输出时，表示实际的ContainerRecordItem结构数量。
//								 ContainerRecordItem中的IsExist总是为真，所以可以忽略
ULONG DEVAPI SKFC_GetContainerRecordItem(const BYTE* pDevSerialNum, 
										 ULONG ulSerialNumLen, 
										 ContainerRecordItem *pRecordItem, 
										 ULONG* pulRecordItemCount);

ULONG DEVAPI SKFC_CleanMemeory(const BYTE* pDevSerialNum, 
							   ULONG ulSerialNumLen);

//---------------------三部需求根证书函数----------------------------------//
//  功能描述	向容器内导入CA数字证书。
//  参数	    hContainer	[IN] 容器句柄。
//  pbCert		[IN] 指向证书内容缓冲区。
//  ulCertLen	[IN] 证书长度。
//  返回值	    SAR_OK：	成功。
ULONG DEVAPI SKF_ImportCACertificate(HCONTAINER hContainer, 
									 BYTE* pbCert, 
									 ULONG ulCertLen);

// 功能描述			从容器内导出CA数字证书。
// 参数	hContainer	[IN] 容器句柄。
// pbCert			[OUT] 指向证书内容缓冲区，如果此参数为NULL时，pulCertLen表示返回数据所需要缓冲区的长度，如果此参数不为NULL时，返回数字证书内容。
// pulCertLen		[IN/OUT] 输入时表示pbCert缓冲区的长度，输出时表示证书内容的长度。
// 返回值			SAR_OK：	成功。
// 其他：			错误码。
ULONG DEVAPI SKF_ExportCACertificate(HCONTAINER hContainer,
									 BYTE* pbCert, 
									 ULONG *pulCertLen);	

#ifdef __cplusplus
}


#endif

#endif //_SCST_GMC_API_H_
