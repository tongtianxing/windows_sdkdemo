#ifndef _TTX_DVR_NET_API_H_
#define _TTX_DVR_NET_API_H_

#include "ttxdvrnetdef.h"
#include "ttxdvralarmdef.h"
#include "ttxdvrtransparentdef.h"

/******************************************************************************
  Author        : afu
  Created       : 2011/06/30
  Last Modified :
  Description   : 网络模块接口定义
  History       :
	  1.	Date        : 2011/06/30
		Author      : afu
		Modification: Created file
		
******************************************************************************/

/*
* 注意事项
* 	1、关于格式化SD卡，如果调用TTXNET_SetDataPath 将GPS、报警信息缓存到SD卡上，
		那么执行格式化SD卡操作需要TTXNET_StopWork 停止网络库程序
	2、建议将日志目录配置到SD卡上，并且发送版本不开启日志功能
		TTXNET_SetLogParam(false, false, 0, "/mnt/sd/", 10);
	3、建立将缓存目录配置到SD卡上
		TTXNET_SetDataPath
*/

/*
1、	版本：	6.1.0.1	
	日期：	20130517	
	修改：
2、	版本：	6.1.0.2	
	日期：	20130520	
	修改：	1、将Socket发送缓存调整为64K
				2、TTXPfnAVEncoderCB 增加返回值TTX_NET_ERR_BUF_FULL，通知网络库出现丢弃媒体数据的情况
				3、对分配内存进行相应处理，避免出现分配内存出错，而继续使用内存的情况
3、	版本：	6.1.0.3	
	日期：	20130530	
	修改：	1、去除Socket发送缓存调整为64K 的操作
				2、增加远程回放接口
					上层需要从CTTXRecFile  继承创建文件解析类，按视频帧方式传到服务器				
4、	版本：	6.1.0.4	
	日期：	20130603	
	修改：	1、修正PC对终端进行参数配置时，传送参数文件长度为0，造成参数配置失败的错误

5、 	版本：	6.1.0.5 
	日期：	20130604	
	修改：	1、增加接口获取和配置某个类型的参数信息(见CTTXNetWork::DoGetConfig 和CTTXNetWork::DoSetConfig )
	
6、 	版本：	6.1.0.6
	日期：	20130610	
	修改：	1、增加对串口数据透传，如果网络中断则再先缓存到本地(使用环形缓存队列进行缓存)
				2、增加文件上传报警类型定义，用于设备主动通知服务器需要上传录像文件和图片文件
7、 	版本：	6.1.0.7
	日期：	20130622	
	修改：	1、修改TTXNET_SetDeviceInfo 接口，增加上报磁盘类型和厂家类型
				2、增加TTXNET_SetNetworkInfo接口，用于上报当前使用的网络连接的状态(3G \ WIFI \ 有线)
				3、增加TTXNET_SetMediaInfo接口，用于设置音频媒体格式
8、 	版本：	6.1.0.8
	日期：	20130627	
	修改：	1、修改CTTXNetWork::DoFreePresetGet  接口，用于获取最小有效的预置位
9、 	版本：	6.1.0.9
	日期：	20130629	
	修改：	1、修改TTXNET_SendAudioIntercom  设备主动向服务器发起对讲请求
10、	版本: 		6.1.0.10
	日期:		20130701
	修改		1、修改TTXNET_StartWork接口，增加bInitLogin，用户可以选择是否向服务器注册
				2、增加获取网络参数接口DoGetNetParam和设备网络参数接口DoSetNetParam
				3、增加获取颜色参数接口DoGetVideoColor和DoSetVideoColor
11、	版本: 	6.1.0.11
	日期:		20130729
	修改		1、修正搜索录像文件时，文件时长 nEndTime 始终为0的 BUG
12、	版本: 	6.1.0.12
	日期:		20130731
	修改		1、TTXNET_Initialize接口增加signal(SIGPIPE, SIG_IGN);调用, 屏蔽socket中断时，程序会主动退出
13、	版本: 	6.1.0.13
	日期:		20130802
	修改		1、增加CTTXNetWork::GetVideoResolution 用于获取视频通道的分辨率，方便网络库开启缓存
14、	版本: 	6.1.0.14
	日期:		20130803
	修改		1、增加CTTXNetWork::FindJpegFile 用于查找图片文件信息
15、	版本: 	6.1.0.15
	日期:		20130813
	修改		1、支持同时预览主码流和子码流的视频信息
15、	版本: 	6.1.0.16
	日期:		20130826
	修改		1、支持配置会话绑定本地端口(TTXNET_SetSessPortBind，必须在TTXNET_StartWork 前调用
					在服务器防火墙 双向管制时使用，服务器只接收设备指定端口上传的数据
16、	版本: 	6.1.0.17
	日期:		20130905
	修改		1、加快媒体上传，媒体会话与服务器建立链路后发送请求后，不再等待服务器回复消息
				快速发送数据给服务器，可以加视频上传速度
17、	版本: 	6.1.0.18
	日期:		20130921
	修改		1、优先离线状态速度
					调用TTXNET_StopWork，在服务器连接正常的情况下，及时向服务器发送个注销的数据包
					加快服务器判断离线的速度( 3G 网络环境下, 服务器不一定能及时收到数据包)
				2、增加日志文件查询接口
					主要用于设备端当系统出现问题时，使用日志进行判断
18、	版本:	6.1.0.19
	日期:		20130925
	修改		1、增加上报IO输入, 输出状态
					SetIOStatus(const TTXIOStatus_S& io)
				2、增加上报录像状态和视频丢失状态
					SetChannelStatus(const TTXChannelStatus_S& channel)
				3、增加上报超速、低速、停车时长状态见TTXVehiStatus_S
					typedef struct tagTTXVehiStatus
					{
						bool bOverSpeed;		//超速状态
						bool bLowSpeed;		//低速状态
						unsigned int nParkTime;	//停车时长单位秒，大于0表示静止状态	
					}TTXVehiStatus_S, *LPTTXVehiStatus_S;		
19、	版本:	6.1.20
	日期:		20131009
	修改		1、在信令链路的接收线程，优先处理控制指令
20、	版本:	6.1.21
	日期:		20131021
	修改		1、UDP监听链路支持透明参数配置协议
21、	版本:	6.1.22
	日期:		20140110
	修改		1、增加局域网，WIFI参数配置功能	DoSetWifiParam
				2、增加水平翻转，垂直翻转功能	TTX_CTRL_TYPE_FLIP_HORIZONTAL 和TTX_CTRL_TYPE_FLIP_VERTICAL
22、	版本:	6.1.23
	日期:		20140310
	修改		1、增加TTX_ALARM_TYPE_CUSTOM 自定义报警，客户根据项目定义不同的报警
23、	版本:	6.1.24
	日期:		20140414
	修改		1、TTXNET_SetNetworkInfo 增加imei参数，用于上报imei信息
										增加version参数，用于上报设备主机版本(服务器会将主机和网络版本都上报)
				2、TTXNET_SetReconnNow 设置立即重连，如3G 拔号成功，WIFI连接成功后，及时调用TTXNET_SetReconnNow
										这样可以快速恢复与服务器建立链接
24、	版本:	6.1.25
	日期:		20140426
	修改		1、增加GetUploadFilePath 和SaveUploadFile 用于服务器向设备上传文件
				2、增加TransQuery 用于透明查询功能(可以实时详细操作日志查询等)
				3、增加与服务器校时的功能TTXNET_SetSyncTime 设置是否同步校时，SyncTime 响应校时命令
25、	版本:	6.1.26
	日期:		20140613
	修改		1、修改单次接收到多个指令时，只处理了第一条指令的BUG
26、	版本:	6.1.27
	日期:		20140708
	修改		1、修正停止视频偶尔出现的死锁和当机的BUG
27、	版本:	6.1.28
	日期:		20140718
	修改		1、增加SetHeartInterval  可以设置心跳的时间间隔
28、	版本:	6.1.29
	日期:		20140827
	修改		1、TTXModuleStatus_S，增加两个参数，上报坐标类型和定位类型
					char cCoorType;		//GPS坐标类型TTX_COOR_TYPE_WSG84，TTX_COOR_TYPE_GCJ02, TTX_COOR_TYPE_BD09
					char cLocType; 		//GPS定位类型TTX_LOC_TYPE_GPS，TTX_LOC_TYPE_WIFI
				2、增加TTXNET_IsRunningNormal看门狗可以通过此接口来判断网络库是否运行正常
					如果出现异常建议直接重启程序
				3、将部分共用的头文件移动到 dvrnet/common 目录下，因此需要更新makefile才能正常编译
29、版本:	6.1.30
	日期:		20141217
	修改		1、增加离线升级功能，主机启动时，会从服务器上获取升级的版本信息
					如果获取成功后
					调用CheckUpgradeVer来判断是否需要进行升级，走GetUploadFilePath, GetUpgradeFile, UpgradeDevice这套升级接口
					老版本设备支持此功能，上层软件不需要做修改					
				2、增加启动时上报硬盘状态、通道视频丢失状态等信息到服务器，服务器会提供硬件故障报表
				3、增加UPS剪线报警、硬盘超温报警、前面板撬开报警
30、版本:  	6.1.31
	日期:		20150130
	修改		1、TTXNET_SetMediaInfo增加VideoCoder参数，默认用TTX_VIDEO_CODEC_H264，如果是海思的请使用TTX_VIDEO_CODEC_H264_HI

31、版本:  	6.1.32
	日期:		20150314
	修改		1、增加TTX_ALARM_TYPE_DISK_SPACE_WARNING，硬盘空间警告

32、版本:  	6.1.33
	日期:		20150605
	修改		1、TTXNET_StartWork增加bOnlyMedia接口，808交互时，信令走808，媒体从此协议时使用
					增加TTXNET_TransparentInstruction接口，808透传的指令通过此接口传送到网络库中
					见部标协议8.61  数据下行透传0x8900
						指令类型0xeb;
					请将部标信令里面收到的透传指令(指令类型为0xeb)调用TTXNET_TransparentInstruction，送到网络库
				2、增加TTXNET_InitiativeUploadStatus接口，用于及时上报gps数据
33、版本:  	6.1.34
	日期:		20150723
	修改		1、高清设备注意重载CTTXNetWork::GetVideoResolution接口上报码流的分辨率和缓存的情况
					结合新版本的服务器使用，会将分辨率传送到服务器上，
					客户端解码显示时，会结合分辨率生成使用不同的缓存
				2、回放时，请传递TTXFILEInfo_S 信息内增加传递
					unsigned char ucResolution;		//分辨率		TTX_RESOLUTION_720P
					参数到服务器
34、版本:  	6.1.35
	日期:		20150830
	修改		1、增加TTXPfnJT808UploadTransInstructionCB用于808对接时通过808透传将指令上传到服务器上
35、版本:  	6.1.36
	日期:		20151012
	修改		1、增加TTXPfnJT808CheckOnlineCB用于808对接时判断信令链路是否在线用
36、版本:  	6.1.37
	日期:		20151028
	修改		1、更新TTXAlarmInfo, param[4]改为param[8]
				2、GetUploadFilePath 增加szSvrFile参数，表示服务器上对应的文件名，方便设备判断文件类型
				3、SaveUploadFile增加szMd5参数，表示文件对应的md5值，设备可以通过md5来校验文件的正确性
37、版本:  	6.1.38
	日期:		20151107
	修改		1、TTXNET_StartWork增加bAuthentication接口，处理是否进行鉴权
				2、增加DoAuthentication接口，对服务器返回的数据进行鉴权，鉴权成功后，再将鉴权码加密后返回给服务器
38、版本:  	6.1.39
	日期:		20151120
	修改		1、增加TTXObdStatus_S 和TTXPeopleStatus_S信息，用于上报OBD状态和人数统计信息
39、版本:  	6.1.40
	日期:		20151202
	修改		1、增加IsInitStatus 用于判断gps状态是否初始化成功，避免启动时向服务器传送无效的状态信息
				2、TTXNET_SetDataPath 增加nStatusCacheCount和nAlarmCacheCount参数，用于上层自定义报警和GPS的缓存数目
					在同样的缓存大小下，可以缓存更多的GPS数据
40、版本:  	6.1.41
	日期:		20151208
	修改		1、增加TTXNET_SetAVDirectConnectDiffBuffer视频直连时和3G上报使用不同的缓存
					配合使用TTX_STREAM_TYPE_DIRECT_MAIN	TTX_STREAM_TYPE_DIRECT_SUB 这两个码流类型
41、版本:  	6.1.42
	日期:		20151210
	修改		1、增加TTXNET_SetIsLoginSvr用户上层配置是否与服务器建立连接,默认是与服务器建立连接
42、版本:  	6.1.43
	日期:		20160106
	修改		1、增加TTXNET_SendDirectAlarmInfo用于直连时上报报警信息
43、版本:  	6.1.44
	日期:		20160301
	修改		1、增加状态线程用于产生GPS状态
43、版本:  	6.1.45
	日期:		20160416
	修改		1、obd数据上报增加了几个内容，见TTXObdStatus_S, obd和GPS实时上传
				2、增加TTXTireStatus_S，胎压数据定义，胎压数据使用透传方式进行上报
				3、增加TTX_ALARM_TYPE_TPMS胎压报警的定义
				4、TTXGpsInfo_S结构体增加usGaoDu高程定义，单位米
				5、增加GetAudioParam接口，处理不同通道音频格式不一致的问题，如对讲用g711，通道音频用aac
				6、增加TTXNET_SetMediaIPSameAsLoginIP和TTXNET_SetServerInfo处理WIFI连接IP1，3G连接IP2
44、版本  	6.1.46
	日期:		20161201
	修改:     	1、修改通用库的目录放到dvrnet/ttxcommon内，请将原来的库整体删除，重新更新库文件，再进行编译
				2、增加TTXNET_IsServerDeviceExist接口用于判断服务器上是否添加好的设备，请参照接口函数说明
45、版本  	6.1.47
	日期:		20170312
	修改:     	1、实时视频和远程回放，一次读取多帧的信息，用于提高发送效率
				2、增加GetVideoParam用于不同通道视频编码格式不同
46、版本  	6.1.48
	日期:		20170905
	修改:     	1、增加TTXNET_SetDevicePwd，可以配置设备连接服务器使用的密码
					增加TTXNET_SetLoginType，设置登录类型, 为在linux上登录或者android登录
47、版本  	6.1.49
	日期:		20180122
	修改:     	1、回放时判断如果是wifi网络，每次会多读取帧数进行发送
48、版本  	6.1.50
	日期:		20190322
	修改:     	1、录像搜索增加返回是否支持多路回放和可以多路回放的通道的标识

49、版本  	6.1.51
	日期:		20190618
	修改:     	1、码流切换增加标识
50、版本  	6.1.52
	日期:		20190803
	修改:     	1、增加渣土车状态上报接口	TTXSlagStatus_S   及GetSlagStatus, SetSlagStatus
50、版本  	6.1.53
	日期:		20191205
	修改:     	1、TTXNET_SetNetworkInfo调用时会判断网络状态是否发生变化，如果变化会自动重连
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @Description: 初始化网络库，程序启动时调用
 * @param: 无
 * @return: void 
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_Initialize();

/**
 * @Description: 释放网络库，程序退出时调用
 * @param: 无
 * @return: void 
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_InInitialize();

/**
 * @Description: 设置日志参数
 * @param:	bConsole 	是否输出到控制台
 			bFile 		是否写日志到文件
 			nLogLevel 	日志级别0 - 3，0最小，3最大，级别越大写日志越少
 						0: INFO, 1:DEBUG, 2:WARN, 3: ERROR，测试环境请将级别调低，可以便于进行调试
 						发布版本请将级别调高，可以提高系统运行效率
 			szLogPath	日志目录，日志文件目录，一般写在硬盘上或者SD卡上，示例:  /sd/
 						模块会在此目录下再新建一个ttxnetlog的目录进行，实现存储路径为/sd/ttxnetlog/
 			nMBSize 		日志文件大小，默认为1MB 
 						日志文件每个200KB，日志文件总大小超过限制的大小后
 						则会覆盖历史日志信息
 * @return: 无
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_SetLogParam(bool bConsole, bool bFile, int nLogLevel, const char* szLogPath, int nMBSize);

/*****************************************************************************
* @ 设备通用信息配置
* @ 配置通道数目信息，则默认为4通道的设备
* @ 配置麦克数目，默认为1，这个主要用于做麦克监听和对讲用
* @ 如果没有专门的麦克硬件，建议使用通道1做对讲和监听用
* @ 如果传成0，会导致客户端无法监听麦克和进行对讲
* @ 设备名称，如为MDVR，则表示车牌号
* @ 硬盘类型，默认为TTX_DISK_TYPE_SD
* @ 厂家类型，TTX_FACTORY_TYPE_UNKOWN
* @ 厂家设备类型,	自定义  用于区分同一厂家下的不同类型的设备
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetDeviceInfo(int nChnCount, int nMicCount, const char* szDeviceName, int nDiskType = TTX_DISK_TYPE_SD
			, int nFactoryType = TTX_FACTORY_TYPE_UNKOWN, int nFactoryDevType = TTX_FACTORY_TYPE_UNKOWN
			, const char* szVersion = "");

//szPwd为登录密码
LIBDVRNET_API int	TTXNET_SetDevicePwd(const char* szPwd); 
//登录类型
//@nLoginType: TTX_LOGIN_TYPE_LINUX，如果不配置默认为TTX_LOGIN_TYPE_LINUX
LIBDVRNET_API int	TTXNET_SetLoginType(int nLoginType); 

/*****************************************************************************
* @ 设备网络类型定义
* @ 网络类型3G, WIFI, 有线
* @ 网络名称,当为wifi时表示ssid名称，只在wifi时有效
* @ imei，为手机模块的IMEI号
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetNetworkInfo(int nNetType, const char* szName, const char* szImei = "");

/*****************************************************************************
* @ 媒体类型定义
* @ 音频类型默认为TTX_AUDIO_TYPE_G726_40KBPS
* @ 音频通道nAudioChannel	默认为1
* @ 音频采样率nAudioSamplesPerSec	默认为8000
* @ 音频每个取样所需的位元数，默认为16
* @ 信息帧解码器类型，用于车载终端，主要用于解析 GPS和车辆状态数据
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetMediaInfo(int nAudioType, int nAudioChannel, int nAudioSamplesPerSec, int nAudioBitPerSamples, int nVideoCoder = TTX_VIDEO_CODEC_H264);

/*****************************************************************************
* @ 数据文件位置，主要用于缓存报警事件和GPS数据
* @ szDataPath 数据文件路径: /sd/  末尾为/
* @ GPS数据命名为cache_status.
* @ 报警数据命名为cache_alarm
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetDataPath(const char* szDataPath, int nStatusCacheCount = 8192, int nAlarmCacheCount = 2048);

/*****************************************************************************
* @ 以下接口与服务器维持信念链路
* @ 如果登录后重新配置服务器地址或者设备编号，请先TTXNET_StopWork，再TTXNET_StartWork
* @ 与服务器维持通信链，心跳间隔时间为1分钟，服务器5分钟没有收到数据，则认为通信断开
******************************************************************************/

