#ifndef _FILE_HEAD_H_
#define _FILE_HEAD_H_

#pragma pack(4)

typedef struct _tagAVFrmHead
{
	int nFrameType;
	int nFrameLen;
	unsigned __int64 u64Stamp;
}AVFrmHead_S;

const int AVFRM_TYPE_HEAD = 1;
const int AVFRM_TYPE_REC_HEAD = 2;
const int AVFRM_TYPE_I = 0x63643030;
const int AVFRM_TYPE_P = 0x63643130;
const int AVFRM_TYPE_A = 0x63643230;
const int AVFRM_TYPE_D = 0x63643930;
const int AVFRM_TYPE_H_EX = 0x63643830;
const int AVFRM_HEAD_LENGTH = sizeof(AVFrmHead_S);

const unsigned int VIDEO_VERSION = 0x40000001;
const unsigned int VIDEO_HEAD_LENGTH = 512;

const int VIDEO_CODER_TYPE_H264	= 0;
const int VIDEO_CODER_TYPE_H264_HI	= 1;	//海思编码器使用此海思编码器进行解码
const int VIDEO_CODER_TYPE_H264_PRI_1 = 2;	//思拓加密的版本
const int VIDEO_CODER_TYPE_H265_HI = 3;		//海思编码的H265
const int VIDEO_CODER_TYPE_H265 = 4;		//原为3,添加海思265后改为4 [2017-11-22]

const int GPS_RESOLUTION_QCIF		= 1;	//分辨率
const int GPS_RESOLUTION_CIF		= 2;	//分辨率
const int GPS_RESOLUTION_HD1		= 3;	//分辨率
const int GPS_RESOLUTION_D1			= 4;	//分辨率
const int GPS_RESOLUTION_720P		= 5;	//分辨率
const int GPS_RESOLUTION_1080P		= 6;	//分辨率

typedef struct _tagVideoHead
{
	unsigned int uiVersion;
	unsigned int uiVideoCoder;	//视频解码器
	unsigned int uiAudioCoder;	//音频解码器
	unsigned int uiBinaryCoder;	//二进制数据解码器
	int	nAudioChannel;
	int nAudioSamplesPerSec;
	int nAudioBitPerSamples;
	char bWatermark;			//是否启用数字水印校验
	unsigned char ucWatermarkKeyLen;
	unsigned char ucWatermarkUsrDataLen;	
	char cWatermarkReserve;
	char cWatermarkKey[32];		//数字水印密码
	char cWatermarkUsrData[32];	//数字水印密码
	unsigned int nFrameBufLen;	//帧缓存大小
	unsigned char ucResolution;	//分辨率
	char cReserve[183];		//保留参数
}VideoHead_S;

const unsigned int AUDIO_VERSION = 0x60000001;
const unsigned int AUDIO_HEAD_LENGTH = 512;

typedef struct _tagAudioHead
{
	unsigned int uiVersion;
	unsigned short usType;
	unsigned short usFrmLen;
}AudioHead_S;

typedef struct _tagAudioData
{
	unsigned int uiLength;
	unsigned __int64 u64Stamp;
}AudioData_S;
const int AUDIO_DATA_LENGTH = sizeof(AudioData_S);

typedef struct _tagAudioDataEx
{
	unsigned __int64 u64Stamp;
}AudioDataEx_S;
const int AUDIO_DATA_EX_LENGTH = sizeof(AudioDataEx_S);

typedef struct _tagAVFrmHeadEx
{
	unsigned __int64 u64Stamp;
}AVFrmHeadEx_S;

const int AVFRM_HEAD_EX_LENGTH = sizeof(AVFrmHeadEx_S);

typedef struct _tagAVFrmHeadV3
{
	unsigned __int64 u64Stamp;
	unsigned char ucChannel;
	char cReserve[3];
}AVFrmHeadV3_S;

const int AVFRM_HEAD_V3_LENGTH = sizeof(AVFrmHeadV3_S);


#pragma pack()


#endif

