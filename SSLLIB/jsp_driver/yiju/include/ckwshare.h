//ʱ����ַ���������
#ifndef CKWSHARE_H
#define CKWSHARE_H

#include "string.h"
#include "stdlib.h"
#include "time.h"

#ifndef IN
#define IN
#endif // IN

#ifndef OUT
#define OUT
#endif // OUT

#define  TIME_FMT  "%Y%m%d %H:%M:%S"

#if (defined(_WIN32) || defined(_WIN64))
	#define SLEEPMS(ms)	Sleep(ms)
	#define	SLEEPS(s)	Sleep((s*1000))
#else
	#define SLEEPMS(ms)	usleep(ms*1000)
	#define	SLEEPS(s)	sleep(s)
	#define stricmp(s1, s2) strcasecmp(s1, s2)
	#define strnicmp(s1, s2, maxlen) strncasecmp(s1, s2, maxlen)
#endif

#ifdef __cplusplus
extern "C" {
#endif

char* _strupr (char* str);
char* _strlwr (char* str);
void safestrcpy(char *str1, const char *str2, int maxlen);
void safefree(void *memblock );
void GetCurTime(char * sTime);
void GetThatTime(char * sTime,time_t ltime);
time_t get_time_milisec(time_t *);//�õ���ǰ����ֵ��������NULL����ǿ����������ڲ��������С�
int FindData1InDATA2(unsigned char* data1,int data1len,unsigned char* data2,int data2len);
char* trim(IN char* s);


//�ж�ĳ������num�Ƿ�����ĳһ����Χ str_scope����" 2 -  6 ; 192 ; 80.2 - 0 0. 6 ;"��Ҫ����߽����пո����ֺ�".;-"��
//,"ALL","all","*"�������еķ�Χ;
//����ֵ��0--�����ڣ�1--���ڣ�-1--�������д����Ƿ��ַ���
//1.����ȥ���ַ����еĿո��ж��ַ����н��������ֺ�".;-"�����򷵻�-1��
//2.������Χ�ִ�������";"Ϊһ���Σ���������"-"��������ε�������ת��Ϊ������ʽ���ж������Ƿ�������ޣ�Ҳ���Բ��жϣ���Ӱ��Ч������
//3.��num�Ƿ����ڴ˶Σ�����ǣ�����ֵ1��������ǣ�����������Χ�ִ���
//4.��Χ�ִ��������ˣ�����0��
//////////
int  IsThisNumInTheScope(IN int num,IN char* str_scope);//ckw add 20141102.

#ifdef __cplusplus
}
#endif

#endif
