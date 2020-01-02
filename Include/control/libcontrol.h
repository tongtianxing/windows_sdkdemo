#pragma once


#pragma warning(disable : 4786)
#include <stdio.h>


#include <map>
#include <list>
#include <vector>
#include "safedef.h"
#include "StaticObject.h"
#include "color_def.h"

#include "PublicApi.h"
#include "PathManager.h"

inline CString GetThemePath()
{
	return CPathManager::GetInstance()->GetImgPath();
}
inline CString GetThemeCommPath()
{
	return CPathManager::GetInstance()->GetCommImgPath();
}
inline CString GetThemeLogPath()
{
	return CPathManager::GetInstance()->GetLogPath();
}
#include "GlobalFont.h"

//#include "MemDC.h"
#include "Img/ImgBase.h"
#include "Img/ImgGdiPlus.h"
#include "TransparentWnd.h"
#include "WndShadow.h"

#include "CxButton.h"
#include "BtnST.h"
#include "BtnST_ex.h"
#include "ColorPicker.h"
#include "TransparentStatic.h"
#include "GuiCheckBox.h"

#include "CommonWndFun.h"
#include "WndShadow.h"
#include "DlgPopupBase.h"
#include "DlgPopupEx.h"
#include "DlgBase.h"
#include "WndChildBase.h"
#include "DlgChildBase.h"

#include "DGTreeCtrl.h"
#include "MutiTreeCtrl.h"
#include "XTreeCtrl.h"
#include "XTPaneWnd.h"
#include "XTPFrame.h"
//#define _XTPLIB_NOAUTOLINK
#ifdef _XTPLIB_AUTOLINK
#include <XTToolkitPro.h>    // Xtreme Toolkit Pro components
#include "CustomItems.h"
#include "XTPRadioBox.h"
#endif // _XTPLIB_AUTOLINK

#include "EditItem.h"
#include "EditList.h"
#include "XListCtrl.h"
#include "DragListCtrl.h"
#include "NumEdit.h"
#include "MRUCombo.h"
#include "XGroupBox.h"

#include "XProgressCtrl.h"
#include "TextProgressCtrl.h"
#include "mySliderControl.h"
//#include "ProSliderCtrl.h"	//调用时候找不到 hw2014/7/1
#include "BitmapSlider.h"

#include "StPicture.h"
#include "PictureEx.h"

#include "OleDropTargetEx.h"

// #include "PPToolTip/PPDrawManager.h"
// #include "PPToolTip/PPHtmlDrawer.h"
// #include "PPToolTip/PPHtmlStatic.h"
#include "PPToolTip/PPTooltip.h"
//#include "PPToolTip/CeXDib.h"

#include "TipSmart.h"

#include "DialogBase.h"
#include "Monitors.h"
#include "MultiMonitor.h"
#include "CtrlSort.h"
#include "DlgMsgTipBase.h"
#include "DlgLoadingBase.h"
#include "WndLoadingBase.h"


// #include "ComboTree/ComboTree.h"
// #include "ComboTree/ComboTreeButton.h"
// #include "ComboTree/ComboTreeDropList.h"
// #include "ComboTree/ComboTreeEdit.h"
// #include "ComboTree/ComboTreeHook.h"
// #include "ComboTree/ComboTreeTip.h"
// #include "ComboTree/PupText.h"
// #include "ComboTree/Subclass.h"

