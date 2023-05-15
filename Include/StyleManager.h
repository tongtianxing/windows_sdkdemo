#pragma once
#include <map>

// 2021新增颜色
enum EUIColor2021
{
	E_UICOLOR_2021_START = 200,
	E_UICOLOR_ExcelTabText0 = E_UICOLOR_2021_START,
	E_UICOLOR_ExcelTabText1,
	E_UICOLOR_ExcelTabText2,
	E_UICOLOR_ExcelTabBackRGB,
	E_UICOLOR_ExcelTabBorderRGB,
	E_UICOLOR_ListHeadVoidStart,
	E_UICOLOR_ListHeadVoidEnd,
	E_UICOLOR_MonoListItemText,
	E_UICOLOR_MonoListItemHilightText,
	E_UICOLOR_MonoListItemSpecialText,
	E_UICOLOR_MonoListItemBK,
	E_UICOLOR_SpinControlMid,
	E_UICOLOR_SpinControlBorder,
	E_UICOLOR_DatePickerWndBk,
	E_UICOLOR_DatePickerMonthBtn,
	E_UICOLOR_DatePickerToday,
	E_UICOLOR_DatePickerText0,
	E_UICOLOR_DatePickerText1,
	E_UICOLOR_DatePickerText2,
	E_UICOLOR_DatePickerText3,
	E_UICOLOR_DatePickerText4,
	E_UICOLOR_DatePickerText5,
	E_UICOLOR_DatePickerBk0,
	E_UICOLOR_DatePickerBk1,
	E_UICOLOR_DatePickerBk2,
	E_UICOLOR_DatePickerBk3,
	E_UICOLOR_DatePickerBk4,
	E_UICOLOR_DatePickerBk5,
	E_UICOLOR_DropdownText0,
	E_UICOLOR_DropdownText1,
	E_UICOLOR_DropdownText2,
	E_UICOLOR_DropdownText3,
	E_UICOLOR_DropdownTextBk,
	E_UICOLOR_DevDropdownTextBk,