/**
 * @Description: 设置网络适配层，此接口必须在TTXNET_StartWork前调用
 * @param: 上层应用需要从CTTXNetWork继承子类，实现相应的接口
 * @return: 0表示成功 
 * @Author: afu	2011-06-30
 */
LIBDVRNET_API int TTXNET_SetNetAdapter(CTTXNetWork* pNetwork);


/**
 * @Description: 开始网络模块，调用此接口后，与服务器维持通信链路
 * @param: 	szIDNO: 设备编号，如13510907654，建议终端序列号使用SIM卡对应的手机号码，最多16位
 			szServerIP 服务器地址
 			usPort 服务器端口
 			bInitListen: 实始化监听
 			usListenPort: 本地监听端口
 			bInitLogin: 是否与服务器建议通信
 			bOnlyMedia: 是否只跑流媒体,808协议使用
 			bAuthentication: 表示是否启用鉴权模式，如果为true时，则服务器会下发一个鉴权码
 				A、设备DoAuthentication 对鉴权码校验后，如果鉴权码不满足规则，则服务器有误，此时sdk会中断链接
 				B、当检验通过后，对authkey进行加密，并返回数据给服务器
 * @return: 0表示成功 
 * @Author: afu
 */
LIBDVRNET_API int	TTXNET_StartWork(const char* szIDNO, const char* szServerIP, unsigned short usPort
							, bool bInitListen, unsigned short usListenPort, bool bInitLogin = true, bool bOnlyMedia = false
							, bool bAuthentication = false);


