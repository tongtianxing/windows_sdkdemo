// DownSnapshot.cpp: implementation of the CDownSnapshot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DownSnapshot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDownSnapshot::CDownSnapshot()
{

}

CDownSnapshot::~CDownSnapshot()
{

}

BOOL CDownSnapshot::StartDown()
{
	if (NULL == m_lHandle)
	{
		OpenDownFile();
		/*CDevBase* pDevice = CVMgrDevice::GetInstance()->FindDvByID(m_nDevID);*/
		//mapVehicleBase mapVehicle;
		//CVehicleBaseMgr::GetInstance()->GetAllDevMap(mapVehicle);
		//CVehicleBase* pVehi = CVehicleBaseMgr::GetInstance()->FindDvsDeviceByID(m_nDevID);
		CVehicleBase* pVehi = CVehicleBaseMgr::GetInstance()->FindVechicleFromDevID(m_nDevID);
		if (pVehi)
		{
			CDevBase* pDev = pVehi->GetDevByChn(m_nChn);
			if (pDev)
			{
				NETMEDIA_SNOpenSnapshot(&m_lHandle, pDev->GetIDNOForChar(), m_nChn);
				NETMEDIA_SNSetSnapMsgCB(m_lHandle, this, FUNRealMsgCB);
				NETMEDIA_SNSetSnapDataCB(m_lHandle, this, FUNDataCB);
				NETMEDIA_SNStartSnapshot(m_lHandle);
				return TRUE;
			}
		}
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDownSnapshot::StopDown()
{
	if (m_lHandle)
	{
		NETMEDIA_SNStopSnapshot(m_lHandle);
		NETMEDIA_SNCloseSnapshot(m_lHandle); m_lHandle = NULL;
		CloseDownFile();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CString	CDownSnapshot::GetDownTitle()
{
	return LOADSTRINGEX(ID_STR_DLG_DOWNLOAD_SNAPSHOT);
}

void CDownSnapshot::FUNRealMsgCB(int nMsg, void* pUsr)
{
	CDownSnapshot* pThis = (CDownSnapshot*)pUsr;
	pThis->DoRealMsgCB(nMsg);
}

void CDownSnapshot::DoRealMsgCB(int nMsg)
{
	switch(nMsg)
	{
	case NETMEDIA_REAL_MSG_SUCCESS:
	case NETMEDIA_REAL_MSG_CNT_MS_SUC:
	case NETMEDIA_REAL_MSG_CNT_DEV_SUC:
//		PostDownMsg(GPS_DOWNLOAD_MSG_BEGIN, 0);
		break;
	case NETMEDIA_REAL_MSG_FINISHED:
		{
			DoFinished();
			PostDownMsg(GPS_DOWNLOAD_MSG_FINISHED, 0);
		}
		break;
	default:
		PostDownMsg(GPS_DOWNLOAD_MSG_FAILED, 0);
		break;
	}
}

void CDownSnapshot::DoFinished()
{
	CString strJPGFile;
	if (DecodeI2JPG(m_pFile, strJPGFile))
	{
		SetDownFileName(strJPGFile.GetBuffer(0));
	}
	else
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = NULL;
		}
	}
}

BOOL CDownSnapshot::DecodeI2JPG( FILE* pFile, CString& strJPGFile )
{
	BOOL bRet = FALSE;
	if(pFile)
	{
		fseek(pFile, 0, SEEK_SET);
		int nFrameType = 0;
		int nRead = fread(&nFrameType, 1, sizeof(int), pFile);
		if(nFrameType == 16777216)
		{
			long lHandle = 0;
			AVDEC_OpenPlayHandle(NETMEDIA_GetDecHandle(), &lHandle);
			fseek(pFile, 0, SEEK_END);
			int nLen = ftell(pFile);
			char* pFrameBuf = new char[nLen];
			memset(pFrameBuf, 0, nLen);
			fseek(pFile, 0, SEEK_SET);
			fread(pFrameBuf, 1, nLen, pFile);

			TCHAR szTmpPath[MAX_PATH], szFilename[MAX_PATH], szFilenameJPGE[MAX_PATH];
			::GetTempPath (MAX_PATH, szTmpPath);
			::GetTempFileName (szTmpPath, TEXT("cmsclientbmp1"), 0, szFilename);
			::GetTempFileName (szTmpPath, TEXT("cmsclientJPGE"), 0, szFilenameJPGE);

			if(S_OK == AVDEC_IFrameToBMP(lHandle, pFrameBuf, nLen, CStringA(szFilename).GetBuffer()))
				//			if(S_OK == AVDEC_IFrameToBMP(lHandle, pFrameBuf, nLen, Asi2Unicode(szFilename).GetBuffer(0)))
			{
				//BMP->JPG
				CImgBase* pImg = CImgBase::SCreateImage();
				ASSERT(pImg);
				if (pImg)
				{
					pImg->LoadFile(szFilename);
					ASSERT(pImg->HasPic());
					if(pImg->HasPic() && pImg->SaveToJPGFile(szFilenameJPGE))
					{
						strJPGFile = szFilenameJPGE;
						bRet = TRUE;
					}
					SAFE_DELETE_OBJECT(pImg);
				}
			}
			SAFE_DELETE_ARRAY(pFrameBuf);
			AVDEC_ClosePlayHandle(lHandle);
		}
		// 		else
		// 		{
		// 			//不是I帧文件，直接返回成功
		// 			bRet = TRUE;
		// 		} 
	}

	return bRet;
}