	E_UICOLOR_DlgLoginEditText,
	E_UICOLOR_DlgLoginEditTextBk,
	E_UICOLOR_DlgLoginEditTipText,
	E_UICOLOR_DlgLoginCtrlText,
	E_UICOLOR_DlgLoginBtnText,
	E_UICOLOR_DlgTopTagBtnBk0,
	E_UICOLOR_DlgTopTagBtnBk1,
	E_UICOLOR_DlgTopTagBtnBk2,
	E_UICOLOR_DlgTopTagBtnBk3,
	E_UICOLOR_DlgTopTagBtnText0,
	E_UICOLOR_DlgTopTagBtnText1,
	E_UICOLOR_DlgTopTagBtnText2,
	E_UICOLOR_DlgTopTagBtnText3,
	E_UICOLOR_DevTreeDropdownText0,
	E_UICOLOR_DevTreeDropdownText1,
	E_UICOLOR_DevTreeDropdownText2,
	E_UICOLOR_DevTreeDropdownText3,
	E_UICOLOR_DlgPaneCamTabBk0,
	E_UICOLOR_DlgPaneCamTabBk1,
	E_UICOLOR_DlgPaneCamTabBk2,
	E_UICOLOR_DlgPaneCamTabBk3,
	E_UICOLOR_DlgPaneCamTabText0,
	E_UICOLOR_DlgPaneCamTabText1,
	E_UICOLOR_DlgPaneCamTabText2,
	E_UICOLOR_DlgPaneCamTabText3,
	E_UICOLOR_DlgSafetyMonTotalBk0,
	E_UICOLOR_DlgSafetyMonTotalBk1,
	E_UICOLOR_DlgSafetyMonTotalBk2,
	E_UICOLOR_DlgSafetyMonTotalBk3,
	E_UICOLOR_DlgSafetyMonTotalText,
	E_UICOLOR_DlgSafetyMonSwitchText0,
	E_UICOLOR_DlgSafetyMonSwitchText1,
	E_UICOLOR_DlgSafetyMonSwitchText2,
	E_UICOLOR_DlgSafetyMonSwitchText3,
	E_UICOLOR_DlgSafetyMonSidePanelBk,
	E_UICOLOR_DlgSafetyMonVehiAlarmBk,
	E_UICOLOR_DlgSafetyMonVehiAlarmBtnBk,
	E_UICOLOR_DlgSafetyMonDriverBk,
	E_UICOLOR_PlayBackSidePanelBk,
	E_UICOLOR_PlayBackSidePanelGroup,
	E_UICOLOR_PlayBackControlBk,
	E_UICOLOR_PlayBackProgressChannel,
	E_UICOLOR_PlayBackInfoTabBk0,
	E_UICOLOR_PlayBackInfoTabBk1,
	E_UICOLOR_PlayBackInfoTabBk2,
	E_UICOLOR_PlayBackInfoTabBk3,
	E_UICOLOR_PlayBackInfoTabText0,
	E_UICOLOR_PlayBackInfoTabText1,
	E_UICOLOR_PlayBackInfoTabText2,
	E_UICOLOR_PlayBackInfoTabText3,
	E_UICOLOR_DlgOtherSetBk,
	E_UICOLOR_DlgOtherSetTitle,
	E_UICOLOR_DlgOtherSetBtnBk0,
	E_UICOLOR_DlgOtherSetBtnBk1,
	E_UICOLOR_DlgOtherSetBtnBk2,
	E_UICOLOR_DlgOtherSetBtnBk3,
	E_UICOLOR_DlgOtherSetBtnText0,
	E_UICOLOR_DlgOtherSetBtnText1,
	E_UICOLOR_DlgOtherSetBtnText2,
	E_UICOLOR_DlgOtherSetBtnText3,
	E_UICOLOR_DlgSysCtrlTabBtnBk0,
	E_UICOLOR_DlgSysCtrlTabBtnBk1,
	E_UICOLOR_DlgSysCtrlTabBtnBk2,
	E_UICOLOR_DlgSysCtrlTabBtnBk3,
	E_UICOLOR_DlgSysCtrlTabBtnText0,
	E_UICOLOR_DlgSysCtrlTabBtnText1,
	E_UICOLOR_DlgSysCtrlTabBtnText2,
	E_UICOLOR_DlgSysCtrlTabBtnText3,

	E_UICOLOR_TreeCtrlSelectedItemBk,
	E_UICOLOR_TreeCtrlItemText0,
	E_UICOLOR_TreeCtrlItemText1,

	E_UICOLOR_DateTimeCtrlText,
	E_UICOLOR_DateTimeCtrlSelectedText,
	E_UICOLOR_DateTimeCtrlSelectedBk,

	E_UICOLOR_TrackBackInfoChartBk,
	E_UICOLOR_TrackBackInfoChartFrame,
	E_UICOLOR_TrackBackInfoChartGrid,
	E_UICOLOR_TrackBackInfoChartCursor,

	E_UICOLOR_ListItemTextCarStateNormal,
	E_UICOLOR_ListItemTextCarStateOnline,
	E_UICOLOR_ListItemTextCarStateOffline,
	E_UICOLOR_ListItemTextCarStateAccOn,
	E_UICOLOR_ListItemTextCarStateAccOff,
	E_UICOLOR_ListItemTextCarStateAlarm,
	E_UICOLOR_ListItemTextCarStateConfirmedWarning,
	E_UICOLOR_ListItemTextCarStateHeavyVehicle,	//重车颜色

	E_UICOLOR_InfoPopupBkLight,
	E_UICOLOR_InfoPopupBkDark,
	E_UICOLOR_InfoPopupBorderLight,
	E_UICOLOR_InfoPopupBorderDark,
	E_UICOLOR_InfoPopupTitle,
	E_UICOLOR_InfoPopupText,

