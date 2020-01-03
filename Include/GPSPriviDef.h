#pragma once


#define PRIVI_USERMGR_USER						11 //用户管理
#define PRIVI_USERMGR_ROLE						12 //角色管理
//车辆参数配置权限
#define PRIVI_VEHIMGR_VEHICLE					21 //车辆参数配置
#define PRIVI_VEHIMGR_GROUP						22 //车辆分组
#define PRIVI_VEHIMGR_DOWN_PLAN					23 //车辆下载计划
#define PRIVI_VEHIMGR_FENCE						24 //围栏报警配置
#define PRIVI_VEHIMGR_MOBILE					25 // 终端管理
//报表配置
#define PRIVI_REPORT_NORMAL						31	//常用报表
#define PRIVI_REPORT_NORMAL_LICHENG_SUMMARY		311 //里程汇总表
#define PRIVI_REPORT_NORMAL_LICHENG_DETAIL		312 //里程明细表
#define PRIVI_REPORT_NORMAL_TRACK_DETAIL		313 //行驶轨迹明细表

#define PRIVI_REPORT_ALARM						32	//报警报表
#define PRIVI_REPORT_ALARM_SUMMARY				321 //报警汇总表
#define PRIVI_REPORT_ALARM_GPSSINAL_DETAIL		322 //GPS信息丢失报表
#define PRIVI_REPORT_ALARM_URGENCY_BUTTON		323 //紧急按钮报警明细表
#define PRIVI_REPORT_ALARM_DOOR_OPEN_LAWLESS_DETAIL 324 //非法开门明细表
#define PRIVI_REPORT_ALARM_DISK_ERROR_DETAIL	325 //硬盘错误明细表
#define PRIVI_REPORT_ALARM_MOTION_DETAIL		326 //移动侦测报警明细表
#define PRIVI_REPORT_ALARM_SHAKE_DETAIL			327 //G-Sensor报警明细表

#define PRIVI_REPORT_SPEED						33 //速度报表
#define PRIVI_REPORT_SPEED_ALARM_SUMMARY		331 //超速汇总表
#define PRIVI_REPORT_SPEED_ALARM_DETAIL			332 //超速明细表
#define PRIVI_REPORT_SPEED_DETAIL				333 //行驶速度分析

#define PRIVI_REPORT_LOGIN						34 //上下线报表
#define PRIVI_REPORT_LOGIN_SUMMARY				341 //上下线汇总表
#define PRIVI_REPORT_LOGIN_DETAIL				342 //上下线明细表
#define PRIVI_REPORT_LOGIN_RATE					343 //上线率汇总表

#define PRIVI_REPORT_IOIN						35 //IO输入报警报表
#define PRIVI_REPORT_IOIN_SUMMARY				351 //IO输入报警汇总表
#define PRIVI_REPORT_IOIN_DETAIL				352 //IO输入报警明细表

#define PRIVI_REPORT_OIL						36 //油量报表
#define PRIVI_REPORT_OIL_TRACK_DETAIL			361 //油量动态明细表
#define PRIVI_REPORT_OIL_EXCEPTION_DETAIL		362//油量异常明细表

#define PRIVI_REPORT_PARK						37 //停车报表
#define PRIVI_REPORT_PARK_SUMMARY				371 //停车汇总表
#define PRIVI_REPORT_PARK_DETAIL				372//停车明细表
#define PRIVI_REPORT_PARK_ACCON_SUMMARY			373 //停车未熄火汇总表
#define PRIVI_REPORT_PARK_ACCON_DETAIL			374//停车未熄火明细表

#define PRIVI_REPORT_FENCE						38 //围栏报表
#define PRIVI_REPORT_FENCE_ALARM_DETAIL			381 //围栏报警明细表
#define PRIVI_REPORT_FENCE_ACCESS_DETAIL		382 //进出区域报表
#define PRIVI_REPORT_FENCE_PARK_DETAIL			383 //区域停车报表

#define PRIVI_REPORT_EXTEND						39 //扩展功能报表
#define PRIVI_REPORT_EXTEND_ALARM_DETAIL		391 //报警明细表
#define PRIVI_REPORT_EXTEND_DISPATCH_DETAIL		392 //调度明细表


#define PRIVI_REPORT_STORAGE                    43	//存储介质报表
#define PRIVI_REPORT_EQUIPMENT                  44	//设备升级报表

