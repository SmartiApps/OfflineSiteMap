
// OfflineSiteMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OfflineSiteMap.h"
#include "OfflineSiteMapDlg.h"
#include "Utils.h"
#include "Sitemap.h"
#include "Definations.h"
#include "hyperlink.h"
#include "afxwin.h"
#pragma comment(lib,"Version.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	virtual BOOL OnInitDialog();
	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CHyperLink m_stwebLink;
	CHyperLink m_stEmail;
	CStatic m_stVersion;
};
BOOL GetAppVersion( char *LibName, WORD *MajorVersion, WORD *MinorVersion, WORD *BuildNumber, WORD *RevisionNumber )
{
	DWORD dwHandle, dwLen;
	UINT BufLen;
	LPTSTR lpData;
	VS_FIXEDFILEINFO *pFileInfo;
	dwLen = GetFileVersionInfoSize( LibName, &dwHandle );
	if (!dwLen) 
		return FALSE;

	lpData = (LPTSTR) malloc (dwLen);
	if (!lpData) 
		return FALSE;

	if( !GetFileVersionInfo( LibName, dwHandle, dwLen, lpData ) )
	{
		free (lpData);
		return FALSE;
	}
	if( VerQueryValue( lpData, "\\", (LPVOID *) &pFileInfo, (PUINT)&BufLen ) ) 
	{
		*MajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
		*MinorVersion = LOWORD(pFileInfo->dwFileVersionMS);
		*BuildNumber = HIWORD(pFileInfo->dwFileVersionLS);
		*RevisionNumber = LOWORD(pFileInfo->dwFileVersionLS);
		free (lpData);
		return TRUE;
	}
	free (lpData);
	return FALSE;
}
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//m_stEmail.SetURL("mailto:contactus@smartpricedeal.com");

	/*theApp.pro
	csVersion.LoadString(FILE*/
	//CWnd* pWndAppStatic= GetDlgItem (IDC_ST_VER);

	//if (pWndAppStatic)
	//	pWndAppStatic->SetWindowText (csVersion);

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ST_WEB, m_stwebLink);
	DDX_Control(pDX, IDC_ST_EMAIL, m_stEmail);
	DDX_Control(pDX, IDC_ST_VER, m_stVersion);
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csVersion;

	WORD MajorVersion        =0; 
	WORD MinorVersion        =0; 
	WORD BuildNumber        =0; 
	WORD RevisionNumber        =0;

	TCHAR fileName[4096];
	GetModuleFileName(NULL,fileName,4096);
	//theApp.m_pszExeName is no good

	GetAppVersion(fileName,
		&MajorVersion,    
		&MinorVersion,    
		&BuildNumber,    
		&RevisionNumber);

	csVersion.Format (_T("%hu.%hu"),MajorVersion,MinorVersion);

	m_stVersion.SetWindowText(csVersion);
	m_stwebLink.SetURL("http://www.smartpricedeal.com/products/chatclientcheater.html");
	return TRUE;
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COfflineSiteMapDlg dialog


LPSTR lpFolder=_T("List of folders seperated by comma\r\n(Example: admin,etc,secret)");
LPSTR lpFiles= _T("List of files seperated by comma\r\n(Example: robots.txt,secret.html,*.jpg,*.gif,*.php)");
LPSTR lpIncludeFolder=_T("Check this option, Incase if you have excluded index.htm,default.htm and want to include folder names in sitemap \r\n example: http://www.smartpricedeal.com/deals/  instead of http://www.smartpricedeal.com/deals/index.html  ");
COfflineSiteMapDlg::COfflineSiteMapDlg(CWnd* pParent /*=NULL*/)
: CDialog(COfflineSiteMapDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LOGO);
}

void COfflineSiteMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_LAST_MODIFIED, m_chkLastModified);
	DDX_Control(pDX, IDC_CHK_FREQUENCY, m_chkChangeFreq);
	DDX_Control(pDX, IDC_CHK_PRIORITY, m_chkPriority);
	DDX_Control(pDX, IDC_CMB_CHNG_FREQ, m_cmbChangeFreq);
	DDX_Control(pDX, IDC_CMB_PRIORITY, m_cmbPriority);
	DDX_Control(pDX, IDC_DATETIME_MODIFIED, m_DTLastModified);
	DDX_Control(pDX, IDC_CMB_URLS, m_cmbUrl);
	DDX_Control(pDX, IDC_ED_EXCLUDEFILES, m_edExcludeFiles);
	DDX_Control(pDX, IDC_ED_EXCLUDEFOLDERS, m_edExcludeFolders);
	DDX_Control(pDX, IDC_CMB_TIMEZONE, m_cmbTimeZone);
	DDX_Control(pDX, IDC_DT_LASTMODIFIED_TIME, m_dtLastModifiedTime);

	DDX_Control(pDX, IDC_CHK_LAST_MODIFIED_TIME, m_chkLastModifiedTime);
	//	DDX_Control(pDX, IDC_CHK_TIMEZONE, m_chkTimeZone);
	DDX_Control(pDX, IDC_BTN_OPENFOLDER, m_cBtnAddFolder);
	DDX_Control(pDX, IDC_CHK_FOLDER_NAME, m_chkIncludeFoldersName);
}

BEGIN_MESSAGE_MAP(COfflineSiteMapDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPENFOLDER, &COfflineSiteMapDlg::OnBnClickedBtnOpenfolder)


	ON_BN_CLICKED(IDC_CHK_FREQUENCY, &COfflineSiteMapDlg::OnBnClickedChkFrequency)
	ON_BN_CLICKED(IDC_CHK_PRIORITY, &COfflineSiteMapDlg::OnBnClickedChkPriority)
	ON_COMMAND(ID_FILE_EXIT, &COfflineSiteMapDlg::OnFileExit)
	ON_BN_CLICKED(IDC_BTN_GENERATE_SITEMAP, &COfflineSiteMapDlg::OnBnClickedBtnGenerateSitemap)
	ON_BN_CLICKED(IDC_BTN_SAVE_SETTINGS, &COfflineSiteMapDlg::OnBnClickedBtnSaveSettings)
	ON_CBN_SELCHANGE(IDC_CMB_URLS, &COfflineSiteMapDlg::OnCbnSelchangeCmbUrls)

	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipNotify)
	ON_EN_SETFOCUS(IDC_ED_EXCLUDEFOLDERS, &COfflineSiteMapDlg::OnEnSetfocusEdExcludefolders)
	ON_EN_SETFOCUS(IDC_ED_EXCLUDEFILES, &COfflineSiteMapDlg::OnEnSetfocusEdExcludefiles)
	ON_EN_KILLFOCUS(IDC_ED_EXCLUDEFILES, &COfflineSiteMapDlg::OnEnKillfocusEdExcludefiles)
	ON_EN_KILLFOCUS(IDC_ED_EXCLUDEFOLDERS, &COfflineSiteMapDlg::OnEnKillfocusEdExcludefolders)
	ON_BN_CLICKED(IDC_CHK_LAST_MODIFIED_DATE, &COfflineSiteMapDlg::OnBnClickedChkLastModifiedDate)
	ON_BN_CLICKED(IDC_CHK_LAST_MODIFIED_TIME, &COfflineSiteMapDlg::OnBnClickedChkLastModifiedTime)
	//	ON_BN_CLICKED(IDC_CHK_TIMEZONE, &COfflineSiteMapDlg::OnBnClickedChkTimezone)	
	ON_BN_CLICKED(IDC_RD_TIME, &COfflineSiteMapDlg::OnBnClickedRdTime)
	ON_BN_CLICKED(IDC_RD_CURRENTTIME, &COfflineSiteMapDlg::OnBnClickedRdCurrenttime)
	ON_BN_CLICKED(IDC_BTN_DEL_SETTINGS, &COfflineSiteMapDlg::OnBnClickedBtnDelSettings)
	ON_COMMAND(ID_HELP_ABOUT, &COfflineSiteMapDlg::OnHelpAbout)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COfflineSiteMapDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// COfflineSiteMapDlg message handlers

