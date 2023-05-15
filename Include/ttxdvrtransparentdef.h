#ifndef _TTX_DVR_TRANSPARENT_DEF_H_
#define _TTX_DVR_TRANSPARENT_DEF_H_

//̥ѹ����͸������
#define TTX_TRANSPARENT_TYPE_TPMS		101			//̥ѹ����͸�����壬̥ѹ���3���Ӵ���һ�ξͺ���

#pragma pack(4)

//̥ѹ����(20��̥ѹ)
typedef struct _tagTTXTirePressure
{
	unsigned char ucTireBattery;	//����0-5V��55=5.5V
	char ucTirePress;		//̥ѹ,  23 = 2.3PA��������Χһ����2.3 - 2.5
	short ucTireTemperure;	//�¶�200 ��ʾ20��	
}TTXTirePress_S;

typedef struct _tagTTXTireStatus
{
	unsigned char ucTireCount;	//̥ѹ�ĸ���
	unsigned char ucReserve[3];	
	TTXTirePress_S arrPress[20];	//
}TTXTireStatus_S;

#pragma pack()

#endif