//PC 客户端
#define PRIVI_MAP_MY_MAP_MANAGE		611		//我的地图管理
#define PRIVI_MAP_SHARE_MAP			612		//共享企业地图
#define PRIVI_MAP_MONITOR			613		//地图监控

#define PRIVI_VIDEO					621		//视频
#define PRIVI_VIDEO_SOUND			622		//声音
#define PRIVI_VIDEO_TALK			623		//对讲
#define PRIVI_VIDEO_MONITOR			624		//监听
#define PRIVI_VIDEO_DEV_CAPTURE		625		//前端抓拍
#define PRIVI_VIDEO_PTZ				626		//云台
#define PRIVI_VIDEO_RECORD			627		//录像
#define PRIVI_VIDEO_PTZ_LIGHT		628		//PTZ灯光

#define PRIVI_TRACK_BACK			631		//轨迹回放
#define PRIVI_RECORD_BACK			641		//录像回放

//设备控制
#define PRIVI_DEVICE_PARAMETER		651		//设备参数
#define PRIVI_DEVICE_INFOR			652		//设备信息
#define PRIVI_DEVICE_UPDATE			653		//升级
#define PRIVI_DEVICE_3G_FLOW		654		//3G流量
#define PRIVI_DEVICE_MOVE			655		//移动侦测配置
#define PRIVI_DEVICE_OTHER			656		//其它控制(TTS,重启，恢复出厂配置，GPS间隔等)
#define PRIVI_DEVICE_WIFI			657		//WIFI下载任务,WIFI区域设置


//系统设置
#define PRIVI_SYSTEM_SET			663		//系统设置
#define PRIVI_SYSTEM_RECORD_SET		664		//录像设置

//报表查询
#define PRIVI_LOG_QUERY_ALARM		671		//报警日志查询
#define PRIVI_LOG_QUERY_USER		672		//用户日志查询
#define PRIVI_AUDIT_VEHICLE			673		//车辆货物审批
#define PRIVI_AUDIT_LINE_DEV		674		//线路终端审批

// 报警管理
#define PRIVI_SYSTEM_ALARM_LINK		661		//报警联动
#define PRIVI_SYSTEM_ALARM_SHIELD	662		//报警屏蔽 特殊处理,有此标志位表示无权限
#define PRIVI_SYSTEM_ALARM_HANDLE	680		//报警处理 特殊处理,有此标志位表示无权限

// 协同小组
#define PRIVI_PTT_SWITCH			700	//换组
#define PRIVI_PTT_PULL				701	//强拉
#define PRIVI_PTT_DEMOLITIONS		702	//强拆
#define PRIVI_PTT_GROUP_CALL		703	//群呼
#define PRIVI_PTT_TEMP_CALL			704	//临时呼叫(单呼)
#define PRIVI_PTT_GROUP_MANAGER		707	//协同小组管理

#define PRIVE_CHANGE_VEHICLE		36	//终端信息修改


//用户权限
typedef struct _tagUserPrivilege
{
	UINT nUserType;					//0-企业管理用户 1-子用户
	char szPrivilege[1024];			//用户权限用逗号分开
}UserPrivilege_S, *LPUserPrivilege_S;

typedef struct _tagClientConfigUserPrivilege_S
{
	UserPrivilege_S UserPrivilege;
}ClientConfigUserPrivilege_S, *LPClientConfigUserPrivilege_S;

//本地屏蔽(上面权限未定义项),客户端使用
#define PRIVI_SHIELD_DEV_STATUS		500		//设备状态信息
#define PRIVE_SHIELD_ALARM_LIST		501		//报警信息列表框
#define PRIVE_SHIELD_COLOR			502		//色彩
#define PRIVE_SHIELD_COSTSTOTAL		503		//统计功能
#define PRIVE_SHIELD_OTHER_APPS		504		//其他应用按钮
#define PRIVE_SHIELD_OIL_SET_MENU	505		//油量传感器设置菜单
#define PRIVE_SHIELD_BOTTOMBAR		506		//底部状态栏
#define PRIVE_SHIELD_DEVTOTAL		507		//窗口中间设备统计数量
#define PRIVE_SHIELD_MULTI_PIC		508		//多图片显示窗口
#define PRIVE_SHIELD_SPEED			509		//显示速度
#define PRIVE_SHIELD_LICHENG		510		//显示里程