BOOL COfflineSiteMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//HBITMAP hbit=::LoadBitmap(theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	//m_cBtnAddFolder.SetBitmap(hbit);
	//DeleteObject(hbit);
	// TODO: Add extra initialization here
	//	m_cBtnAddFolder.SetBitmap(  );

	LoadUrls();
	AddTimeZones();
	InitializeUI();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COfflineSiteMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COfflineSiteMapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COfflineSiteMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COfflineSiteMapDlg::OnBnClickedBtnOpenfolder()
{
	CString csFolderPath;
	if(CUtils::OpenFolderDialog(csFolderPath))
	{
		SetDlgItemText(IDC_ED_FOLDERPATH,csFolderPath);
	}
}


void COfflineSiteMapDlg::OnBnClickedChkFrequency()
{

	if(m_chkChangeFreq.GetCheck())
	{
		m_cmbChangeFreq.EnableWindow(TRUE);
	}
	else
	{
		m_cmbChangeFreq.EnableWindow(FALSE);
	}
}

void COfflineSiteMapDlg::OnBnClickedChkPriority()
{
	if(m_chkPriority.GetCheck())
	{
		m_cmbPriority.EnableWindow(TRUE);
	}
	else
	{
		m_cmbPriority.EnableWindow(FALSE);
	}
}

void COfflineSiteMapDlg::OnFileExit()
{
	PostMessage(WM_QUIT,NULL,NULL);
}

void COfflineSiteMapDlg::OnBnClickedBtnGenerateSitemap()
{
	CSiteMap cSitemap;
	stSiteMapInfo stSiteMapInfoObj;

	GetDlgItemText(IDC_ED_FOLDERPATH,stSiteMapInfoObj.csLocalFolderPath);
	GetDlgItemText(IDC_ED_SITEMAP_PATH,stSiteMapInfoObj.csSiteMapPath);
	GetDlgItemText(IDC_CMB_URLS,stSiteMapInfoObj.csUrl);


	int nUrlLength=stSiteMapInfoObj.csUrl.GetLength();
	int nFolderPathLength=stSiteMapInfoObj.csLocalFolderPath.GetLength();
	if(nFolderPathLength==0)
	{
		AfxMessageBox("Please select the local folder path of the website");
	}
	else
	{
		CString csSlash(stSiteMapInfoObj.csLocalFolderPath.GetAt(nFolderPathLength-1));
		if(_tcscmp(csSlash,"\\")!=0)
		{
			stSiteMapInfoObj.csLocalFolderPath=stSiteMapInfoObj.csLocalFolderPath+"\\";
		}
	}
	if(nUrlLength==0)
	{
		AfxMessageBox("Please enter the website address");
	}
	else
	{
		CString csSlash(stSiteMapInfoObj.csUrl.GetAt(nUrlLength-1));
		if(_tcscmp(csSlash,"/")!=0)
		{
			stSiteMapInfoObj.csUrl=stSiteMapInfoObj.csUrl+"/";
		}
	}
	if(m_chkPriority.GetCheck())
		GetDlgItemText(IDC_CMB_PRIORITY,stSiteMapInfoObj.csPriority);

	if(m_chkChangeFreq.GetCheck())
		GetDlgItemText(IDC_CMB_CHNG_FREQ,stSiteMapInfoObj.csChangefreq);

	if(m_chkIncludeFoldersName.GetCheck())
		stSiteMapInfoObj.bIncludeFolderNames=TRUE;
	else
		stSiteMapInfoObj.bIncludeFolderNames=FALSE;

	if(m_chkLastModified.GetCheck())
	{
		CString csDateTime,csDate,csTime,csGMT;
		m_DTLastModified.GetWindowText(csDate);
		csDateTime=csDate;

		if(m_chkLastModifiedTime.GetCheck())
		{

			if(m_dtLastModifiedTime.IsWindowEnabled())
			{
				CTime cTime;
				m_dtLastModifiedTime.GetTime(cTime);
				csTime=cTime.Format("%H:%M:%S");
			}
			else
			{
				const time_t curr = time(NULL);
				const tm* local = localtime(&curr);
				csTime.Format("%.2d:%.2d:%.2d",local->tm_hour , local->tm_min, local->tm_sec);
			}
			m_cmbTimeZone.GetWindowText(csGMT);
			csGMT.Replace("UTC","");
			csDateTime=csDate+"T"+csTime+csGMT;

		}
		stSiteMapInfoObj.csLastmod=csDateTime;

	}

	GetDlgItemText(IDC_ED_EXCLUDEFILES,stSiteMapInfoObj.csExcludeFiles);
	GetDlgItemText(IDC_ED_EXCLUDEFOLDERS,stSiteMapInfoObj.csExcludeFolder);

	stSiteMapInfoObj.csExcludeFolder.Replace(lpFolder,"");
	stSiteMapInfoObj.csExcludeFiles.Replace(lpFiles,"");

	if(cSitemap.GenerateSiteMap(stSiteMapInfoObj)==TRUE)
	{
		AfxMessageBox("Sucessfully Generated!!!");
	}
	else
	{
		AfxMessageBox("Sitemap Generation Failed!!!");
	}
}

