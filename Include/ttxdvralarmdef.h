#ifndef _TTX_DVR_ALARM_DEF_H_
#define _TTX_DVR_ALARM_DEF_H_

/******************************************************************************
  Author        : afu
  Created       : 2012/11/30
  Last Modified :
  Description   : ������Ϣ���壬ÿ��������һ����ʼ�¼���һ�������¼����
  History       :
	  1.	Date        : 2012/11/30
		Author      : leeafu
		Modification: Created file
******************************************************************************/

#define TTX_ALARM_TYPE_USEDEFINE				1		//�Զ��屨��AlarmInfoΪ����Դ��0λ��ʾio1����1λ��ʾio2���Դ�����
#define TTX_ALARM_TYPE_URGENCY_BUTTON			2		//������ť����AlarmInfoΪ��ť���
#define TTX_ALARM_TYPE_SHAKE					3		//�񶯱���AlarmInfo�����ٶȱ�����bit0��X����,bit1��Y����,bit2��Z����bit3����ײ,bit4���෭��
#define TTX_ALARM_TYPE_VIDEO_LOST				4		//����ͷ���źű���alarmInfoΪͨ���ţ���λ��ʾ����0λ��ʾͨ��1
#define TTX_ALARM_TYPE_VIDEO_MASK				5		//����ͷ�ڵ�����alarmInfoΪͨ���ţ���λ��ʾ����0λ��ʾͨ��1
#define TTX_ALARM_TYPE_DOOR_OPEN_LAWLESS		6		//�Ƿ����ű���
#define TTX_ALARM_TYPE_WRONG_PWD				7		//����������󱨾�
#define TTX_ALARM_TYPE_FIRE_LOWLESS				8		//�Ƿ���𱨾�
#define TTX_ALARM_TYPE_TEMPERATOR				9		//�¶ȱ���, AlarmInfo��������ţ�0��ʾ������1��1��ʾ������2��, param[0]�¶����ͣ�0��ʾ�����£�1��ʾ�����£�, param[1]��ǰ�¶�10000=100�� 
#define TTX_ALARM_TYPE_DISK_ERROR				10		//Ӳ�̴��󱨾�, alarmInfoΪӲ������(TTX_DISK_TYPE_SD��) param[1]Ϊ������ţ�1��ʾ����1��2��ʾ����2
#define TTX_ALARM_TYPE_OVERSPEED				11		//���ٱ���,  param[0]��ǰ�ٶ�9900=99����, param[1]�ٶ����ֵ, param[2]�ٶ����ֵ, param[3]����ʱ��, alarmInfo: 1����,2����,3��������,4��������
#define TTX_ALARM_TYPE_BEYOND_BOUNDS			12		//Խ�籨��
#define TTX_ALARM_TYPE_DOOR_ABNORMAL			13		////�쳣���س��ű�����alarmInfoΪ�ű�־
#define TTX_ALARM_TYPE_PARK_TOO_LONG			14		//ͣ��ʱ�����������alarmInfoΪͣ��ʱ����param[0]Ϊ�趨��ʱ����(��λ��)
#define TTX_ALARM_TYPE_MOTION					15		//�ƶ���ⱨ������λ��ʾ����0λ��ʾͨ��1
#define TTX_ALARM_TYPE_ACC_ON					16		//ACC��������
#define TTX_ALARM_TYPE_DEV_ONLINE				17		//�豸����
#define TTX_ALARM_TYPE_GPS_SIGNAL_LOSS          18      //GPSѶ�Ŷ�ʧ��ʼ
//#define TTX_ALARM_TYPE_IO_1                     19      //IO_1����
//#define TTX_ALARM_TYPE_IO_2                     20      //IO_2����
//#define TTX_ALARM_TYPE_IO_3                     21      //IO_3����
//#define TTX_ALARM_TYPE_IO_4                     22      //IO_4����
//#define TTX_ALARM_TYPE_IO_5                     23      //IO_5����
//#define TTX_ALARM_TYPE_IO_6                     24      //IO_6����
//#define TTX_ALARM_TYPE_IO_7                     25		//IO_7����
//#define TTX_ALARM_TYPE_IO_8                     26      //IO_8����

//27-34 Ϊ����Χ������
#define TTX_ALARM_TYPE_IN_FENCE				27	 //��������(	 param[0]-λ������ param[1]-���������·ID
#define TTX_ALARM_TYPE_OUT_FENCE	 		28	//������ param[0]-λ������ param[1]-���������·ID
//param[0]��ʱ��ʹ��
//param[1]��Ӧ���������    //aid: (area id)����id ������������Ҫ������id���ظ�������

//����4�����������Գ�����Ŀ
#define TTX_ALARM_TYPE_FIRE                     35      //��
#define TTX_ALARM_TYPE_PANIC                    36      //�پ�
#define TTX_ALARM_TYPE_TASK_FINISHED			37		//�����������
#define TTX_ALARM_TYPE_IMAGE_UPLOAD				38		//ͼƬ�ϴ����

