#pragma once

/*
* 2021新界面的初始化函数头文件
* 对话框使用新界面，需要按以下步骤进行修改:
* 1. 在Dialog头文件添加或修改控件对应的成员，使用新类名。控件与类名对应关系如下表
* 2. 在Dialog::DoDataExchange()函数调用DDX_Control(...)实现绑定对象
* 3. 在Dialog::OnInitDialog()初始化控件，一般是在控件的数据初始化结束后，再调用ImgCtrlInit.h文件的函数初始化控件。有两种方式
*	A. 单独初始化每个控件，参考GPSClient CDlgPaneTrackBackControl::InitCtrl2021()，基本覆盖了常用控件类型。
*		客户端GPSClient项目的窗口是较早时间处理的，基本是用这种方式。
*	B. 调用EnumChildInitImgCtrl()接口，参考GPSClient CDlgDevFenceInfo::InitCtrl()。
*		接口是后面加的，会遍历检查子控件对象的类型，符合时调用初始化接口。设置插件（如libconfig_106、libpluginjt808_common）基本是用这种方式。
* 4. 如果部分控件需要自定义，可以再次以不同的参数调用初始化函数
*/

/*
* 控件功能					原类名				新类名
* ----------------------------------------------------------------
* 普通按钮					CButton				CCxTextButton / CCxLongTextButton
* 编辑框					CEdit				CImgEdit
* 上下转轮按钮				CSpinButtonCtrl		CImgSpin
* RichText编辑框			CRichEditCtrl		CImgRichEdit
* 单选按钮					CButton				CXTPRadioBox
* 列表						CListCtrl			CXListCtrl
* 复选框					CButton				CGuiCheckBox
* 组合框、下拉列表			CComboBox			CXTPImgComboBox
* 时间日期控件				CDateTimeCtrl		CImgDateTimeCtrl
* 滑动条					CSliderCtrl			CImgSliderCtrl
* 标签页					CXTPExcelTabCtrl	CImgExcelTabCtrl
* 列表（不常用）			CListBox			CColorListBox
* 复选框列表（不常用）		CCheckListBox		CImgCheckListBox
* IP地址编辑框（不常用）	CIPAddressCtrl		CImgIPAddressCtrl
* 快捷键编辑框（不常用）	CHotKeyCtrl			CImgCHotKeyCtrl
* 分组外框					CStatic				CXGroupBox
*/

class CXTPButton;
class CGuiCheckBox;
class CXTPImgComboBox;
class CImgEdit;
class CImgSpin;
class CImgExcelTabCtrl;
class CImgDateTimeCtrl;
class CXTPDatePickerControlEx;
class CXListCtrl;
class CDGTreeCtrl;

// 使用图片的单选按钮（radiobtn_sprite.png，8状态）、复选框（checkbox_sprite.png，12状态）
// 适用于CXTPButton对象
void SetXTPBtnImgTheme(CXTPButton& btn);

// 使用图片的复选框（checkbox_sprite.png，12状态）
// 适用于CGuiCheckBox对象
void SetGuiCheckboxImgTheme(CGuiCheckBox& btn);

// 使用图片的圆形风格复选框（checkbox_circle_sprite.png，12状态）
// 适用于CGuiCheckBox对象
void SetGuiCheckboxCircleImgTheme(CGuiCheckBox& btn);


#ifdef _XTP_INCLUDE_CONTROLS

// 使用图片的可编辑下拉列表
// 外框：combobox_dropdown_normal.png, combobox_dropdown_over.png
// 按钮：combobox_dropdown_dropbtn.png, combobox_dropdown_dropbtn_over.png
void InitXTPImgComboBoxDropdown(CXTPImgComboBox&);
void InitXTPImgComboBoxDropdown24(CXTPImgComboBox&);	// 加载高度为24的下拉按钮图片，系统设置界面使用 combobox_dropdown_dropbtn_24.png combobox_dropdown_dropbtn_24_over.png

// 使用图片的可编辑下拉列表，右边的按钮用一个小箭头代替
// 外框：combobox_dropdown_normal.png, combobox_dropdown_over.png
// 小箭头：combobox_dropdown_drop.png
void InitXTPImgComboBoxDropdownCompact(CXTPImgComboBox&);

// 一体式只读下拉列表，
// 外框：combobox_droplist_normal.png, combobox_droplist_over.png
// 小箭头：combobox_droplist_drop.png
void InitXTPImgComboBoxDropdownlist(CXTPImgComboBox&);

#endif // _XTP_INCLUDE_CONTROLS