void COfflineSiteMapDlg::OnBnClickedBtnSaveSettings()
{
	CString csFolderPath,csUrl,csSiteMapPath;
	GetDlgItemText(IDC_ED_FOLDERPATH,csFolderPath);
	GetDlgItemText(IDC_CMB_URLS,csUrl);
	GetDlgItemText(IDC_ED_SITEMAP_PATH,csSiteMapPath);

	int nUrlLength=csUrl.GetLength();
	int nFolderPathLength=csFolderPath.GetLength();
	if(nFolderPathLength==0)
	{
		AfxMessageBox("Please select the local folder path of the website");
	}
	else
	{
		CString csSlash(csFolderPath.GetAt(nFolderPathLength-1));
		if(_tcscmp(csSlash,"\\")!=0)
		{
			csFolderPath=csFolderPath+"\\";
		}
	}
	if(nUrlLength==0)
	{
		AfxMessageBox("Please enter the website address");
	}
	else
	{
		CString csSlash(csUrl.GetAt(nUrlLength-1));
		if(_tcscmp(csSlash,"/")!=0)
		{
			csUrl=csUrl+"/";
		}
	}
	if(csSiteMapPath.IsEmpty())
	{
		AfxMessageBox("Please select the path to save sitemap file");
	}

	SaveSettings();

}

void COfflineSiteMapDlg::OnCbnSelchangeCmbUrls()
{

	LoadSettings();
}


BOOL COfflineSiteMapDlg::OnToolTipNotify( UINT id,
										 NMHDR * pNMHDR,
										 LRESULT * pResult )
{
	// Get the tooltip structure.
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;

	// Actually the idFrom holds Control's handle.
	UINT CtrlHandle = pNMHDR->idFrom;

	// Check once again that the idFrom holds handle itself.
	if (pTTT->uFlags & TTF_IDISHWND)
	{
		// Get the control's ID.
		UINT nID = ::GetDlgCtrlID( HWND( CtrlHandle ));

		// Now you have the ID. depends on control,
		// set your tooltip message.
		switch( nID )
		{
		case IDC_ED_EXCLUDEFILES:
			// Set the tooltip text.
			pTTT->lpszText =lpFiles;
			break;
		case IDC_ED_EXCLUDEFOLDERS:
			// Set the tooltip text.
			pTTT->lpszText = lpFolder;
			break;
		case IDC_CHK_FOLDER_NAME:
			pTTT->lpszText = lpIncludeFolder;
			break;



		default:
			// Set the tooltip text.
			//pTTT->lpszText = _T("Tooltips everywhere!!!");
			break;
		}

		return TRUE;
	}

	// Not handled.
	return FALSE;
}

