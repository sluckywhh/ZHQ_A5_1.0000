#ifndef __LIB_VERSION_CONFIG_H
#define __LIB_VERSION_CONFIG_H

#define SOFTWARE_VERSION		1.000039		//软件版本号(对应debug版本号：1.110013)


#define PROJECT_TYPE_ARM9		1		/**< ARM9转换器工程 */
#define PROJECT_TYPE_ZJJ		2		/**< 中间件工程 */
#define PROJECT_TYPE_A5_ZHH		3		/**< A5转换器工程 */
#define PROJECT_TYPE_A5_YTJ		4		/**< A5一体机工程 */

#define PROJECT_TYPE_MODE		PROJECT_TYPE_A5_ZHH


#define NET_VERSION					1		//网络版本
#define NO_NET_VERSION				2		//无网络版本
#define BLUETOOTH_VERSION			3		//蓝牙版本

#if(PROJECT_TYPE_MODE == PROJECT_TYPE_A5_YTJ)
#define COMMUNICATE_VERSION			NO_NET_VERSION
#else
#define COMMUNICATE_VERSION			NET_VERSION
#endif


#define BUSINESS_JSK_MODE	1		//转换器方式调用金税盘流程接口
#define BUSINESS_XML_MODE	2		//直连方式调用统一xml接口
#if (PROJECT_TYPE_MODE == PROJECT_TYPE_ZJJ)
//#define BUSINESS_TYPE_MODE	BUSINESS_XML_MODE
#else
#define BUSINESS_TYPE_MODE	BUSINESS_JSK_MODE
#endif

#endif
