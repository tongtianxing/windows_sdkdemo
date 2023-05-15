#pragma once

/*
* 2021�½���ĳ�ʼ������ͷ�ļ�
* �Ի���ʹ���½��棬��Ҫ�����²�������޸�:
* 1. ��Dialogͷ�ļ���ӻ��޸Ŀؼ���Ӧ�ĳ�Ա��ʹ�����������ؼ���������Ӧ��ϵ���±�
* 2. ��Dialog::DoDataExchange()��������DDX_Control(...)ʵ�ְ󶨶���
* 3. ��Dialog::OnInitDialog()��ʼ���ؼ���һ�����ڿؼ������ݳ�ʼ���������ٵ���ImgCtrlInit.h�ļ��ĺ�����ʼ���ؼ��������ַ�ʽ
*	A. ������ʼ��ÿ���ؼ����ο�GPSClient CDlgPaneTrackBackControl::InitCtrl2021()�����������˳��ÿؼ����͡�
*		�ͻ���GPSClient��Ŀ�Ĵ����ǽ���ʱ�䴦��ģ������������ַ�ʽ��
*	B. ����EnumChildInitImgCtrl()�ӿڣ��ο�GPSClient CDlgDevFenceInfo::InitCtrl()��
*		�ӿ��Ǻ���ӵģ����������ӿؼ���������ͣ�����ʱ���ó�ʼ���ӿڡ����ò������libconfig_106��libpluginjt808_common�������������ַ�ʽ��
* 4. ������ֿؼ���Ҫ�Զ��壬�����ٴ��Բ�ͬ�Ĳ������ó�ʼ������
*/