void COfflineSiteMapDlg::InitializeUI()
{
	EnableToolTips();
	m_cmbPriority.SetCurSel(4);
	m_DTLastModified.SetFormat("yyyy-MM-dd");
	m_DTLastModified.EnableWindow(FALSE);

	m_cmbPriority.EnableWindow(FALSE);	
	m_cmbChangeFreq.EnableWindow(FALSE);
	m_edExcludeFiles.SetWindowText(lpFiles);
	m_edExcludeFolders.SetWindowText(lpFolder);

	m_cmbTimeZone.SetCurSel(DEFAULT_TIME_ZONE);
	//For Default check
	CheckRadioButton(IDC_RD_CURRENTTIME,IDC_RD_TIME,IDC_RD_CURRENTTIME);
	m_chkLastModifiedTime.EnableWindow(FALSE);
	OnBnClickedChkLastModifiedTime();
}
void COfflineSiteMapDlg::LoadSettings()
{
	int nChangeFreq	=-1, nPriority	=-1;
	int nChangeFreqStatus=-1, nPriorityStatus=-1, nLastModifiedStatus=-1,nLastModifiedTimeStatus=-1,nTimeZone=-1,nIncludeFolders=-1;


	CString csSettingsPath=CUtils::GetSettingsPath();
	CString csFolderPath,csUrl,csLastModified,csChangeFreq,csPriority,csExcludeFolder, csExcludeFiles,csSiteMapPath;
	int nSel=0;
	nSel=	m_cmbUrl.GetCurSel();
	if(nSel>=0)
	{
		m_cmbUrl.GetLBText(nSel,csUrl);
	}
	if(csUrl.IsEmpty())
	{
		GetDlgItemText(IDC_CMB_URLS,csUrl);

		return;
	}

	CString csFileName;
	UrlToIniFileName(csUrl,csFileName);
	CString csIniFilePath=csSettingsPath+csFileName;

	csFolderPath	=CUtils::GetFolderPath(csIniFilePath);
	csLastModified	=CUtils::GetLastModified(csIniFilePath);
	nChangeFreq	=CUtils::GetChangeFrequency(csIniFilePath);
	nPriority		=CUtils::GetPriority(csIniFilePath);
	csExcludeFolder	=CUtils::GetExcludeFolder(csIniFilePath);
	csExcludeFiles	=CUtils::GetExcludeFiles(csIniFilePath);
	csSiteMapPath	=CUtils::GetSiteMapPath(csIniFilePath);

	//Status
	nChangeFreqStatus=CUtils::GetChangeFrequencyStatus(csIniFilePath);
	nLastModifiedStatus=CUtils::GetLastModifiedStatus(csIniFilePath);
	nLastModifiedTimeStatus=CUtils::GetLastModifiedTimeStatus(csIniFilePath);
	nPriorityStatus=CUtils::GetPriorityStatus(csIniFilePath);
	nTimeZone=CUtils::GetTimeZone(csIniFilePath);
	nIncludeFolders=CUtils::GetIncludeFoldersName(csIniFilePath);

	SetDlgItemText(IDC_ED_FOLDERPATH,csFolderPath);
	SetDlgItemText(IDC_ED_EXCLUDEFILES,csExcludeFiles);
	SetDlgItemText(IDC_ED_EXCLUDEFOLDERS,csExcludeFolder);
	SetDlgItemText(IDC_ED_SITEMAP_PATH,csSiteMapPath);



	if(nTimeZone==-1)
	{
		m_cmbTimeZone.SetCurSel(DEFAULT_TIME_ZONE);
	}
	else
	{

		m_cmbTimeZone.SetCurSel(nTimeZone);
	}

	if(nPriority==-1)
	{
		m_chkPriority.SetCheck(FALSE);
	}
	else
	{
		m_cmbPriority.SetCurSel(nPriority);
	}

	if(nChangeFreq==-1)
	{
		m_chkChangeFreq.SetCheck(FALSE);
	}
	else
	{

		m_cmbChangeFreq.SetCurSel(nChangeFreq);
	}


	if(nChangeFreqStatus==1)
	{
		m_chkChangeFreq.SetCheck(TRUE);
		m_cmbChangeFreq.EnableWindow(TRUE);
	}
	else
	{
		m_chkChangeFreq.SetCheck(FALSE);
		m_cmbChangeFreq.EnableWindow(FALSE);
	}

	if(nPriorityStatus==1)
	{
		m_chkPriority.SetCheck(TRUE);
		m_cmbPriority.EnableWindow(TRUE);
	}
	else
	{
		m_chkPriority.SetCheck(FALSE);
		m_cmbPriority.EnableWindow(FALSE);
	}

	if(nLastModifiedStatus==1)
	{
		m_chkLastModified.SetCheck(TRUE);
		m_DTLastModified.EnableWindow(TRUE);
		m_chkLastModifiedTime.EnableWindow(TRUE);
	}
	else
	{
		m_chkLastModifiedTime.EnableWindow(FALSE);
		m_chkLastModified.SetCheck(FALSE);
		m_DTLastModified.EnableWindow(FALSE);
	}
	if(nLastModifiedTimeStatus==1)
	{
		m_chkLastModifiedTime.SetCheck(TRUE);
		m_dtLastModifiedTime.EnableWindow(TRUE);

	}
	else
	{
		m_dtLastModifiedTime.EnableWindow(FALSE);
		m_cmbTimeZone.EnableWindow(FALSE);

	}
	if(nIncludeFolders==1)
	{
		m_chkIncludeFoldersName.SetCheck(TRUE);
	}
	else
	{
		m_chkIncludeFoldersName.SetCheck(FALSE);
	}
	OnBnClickedChkLastModifiedTime();
}
void COfflineSiteMapDlg::UrlToIniFileName(const CString &csUrl,CString &csIniFileName)
{
	csIniFileName=csUrl;
	csIniFileName.MakeLower();
	csIniFileName.Replace("www.","");
	csIniFileName.Replace("http://","");
	csIniFileName.Replace("https://","");
	csIniFileName.Replace(".","_");
	csIniFileName=csIniFileName+".ini";

}
void COfflineSiteMapDlg::SaveSettings()
{
	CString csSettingsPath=CUtils::GetSettingsPath();
	CString csWebUrl,csFolderPath,csUrl,csLastModified,csChangeFreq,csPriority,csExcludeFolder, csExcludeFiles,csSiteMapPath;
	GetDlgItemText(IDC_ED_FOLDERPATH,csFolderPath);
	GetDlgItemText(IDC_CMB_URLS,csUrl);
	GetDlgItemText(IDC_ED_EXCLUDEFILES,csExcludeFiles);
	GetDlgItemText(IDC_ED_EXCLUDEFOLDERS,csExcludeFolder);
	GetDlgItemText(IDC_ED_SITEMAP_PATH,csSiteMapPath);
	csExcludeFolder.Replace(lpFolder,"");
	csExcludeFiles.Replace(lpFiles,"");

	int nPriorty=m_cmbPriority.GetCurSel();
	int nChangeFreq=m_cmbChangeFreq.GetCurSel();
	int nTimeZone=m_cmbTimeZone.GetCurSel();

	GetDlgItemText(IDC_CMB_CHNG_FREQ,csChangeFreq);
	if(csUrl.IsEmpty())
		return;

	UrlToIniFileName(csUrl,csWebUrl);
	CString csIniFilePath=csSettingsPath+csWebUrl;

	CUtils::SetFolderPath(csIniFilePath,csFolderPath);
	CUtils::SetUrlName(csIniFilePath,csUrl);
	CUtils::SetPriority(csIniFilePath,nPriorty);
	CUtils::SetChangeFrequency(csIniFilePath,nChangeFreq);
	CUtils::SetTimeZone(csIniFilePath,nTimeZone);
	CUtils::SetExcludeFiles(csIniFilePath,csExcludeFiles);
	CUtils::SetExcludeFolder(csIniFilePath,csExcludeFolder);
	CUtils::SetSiteMapPath(csIniFilePath,csSiteMapPath);

	if(m_chkChangeFreq.GetCheck())
		CUtils::SetChangeFrequencyStatus(csIniFilePath,1);
	else
		CUtils::SetChangeFrequencyStatus(csIniFilePath,0);


	if(m_chkLastModified.GetCheck())
		CUtils::SetLastModifiedStatus(csIniFilePath,1);
	else
		CUtils::SetLastModifiedStatus(csIniFilePath,0);

	if(m_chkLastModifiedTime.GetCheck())
		CUtils::SetLastModifiedTimeStatus(csIniFilePath,1);
	else
		CUtils::SetLastModifiedTimeStatus(csIniFilePath,0);


	if(m_chkPriority.GetCheck())
		CUtils::SetPriorityStatus(csIniFilePath,1);
	else
		CUtils::SetPriorityStatus(csIniFilePath,0);

	if(m_chkIncludeFoldersName.GetCheck())
		CUtils::SetIncludeFoldersName(csIniFilePath,1);	
	else
		CUtils::SetIncludeFoldersName(csIniFilePath,0);	

}
void COfflineSiteMapDlg::LoadUrls()
{
	CString csSettingsPath=CUtils::GetSettingsPath();
	CStringArray csFileArray;
	CUtils::GetAllFiles(csSettingsPath,csFileArray);
	for(int nFile=0;nFile<csFileArray.GetCount();++nFile)
	{
		CString csUrl= CUtils::GetUrlName(csFileArray.GetAt(nFile));
		m_cmbUrl.AddString(csUrl);
	}
}


