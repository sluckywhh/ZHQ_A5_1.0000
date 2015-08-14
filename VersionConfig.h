#ifndef __LIB_VERSION_CONFIG_H
#define __LIB_VERSION_CONFIG_H

#define SOFTWARE_VERSION		1.000039		//����汾��(��Ӧdebug�汾�ţ�1.110013)


#define PROJECT_TYPE_ARM9		1		/**< ARM9ת�������� */
#define PROJECT_TYPE_ZJJ		2		/**< �м������ */
#define PROJECT_TYPE_A5_ZHH		3		/**< A5ת�������� */
#define PROJECT_TYPE_A5_YTJ		4		/**< A5һ������� */

#define PROJECT_TYPE_MODE		PROJECT_TYPE_A5_ZHH


#define NET_VERSION					1		//����汾
#define NO_NET_VERSION				2		//������汾
#define BLUETOOTH_VERSION			3		//�����汾

#if(PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ)
#define COMMUNICATE_VERSION			NO_NET_VERSION
#else
#define COMMUNICATE_VERSION			NET_VERSION
#endif


#define BUSINESS_JSK_MODE	1		//ת������ʽ���ý�˰�����̽ӿ�
#define BUSINESS_XML_MODE	2		//ֱ����ʽ����ͳһxml�ӿ�
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
//#define BUSINESS_TYPE_MODE	BUSINESS_XML_MODE
#else
#define BUSINESS_TYPE_MODE	BUSINESS_JSK_MODE
#endif

#endif