/*
* �ؼ�����					ԭ����				������
* ----------------------------------------------------------------
* ��ͨ��ť					CButton				CCxTextButton / CCxLongTextButton
* �༭��					CEdit				CImgEdit
* ����ת�ְ�ť				CSpinButtonCtrl		CImgSpin
* RichText�༭��			CRichEditCtrl		CImgRichEdit
* ��ѡ��ť					CButton				CXTPRadioBox
* �б�						CListCtrl			CXListCtrl
* ��ѡ��					CButton				CGuiCheckBox
* ��Ͽ������б�			CComboBox			CXTPImgComboBox
* ʱ�����ڿؼ�				CDateTimeCtrl		CImgDateTimeCtrl
* ������					CSliderCtrl			CImgSliderCtrl
* ��ǩҳ					CXTPExcelTabCtrl	CImgExcelTabCtrl
* �б������ã�			CListBox			CColorListBox
* ��ѡ���б������ã�		CCheckListBox		CImgCheckListBox
* IP��ַ�༭�򣨲����ã�	CIPAddressCtrl		CImgIPAddressCtrl
* ��ݼ��༭�򣨲����ã�	CHotKeyCtrl			CImgCHotKeyCtrl
* �������					CStatic				CXGroupBox
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

// ʹ��ͼƬ�ĵ�ѡ��ť��radiobtn_sprite.png��8״̬������ѡ��checkbox_sprite.png��12״̬��
// ������CXTPButton����
void SetXTPBtnImgTheme(CXTPButton& btn);

// ʹ��ͼƬ�ĸ�ѡ��checkbox_sprite.png��12״̬��
// ������CGuiCheckBox����
void SetGuiCheckboxImgTheme(CGuiCheckBox& btn);

// ʹ��ͼƬ��Բ�η��ѡ��checkbox_circle_sprite.png��12״̬��
// ������CGuiCheckBox����
void SetGuiCheckboxCircleImgTheme(CGuiCheckBox& btn);


#ifdef _XTP_INCLUDE_CONTROLS

// ʹ��ͼƬ�Ŀɱ༭�����б�
// ���combobox_dropdown_normal.png, combobox_dropdown_over.png
// ��ť��combobox_dropdown_dropbtn.png, combobox_dropdown_dropbtn_over.png
void InitXTPImgComboBoxDropdown(CXTPImgComboBox&);
void InitXTPImgComboBoxDropdown24(CXTPImgComboBox&);	// ���ظ߶�Ϊ24��������ťͼƬ��ϵͳ���ý���ʹ�� combobox_dropdown_dropbtn_24.png combobox_dropdown_dropbtn_24_over.png

// ʹ��ͼƬ�Ŀɱ༭�����б��ұߵİ�ť��һ��С��ͷ����
// ���combobox_dropdown_normal.png, combobox_dropdown_over.png
// С��ͷ��combobox_dropdown_drop.png
void InitXTPImgComboBoxDropdownCompact(CXTPImgComboBox&);

// һ��ʽֻ�������б�
// ���combobox_droplist_normal.png, combobox_droplist_over.png
// С��ͷ��combobox_droplist_drop.png
void InitXTPImgComboBoxDropdownlist(CXTPImgComboBox&);

#endif // _XTP_INCLUDE_CONTROLS


// ʹ��ͼƬ�ı༭��
// ������CImgEdit����
// !!!ע�⣺�ؼ���ֱ��Parent����ı䣬����ʹ��DeferWindowPos�ı�ؼ�λ�ã�MoveWindow��SetWindowPos��Ȼ����
void InitImgEdit(CImgEdit& ed,
	LPCTSTR szNormal = NULL,
	LPCTSTR szOver = NULL,
	LPCTSTR szHighlight = NULL,
	LPCTSTR szDisabled = NULL);

// ʹ��ͼƬ��RichEdit�༭��
// �߿��ȹ̶�Ϊ2x2
// ���ֱ���ֻ֧�ִ�ɫ���ڲ�����CRichEditCtrl::SetBackgroundColor�趨
// ������CImgRichEdit����
// !!!ע�⣺�ؼ���ֱ��Parent����ı䣬����ʹ��DeferWindowPos�ı�ؼ�λ�ã�MoveWindow��SetWindowPos��Ȼ����
void InitImgRichEdit(CImgRichEdit& ed,
	LPCTSTR szNormal = NULL,
	LPCTSTR szOver = NULL,
	LPCTSTR szHighlight = NULL,
	LPCTSTR szDisabled = NULL);

// ʹ��ͼƬ��ת��
// ������CImgSpin����
void InitImgSpinButtonCtrl(CImgSpin& sp);

// ʹ��ͼƬ�Ļ�����
// ������CImgSliderCtrl����
// �������ص��ǿͻ������½�ɫ�ʵĻ���������漰�����϶ࡣ����Ҫ�Զ��壬����ο����������ʵ�֣����ⲿ�������ò���
void InitImgSliderCtrl(CImgSliderCtrl& sl);
void InitImgSliderCtrlColor(CImgSliderCtrl& sl, COLORREF clrChannel = COLOR_GRAY, COLORREF clrChannelUsed = COLOR_DODGERBLUE);

// ʹ��ͼƬ�ı�ǩҳ
// ������CImgExcelTabCtrl����
class CImgExcelTabCtrl;
void InitImgExcelTabCtrl(CImgExcelTabCtrl&);

// ʹ��ͼƬ������������ʱ��ؼ�
// ������CImgDateTimeCtrl����
void InitImgDateCtrl(CImgDateTimeCtrl& dt);
void InitImgTimeCtrl(CImgDateTimeCtrl& dt);
void InitImgDateTimeCtrl(CImgDateTimeCtrl& dt);

// �����ؼ�
// ������CXTPDatePickerControlEx����
void InitXTPImgDatePickerCtrlEx(CXTPDatePickerControlEx& dp);

// �б�ؼ�CXListCtrl�ķ��ֱ����CXListCtrlStyleDataMgr::SetListCtrlStyle()�����ã������������
// ����Ľӿ�����dllʹ��
// !!!ע�⣺�ؼ���ֱ��Parent����ı䣬����ʹ��DeferWindowPos�ı�ؼ�λ�ã�MoveWindow��SetWindowPos��Ȼ����
void InitXListCtrlStyle(CXListCtrl& ls, BOOL bMono = FALSE);

// ���ؼ�CDGTreeCtrl�ķ��ֱ����CDataManager::SetTreeCtrlStyle()�����ã������������
// ����Ľӿ�����dllʹ��
// !!!ע�⣺�ؼ���ֱ��Parent����ı䣬����ʹ��DeferWindowPos�ı�ؼ�λ�ã�MoveWindow��SetWindowPos��Ȼ����
void InitDGTreeCtrlStyle(CDGTreeCtrl& tree);

// class CImgCheckListBox: public CCheckListBox
// !!!ע�⣺�ؼ���ֱ��Parent����ı䣬����ʹ��DeferWindowPos�ı�ؼ�λ�ã�MoveWindow��SetWindowPos��Ȼ����
void InitImgCheckListBox(CImgCheckListBox&);

// class CColorListBox: public CListBox
// !!!ע�⣺�ؼ���ֱ��Parent����ı䣬����ʹ��DeferWindowPos�ı�ؼ�λ�ã�MoveWindow��SetWindowPos��Ȼ����
void InitColorListBox(CColorListBox&);

// class CImgHotKeyCtrl: public CHotKeyCtrl
void InitImgHotKeyCtrl(CImgHotKeyCtrl&);

// class CImgIPAddressCtrl: public CIPAddressCtrl
void InitImgIPAddressCtrl(CImgIPAddressCtrl&);

// �����ӿؼ���ִ�г�ʼ��
// nComboBoxType: 0:InitXTPImgComboBoxDropdown 1:InitXTPImgComboBoxDropdown24 2:InitXTPImgComboBoxDropdownCompact 3:InitXTPImgComboBoxDropdownlist
// nCheckBoxType: 0:SetGuiCheckboxImgTheme 1:SetGuiCheckboxCircleImgTheme
void EnumChildInitImgCtrl(HWND hParent, int nComboBoxType = 1, int nCheckboxType = 0);