/**
 * @Description:停止服务
 * @param: 	无
 * @return: 0表示成功 
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int	TTXNET_StopWork();

/**
 * @Description:判断是否连接成功
 * @return: 0表示成功 
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int TTXNET_IsLoginSuc();

/*
 *判断设备是否存在，TTXNET_IsLoginSuc返回0后，可以再调用TTXNET_IsServerDeviceExist判断服务器上是否存在些设备
 * @return: 0表示存在,1表示不存在
*/
LIBDVRNET_API int TTXNET_IsServerDeviceExist();

/**
 * @Description:添加报警事件，如果与中心通信中断，则在恢复通信后，再进行上传
 * @param:	pAlarmInfo: 报警事件
 * @return: 0表示成功 
 * @szId，输出参数，长度必须超过40 个字符，返回报警对应的guid信息，用于唯一标识此条报警信息
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int TTXNET_AddAlarmInfo(TTXAlarmInfo_S* pAlarmInfo, char* szId = NULL);

/**
 * @Description:发送串口透传数据
 * @param: 	nType: 数据类型
 			pBuffer: 数据内容
 			nLength: 数据长度
 			bReliable: 表示是否可靠传输,  true表示会最大可能保证传送到服务器上
 * @return: 0表示成功 
 * @Author: afu 2011-06-30
 */