void COfflineSiteMapDlg::OnEnSetfocusEdExcludefolders()
{
	CString csTxt;
	m_edExcludeFolders.GetWindowText(csTxt);
	csTxt.Replace(lpFolder,"");
	m_edExcludeFolders.SetWindowText(csTxt);
}

void COfflineSiteMapDlg::OnEnSetfocusEdExcludefiles()
{
	CString csTxt;
	m_edExcludeFiles.GetWindowText(csTxt);
	csTxt.Replace(lpFiles,"");
	m_edExcludeFiles.SetWindowText(csTxt);
}

void COfflineSiteMapDlg::OnEnKillfocusEdExcludefiles()
{
	CString csTxt;
	m_edExcludeFiles.GetWindowText(csTxt);
	if(csTxt.IsEmpty())
	{
		m_edExcludeFiles.SetWindowText(lpFiles);
	}
}

void COfflineSiteMapDlg::OnEnKillfocusEdExcludefolders()
{
	CString csTxt;
	m_edExcludeFolders.GetWindowText(csTxt);
	if(csTxt.IsEmpty())
		m_edExcludeFolders.SetWindowText(lpFolder);
}


void COfflineSiteMapDlg::OnBnClickedChkLastModifiedDate()
{
	if(m_chkLastModified.GetCheck())
	{
		m_DTLastModified.EnableWindow(TRUE);
		m_chkLastModifiedTime.EnableWindow(TRUE);
		OnBnClickedChkLastModifiedTime();
	}
	else
	{

		m_DTLastModified.EnableWindow(FALSE);
		m_chkLastModifiedTime.EnableWindow(FALSE);
		OnBnClickedChkLastModifiedTime();
	}
}

