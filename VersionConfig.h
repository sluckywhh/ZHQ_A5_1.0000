#ifndef __LIB_VERSION_CONFIG_H
#define __LIB_VERSION_CONFIG_H

#define SOFTWARE_VERSION		1.000033		//����汾��(��Ӧdebug�汾�ţ�1.110013)


#define PROJECT_TYPE_ARM9		1		/**< ARM9ת�������� */
#define PROJECT_TYPE_ZJJ		2		/**< �м������ */
#define PROJECT_TYPE_A5			3		/**< A5ת�������� */

#define PROJECT_TYPE_MODE		PROJECT_TYPE_A5


#define BUSINESS_JSK_MODE	1		//ת������ʽ���ý�˰�����̽ӿ�
#define BUSINESS_XML_MODE	2		//ֱ����ʽ����ͳһxml�ӿ�
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
//#define BUSINESS_TYPE_MODE	BUSINESS_XML_MODE
#else
#define BUSINESS_TYPE_MODE	BUSINESS_JSK_MODE
#endif

#endif
