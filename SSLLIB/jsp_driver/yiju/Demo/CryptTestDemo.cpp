//for x86:   gcc -o demo CryptTestDemo.cpp -I ../include -L . -lcryptapi -lgetcertinfo -lpthread -ldl -lstdc++
//for arm: arm-linux-gnueabihf-g++ -o armdemoa CryptTestDemo.cpp  armcryptlib.a -I ../include  -L /home/aisino/WTlib -lwt_skf -lwt_pkcs11 -lwt_hw -lcrypto -lssl -lpthread -lrt -ldl -lstdc++



#include "../include/isccryptapi.h"
#include "../include/decodecert.h"
#include "../include/ckwshare.h"


char g_LogPath[_MAX_PATH];
UINT g_nDbgDispLvl,g_bDbgToFile;

#include <iostream>

using namespace std;

typedef unsigned char byte;
typedef unsigned char BYTE;

BOOL bGBSDF=FALSE;

#define MAX_BUF		4096
#define ERR_LEN		200
#define BUF_LENGTH 200000


#pragma comment(lib,"../lib/cryp_api")
#pragma comment(lib,"../lib/decodecert")


int main()
{
	HCRYPTPROV hProv;
	char err[ERR_LEN]={0};
	char pOri[MAX_BUF] = "abcdefghijklmnopqrstuvwxyz�й�12345";//��������test12345
	DWORD nOriLen = strlen(pOri);

	int inputnum=0;
	puts(" ʹ�����ֽӿڣ�1---CSP    2--- ����ӿڣ���");
	scanf("%d",&inputnum);
	if(inputnum == 2) bGBSDF=TRUE;
	else bGBSDF = FALSE;

	char container[ERR_LEN]="//Default/CTAS0002        ";//"//SM2/SM2CONTAINER";//{0};
	printf(" ������container��������(NULL����հ�,����y��ʾĬ�� '%s')��\n",container);
	gets(container);
	gets(container);
	puts(" ");
	if(0 == stricmp(container,"NULL"))
		memset(container,0,ERR_LEN);
	else if(0 == stricmp(container,"y"))
		strcpy(container,"//Default/CTAS0002        ");
	printf("Now,  container = '%s'. \n",container);


	char provider[ERR_LEN]="Aisino Cryptographic Service Provider V1.0";//"./libNISEC_UKEY.so";//{0};
	printf(" ���̣�provider��������(NULL����հ�,����y��ʾĬ�� '%s')��\n",provider);
	gets(provider);printf("------ provider= '%s'. \n",provider);
	puts(" ");
	if(0 == stricmp(provider,"NULL"))
		memset(provider,0,ERR_LEN);
	else if(0 == stricmp(provider,"y"))
		strcpy(provider,"Aisino Cryptographic Service Provider V1.0");
	printf("Now,  provider= '%s'. \n",provider);

	//�������豸--�ͻ���
	int ret = Crypt_OpenDevice(&hProv,container,provider,bGBSDF ? 0x802 : 1,0);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	if(ret != 0)
	{
		cout<<"�����豸��ʧ��(�ͻ���)--"<<err<<endl;
		return 0;
	}
	cout<<"�������豸(�ͻ���)--"<<err<<endl;

	//===============��֤�ͻ��˿���===========================================================
	//��֤�ͻ��˿���
	ret = Crypt_Login(hProv,"88888888");
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"��֤����--"<<err<<endl;
	
	//�������豸--����ˣ�
	HCRYPTPROV hSrvProv = hProv;//�˴��ÿͻ��˴���������ʾ��ʵ������֤��������֤���.

	//==============��ȡ�û�֤��===============================================
	//��ȡCA֤��
	byte pbCACert[MAX_BUF]={0};
	DWORD nCACertLen = MAX_BUF;
	ret = Crypt_ReadCert(hProv,0,pbCACert,&nCACertLen);
	if(ret == 0)
	{
		cout<<"CA֤���ȡ�ɹ�,֤�鳤��Ϊ: "<<nCACertLen<<endl;
		//����֤������
		byte buf[2000]={0};
		int buflen = 2000;
		INT4 outIntN=0;
//		DWORD XX = GetCertInfo(nCACertLen,pbCACert,1,&outIntN,&buflen,buf);
		cout<<"֤�����к�: "<<buf<<endl;		
	}
	else
	{
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"CA֤���ȡ--"<<err<<endl;
	}
	
	//��ȡ�û�֤��
	byte pbCert[MAX_BUF]={0};
	DWORD nCertLen = MAX_BUF;
	ret = Crypt_ReadCert(hProv,1,pbCert,&nCertLen);
	if(ret == 0)
	{
		cout<<"����֤���ȡ�ɹ�,֤�鳤��Ϊ: "<<nCertLen<<endl;
		//����֤������
		byte buf[2000]={0};
		int buflen = 2000;
		INT4 outIntN=0;
		//	DWORD XX = GetCertData(1,pbCert,nCertLen,buf);
//		DWORD XX = GetCertInfo(nCertLen,pbCert,1,&outIntN,&buflen,buf);
		cout<<"֤�����к�: "<<buf<<endl;
	}
	else
	{
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"����֤���ȡ--"<<err<<endl;
	}
	
	nCertLen = MAX_BUF;
	memset(pbCert,0,MAX_BUF);
	ret = Crypt_ReadCert(hProv,2,pbCert,&nCertLen);
	if(ret == 0)
	{
		cout<<"ǩ��֤���ȡ�ɹ�,֤�鳤��Ϊ: "<<nCertLen<<endl;
		//����֤������
		byte buf[2000]={0};
		int buflen = 2000;
		INT4 outIntN=0;
		//	DWORD XX = GetCertData(1,pbCert,nCertLen,buf);
	//	DWORD XX = GetCertInfo(nCertLen,pbCert,1,&outIntN,&buflen,buf);
	//	cout<<"֤�����к�: "<<buf<<endl;
	}
	else
	{
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"ǩ��֤���ȡ--"<<err<<endl;
	}
	
//////////////////////////////////////////////////////////////////////////
	
	int menu=0;
CHOICE:
	puts("\n\n1.ȫ������       2.�������֤ ");
	puts("3.������ǩ��  4.�������ŷ� ");
	puts("\n ��ѡ��");
	scanf("%d",&menu);
	if((menu <1 )||(menu > 4))goto CHOICE;
	bool bJumpToOver=true;
	if(menu == 1)bJumpToOver=FALSE;
	else bJumpToOver = TRUE;
	if(menu == 3) goto SIGN;
	if(menu == 4) goto ENVELOPE;

	//=========================�����֤����==============================
	{
	//--ClientHello
	byte pbClientHello[MAX_BUF]={0};
	DWORD cbClientHello = MAX_BUF;
	ret = Crypt_ClientHello(hProv,0,pbClientHello,&cbClientHello);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"ClientHello( " << cbClientHello << " Bytes) --"<<err<<endl;
	
	//--ServerHello
	byte pbServerHello[MAX_BUF]={0};
	DWORD cbServerHello = MAX_BUF;
	byte pbServerRandom[MAX_BUF]={0};
	DWORD cbServerRandom = MAX_BUF;

	ret = Crypt_ServerHello(hSrvProv,pbClientHello,cbClientHello,pbServerHello,
						&cbServerHello,pbServerRandom,&cbServerRandom);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"ServerHello( " << cbServerHello << " Bytes) --"<<err<<endl;
	//--ClientAuth
	byte pbClientAuth[MAX_BUF]={0};
	DWORD cbClientAuth = MAX_BUF;
	ret = Crypt_ClientAuth(hProv,pbServerHello,cbServerHello,pbClientAuth,&cbClientAuth);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"ClientAuth( " << cbClientAuth << " Bytes) --"<<err<<endl;
	//--ServerAuth
	byte pbClientInfo[MAX_BUF]={0};
	DWORD cbClientInfo = MAX_BUF;
	byte pbSessionKey[MAX_BUF]={0};
	DWORD cbSessionKey = MAX_BUF;
	ret = Crypt_ServerAuth(hSrvProv,pbClientAuth,cbClientAuth,
						pbServerRandom,cbServerRandom,
						pbClientInfo,&cbClientInfo,
						pbSessionKey,&cbSessionKey);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"ServerAuth--"<<err<<endl;
	
	if(bJumpToOver) goto OVER;
	
	}

	//==================PKCS7����ǩ��==================================================
SIGN:
	{
	//PKCS7����ǩ��
	BYTE pSignedData[MAX_BUF]={0};
	DWORD nSignedLen = MAX_BUF;
	ret = Crypt_SignData(hProv,(byte*)pOri,nOriLen, CRYPT_ALGID_SHA1_RSA_PKCS,
				NULL,SIGN_INCLUDE_CERT,pSignedData,&nSignedLen);//SIGN_INCLUDE_DATA|
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P7����ǩ��RSA--"<<err<<endl;
	//��֤PKCS7ǩ��
	ret = Crypt_VerifySignedData(hProv,pSignedData,nSignedLen,0,(byte*)pOri,nOriLen,NULL,0);//NULL,0
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P7��֤ǩ��RSA--"<<err<<endl;

	//PKCS7����ǩ��
	nSignedLen = MAX_BUF;
	memset(pSignedData,0,MAX_BUF);
	ret = Crypt_SignData(hProv,(byte*)pOri,nOriLen, CRYPT_ALGID_GB_ECDSA_SM3 ,
				NULL,SIGN_INCLUDE_CERT,pSignedData,&nSignedLen);//SIGN_INCLUDE_DATA|
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P7����ǩ��SM2--"<<err<<endl;
	//��֤PKCS7ǩ��
	ret = Crypt_VerifySignedData(hProv,pSignedData,nSignedLen,0,(byte*)pOri,nOriLen,NULL,0);//NULL,0
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P7��֤ǩ��SM2--"<<err<<endl;
	//==================PKCS1ǩ��===================================================
	// PKCS1ǩ��
	nSignedLen = MAX_BUF;
	memset(pSignedData,0,nSignedLen);
	ret = Crypt_Sign(hProv, (byte*)pOri,nOriLen,  CRYPT_ALGID_SHA1_RSA_PKCS,
		2, pSignedData,&nSignedLen);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P1����ǩ��RSA--"<<err<<endl;
	//��֤PKCS1ǩ��
	ret = Crypt_VerifySign(hProv, (byte*)pOri,nOriLen,  CRYPT_ALGID_SHA1_RSA_PKCS,
		 PUBKEY_CERTIFICATE, pSignedData,nSignedLen, pbCert,nCertLen);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P1��֤ǩ��RSA--"<<err<<endl;
	

	// PKCS1ǩ��
	nSignedLen = MAX_BUF;
	memset(pSignedData,0,nSignedLen);
	ret = Crypt_Sign(hProv, (byte*)pOri,nOriLen,  CRYPT_ALGID_GB_ECDSA_SM3 ,
		2, pSignedData,&nSignedLen);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P1����ǩ��SM2--"<<err<<endl;
	//��֤PKCS1ǩ��
	ret = Crypt_VerifySign(hProv, (byte*)pOri,nOriLen, CRYPT_ALGID_GB_ECDSA_SM3 ,
		 PUBKEY_CERTIFICATE, pSignedData,nSignedLen, pbCert,nCertLen);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"P1��֤ǩ��SM2--"<<err<<endl;

	if(bJumpToOver) goto OVER;

	}

	//*
	//==================��������ǩ���������ŷ�====================================================
ENVELOPE:	
	{
		// �����ý����߼���֤�����������ŷ�,������ʹ���Լ��ļ���֤����ʾ��
		//������֤��
		BYTE  pbReceiverInfo[MAX_BUF]={0};
		DWORD   cbReceiverInfo = MAX_BUF;
		
		ret = Crypt_ReadCert(hProv, 1, pbReceiverInfo, &cbReceiverInfo);
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"������֤��--"<<err<<endl;
		
		BYTE pbEnvelopedData[MAX_BUF]={0};//binary
		DWORD  cbEnvelopedData = MAX_BUF;
		ret = Crypt_EnvelopData(hProv, (BYTE*)pOri, nOriLen, CRYPT_ALGID_DES3_CBC,
			pbReceiverInfo,  cbReceiverInfo,		0, NULL, 			
			SIGN_INCLUDE_DATA|SIGN_EXCLUDE_SIGN, // dwFlags:��������ϢΪ֤�飬�������ŷ��а������ݣ�������ǩ��
			pbEnvelopedData, &cbEnvelopedData);
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"----------------��������ǩ���������ŷ�------------"<<err<<endl;
		//cout<<""<< pbEnvelopedData <<endl;
		//	Write_CKW_DEBUGLog(NULL,"binary result��",pbEnvelopedData,cbEnvelopedData,NULL);
		printf("�����ŷⳤ��=%d\n", cbEnvelopedData);
		//*/
		
		char  strResult [BUF_LENGTH]={0};
		DWORD   lenResult = BUF_LENGTH;
		ret = Crypt_BinaryToBase64String(
			pbEnvelopedData,		//in 2��������
			cbEnvelopedData,		//in ���鳤��
			0x40,					//in
			strResult,				//out ���Base64�ִ�
			&lenResult);			//in/out ����������/�����ʵ�ʳ���
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"Base64����--"<<err<<endl;
		
		
		char *strEnvelopedDataB64 = strdup(strResult);
		//�����ŷ���
		printf("�����ŷ�: %s\n", strEnvelopedDataB64);  
		
		//*
		//(�������ŷ�)
		// ��ʵ�ʱ��ʱ����Ҫ��Base64������ִ�ת��Ϊ�ֽ����������
		
		cbEnvelopedData = MAX_BUF;
		memset(pbEnvelopedData,0,cbEnvelopedData);
		ret = Crypt_Base64StringToBinary(
			strEnvelopedDataB64,			//in �ַ���(�ɺ��س����з���ͷβ���)
			strlen(strEnvelopedDataB64),	//in �ַ�����󳤶�
			pbEnvelopedData,				//out �������������Ļ�����(����ΪNULL)
			&cbEnvelopedData);				//in/out ����������/���س���
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"ת��Ϊ�ֽ�����--"<<err<<"   ������� " << cbEnvelopedData << "�ֽ�" <<endl;
		//*/
		
		nOriLen = MAX_BUF;
		memset(pOri,0,nOriLen);
		ret = Crypt_VerifyEnvelopedData(hProv, 
			pbEnvelopedData, cbEnvelopedData, 
			NULL, 0, NULL, 0, 
			(BYTE*)pOri, &nOriLen);
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"�������ŷ�--"<<err<<endl;
		
		if (ret == 0)
		{
			printf("����ķ�װ���ݳ���=%d\n", nOriLen);
			printf("����ķ�װ����: %s\n", pOri);   	
		}
		
		
		//==================������ǩ���������ŷ�====================================================
		
		char pOri2[MAX_BUF] = "abcdefghijklmnopqrstuvwxyz�й�12345";//��������test12345
		DWORD nOriLen2 = strlen(pOri2);
		
		cbEnvelopedData = MAX_BUF;
		memset(pbEnvelopedData,0,cbEnvelopedData);
		ret = Crypt_EnvelopData(hProv, (BYTE*)pOri2, nOriLen2, CRYPT_ALGID_GB_SMS4_CBC,//CRYPT_ALGID_DES3_CBC,
			pbReceiverInfo,  cbReceiverInfo,		bGBSDF ? CRYPT_ALGID_GB_ECDSA_SM3 : CRYPT_ALGID_SHA1_RSA_PKCS, NULL, 			
			SIGN_INCLUDE_DATA|SIGN_INCLUDE_CERT, // dwFlags:��������ϢΪ֤�飬�������ŷ��в��������ݣ�����ǩ��
			pbEnvelopedData, &cbEnvelopedData);
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"------------������ǩ���������ŷ�----------"<<err<<endl;
		//	cout<<"binary result��"<< pbEnvelopedData <<endl;
		//	Write_CKW_DEBUGLog(NULL,"binary result��",pbEnvelopedData,cbEnvelopedData,NULL);
		
		printf("�����ŷⳤ��=%d\n", cbEnvelopedData);
		//*/
		
		lenResult = BUF_LENGTH;
		memset(strResult,0,lenResult);
		ret = Crypt_BinaryToBase64String(
			pbEnvelopedData,		//in 2��������
			cbEnvelopedData,		//in ���鳤��
			0x40,					//in
			strResult,				//out ���Base64�ִ�
			&lenResult);			//in/out ����������/�����ʵ�ʳ���
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"Base64����--"<<err<<endl;
		
		
		strEnvelopedDataB64 = strdup(strResult);
		//�����ŷ���
		printf("�����ŷ�: %s\n", strEnvelopedDataB64);  
		
		//*
		//(�������ŷ�)
		// ��ʵ�ʱ��ʱ����Ҫ��Base64������ִ�ת��Ϊ�ֽ����������
		
		cbEnvelopedData = MAX_BUF;
		memset(pbEnvelopedData,0,cbEnvelopedData);
		ret = Crypt_Base64StringToBinary(
			strEnvelopedDataB64,			//in �ַ���(�ɺ��س����з���ͷβ���)
			strlen(strEnvelopedDataB64),	//in �ַ�����󳤶�
			pbEnvelopedData,				//out �������������Ļ�����(����ΪNULL)
			&cbEnvelopedData);				//in/out ����������/���س���
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"ת��Ϊ�ֽ�����--"<<err<<"   ������� " << cbEnvelopedData << "�ֽ�" <<endl;
		//*/
		
		nOriLen = MAX_BUF;
		memset(pOri,0,nOriLen);
		ret = Crypt_VerifyEnvelopedData(hProv, 
			pbEnvelopedData, cbEnvelopedData, 
			NULL, 0, NULL, 0, 
			(BYTE*)pOri, &nOriLen);
		Crypt_GetErrorMsg(ret,err,ERR_LEN);
		cout<<"�������ŷ�--"<<err<<endl;
		
		if (ret == 0)
		{
			printf("����ķ�װ���ݳ���=%d\n", nOriLen);
			printf("����ķ�װ����: %s\n", pOri);   	
		}  			
	}
OVER:
CLOSEDEVICE:

	
	//�رշ����
	ret = Crypt_Logout(hSrvProv);
	Crypt_GetErrorMsg(ret,err,ERR_LEN);
	cout<<"Crypt_Logout--"<<err<<endl;
	
	if(hSrvProv != hProv)
		Crypt_CloseDevice(hSrvProv);
	//�ر������豸
	Crypt_CloseDevice(hProv);
	
	system("pause");
	return 0;
}
