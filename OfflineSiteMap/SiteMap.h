#pragma once
#include <vector>
using namespace std;
struct stSiteMapInfo
{
	BOOL bIncludeFolderNames;
	CString csUrl;
	CString csLocalFolderPath;	
	CString csLastmod;
	CString csChangefreq;
	CString csPriority;
	CString csExcludeFolder;
	CString csExcludeFiles;
	CString csSiteMapPath;
	stSiteMapInfo()
	{
		bIncludeFolderNames=FALSE;
	}

};

class CSiteMap
{
public:
	CSiteMap(void);
	~CSiteMap(void);
	BOOL GenerateSiteMap(const stSiteMapInfo &stSiteMapObj);
private:
	BOOL WriteHeader();
	BOOL WriteFooter();
	void GetAllFiles(LPCTSTR lpPath);
	void SetFilePath(LPCTSTR lpFilePath);
	int CreateSiteMapFile();
	int AppendSiteMap(LPCTSTR lpcText);
	int CloseSiteMap();
	void AddFolderSlash();
	BOOL IsFileInExcludeList(const CString &csFilePath);
	BOOL IsFolderInExcludeList(const CString &csFolderPath);
	stSiteMapInfo m_stSiteMapInfo;
	CString m_csSiteMapFilePath;
	CString m_csSiteMapFileContent;


	vector<CString> m_vecExcludeFile;
	vector<CString> m_vecExcludeFolder;
	CFile m_cf;
	CFileException m_cfe;
};
