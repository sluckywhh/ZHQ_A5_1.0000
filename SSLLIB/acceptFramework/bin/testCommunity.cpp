#include "uniAcceptFrameworkApi.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


#include "isccryptapi.h"
#include "decodecert.h"

#include <iostream>

using namespace std;


#define MAX_BUF		1024
#define ERR_LEN		200
#define BUF_LENGTH 200000


int main(int argc,char *argv){
	int retval=0;

	if(argc<=2){
		/*
		unsigned char* pOrg=(unsigned char*)"zhuyanchao ";
		unsigned char pOutSign[2048];
		int cbOutSign=sizeof(pOutSign);
		memset(pOutSign,0,sizeof(pOutSign));

		printf("\n\n begin aisino_Sign_pkcs7 ..[%d].",argc);

		retval=aisino_Sign_pkcs7("88888888",pOrg,strlen((char*)pOrg),
			pOutSign,&cbOutSign,TRUE,TRUE);
		
		printf("\n\naisino_Sign_pkcs7 retval=%d,%s\n",retval,pOutSign);*/



		int retval=0;
		int retryCount=0;
		string m_keyProvider="Aisino Cryptographic Service Provider V1.0";//SM2CONTAINER RSA1024CONTAINER RSA2048CONTAINER
		string m_keyContainer="//Default/CTAS0002        ";
		
		HCRYPTPROV m_hProv;
		
		printf("\nbegin opendivice..pkcs7..%x",m_hProv);
		if(m_hProv==NULL) {
			//retval=this->OpenKey();
		}
		
		
		
		retval=Crypt_OpenDevice(&m_hProv,(char*)m_keyContainer.c_str(),(char*)m_keyProvider.c_str(),0x802,0);
		//int ret = Crypt_OpenDevice(&m_hProv,"","",1,0);
		if(retval==36|| retval==167){
			//ret=Crypt_OpenDevice(&m_hProv,"","NISEC CSP V1.0",0x802,0);
			//m_isAisinoKey=FALSE;
		}
		if(retval != 0)
		{
			//cout<<"密码设备打开失败(客户端)"<<endl;
			char errorMessage[ERR_LEN];
			memset(errorMessage,0,ERR_LEN);
			Crypt_GetErrorMsg(retval,errorMessage,ERR_LEN);
			//m_errorMessage.assign(errorMessage);
			//return (UA_AUTH_OPEN_KEY-ret);
			//return checkLoginReturn(UA_AUTH_OPEN_KEY,retval,retryCount);
			
			
			printf("\nerror begin Crypt_OpenDevice....%s,retval=%d",errorMessage,retval);
		}
		
		if(retval<0) {
			return retval;
		}
		
		printf("\n1....pkcs7 %x",m_hProv);
		//验证客户端口令
		//if(m_isAisinoKey) {
		//retval = Crypt_Login(m_hProv,(char*)CSessionManager::m_keyUseCacheDefaultPassword);
		retval = Crypt_Login(m_hProv,(char*)"88888888");
		//}
		
		
		
		if(retval!=0) {		
			char errorMessage[ERR_LEN];
			memset(errorMessage,0,ERR_LEN);
			Crypt_GetErrorMsg(retval,errorMessage,ERR_LEN);
			
			int retryCount=0;
			
			
			//retval=this->checkLoginReturn(retval,retryCount);
			//return (UA_CLIENT_SIGN_CODE-retval);
			//return checkLoginReturn(UA_CLIENT_SIGN_CODE,retval,retryCount);
			printf("\nerror begin Crypt_Login....%s,retval=%d",errorMessage,retval);
			//return retval;
		}
		//BYTE* pSignedData = new byte[MAX_BUF];
		//DWORD nSignedLen = MAX_BUF;
		printf("\n2....sign pkcs7 ,SIGN_INCLUDE_CERT");
		
		
		char pOrg[MAX_BUF] = "abcdefghijklmnopqrstuvwxyz12345";//测试数据test12345
		DWORD cbOrg = strlen(pOrg);
		BYTE pSignedData[MAX_BUF]={0};
		DWORD nSignedLen = MAX_BUF;
		
		sleep(1);
		printf("\n3....Crypt_SignData ");
		retval = Crypt_SignData(m_hProv,(unsigned char*)pOrg,cbOrg,CRYPT_ALGID_SHA1_RSA_PKCS,
			NULL,SIGN_INCLUDE_NONE,pSignedData,(DWORD*)&nSignedLen);//SIGN_INCLUDE_DATA|
		
		//retval = Crypt_SignData(m_hProv,pOrg,cbOrg,CRYPT_ALGID_SHA1_RSA_PKCS,
		//		NULL,SIGN_INCLUDE_CERT,pOutSignData,(DWORD*)&cbOutSignData);//SIGN_INCLUDE_DATA|
		sleep(1);
		printf("\n2....sign pkcs7 finish %x,SIGN_INCLUDE_CERT[%d] retval=%d",m_hProv,SIGN_INCLUDE_NONE,retval);
		
		sleep(1);
		if(retval!=0) {		
			char errorMessage[ERR_LEN];
			memset(errorMessage,0,ERR_LEN);
			Crypt_GetErrorMsg(retval,errorMessage,ERR_LEN);
			printf("\nerror begin Crypt_OpenDevice....%s,retval=%d",errorMessage,retval);
		}
		printf("\n3....exit pkcs7 %x",m_hProv);	
		Crypt_Logout(m_hProv);
		Crypt_CloseDevice(m_hProv);
	}




	string techMsg;
	techMsg.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	techMsg.append("<tripTechnologyPackage version=\"1.0\">");
	techMsg.append("<identity>");
	techMsg.append("<applicationId>zzs_fp_cgl_cj</applicationId>");
	techMsg.append("<serviceId>jsp_dzdz_cb_zzszp</serviceId>");
	techMsg.append("<serviceURI>https://192.168.2.235:7444</serviceURI>");
	if(argc>2) {
		techMsg.append("<SSL>TA</SSL>");
	} else {
		techMsg.append("<SSL>OA</SSL>");
	}
	
	techMsg.append("<digigalCertPassword>88888888</digigalCertPassword>");
	techMsg.append("<showDigigalCertSelectDialog>FALSE</showDigigalCertSelectDialog>");
	techMsg.append("<logEnabled>TRUE</logEnabled>");
	techMsg.append("<password>x</password>");
	techMsg.append("<nsrsbh>00103434</nsrsbh>");
	techMsg.append("<senderName>zyc</senderName>");
	techMsg.append("</identity>");
	techMsg.append("</tripTechnologyPackage>");
	string bizMsg="hello,I am here";

	unsigned char responseBizMsg[2048];
	int responseBizMsgLength=sizeof(responseBizMsg);
	unsigned char errorMessage[1024];
	retval=aisino_ssl_transfer_call("htxx_test",(char*)techMsg.c_str(),
		techMsg.size(),(unsigned char*)bizMsg.c_str(),bizMsg.size(),responseBizMsg,&responseBizMsgLength,errorMessage);

	
	printf("aisino_ssl_transfer_call retval=%d",retval);
	if(retval==0) {
		string ret;
		char* pp=new char[responseBizMsgLength+1];
		memcpy(pp,responseBizMsg,responseBizMsgLength);
		*(pp+responseBizMsgLength)=0;
		ret.assign(pp);
		delete []pp;
		printf("\naisino_ssl_transfer_call\n%s",ret.c_str());
	}


	
	//acceptFrameworkCleanup();
	return 0;
	
}