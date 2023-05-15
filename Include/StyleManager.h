#pragma once
#include <map>

// 2021������ɫ
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
	E_UICOLOR_ListItemTextCarStateHeavyVehicle,	//�س���ɫ

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
		
	E_UICOLOR_DatePickerText6,	//����ı���ɫ
	E_UICOLOR_DatePickerFrameRect,	//�߿���ɫ


	E_UICOLOR_2021_END
};

// UI��С����Ȼ�ȡ
enum EUISize
{
	E_UISIZE_START = 100,
	E_UISIZE_nTopTagHeight = E_UISIZE_START, // �����������߶�
	E_UISIZE_nTopTagBtnTextTop,          // ������������ť�������ϱ�Ե��С
	E_UISIZE_nControlBorderX,			 // �豸����������
	E_UISIZE_nControlBorderY,			 // �豸���Ϸ�����
	E_UISIZE_nControlItemInterval,		 // �豸���������
	E_UISIZE_nControlItemInterval2,		 // �������͡�״̬���
	E_UISIZE_nControlCamTabHeight,		 // ����״̬���ǩҳ�߶�
	E_UISIZE_nControlResizeWidth,		 // �豸�����������
	E_UISIZE_nControlColorBorderX,       // ��ɫ������������
	E_UISIZE_nControlColorBorderY,       // ��ɫ�����Ϸ�����
	E_UISIZE_nControlColorRowHeight,     // ��ɫ����ÿ�и߶�
	E_UISIZE_nVideoToolbarBorderX,		 // ��Ƶ��������ť���Ҽ��
	E_UISIZE_nVideoToolbarBorderY,		 // ��Ƶ��������ť�ϼ��
	E_UISIZE_nVideoToolbarHeight,		 // ��Ƶ�������߶�
	E_UISIZE_nVideoToolbarBtnInterval,	 // ��Ƶ��������ť���
	E_UISIZE_nVideoToolbarBtnSize,		 // ��Ƶ���������ΰ�ť���
	E_UISIZE_nVideoToolbarDropBtnSize,	 // ��Ƶ�������˵���ť���
	E_UISIZE_nVideoToolbarDropBtnSize2,	 // ��Ƶ�������˵���ť���߿��
	E_UISIZE_nVideoPreviewTitleHeight,   // ��ƵԤ���������߶�
	E_UISIZE_nVideoPreviewBorder,		 // ��ƵԤ������߿��ϸ
	E_UISIZE_nEventMinHeightPropotion,	 // �¼�������С�߶ȱ���
	E_UISIZE_nEventToolbarBorderX,       // �¼����ڹ������Ҽ��
	E_UISIZE_nEventToolbarHeight,        // �¼����ڹ������߶�
	E_UISIZE_nEventToolbarBtnInterval,   // �¼����ڹ�������ť���
	E_UISIZE_nEventDevSummaryTopInterval,// ״̬ͳ�����ϱ�Ե�߶�
	E_UISIZE_nEventDevSummaryInterval,	 // ״̬ͳ�Ƽ��
	E_UISIZE_nEventDevSummaryItemHeight, // ״̬ͳ�Ƹ߶�
	E_UISIZE_nExcelCtrlHeaderHeight,     // �¼�ͷ���߶�
	E_UISIZE_nExcelCtrlItemHeight,       // �¼��б���߶�
	E_UISIZE_nExcelCtrlListItemHeight,   // �ñ��ʵ�ֵ��б��и�
	E_UISIZE_nPaneMapMinWidth,			 // �Ҵ�����С���
	E_UISIZE_nPaneMapWidthPropotion,	 // �Ҵ���ռ��ȱ�
	E_UISIZE_nRealBottomHeight,			 // ״̬���߶�
	E_UISIZE_nSysInLineInterval,         // ���ÿؼ�ˮƽ���
	E_UISIZE_nSysLeftInterval,           // �������߿�ľ���
	E_UISIZE_nSysLineInterval,           // �������м����
	E_UISIZE_nSafetyTotalHeight,         // ��ȫ���ͳ�����߶�
	E_UISIZE_nSafetyVehiAlarmWidth,      // ��ȫ��ص����������б������ڣ��󣩸߶�
	E_UISIZE_nSafetyDriverWidth,         // ��ȫ��س��������������ڣ��ң����

	E_UISIZE_END
};


// ���ֶԻ��򡢿ؼ�����GPSClient10�ͻ�����Ŀ�У����ܷ��ʿͻ��˵�����ӿ�
// ���ڿͻ�����Ŀ�Ŀؼ�����ͨ��������÷������
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

	// ��Ҫ����libcontrol��Ŀ�Ŀؼ�ȡ��CUIManager�д洢����ɫ
	void SetCustomColor(int nID, COLORREF color);
	COLORREF GetCustomColor(int nID, COLORREF clrDefault = COLOR_BLACK) const;

	// ��Ҫ����libclientdialog��Ŀ�Ŀؼ�ȡ��CUIManager�д洢�Ŀؼ���С
	void SetCustomSize(int nID, int nSize);
	int GetCustomSize(int nID, int nSizeDefault = -1) const;

	// ���ԡ�����ӿ�
	static int LoadCurrentLangType();
	int GetCurrentLangType();
	static CString GetFaceName(int nLangType, int nStyleID = 1);
	CString GetFaceName();
	static int GetFontSizePt(int nLangType, int nStyleID = 1);
	int GetFontSizePt();
};