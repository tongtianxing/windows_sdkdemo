#pragma once

class CExportDataBase
{
protected:
	enum enumExcelLangusge {
		E_STR_EXCEL_EXPT_FILEDLG_TITLE = 101,		//导出Excel表	
		E_STR_EXCEL_EXPT_TIP_NODIRVER = 102,		//没有安装Excel!\n请先安装Excel软件才能使用导出功能!
		E_STR_EXCEL_EXPT_TIP_SUCCEED = 103,			//导出文件保存于
		E_STR_EXCEL_EXPT_TIP_OV_FAILED = 104,		//覆盖文件时出错！
		E_STR_EXCEL_EXPT_FILTER = 105,				//Excel文件(*.xls)
		E_STR_EXCEL_EXPT_TIP_DB_EXCEPTION = 106,	//导出文件时出错！
		E_STR_CSV_EXPT_FILEDLG_TITLE = 107,			//导出Csv表	
		E_STR_CSV_EXPT_FILTER = 108,				//Csv文件(*.csv)
		E_STR_CSV_EXPT_TIP_NODIRVER = 109,			//没有安装Excel!\n是否导出为Csv文件!
		E_STR_CSV_EXPT_TIP_DB_EXCEPTION = 110,		//导出文件时出错！\n是否导出为Csv文件!
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

	// 导出宽度为0的列,默认不导出
	BOOL m_bExportZeroWidthColumn;

	// 按csv格式写入文件
	BOOL m_bUseCsvFile;
};