LIBDVRNET_API int	TTXNET_SendTransparentSerial(int nType, const char* pBuffer, int nLength, bool bReliable = false);

/**
 * @Description:主动请求对讲，只有在与服务器通信成功的时间，才会返回成功
 * @param: 	bStart: 是否启动双向对讲
 			nChn: 通道号
 * @return: 0表示成功 
 * @Author: afu 2013-06-29
 */
LIBDVRNET_API int	TTXNET_SendAudioIntercom(bool bStart, int nChn = 0);

/**
 * @Description:获取端口绑定参数
 * @param: 	lpBindPort: 端口绑定参数
 * @return: 0表示成功 
 * @Author: afu 2013-08-26
 */
LIBDVRNET_API int	TTXNET_GetSessPortBind(TTXSessPortBind_S* lpPort);

/**
 * @Description:设置端口绑定参数
 * @param: 	lpBindPort: 端口绑定参数
 * @return: 0表示成功 
 * @Author: afu 2013-08-26
 */
LIBDVRNET_API int	TTXNET_SetSessPortBind(const TTXSessPortBind_S* lpPort);

/**
 * @Description:设置进行及时重连，如当设备连接上3G网络后，及时调用些接口，这样会可以快速连接到服务器
 * @return: 0表示成功 
 * @Author: afu 2014-04-14
 */