void COfflineSiteMapDlg::OnBnClickedChkLastModifiedTime()
{
	if(m_chkLastModifiedTime.GetCheck() && m_chkLastModifiedTime.IsWindowEnabled())
	{
		m_dtLastModifiedTime.EnableWindow(TRUE);
		EnableControl(IDC_RD_CURRENTTIME);
		EnableControl(IDC_RD_TIME);
		m_cmbTimeZone.EnableWindow(TRUE);

		OnBnClickedRdCurrenttime();


	}
	else
	{

		m_dtLastModifiedTime.EnableWindow(FALSE);
		EnableControl(IDC_RD_CURRENTTIME,FALSE);
		EnableControl(IDC_RD_TIME,FALSE);

		m_cmbTimeZone.EnableWindow(FALSE);

	}
	//	//-12,-11,-10,-9:30,-9,-8,-7,-6,-5,-4:30,-4,-3:30,-3,-2,-1,0,1,2,3,3:30,4,4:30,5,5:30,5:45,6,6:30,7,8,8:45,9,9:30,10,10:30,11,11:30,12,12:45,13,14
}


void COfflineSiteMapDlg::OnBnClickedRdTime()
{	
	m_dtLastModifiedTime.EnableWindow();
}

void COfflineSiteMapDlg::OnBnClickedRdCurrenttime()
{
	CheckRadioButton(IDC_RD_CURRENTTIME,IDC_RD_TIME,IDC_RD_CURRENTTIME);
	m_dtLastModifiedTime.EnableWindow(FALSE);
}
void COfflineSiteMapDlg::EnableControl( int nControlID, BOOL bEnable )
{
	CWnd* wndctrl = (CWnd*)( GetDlgItem( nControlID ) );
	if( wndctrl != NULL ) 
	{
		wndctrl->EnableWindow( bEnable ) ;
	}
}
void COfflineSiteMapDlg::AddTimeZones()
{
	m_cmbTimeZone.AddString("UTC-12:00");
	m_cmbTimeZone.AddString("UTC-11:00");
	m_cmbTimeZone.AddString("UTC-10:00");
	m_cmbTimeZone.AddString("UTC-09:30");
	m_cmbTimeZone.AddString("UTC-09:00");
	m_cmbTimeZone.AddString("UTC-08:00");
	m_cmbTimeZone.AddString("UTC-07:00");
	m_cmbTimeZone.AddString("UTC-06:00");
	m_cmbTimeZone.AddString("UTC-05:00");
	m_cmbTimeZone.AddString("UTC-04:30");
	m_cmbTimeZone.AddString("UTC-04:00");
	m_cmbTimeZone.AddString("UTC-03:30");
	m_cmbTimeZone.AddString("UTC-03:00");
	m_cmbTimeZone.AddString("UTC-02:00");
	m_cmbTimeZone.AddString("UTC-01:00");
	m_cmbTimeZone.AddString("UTC+00:00");
	m_cmbTimeZone.AddString("UTC+01:00");
	m_cmbTimeZone.AddString("UTC+02:00");
	m_cmbTimeZone.AddString("UTC+03:00");
	m_cmbTimeZone.AddString("UTC+03:30");
	m_cmbTimeZone.AddString("UTC+04:00");
	m_cmbTimeZone.AddString("UTC+04:30");
	m_cmbTimeZone.AddString("UTC+05:00");
	m_cmbTimeZone.AddString("UTC+05:30");
	m_cmbTimeZone.AddString("UTC+05:45");
	m_cmbTimeZone.AddString("UTC+06:00");
	m_cmbTimeZone.AddString("UTC+06:30");
	m_cmbTimeZone.AddString("UTC+07:00");
	m_cmbTimeZone.AddString("UTC+08:00");
	m_cmbTimeZone.AddString("UTC+08:45");
	m_cmbTimeZone.AddString("UTC+09:00");
	m_cmbTimeZone.AddString("UTC+09:30");
	m_cmbTimeZone.AddString("UTC+10:00");
	m_cmbTimeZone.AddString("UTC+10:30");
	m_cmbTimeZone.AddString("UTC+11:00");
	m_cmbTimeZone.AddString("UTC+11:30");
	m_cmbTimeZone.AddString("UTC+12:00");
	m_cmbTimeZone.AddString("UTC+12:45");
	m_cmbTimeZone.AddString("UTC+13:00");
	m_cmbTimeZone.AddString("UTC+14:00");

}

