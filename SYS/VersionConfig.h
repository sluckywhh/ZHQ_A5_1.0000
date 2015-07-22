#ifndef __LIB_VERSION_CONFIG_H
#define __LIB_VERSION_CONFIG_H

#define SOFTWARE_VERSION		1.3001		//软件版本号(对应debug版本号：1.110013)

#define RELEASE_VER				1  /**< 1: 发布版本，0: 测试版本 */

#define	KEYPAD_TYPE				1	/**< 键盘硬件版本，1: 新版键盘（shift与部类5对调，T9输入法键位调整），0: 老版键盘 */
#define	CORP_NAME_LEN_TPYE		0	/**< 纳税户名称长度类型 1: 200字节，0: 40字节 */
#define ON_LINE                 0   /**< 1:纯在线开票模式   0：允许离线开票模式 */    

//#define ZONGCAN_TEST			0   /**< 1: 总参版本，0: 正常版本 */
//#define BACKUP_15S_TEST			0   /**< 1: 15所存档版本, 0: 正常版本*/
#define LANGCHAO_LIB			1   /**< 0: 重庆国税航信版本, 1: 重庆国税浪潮中间件版本*/


#define PRN_ADDR_TEL            1   /**< 1: 支持打印收款单位地址和电话 0: 不支持*/
#define VOL_INV_PRN             1   /**< 1: 卷票打印  0: 平推票打印*/
#endif
