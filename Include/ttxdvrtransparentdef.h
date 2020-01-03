#ifndef _TTX_DVR_TRANSPARENT_DEF_H_
#define _TTX_DVR_TRANSPARENT_DEF_H_

//胎压数据透传定义
#define TTX_TRANSPARENT_TYPE_TPMS		101			//胎压数据透传定义，胎压大概3分钟传送一次就好了

#pragma pack(4)

//胎压定义(20个胎压)
typedef struct _tagTTXTirePressure
{
	unsigned char ucTireBattery;	//电量0-5V，55=5.5V
	char ucTirePress;		//胎压,  23 = 2.3PA，正常范围一般是2.3 - 2.5
	short ucTireTemperure;	//温度200 表示20度	
}TTXTirePress_S;

typedef struct _tagTTXTireStatus
{
	unsigned char ucTireCount;	//胎压的个数
	unsigned char ucReserve[3];	
	TTXTirePress_S arrPress[20];	//
}TTXTireStatus_S;

#pragma pack()

#endif
