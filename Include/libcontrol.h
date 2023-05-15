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
//#include <ImgBase.h>
//#pragma comment(lib, "GdiPlus.lib")

#include "libImgBase.h"
#pragma comment(lib, "libImgBase.lib")
#include <ObjTemplate.h>
#include "GlobalFont.h"

#include "StyleManager.h"

//#include "MemDC.h"
//#include "Img/ImgBase.h"
//#include "Img/ImgGdiPlus.h"
#include "TransparentWnd.h"
#include "WndShadow.h"

#include "CxButton.h"

#include "StateImgBase.h"
#include "CxButtonPanel.h"
#include "CxIconTextButton.h"
#include "VirtualToolbar.h"
#include "ImgEdit.h"
#include "ImgSliderCtrl.h"
#include "ImgSpinButtonCtrl.h"
#include "ImgDateTimeCtrl.h"
#include "ImgRichEdit.h"
#include "ImgCheckListBox.h"
#include "ColorListBox.h"
#include "ImgHotKeyCtrl.h"
#include "ImgIPAddressCtrl.h"
#include "ImgCtrlInit.h"

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
// 注意 [2017-8-26 ydl]
// 此处有定义_XTPLIB_NOAUTOLINK,将不会连接lib库
// 如果程序中需要使用此库接口,需要在此文件前添加头文件包含并链接lib库
// 示例:以下两行
// #define _XTP_STATICLINK
// #include <XTToolkitPro.h>
#include "CustomItems.h"
#include "XTPRadioBox.h"
#include "XTPButtonImgTheme.h"
#include "XTPImgComboBox.h"
#include "XTPDatePickerControlEx.h"

#include "EditItem.h"
#include "EditList.h"
#include "EditBoundsBase.h"
#include "XListCtrl.h"
#include "DragListCtrl.h"
#include "NumEdit.h"
#include "MRUCombo.h"
#include "XGroupBox.h"
#include "XComboBox.h"
#include "EditChangeDelayTimer.h"

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

#include "WndBase.h"
#include "DialogBase.h"
#include "Monitors.h"
#include "MultiMonitor.h"
#include "CtrlSort.h"
#include "DlgMsgTipBase.h"
#include "DlgLoadingBase.h"
#include "WndLoadingBase.h"
#include "MultiListCtrl.h"
#include "XSpinButtonCtrl.h"
#include "ScrollFrame.h"


// #include "ComboTree/ComboTree.h"
// #include "ComboTree/ComboTreeButton.h"
// #include "ComboTree/ComboTreeDropList.h"
// #include "ComboTree/ComboTreeEdit.h"
// #include "ComboTree/ComboTreeHook.h"
// #include "ComboTree/ComboTreeTip.h"
// #include "ComboTree/PupText.h"
// #include "ComboTree/Subclass.h"





#ifndef _LIBALL_NOAUTOLINK
// libcontrol自动链接,定义此宏可手动指定链接库
#ifndef _LIBCONTROL_NOAUTOLINK
// #if (_MSC_VER == 1600)	//vs2010
// 
// 	#if defined(_AFXDLL)
// 		#if defined(_UNICODE) 
// 			#if defined(_DEBUG)
// 				#pragma comment(lib, "libcontrol10mdud.lib")
// 			#else
// 				#pragma comment(lib, "libcontrol10mdu.lib")
// 			#endif // _DEBUG
// 
// 		#else
// 			#if defined(_DEBUG)
// 				#pragma comment(lib, "libcontrol10mdd.lib")
// 			#else
// 				#pragma comment(lib, "libcontrol10md.lib")
// 			#endif // _DEBUG
// 		#endif // _UNICODE
// 	#else
// 		#if defined(_UNICODE) 
// 			#if defined(_DEBUG)
// 				#pragma comment(lib, "libcontrolud.lib")
// 			#else
// 				#pragma comment(lib, "libcontrolu.lib")
// 			#endif // _DEBUG
// 
// 		#else
// 			#if defined(_DEBUG)
// 				#pragma comment(lib, "libcontrold.lib")
// 			#else
// 				#pragma comment(lib, "libcontrol.lib")
// 			#endif // _DEBUG
// 		#endif // _UNICODE
// 
// 	#endif //_AFXDLL
// 
// #endif //(_MSC_VER == 1600)

//libcontrol-vc100-x86-MD-Release-U
#pragma comment(lib, "libcontrol-"  _LIB_VISUALSTUDIO_VERSION _LIB_PLATFORM _LIB_CONFIGURATION ".lib")
#endif //_LIBCONTROL_AUTOLINK
#endif