	E_UICOLOR_PopupMenuBk,
	E_UICOLOR_PopupMenuBorder,
	E_UICOLOR_PopupMenuItemBk,
	E_UICOLOR_PopupMenuItemOverBk,
	E_UICOLOR_PopupMenuItemHilightBk,
	E_UICOLOR_PopupMenuItemDisabledBk,
	E_UICOLOR_PopupMenuItemTextBk,
	E_UICOLOR_PopupMenuItemTextOverBk,
	E_UICOLOR_PopupMenuItemTextHilightBk,
	E_UICOLOR_PopupMenuItemTextDisabledBk,

	E_UICOLOR_PVTitleTextSel,
	E_UICOLOR_PVTitleText,
	E_UICOLOR_PVTitleTextAlarmSel,
	E_UICOLOR_PVTitleTextAlarm,
	E_UICOLOR_PVTitleTextRecSel,
	E_UICOLOR_PVTitleTextRec,
	E_UICOLOR_PVTitleTextRecAlarmSel,
	E_UICOLOR_PVTitleTextRecAlarm,
	E_UICOLOR_PVTitleTextRecPreviewSel,
	E_UICOLOR_PVTitleTextRecPreview,
		
	E_UICOLOR_DatePickerText6,	//里程文本颜色
	E_UICOLOR_DatePickerFrameRect,	//边框颜色


	E_UICOLOR_2021_END
};

// UI大小、宽度获取
enum EUISize
{
	E_UISIZE_START = 100,
	E_UISIZE_nTopTagHeight = E_UISIZE_START, // 顶部工具栏高度
	E_UISIZE_nTopTagBtnTextTop,          // 顶部工具栏按钮文字离上边缘大小
	E_UISIZE_nControlBorderX,			 // 设备窗左右留白
	E_UISIZE_nControlBorderY,			 // 设备窗上方留白
	E_UISIZE_nControlItemInterval,		 // 设备搜索栏间距
	E_UISIZE_nControlItemInterval2,		 // 车辆类型、状态间距
	E_UISIZE_nControlCamTabHeight,		 // 左下状态框标签页高度
	E_UISIZE_nControlResizeWidth,		 // 设备窗拖拉条宽度
	E_UISIZE_nControlColorBorderX,       // 颜色窗口左右留白
	E_UISIZE_nControlColorBorderY,       // 颜色窗口上方留白
	E_UISIZE_nControlColorRowHeight,     // 颜色窗口每行高度
	E_UISIZE_nVideoToolbarBorderX,		 // 视频工具栏按钮左右间距
	E_UISIZE_nVideoToolbarBorderY,		 // 视频工具栏按钮上间距
	E_UISIZE_nVideoToolbarHeight,		 // 视频工具栏高度
	E_UISIZE_nVideoToolbarBtnInterval,	 // 视频工具栏按钮间距
	E_UISIZE_nVideoToolbarBtnSize,		 // 视频工具栏方形按钮宽度
	E_UISIZE_nVideoToolbarDropBtnSize,	 // 视频工具栏菜单按钮宽度
	E_UISIZE_nVideoToolbarDropBtnSize2,	 // 视频工具栏菜单按钮左半边宽度
	E_UISIZE_nVideoPreviewTitleHeight,   // 视频预览方格标题高度
	E_UISIZE_nVideoPreviewBorder,		 // 视频预览方格边框粗细
	E_UISIZE_nEventMinHeightPropotion,	 // 事件窗口最小高度比例
	E_UISIZE_nEventToolbarBorderX,       // 事件窗口工具栏右间距
	E_UISIZE_nEventToolbarHeight,        // 事件窗口工具栏高度
	E_UISIZE_nEventToolbarBtnInterval,   // 事件窗口工具栏按钮间距
	E_UISIZE_nEventDevSummaryTopInterval,// 状态统计离上边缘高度
	E_UISIZE_nEventDevSummaryInterval,	 // 状态统计间距
	E_UISIZE_nEventDevSummaryItemHeight, // 状态统计高度
	E_UISIZE_nExcelCtrlHeaderHeight,     // 事件头部高度
	E_UISIZE_nExcelCtrlItemHeight,       // 事件列表项高度
	E_UISIZE_nExcelCtrlListItemHeight,   // 用表格实现的列表行高
	E_UISIZE_nPaneMapMinWidth,			 // 右窗口最小宽度
	E_UISIZE_nPaneMapWidthPropotion,	 // 右窗口占宽度比
	E_UISIZE_nRealBottomHeight,			 // 状态栏高度
	E_UISIZE_nSysInLineInterval,         // 设置控件水平间隔
	E_UISIZE_nSysLeftInterval,           // 设置项到左边框的距离
	E_UISIZE_nSysLineInterval,           // 设置项行间距离
	E_UISIZE_nSafetyTotalHeight,         // 安全监控统计栏高度
	E_UISIZE_nSafetyVehiAlarmWidth,      // 安全监控单车辆的所有报警窗口（左）高度
	E_UISIZE_nSafetyDriverWidth,         // 安全监控车辆单个报警窗口（右）宽度

