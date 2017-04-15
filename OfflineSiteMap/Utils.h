#pragma once
#include <vector>
using namespace std;
class CUtils
{
public:
	CUtils(void);
	~CUtils(void);
	static void GetAllFiles(LPCTSTR lpPath, CStringArray &csaFileArray);
	 static int ReadFromFile(LPCTSTR lpcFileName, CString &cContents);
	static BOOL DoesFileExist(LPCTSTR lpcFileName );
	static int WriteToFile(LPCTSTR lpcFileName, LPCTSTR lpcText);
	static int AppendToFile(LPCTSTR lpFileName, LPCTSTR lpData);
	static BOOL OpenFolderDialog(CString& csFolderPath);

	static int SplitString(const CString& input, const CString& delimiter, vector<CString>& results);
	//Settings
	static CString GetUrlName(LPCTSTR lpPath);
	static void SetUrlName(LPCTSTR lpPath,LPCTSTR lpUrl);
	static CString GetFolderPath(LPCTSTR lpPath);
	static void SetFolderPath(LPCTSTR lpPath,LPCTSTR lpFolder);
	static CString GetLastModified(LPCTSTR lpPath);
	static void SetLastModified(LPCTSTR lpPath, LPCTSTR lpLastModified);
	static int GetChangeFrequency(LPCTSTR lpPath);
	static void SetChangeFrequency(LPCTSTR lpPath,int nChangeFreq);
	static int GetPriority(LPCTSTR lpPath);
	static void SetPriority(LPCTSTR lpPath,int nPriority);
	static CString GetExcludeFolder(LPCTSTR lpPath);
	static void SetExcludeFolder(LPCTSTR lpPath,LPCTSTR lpFolder);
	static CString GetExcludeFiles(LPCTSTR lpPath);
	static void SetExcludeFiles(LPCTSTR lpPath,LPCTSTR lpFiles);
	static int GetChangeFrequencyStatus(LPCTSTR lpPath);
	static int GetLastModifiedStatus(LPCTSTR lpPath);
	static int GetPriorityStatus(LPCTSTR lpPath);
	static void SetChangeFrequencyStatus(LPCTSTR lpPath,int nStatus);
	static void SetLastModifiedStatus(LPCTSTR lpPath,int nStatus);
	static void SetPriorityStatus(LPCTSTR lpPath, int nStatus);
	static void SetTimeZone(LPCTSTR lpPath,int nChangFreq);
	static int GetTimeZone(LPCTSTR lpPath);
	static void SetLastModifiedTimeStatus(LPCTSTR lpPath,int nStatus);
	static int GetLastModifiedTimeStatus(LPCTSTR lpPath);
	static CString GetSiteMapPath(LPCTSTR lpPath);
	static void SetSiteMapPath(LPCTSTR lpPath,LPCTSTR lpSitemap);
	static int GetIncludeFoldersName(LPCTSTR lpPath);
	static void SetIncludeFoldersName(LPCTSTR lpPath, int nStatus);
	static CString GetAppDataPath();
	static CString GetSettingsPath();
	static CString  m_csAppDataPath;
	static CString  m_csSettingsPath;
};
