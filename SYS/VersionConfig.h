#ifndef __LIB_VERSION_CONFIG_H
#define __LIB_VERSION_CONFIG_H

#define SOFTWARE_VERSION		1.3001		//软件版本号(对应debug版本号：1.110013)


#define PROJECT_TYPE_ZHQ		1		/**< ARM9转换器工程 */
#define PROJECT_TYPE_ZJJ		2		/**< 中间件工程 */

#define PROJECT_TYPE_MODE		PROJECT_TYPE_ZHQ


#define BUSINESS_JSK_MODE	1		//转换器方式调用金税盘流程接口
#define BUSINESS_XML_MODE	2		//直连方式调用统一xml接口
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZHQ)
#define BUSINESS_TYPE_MODE	BUSINESS_JSK_MODE
// #elif (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
// #define BUSINESS_TYPE_MODE	BUSINESS_XML_MODE
#endif

#endif
