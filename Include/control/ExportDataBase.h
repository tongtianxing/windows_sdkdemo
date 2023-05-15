#pragma once

class CExportDataBase
{
protected:
	enum enumExcelLangusge {
		E_STR_EXCEL_EXPT_FILEDLG_TITLE = 101,		//����Excel��	
		E_STR_EXCEL_EXPT_TIP_NODIRVER = 102,		//û�а�װExcel!\n���Ȱ�װExcel�������ʹ�õ�������!
		E_STR_EXCEL_EXPT_TIP_SUCCEED = 103,			//�����ļ�������
		E_STR_EXCEL_EXPT_TIP_OV_FAILED = 104,		//�����ļ�ʱ����
		E_STR_EXCEL_EXPT_FILTER = 105,				//Excel�ļ�(*.xls)
		E_STR_EXCEL_EXPT_TIP_DB_EXCEPTION = 106,	//�����ļ�ʱ����
		E_STR_CSV_EXPT_FILEDLG_TITLE = 107,			//����Csv��	
		E_STR_CSV_EXPT_FILTER = 108,				//Csv�ļ�(*.csv)
		E_STR_CSV_EXPT_TIP_NODIRVER = 109,			//û�а�װExcel!\n�Ƿ񵼳�ΪCsv�ļ�!
		E_STR_CSV_EXPT_TIP_DB_EXCEPTION = 110,		//�����ļ�ʱ����\n�Ƿ񵼳�ΪCsv�ļ�!
	};
public:
	CExportDataBase(void);
	~CExportDataBase(void);

	BOOL IsExportZeroWidthColumn() const { return m_bExportZeroWidthColumn; }
	void SetExportZeroWidthColumn(BOOL val) { m_bExportZeroWidthColumn = val; }

	BOOL IsUseCsvFile() const { return m_bUseCsvFile; }
	void SetUseCsvFile(BOOL val) { m_bUseCsvFile = val; }
public:
	void SetXLSFileName(const CString& strXLSFileName);
	virtual void ExportListToExcel(CListCtrl* pList, CString strTitle);
	void ExportListToCsv(CListCtrl* pList, const CString &strTitle);

protected:
	virtual CString GetExcelLang(enumExcelLangusge enumValue) = 0;
	virtual int ShowMessageTip(LPCTSTR lpszText);
	virtual int ShowMessageTipType(LPCTSTR lpszText, int nType = MB_OK);


	BOOL MakeSurePathExists(CString &Path, bool FilenameIncluded);
private:
	void ExportListToExcel(void* database, CListCtrl* pList, CString strTitle, int nStartIndex, int nEndIndex);

	BOOL GetDefaultXlsFileName(CString& sExcelFile, const CString &strTitle);

	CString GetExcelDriver();



protected:
	CString m_strXLSFileName;

	// �������Ϊ0����,Ĭ�ϲ�����
	BOOL m_bExportZeroWidthColumn;

	// ��csv��ʽд���ļ�
	BOOL m_bUseCsvFile;
};