// 使用图片的编辑框
// 适用于CImgEdit对象
// !!!注意：控件的直接Parent将会改变，不能使用DeferWindowPos改变控件位置；MoveWindow和SetWindowPos仍然可用
void InitImgEdit(CImgEdit& ed,
	LPCTSTR szNormal = NULL,
	LPCTSTR szOver = NULL,
	LPCTSTR szHighlight = NULL,
	LPCTSTR szDisabled = NULL);

// 使用图片的RichEdit编辑框
// 边框宽度固定为2x2
// 文字背景只支持纯色，内部调用CRichEditCtrl::SetBackgroundColor设定
// 适用于CImgRichEdit对象
// !!!注意：控件的直接Parent将会改变，不能使用DeferWindowPos改变控件位置；MoveWindow和SetWindowPos仍然可用
void InitImgRichEdit(CImgRichEdit& ed,
	LPCTSTR szNormal = NULL,
	LPCTSTR szOver = NULL,
	LPCTSTR szHighlight = NULL,
	LPCTSTR szDisabled = NULL);

// 使用图片的转轮
// 适用于CImgSpin对象
void InitImgSpinButtonCtrl(CImgSpin& sp);

// 使用图片的滑动条
// 适用于CImgSliderCtrl对象
// 函数加载的是客户端左下角色彩的滑动条风格，涉及参数较多。如需要自定义，建议参考这个函数的实现，在外部单独设置参数
void InitImgSliderCtrl(CImgSliderCtrl& sl);
void InitImgSliderCtrlColor(CImgSliderCtrl& sl, COLORREF clrChannel = COLOR_GRAY, COLORREF clrChannelUsed = COLOR_DODGERBLUE);

// 使用图片的标签页
// 适用于CImgExcelTabCtrl对象
class CImgExcelTabCtrl;
void InitImgExcelTabCtrl(CImgExcelTabCtrl&);

// 使用图片的下拉月历、时间控件
// 适用于CImgDateTimeCtrl对象
void InitImgDateCtrl(CImgDateTimeCtrl& dt);
void InitImgTimeCtrl(CImgDateTimeCtrl& dt);
void InitImgDateTimeCtrl(CImgDateTimeCtrl& dt);

// 月历控件
// 适用于CXTPDatePickerControlEx对象
void InitXTPImgDatePickerCtrlEx(CXTPDatePickerControlEx& dp);

// 列表控件CXListCtrl的风格直接在CXListCtrlStyleDataMgr::SetListCtrlStyle()里设置，无需另外调用
// 下面的接口留给dll使用
// !!!注意：控件的直接Parent将会改变，不能使用DeferWindowPos改变控件位置；MoveWindow和SetWindowPos仍然可用
void InitXListCtrlStyle(CXListCtrl& ls, BOOL bMono = FALSE);

// 树控件CDGTreeCtrl的风格直接在CDataManager::SetTreeCtrlStyle()里设置，无需另外调用
// 下面的接口留给dll使用
// !!!注意：控件的直接Parent将会改变，不能使用DeferWindowPos改变控件位置；MoveWindow和SetWindowPos仍然可用
void InitDGTreeCtrlStyle(CDGTreeCtrl& tree);

// class CImgCheckListBox: public CCheckListBox
// !!!注意：控件的直接Parent将会改变，不能使用DeferWindowPos改变控件位置；MoveWindow和SetWindowPos仍然可用
void InitImgCheckListBox(CImgCheckListBox&);

// class CColorListBox: public CListBox
// !!!注意：控件的直接Parent将会改变，不能使用DeferWindowPos改变控件位置；MoveWindow和SetWindowPos仍然可用
void InitColorListBox(CColorListBox&);

// class CImgHotKeyCtrl: public CHotKeyCtrl
void InitImgHotKeyCtrl(CImgHotKeyCtrl&);

// class CImgIPAddressCtrl: public CIPAddressCtrl
void InitImgIPAddressCtrl(CImgIPAddressCtrl&);

// 遍历子控件并执行初始化
// nComboBoxType: 0:InitXTPImgComboBoxDropdown 1:InitXTPImgComboBoxDropdown24 2:InitXTPImgComboBoxDropdownCompact 3:InitXTPImgComboBoxDropdownlist
// nCheckBoxType: 0:SetGuiCheckboxImgTheme 1:SetGuiCheckboxCircleImgTheme
void EnumChildInitImgCtrl(HWND hParent, int nComboBoxType = 1, int nCheckboxType = 0);