LIBDVRNET_API int	TTXNET_SetReconnNow();

/*****************************************************************************
* @ 同步时间(只是一次有效)
* 从服务器上取得的时间会通过SyncTime 接口返回
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetSyncTime();

/**
 * @Description:主动向服务器上报视频数据
 * @return: 0表示成功 
 * @Author: afu 2014-07-18
 */
LIBDVRNET_API int	TTXNET_StartUploadVideo(int nChannel, int nStreamType);

/**
 * @Description:停止上报视频
 * @return: 0表示成功 
 * @Author: afu 2014-07-18
 */
LIBDVRNET_API int	TTXNET_StopUploadVideo(int nChannel, int nStreamType);

/**
 * @Description:判断网络库运行状态，上层定时调用此接口判断网络库是否运行正常
 * 			网络库会判断各个线程的运行状态，如果某个线程运行不正常，则会返回失败
 			建议每2秒调用一次
 * @return: true表示成功 , false表示运行失败
 * @Author: afu 2014-08-29
 */
LIBDVRNET_API bool TTXNET_IsRunningNormal();

/**
 * @Description:是否发送视频时，同时传送音频
 * @return: 无 
 * @Author: afu 2014-09-19
 */
LIBDVRNET_API void TTXNET_SetSyncSendAudio(bool bSyncSendAudio);

