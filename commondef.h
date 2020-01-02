#ifndef _COMMONDEF_H_
#define _COMMONDEF_H_

typedef std::vector<int>	vecInt;
typedef vecInt::iterator	vecIntIter;


#define DEVNODE_TYPE_ROOT		1
#define DEVNODE_TYPE_GROUP		2
#define DEVNODE_TYPE_DEV		3

#define ALARM_USR_DEF_COUNT			16
#define ALARM_OTHER_COUNT			16

#define VIEW_MODE_UNDEFINE			-1
#define VIEW_MODE_REAL				0
#define VIEW_MODE_SMOOTH			1

#define IRP_CNT_TYPE_TCP		0
#define IRP_CNT_TYPE_UDP		1

#define VIEW_SIZE_UNDEFINE			-1
#define VIEW_SIZE_FULL				0
#define VIEW_SIZE_4_3				1
#define VIEW_SIZE_16_9				2

#define CLIENT_LAYOUT_COUNT			4


#pragma pack(4)

typedef struct _tagAlarmAction
{
	int		A_Type;			//alarm type
	BOOL	V_Video;		//Pop alarm video 
	int		V_Channel;		//preview channel
	int		V_Stream;		//stream type
	BOOL	A_Audio;		//Sound alarm
	char	A_Wav[32];		//sound alarm file
	int		A_Count;		//sound play count
	BOOL	T_ShowTip;		//show pop message 
	BOOL	C_CenterMap;	//Center device
	BOOL    A_AlarmVideo;      //record if alarm      4 bytes
    short   A_AlarmVideoCount; //record time  2 bytes

    char	Reserve[26];
}AlarmAction_S;


typedef struct _tagDevArmAction
{
	int		DevID;
	BOOL	Valid;
	unsigned int	TimeBeg;
	unsigned int	TimeEnd;
	AlarmAction_S	UsrDefine[ALARM_USR_DEF_COUNT];
	AlarmAction_S	UrgencyButton;						
	AlarmAction_S	VideoLost;					
	AlarmAction_S	DoorOpenLawless;			
	AlarmAction_S	DiskError;					
	AlarmAction_S	OverSpeed;					
	AlarmAction_S   VehicleParkTooLong;	
	AlarmAction_S	MotionDetect;         
	AlarmAction_S   MotionGpsSignalLoss;  
	AlarmAction_S   Temperator;

	//alarm of map
	AlarmAction_S   EnterFence;		
	AlarmAction_S   OutFence;
	AlarmAction_S   InFenceOverSpeed;
	AlarmAction_S   OutFenceOverSpeed;
	AlarmAction_S   InFenceLowSpeed;
	AlarmAction_S   OutFenceLowSpeed;
	AlarmAction_S   InFenceStop;
	AlarmAction_S   OutFenceStop;

	//fuel
	AlarmAction_S   Refuel;
	AlarmAction_S   StillFuel;

	AlarmAction_S	Reserve[13];  //alarm flag  , Reserve[N] , N=N-1 if an alarm added
}DevArmAction_S;

typedef struct _tagDevChnDragInfo
{
	int nDevID;
	int	nChan;
}DEVCHNDragInfo_S;

typedef struct _tagChnGroupDragInfo
{
	char szGroup[32];
}CHNGROUPDragInfo_S;

typedef struct _tagDevNodeDragInfo
{
	int nType;
	int nID;
}DEVNODEDragInfo_S;

typedef struct _tagVideoDragInfo
{
	int nDevID;
	int	nChan;
	int	nVideoIndex;
	int	nMapID;
	BOOL bAlarm;
}VIDEODragInfo_S;

typedef struct _tagFILEDragInfo
{
	GPSFile_S	RemoteFile;
}FILEDragInfo_S;

typedef struct _tagEventInfo
{
	SYSTEMTIME	Time;
	CString	EventType;
	CString	Desc;
	BOOL	Alarm;
}EventInfo_S;

typedef struct _tagClientLayout
{
	BOOL bShowLeft;
	BOOL bShowRight;
	BOOL bButtom;
}ClientLayout_S;

const int USERNAME_MAX_NUM = 7;
const int PASSWAOR_MAX_NUM = 7;
typedef struct _DevUserInfo
{
	int		nDevID;
	char	szUserName[USERNAME_MAX_NUM+1];
	char	szPassword[PASSWAOR_MAX_NUM+1];
}DevUserInfo_S;

typedef struct _DevCmdMsg
{
	int		nResult;
	int		nDevID;
	void*	pParam1;
	void*	pParam2;
	void*	pParam3;
}DevCmdMsg_s;

typedef struct _DevSpeedTime 
{
	double fSpeed;
	long   nTimeSecond;	
} DevSpeedSecond_S;

struct CGDeviceChannel_S
{
	int nDevice;
	int nChannel;
};

struct CGGroupInfo_S 
{
	char szGroupName[32];
	int  nChannelCount;
};

#pragma pack()

#endif