//39-40ΪӲ��1, Ӳ��2������

//#define TTX_ALARM_TYPE_IO_9                     41      //IO_9����
//#define TTX_ALARM_TYPE_IO_10                    42      //IO_10����
//#define TTX_ALARM_TYPE_IO_11                    43      //IO_11����
//#define TTX_ALARM_TYPE_IO_12                    44      //IO_12����

//45ΪGPS��Ч

#define TTX_ALARM_TYPE_REFUEL					46		//����	AlarmInfoΪ���͵�����(9999=99.99��)��Param[0]Ϊ����ǰ�ͺ�
#define TTX_ALARM_TYPE_STILL_FUEL				47		//͵��	AlarmInfoΪ͵�͵�����(9999=99.99��)��Param[0]Ϊ͵��ǰ�ͺ�

#define TTX_ALARM_TYPE_TRANSPARENT				48		//����͸������
#define TTX_ALARM_TYPE_FATIGUE					49		//ƣ�ͼ�ʻ	AlarmInfo��ʾ��������	0 , û�У� 1  һ������ 2 ��������, 3 ��������, 4 ��ע�ȱ���

#define TTX_ALARM_TYPE_END_USEDEFINE			51		//�Զ��屨��
#define TTX_ALARM_TYPE_END_URGENCY_BUTTON		52		//������ť����
#define TTX_ALARM_TYPE_END_SHAKE				53		//�񶯱���
#define TTX_ALARM_TYPE_END_VIDEO_LOST			54		//����ͷ���źű���
#define TTX_ALARM_TYPE_END_VIDEO_MASK			55		//����ͷ�ڵ�����
#define TTX_ALARM_TYPE_END_DOOR_OPEN_LAWLESS	56		//�Ƿ����ű���
#define TTX_ALARM_TYPE_END_WRONG_PWD			57		//����������󱨾�
#define TTX_ALARM_TYPE_END_FIRE_LOWLESS			58		//�Ƿ���𱨾�
#define TTX_ALARM_TYPE_END_TEMPERATOR			59		//�¶ȱ���
#define TTX_ALARM_TYPE_END_DISK_ERROR			60		//Ӳ�̴��󱨾�
#define TTX_ALARM_TYPE_END_OVERSPEED			61		//���ٱ���
#define TTX_ALARM_TYPE_END_BEYOND_BOUNDS		62		//Խ�籨��
#define TTX_ALARM_TYPE_END_DOOR_ABNORMAL		63		//�쳣���س��ű���
#define TTX_ALARM_TYPE_END_PARK_TOO_LONG		64		//ͣ��ʱ���������
#define TTX_ALARM_TYPE_END_MOTION				65		//�ƶ���ⱨ��
#define TTX_ALARM_TYPE_ACC_OFF					66		//ACC�رձ���
#define TTX_ALARM_TYPE_DEV_DISONLINE			67		//�豸����
#define TTX_ALARM_TYPE_END_GPS_SIGNAL_LOSS      68      //GPSѶ�Ŷ�ʧ����
//#define TTX_ALARM_TYPE_END_IO_1                 69      //IO_1����
//#define TTX_ALARM_TYPE_END_IO_2                 70      //IO_2����
//#define TTX_ALARM_TYPE_END_IO_3                 71      //IO_3����
//#define TTX_ALARM_TYPE_END_IO_4                 72      //IO_4����
//#define TTX_ALARM_TYPE_END_IO_5                 73      //IO_5����
//#define TTX_ALARM_TYPE_END_IO_6                 74      //IO_6����
//#define TTX_ALARM_TYPE_END_IO_7                 75      //IO_7����
//#define TTX_ALARM_TYPE_END_IO_8                 76      //IO_8����

//77-84 Ϊ����Χ������
#define TTX_ALARM_TYPE_END_IN_FENCE	             	77      //�������򱨾�     param[0]-λ������ param[1]-���������·ID
#define TTX_ALARM_TYPE_END_OUT_FENCE	        78      //�����򱨾�   param[0]-λ������ param[1]-���������·ID

//#define TTX_ALARM_TYPE_END_IO_9                 91      //IO_9����
//#define TTX_ALARM_TYPE_END_IO_10                92      //IO_10����
//#define TTX_ALARM_TYPE_END_IO_11                93      //IO_11����
//#define TTX_ALARM_TYPE_END_IO_12                94      //IO_12����

#define TTX_ALARM_TYPE_END_FATIGUE				99		//ƣ�ͼ�ʻ	AlarmInfo��ʾ��������	0 , û�У� 1  һ������ 2 ��������, 3 ��������, 4 ��ע�ȱ���

//���ļ���Ҫ�ϴ�
#define TTX_ALARM_TYPE_UPLOAD_FILE              109     //¼���ļ���Ҫ�ϴ�AlarmInfo����1��ʾJPGͼƬ��2��ʾ¼���ļ�,  szDescΪ�ļ�����·��
														//param[0] = �ļ����ȣ�param[1] = �ļ�����(������߱���)��param[2] = �ļ�ʱ��, param[3] = ͨ��
														//param[4] = ��Ӧ�ı�������alarmtype��param[5]��Ӧ��alarmInfo
														//szReserve = �ļ���ʼʱ�䣬��: 2013-06-13 100001
														//��ΪJPGͼƬʱ���ļ�ʱ����Ч