/**
 * @Description:主动上报状态
 * @return: 无 
 * @Author: afu 2015-04-27
 */
LIBDVRNET_API void TTXNET_InitiativeUploadStatus();

/**
 * @Description:处理透传过来的命令(808共用时使用，信令走808，媒体走本协议)
 * @return: 无 
 * @Author: afu 2015-06-05
 */
LIBDVRNET_API void TTXNET_TransparentInstruction(const char* pInstruction, int nLength);

/**
 * @Description:上报指令到服务器上(808共用时使用，将回调的数据，通过808透传上报到服务器上)
 * @return: 无 
 * @Author: afu 2015-08-30
 */
LIBDVRNET_API void TTXNET_JT808UploadTransInstruction(void* pUsr, TTXPfnJT808UploadTransInstructionCB pfnUploadInstruction);

/**
 * @Description:上报指令到服务器上(提供接口用于网络库判断808的信令链路是否在线，大概1分钟调用一次)
 * @return: 无 
 * @Author: afu 2015-10-12
 */
LIBDVRNET_API void TTXNET_JT808CheckOnline(void* pUsr, TTXPfnJT808CheckOnlineCB pfnCheckOnline);

/**
 * @Description:视频直连时和3G上报使用不同的缓存
 * @return: 无 
 * @Author: afu 2015-12-08
 */
