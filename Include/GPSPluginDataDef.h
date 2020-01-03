#ifndef _GPS_PLUGIN_DATA_DEF_H_
#define _GPS_PLUGIN_DATA_DEF_H_

//路政系统用 hw2014/8/18
#define DJWL_TASK_STATUS_AUDIT_FINISH	0	//审批完成
#define DJWL_TASK_STATUS_SUC			1	//任务完成
#define DJWL_TASK_STATUS_FAIL			2	//任务失败
#define DJWL_TASK_STATUS_AUDIT_VEHICLE	3	//审批车辆信息(审批完成一半)
#define DJWL_TASK_STATUS_CLOSE			4	//任务关闭


#define DJWL_TASK_APPROVE	 0	 //审批
#define DJWL_TASK_SUBMIT	-1	 //完成或失败
#define DJWL_TASK_MODIFY    -2   //修改

//车辆信息表
typedef struct _tagGPSVehicleInfo
{
	int nID;					//编号
	char szVehicleIDNO[40];		//车牌号
	char szDriverName[64];		//司机名称
	char szDriverPhone[64];		//司机电话
	char szDirverPicture[256];	//司机图片
	char szVehicleType[128];	//车辆类型
	char szCompany[128];		//所属公司
	char szRemark[256];			//备注
	char szReserve[256];		//保留256
}GPSVehicleInfo_S, *LPGPSVehicleInfo_S;

//线路基本信息
typedef struct _tagLZLineBaseInfo
{
	char	szStartPoint[64];			//起点
	char	szEndPoint[64];				//终点
	double	dTotalWeight;				//车货总重量
	double	dTotalLength;				//车货总长
	double	dTotalWidth;				//车货总宽
	double	dTotalHeight;				//车货总高
	double	dAxisWeight;				//单轴轴重
}LZLineBaseInfo_S, *LPLZLineBaseInfo_S;

//车辆运输任务表
typedef struct _tagGPSVehicleTask
{
	int nID;							//编号
	char szVehicleIDNO[40];				//车辆IDNO
	char szMDVRIDNO[40];				//MDVR设备IDNO
	char szPadIDNO[40];					//PAD设备IDNO
	char szPadPsw[256];					//PAD登陆服务器密码
	char szCargoName[256];				//货物名称
// 	double dCargoLength;				//货物长度
// 	double dCargoHeight;				//货物高度
// 	double dCargoWidth;					//货物宽度
// 	double dCargoWeight;				//货物重量
	LZLineBaseInfo_S LineInfo;			//线路规划信息
	GPSTime_S PlanStartTime;			//任务计划开始时间
	GPSTime_S PlanEndTime;				//任务计划结束时间
	GPSTime_S ActualEndTime;			//任务实际结束时间
	int nStatus;						//任务状态 0-审批完成 1-任务完成 2-任务失败 3-审批车辆信息(审批完成一半)
	int nIsManualConfirmation;			//人工确认, 0-没确认,1-确认
	char szReserve[252];				//保留252
}GPSVehicleTask_S, *LPGPSVehicleTask_S;

//线路详细信息
typedef struct _tagLZLineGPSInfo
{
	double	dLatitude;;					//经度
	double	dLongitude;					//纬度
	int		nNodeID;					//节点ID
	int		nNodeType;					//节点类型
	char	szNodePicture[MAX_PATH];	//节点图片URL
	char	szRes[1024];
}LZLineGPSInfo_S, *LPLZLineGPSInfo_S;

// typedef struct _tagLZTaskFailTime
// {
// 	int nTimeMinute;					//偏离路线时长,单位分钟
// }LZTaskFailTime_S, *LPLZTaskFailTime_S;
// 
// typedef struct _tagLZTaskFailConfirm
// {
// 	int	nConfirm;						//0-继续任务 1-任务失败
// 	char szRemark[512];					//原因
// }LZTaskFailConfirm_S, *LPLZTaskFailConfirm_S;

//路政系统 End

#pragma pack()

#endif