void COfflineSiteMapDlg::OnBnClickedBtnDelSettings()
{
	CString csSettingsPath=CUtils::GetSettingsPath();
	CString csUrl;
	int nSel=0;
	nSel=	m_cmbUrl.GetCurSel();
	if(nSel>=0)
	{
		m_cmbUrl.GetLBText(nSel,csUrl);
	}
	if(csUrl.IsEmpty())
	{
		GetDlgItemText(IDC_CMB_URLS,csUrl);

		return;
	}

	CString csFileName;
	UrlToIniFileName(csUrl,csFileName);
	CString csIniFilePath=csSettingsPath+csFileName;
	if(DeleteFile(csIniFilePath))
	{
		AfxMessageBox("Sucessfully deleted!!!");

	}
}

void COfflineSiteMapDlg::OnHelpAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void COfflineSiteMapDlg::OnBnClickedBtnSave()
{
	CFileDialog fileDlg(FALSE,".xml",NULL,OFN_OVERWRITEPROMPT,"Sitemap Files (*.xml)||");
	int iRet = fileDlg.DoModal();
	CString csFileName,csFilePath;
	csFilePath=fileDlg.GetPathName().MakeLower();
	if(csFilePath.Find(".xml")==-1)
	{
		csFileName = fileDlg.GetPathName()+".xml";
	}
	else
	{
		csFileName = fileDlg.GetPathName();
	}
	//CFile file;
	if(iRet == IDOK)
	{
		if(CUtils::WriteToFile(csFileName," ")==-1)
		{
			AfxMessageBox("Error! in writing the file!!!");
		}
		else
		{
			SetDlgItemText(IDC_ED_SITEMAP_PATH,csFileName);
		}
		/*file.Open(csFileName, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		ar.Close();
		file.Close();*/
	}


}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