#define TTX_ALARM_TYPE_CUSTOM					113		//�Զ��屨��, AlarmInfo��ʾ����
														// param[0]��ʾ����1��param[1]��ʾ����2��param[2]��ʾ����3, param[3]��ʾ����4, 
														//szDesc��ʾ���ݣ�Ϊ�ַ�����ʽ���м䲻��������'\0'���Ϊ256���ֽ�
#define TTX_ALARM_TYPE_UPLOAD_COMPLETE          114		//֪ͨ�ļ��������, param[0]��ʾ�ļ�ID��param[1]��ʾ�ļ�����


#define TTX_ALARM_TYPE_USP_CUT		 			155		//UPS ���߱���
#define TTX_ALARM_TYPE_END_USP_CUT				156
#define TTX_ALARM_TYPE_HDD_HIGH_TEMPERATURE		157		//Ӳ�̳��±���, alarmInfoΪӲ�̺�0��ʾ1,param[0]��ʾӲ������TTX_DISK_TYPE_SD, param[1]��ǰ�¶�100=100��
#define TTX_ALARM_TYPE_END_HDD_HIGH_TEMPERATURE	158
#define TTX_ALARM_TYPE_BEFORE_BOARD_OPENED		159		//ǰ��屻�˿�
#define TTX_ALARM_TYPE_END_BEFORE_BOARD_OPENED	160		
#define TTX_ALARM_TYPE_TURN_OFF					161		//�ػ��ϱ�	,	alarmInfoΪԭ��: 1ACC ��Ч�ػ�,2��ʱ�ػ�,3��������, 4�����쳣�ػ�,5����ػ�,6Ӳ�����򿪹ػ�
#define TTX_ALARM_TYPE_DISK_SPACE_WARNING		162		//Ӳ�̿ռ侯��,alarmInfoΪӲ�̺�,param[0]��ʾӲ������TTX_DISK_TYPE_SD, param[1]�ܿռ�, param[2]ʣ��ռ�,  16000��ʾ�ռ�Ϊ16000MB
#define TTX_ALARM_TYPE_END_DISK_SPACE_WARNING	163		//Ӳ�̿ռ侯��,alarmInfoΪӲ�̺�,param[0]��ʾӲ������TTX_DISK_TYPE_SD, param[1]�ܿռ�, param[2]ʣ��ռ�,  16000��ʾ�ռ�Ϊ16000MB
#define TTX_ALARM_TYPE_SIMCARD_LOST				164		//SIMCARD��ʧ����
#define TTX_ALARM_TYPE_END_SIMCARD_LOST			165		//SIMCARD��ʧ����
#define TTX_ALARM_TYPE_TPMS				166		//	̥ѹ����, alarmInfo  TPMS�������ͣ�1��ʾ��ص�ѹ���棬2-̥ѹ���ߣ�3-̥ѹ���� 4-©�� 5-�¶��쳣��ֻ�й��ߣ���,
												//			param[0] ��ǰ�¶� ��: 200 = 20��
												//			param[1] ��ǰ̥ѹ ��: 25 = 2.5P
												//			param[2] ��ǰ��ѹ ��: 102=10.2V
												//			param[3] ��������ţ�01��ʾTPMS��1��02��ʾTPMS��2��03��ʾTPMS��3��04��ʾTPMS��4��11��ʾTPMS��1��12��ʾTPMS��2��13��ʾTPMS��3��14��ʾTPMS��4��

#define TTX_ALARM_TYPE_END_TPMS			167		//TPMS����

#define TTX_ALARM_TYPE_DEVICE_UNLOCKED		182		//�豸����
#define TTX_ALARM_TYPE_DEVICE_LOCKED		183		//�豸����

#define TTX_ALARM_TYPE_SWITCH_VIEW				301		//�л���Ƶ��alarminfo��ʾͨ���ţ�param[0]: 0��ʾ��ԭ��1��ʾ���

//����������Զ��屨��
#define TTX_ALARM_CUSTOM_INOUT_AREA		 351		//param2Ϊ����id��param3Ϊ���ͣ�0Ϊ���룬1Ϊ�뿪��
#define TTX_ALARM_CUSTOM_END_INOUT_AREA	 352	 	//param2Ϊ����id��param3Ϊ���ͣ�0Ϊ���룬1Ϊ�뿪��

#pragma pack(4)

typedef struct _tagTTXAlarmInfo
{
	unsigned int AlarmType;			//��������
	unsigned int AlarmInfo;			//������Ϣ
	int		Param[8];			//��������
	char	szDesc[256];		//��������
	char	szReserve[64];		//�����ֶ�
}TTXAlarmInfo_S, *LPTTXAlarmInfo_S;

#pragma pack()

#endif
