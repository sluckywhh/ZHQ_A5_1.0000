#include "uniAcceptFrameworkApi.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


int main(int argc,char *argv){
	int retval=0;
	string techMsg;
	techMsg.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	techMsg.append("<tripTechnologyPackage version=\"1.0\">");
	techMsg.append("<identity>");
	techMsg.append("<applicationId>zzs_fp_cgl_cj</applicationId>");
	techMsg.append("<serviceId>jsp_dzdz_cb_zzszp</serviceId>");
	techMsg.append("<serviceURI>https://192.168.0.104:8002</serviceURI>");
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
	unsigned char* pOrg=(unsigned char*)"zhuyanchao ";
	unsigned char pOutSign[2048];
	int cbOutSign=sizeof(pOutSign);
	memset(pOutSign,0,sizeof(pOutSign));
	retval=aisino_Sign_pkcs7("88888888",pOrg,strlen((char*)pOrg),
		pOutSign,&cbOutSign,TRUE,TRUE);

	printf("\n\naisino_Sign_pkcs7 retval=%d,%s\n",retval,pOutSign);
	acceptFrameworkCleanup();
	return 0;
	
}