LIBDVRNET_API void TTXNET_SetAVDirectConnectDiffBuffer(bool bAVDiffBuffer);

/**
 * @Description:设置是否与服务器建立连接，如果不设置，则默认与服务器建立连接
 * @return: 无
 * @Author: afu 2015-12-08
 */
LIBDVRNET_API void TTXNET_SetIsLoginSvr(bool bLoginSvr);

/**
  * @Description:直连时传送报警数据到客户端，在客户端直连设备时使用
 * @return: 无
 * @Author: afu 2016-01-06
 */
LIBDVRNET_API void TTXNET_SendDirectAlarmInfo(TTXAlarmInfo_S* pAlarmInfo);

/**
  * @Description:设置服务器信息,如WIFI连接IP1，3G连接IP2，则当网络切换时调用些接口重新配置服务器IP
 * @return: 无
 * @Author: afu 2016-05-11
 */
LIBDVRNET_API void TTXNET_SetServerInfo(const char* szIP, unsigned short usPort);

/**
  * @Description:设置媒体会话和注册服务器使用同一个IP，如WIFI连接IP1，3G连接IP2时使用，配置媒体会话和登录的IP保持一致
 * @return: 无
 * @Author: afu 2016-05-11
 */
LIBDVRNET_API void TTXNET_SetMediaIPSameAsLoginIP(bool bSame);

/*****************************************************************************
* @ imsi，为手机模块的IMSI号
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetImsi(const char* szImsi);

/*****************************************************************************
* @ 设置为实时模式，默认为false，当为实时模式时，视频和对讲会较快判断中断
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetRealTimeMode(bool bRealTimeMode);

/*****************************************************************************
* @ 设置，默认为false，当实时视频发送流的时候是否要带gps,车辆状态等信息
* @return: 无
* @Author: dhy 2017-06-21
******************************************************************************/
LIBDVRNET_API int	TTXNET_SetUpStateInfoMode(bool bStateInfoMode);

/**
 * @Description:获取多少毫秒无数据
 * @return: 返回时间差(毫秒) 
 * @Author: 
 */
LIBDVRNET_API _u64long GetTimeNoRecvData();




#ifdef __cplusplus
}
#endif 


#endif

