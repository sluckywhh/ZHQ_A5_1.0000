#ifndef _DECODE_CERT_H_
#define _DECODE_CERT_H_

#ifdef _WIN32
#include "windows.h"
#endif

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <memory.h>
#include <malloc.h>

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif
	

#define		SoftWare_API		__declspec(dllexport)
#define		WINAPI				__stdcall

typedef unsigned int  uint32;
typedef unsigned int  UINT4;
typedef int INT4;
typedef unsigned int ATTRIB_TYPE;
typedef unsigned char UC;

#ifdef _WIN32
// 	typedef __int64  UINT8;
// 	typedef __int64  INT8;
#else
	typedef unsigned char UCHAR;
	typedef unsigned char BYTE;
	typedef unsigned int  DWORD;
	typedef int LONG;
#endif

#define  CID__NE_SSLClient             0x8000  /*SSL �ͻ�����֤*/
#define  CID__NE_SSLServer             0x4000  /*SSL ��������֤*/
#define  CID__NE_SMIME                 0x2000  /*SMIME*/
#define  CID__NE_ObjectSigning         0x1000  /*ǩ��*/
#define  CID__NE_Reserved              0x0800  /*δ֪��֤������*/
#define  CID__NE_SSLCA                 0x0400  /*SSL CA*/
#define  CID__NE_SMIMECA               0x0200  /*SMIME CA*/
#define  CID__NE_ObjectSigningCA       0x0100  /*ǩ�� CA*/

/*-- the meaning of each bit in x509 cert key usage --*/
#define  CID__KU_digitalSignature      0x8000
#define  CID__KU_nonRepudiation        0x4000
#define  CID__KU_keyEncipherment       0x2000
#define  CID__KU_dataEncipherment      0x1000
#define  CID__KU_keyAgreement          0x0800
#define  CID__KU_keyCertSign           0x0400
#define  CID__KU_crlSign               0x0200
#define  CID__KU_encipherOnly          0x0100
#define  CID__KU_decipherOnly          0x0080

#define STRING_FILED_MAX_LEN 256


typedef struct ydata_ {
	int oidlength;
	UCHAR oidvalue[120];
}ydata;


int GetCertInfo(
	int CertLen,			//DER�����֤�鳤��
	UCHAR *Cert,			//DER�����֤��
	int CertInfoNo,			//����Ĵ�ȡ��֤���������
	INT4 *IntOutData,		//(out)�����֤�����ֵ(����ֵΪ����ʱ,��������)
	int *OutDataLen,		//(in/out)�����֤�����ֵ�ĳ���(����ֵΪ������ʱ,��������)
	UCHAR *CertInfo			//(out)�����֤�����ֵ(����ֵΪ������ʱ,��������)
	);

#ifdef __cplusplus
}
#endif

#endif