	E_UISIZE_END
};


// 部分对话框、控件不在GPSClient10客户端项目中，不能访问客户端的主题接口
// 不在客户端项目的控件可以通过这个类获得风格类型
class CStyleManager: public CStaticObject<CStyleManager>
{
public:
	enum EStyle
	{
		STYLE_INVALID,
		STYLE_DEFAULT,
		STYLE_2021_FLAT_LIGHT,
		STYLE_2021_FLAT_DARK,
	};

	enum ELanguage
	{
		LANG_ID_CHS,	//chinese            
		LANG_ID_EN,	//english            
		LANG_ID_CHT,	//chinese traditional
		LANG_ID_TR,	//turkey             
		LANG_ID_TH,	//thai               
		LANG_ID_PT,	//Portugues          
		LANG_ID_RU,	//russian            
		LANG_ID_ES,	//spanish            
		LANG_ID_BG,	//bulgarian          
		LANG_ID_AR,	//arabic             
		LANG_ID_RO,	//romanian           
		LANG_ID_VI,	//Vietnamese         
		LANG_ID_KO,	//Korean             
		LANG_ID_HU,	//hungarian          
		LANG_ID_FR,	//french             
	};

protected:
	EStyle m_eStyle;
	CString m_strConfigFile;
	CString m_strColorConfigFile;
	std::map<int, COLORREF> m_mapCustomColor;
	std::map<int, int> m_mapCustomSize;

	int m_nLangType;
	CString m_strFaceName;
	int m_nFontSizePt;

public:
	CStyleManager();
	~CStyleManager();

protected:
	void InitColor();
	void InitSize();
	COLORREF GetUIColor(LPCTSTR lpszKey, int nColor);
	int GetUISize(LPCTSTR lpszKey, int nFallback);

public:
	static int LoadStyleID();
	void InitStyle();
	static bool Is2021Style(int nStyleID);
	bool Is2021Style();
	bool IsFlatLight();
	bool IsFlatDark();

	// 主要用于libcontrol项目的控件取得CUIManager中存储的颜色
	void SetCustomColor(int nID, COLORREF color);
	COLORREF GetCustomColor(int nID, COLORREF clrDefault = COLOR_BLACK) const;

	// 主要用于libclientdialog项目的控件取得CUIManager中存储的控件大小
	void SetCustomSize(int nID, int nSize);
	int GetCustomSize(int nID, int nSizeDefault = -1) const;

	// 语言、字体接口
	static int LoadCurrentLangType();
	int GetCurrentLangType();
	static CString GetFaceName(int nLangType, int nStyleID = 1);
	CString GetFaceName();
	static int GetFontSizePt(int nLangType, int nStyleID = 1);
	int GetFontSizePt();
};