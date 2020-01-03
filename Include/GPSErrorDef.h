#ifndef _GPS_ERROR_DEF_H_
#define _GPS_ERROR_DEF_H_

#define GPS_OK							0
#define GPS_FALSE						1
#define GPS_ERR_NORIGHT					2	//用户无权限
#define GPS_ERR_PARAM					3	//参数错误
#define GPS_ERR_DB_ERR					4	//操作数据库出错
#define GPS_ERR_NO_EXIST				5	//信息不存在
#define GPS_ERR_UNKOWN					6	//未知错误
#define GPS_ERR_NAME_EXIST				7	//名称已经被使用

//设备相关错误代码	21-60
#define GPS_ERR_DEV_NO_EXIST			21	//设备信息不存在
#define GPS_ERR_DEV_NO_RESP				22	//没有收到设备的回馈信息
#define GPS_ERR_DEV_DIS_ONLINE			23	//设备不在线
#define GPS_ERR_DEV_DUEING				24	//正在为其它客户端执行对讲操作
#define GPS_ERR_DEV_TRAN_MSVR_EMPTY		25	//设备媒体转发关联信息不存在
#define GPS_ERR_DEV_CNT_FAILED			26	//设备连接中断
#define GPS_ERR_DEV_STO_POS_EMPTY		27	//未定义存储路径
#define GPS_ERR_DEV_UP_UPGRADING		28	//正在升级
#define GPS_ERR_DEV_UP_FILE_WRONG		29	//升级文件不正确
#define GPS_ERR_DEV_UP_VER_LOW			30	//升级文件版本过低
#define GPS_ERR_DEV_UP_VERIFY_FAILED	31	//升级文件校验失败
#define GPS_ERR_DEV_CHN_NO_EXIST		32	//通道信息不存在
#define GPS_ERR_DEV_SNAP_JPG			33	//抓拍图片失败
#define GPS_ERR_DEV_DISK_FULL			34	//硬盘空间不足
#define GPS_ERR_DEV_UP_VER_SAME			35	//升级文件版本与设备版本相同，不执行升级操作
#define GPS_ERR_DEV_UP_FILE_ERR			36	//升级文件不存在或损坏不可读
#define GPS_ERR_DEV_UP_FILE_CRC			37	//升级文件crc校验失败
#define GPS_ERR_DEV_UP_VER_FAILED		38	//不能从当前版本升级到目标版本
#define GPS_ERR_DEV_UP_FAILED			39	//升级失败
#define GPS_ERR_DEV_SESSION_LIMIT		40	//会话限制，如设备限制同时只允许有4个客户进行录像下载
#define GPS_ERR_DEV_SESSION_EXIST		41	//会话重复
#define GPS_ERR_DEV_SESSION_END			42	//结束会话
#define GPS_ERR_DEV_USR_NO_EXIST		43	//设备用户不存在
#define GPS_ERR_DEV_USR_FULL			44	//设备用户超出限制
#define GPS_ERR_DEV_NO_SUPPORT			45	//设备不支持此功能

//文件相关错误代码	61-80		服务器返回的
#define GPS_ERR_FILE_EXT_ERR			61	//文件格式错误
#define GPS_ERR_FILE_NO_EXIST			62	//服务器上不存在此文件
#define GPS_ERR_FILE_DOWN_OK			63	//文件已全部下载完成
#define GPS_ERR_FILE_DOWN_ING			64	//文件正在下载
#define GPS_ERR_FILE_EMPTY				65	//没有搜索到录像文件
#define GPS_ERR_FILE_USED				66	//文件正在被使用

//用户相关错误代码	81-100
#define GPS_ERR_USR_NO_EXIST			81	//用户不存在
#define GPS_ERR_USR_PWD_ERROR			82	//用户密码错误
#define GPS_ERR_USR_ACCOUNT_ERROR		83	//用户名错误
#define GPS_ERR_USR_PRIORITY_ERROR		84  //优先级错误 （1078用户优先级）

//服务器相关错误代码	101-120
#define GPS_ERR_SVR_CNT_FD				101	//服务器连接失败
#define GPS_ERR_SVR_DISK_FULL			102	//服务器空间不足
#define GPS_ERR_SVR_BUSY				103	//服务器忙
#define GPS_ERR_SVR_CREATE_FILE			104	//服务器创建文件失败
#define	GPS_ERR_SVR_SMSMOD_NO_WORK		105	//短信模块服务没有启动
#define GPS_ERR_SVR_EMPTY				106	//服务器信息不存在，无法为客户提供服务
#define GPS_ERR_SVR_DOWNING				107	//服务器正在下载
#define GPS_ERR_SVR_UPLOADING			108	//正在进行升级
#define GPS_ERR_SVR_DISONLINE			109	//服务器不在线
#define GPS_ERR_SVR_DISCONNECT			110	//服务器连接中断


#endif