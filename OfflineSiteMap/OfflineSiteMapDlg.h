
// OfflineSiteMapDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// COfflineSiteMapDlg dialog
class COfflineSiteMapDlg : public CDialog
{
private:
	void InitializeUI();
	void LoadSettings();
	void LoadUrls();
	void SaveSettings();
	void AddTimeZones();
	void UrlToIniFileName(const CString &csUrl,CString &csIniFileName);
	void EnableControl( int nControlID, BOOL bEnable=TRUE );
	// Construction
public:
	COfflineSiteMapDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_OFFLINESITEMAP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnToolTipNotify( UINT id,
		NMHDR* pNMHDR,
		LRESULT* pResult );
	afx_msg void OnBnClickedBtnOpenfolder();

	//afx_msg void OnBnClickedChkLastModified();
	CButton m_chkLastModified;
	CButton m_chkChangeFreq;
	CButton m_chkPriority;
	afx_msg void OnBnClickedChkFrequency();
	CComboBox m_cmbChangeFreq;
	CComboBox m_cmbPriority;
	afx_msg void OnBnClickedChkPriority();
	CDateTimeCtrl m_DTLastModified;
	afx_msg void OnFileExit();
	afx_msg void OnBnClickedBtnGenerateSitemap();
	afx_msg void OnBnClickedBtnSaveSettings();
	CComboBox m_cmbUrl;
	afx_msg void OnCbnSelchangeCmbUrls();

	CEdit m_edExcludeFiles;
	CEdit m_edExcludeFolders;
	afx_msg void OnEnSetfocusEdExcludefolders();
	afx_msg void OnEnSetfocusEdExcludefiles();
	afx_msg void OnEnKillfocusEdExcludefiles();
	afx_msg void OnEnKillfocusEdExcludefolders();	
	afx_msg void OnBnClickedChkLastModifiedDate();
	afx_msg void OnBnClickedChkLastModifiedTime();
	//afx_msg void OnBnClickedChkTimezone();
	afx_msg void OnBnClickedRdTime();
	afx_msg void OnBnClickedRdCurrenttime();
	CComboBox m_cmbTimeZone;
	CDateTimeCtrl m_dtLastModifiedTime;

	CButton m_chkLastModifiedTime;
	//CButton m_chkTimeZone;
	CBitmapButton m_cBtnAddFolder;
	afx_msg void OnBnClickedBtnDelSettings();
	afx_msg void OnHelpAbout();
	afx_msg void OnBnClickedBtnSave();
	CButton m_chkIncludeFoldersName;
};
