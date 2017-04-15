#include "StdAfx.h"
#include "SiteMap.h"
#include "Utils.h"

LPCTSTR g_SiteMapTemplate="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n <urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\"> URLS \r\n</urlset> ";
LPCTSTR g_SiteMapHeader="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\r\n<!-- created with smart offline Sitemap Generator www.smartpricedeal.com -->\r\n";
LPCTSTR g_SiteMapFooter="</urlset>";

CSiteMap::CSiteMap(void)
{
}

CSiteMap::~CSiteMap(void)
{
}
BOOL CSiteMap::GenerateSiteMap(const stSiteMapInfo &stSiteMapObj)
{
	if(stSiteMapObj.csSiteMapPath.IsEmpty())
	{
		m_csSiteMapFilePath=CUtils::GetAppDataPath()+"sitemap.xml";
	}
	else
	{
		m_csSiteMapFilePath=stSiteMapObj.csSiteMapPath;
	}
	//"C:\\Users\\Admin\\AppData\\Local\\WebPageScrapper1.0\\sitemap.xml";

	BOOL bRet=FALSE;
	m_stSiteMapInfo=stSiteMapObj;
	if(!CreateSiteMapFile())
		return FALSE;

	CUtils::SplitString(stSiteMapObj.csExcludeFiles,",",m_vecExcludeFile);
	CUtils::SplitString(stSiteMapObj.csExcludeFolder,",",m_vecExcludeFolder);
	AddFolderSlash();
	WriteHeader();

	//For Home page
	SetFilePath(m_stSiteMapInfo.csLocalFolderPath);

	GetAllFiles(m_stSiteMapInfo.csLocalFolderPath);
	WriteFooter();
	CloseSiteMap();
	bRet=TRUE;
	return bRet;
}

BOOL CSiteMap::WriteHeader()
{
	BOOL bRet=FALSE;
	bRet =AppendSiteMap(g_SiteMapHeader);
	return bRet;
}
BOOL CSiteMap::WriteFooter()
{
	BOOL bRet=FALSE;

	bRet =AppendSiteMap(g_SiteMapFooter);
	return bRet;
}
void CSiteMap::GetAllFiles(LPCTSTR lpPath)
{
	CFileFind finder;

	// build a string with wildcards
	CString strWildcard(lpPath);
	strWildcard += _T("\\*.*");

	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		// skip . and .. files; otherwise, we'd
		// recur infinitely!

		if (finder.IsDots())
			continue;

		// if it's a directory, recursively search it

		if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			if(IsFolderInExcludeList(str))
				continue;
			if(m_stSiteMapInfo.bIncludeFolderNames)
				SetFilePath(str);
			
			GetAllFiles(str);
		}
		else
		{
			CString str = finder.GetFilePath();
			if(IsFileInExcludeList(str))
				continue;
			SetFilePath(str);
		}
	}

	finder.Close();
}
void CSiteMap::SetFilePath(LPCTSTR lpFilePath)
{
	CString csFilePath=lpFilePath;
	csFilePath.Replace(m_stSiteMapInfo.csLocalFolderPath,m_stSiteMapInfo.csUrl);
	csFilePath.Replace("\\","/");

	CString csXML=" <url>\r\n";
	csXML=csXML+"  <loc>"+csFilePath+"</loc>\r\n";
	if(!m_stSiteMapInfo.csLastmod.IsEmpty())
	{
		csXML=csXML+ "  <lastmod>"+m_stSiteMapInfo.csLastmod+"</lastmod>\r\n";
	}
	if(!m_stSiteMapInfo.csChangefreq.IsEmpty())
	{
		csXML=csXML+ "  <changefreq>"+m_stSiteMapInfo.csChangefreq+"</changefreq>\r\n";
	}
	if(!m_stSiteMapInfo.csPriority.IsEmpty())
	{
		csXML=csXML+ "   <priority>"+m_stSiteMapInfo.csPriority+"</priority>\r\n";
	}
	csXML=csXML+" </url>\r\n";
	AppendSiteMap(csXML);

	//<url>

	//     <loc>http://www.example.com/</loc>

	//     <lastmod>2005-01-01</lastmod>

	//     <changefreq>monthly</changefreq>

	//     <priority>0.8</priority>

	//  </url>

}
int CSiteMap::CreateSiteMapFile()
{
	try
	{
		if(!m_cf.Open(m_csSiteMapFilePath,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite, &m_cfe))
		{
			return 0;
		}

	}
	catch(CFileException *ce)
	{
		ce->Delete();
		m_cf.Close();

		return -1;
	}

	return 1;
}
int CSiteMap::AppendSiteMap(LPCTSTR lpcText)
{

	if(!lpcText || lpcText[0]=='\0') return -1;

	try
	{
		m_cf.Write(lpcText, lstrlen(lpcText) );

	}
	catch(CFileException *ce)
	{
		ce->Delete();
		m_cf.Close();

		return -1;
	}	
	return 1;
}
int CSiteMap::CloseSiteMap()
{
	try
	{
		m_cf.Close();

	}
	catch(CFileException *ce)
	{
		ce->Delete();
		m_cf.Close();		
		return -1;
	}	
	return 1;
}
BOOL CSiteMap::IsFolderInExcludeList(const CString &csFolderPath)
{
	CString csFolder(csFolderPath);
	if(csFolder.GetAt(csFolder.GetLength()-1)!='\\')
	{
		csFolder=csFolder+"\\";
	}
	CString csLocalFolder(m_stSiteMapInfo.csLocalFolderPath);
	if(!csLocalFolder.IsEmpty())
	{
		if(csLocalFolder.GetAt(csLocalFolder.GetLength()-1)=='\\')
		{
			csLocalFolder	=	csLocalFolder.Left(csLocalFolder.GetLength()-1);
		}
	}

	csFolder.Replace(csLocalFolder,"");
	vector<CString>::iterator iter;
	for(iter=m_vecExcludeFolder.begin();iter!=m_vecExcludeFolder.end();++iter)
	{
		if(csFolder.Find(*iter)>-1)
		{
			return TRUE;
		}
	}

	return FALSE;
}
BOOL CSiteMap::IsFileInExcludeList(const CString &csFilePath)
{
	int nPos=-1;
	CString csFile(csFilePath);
	csFile.Replace(m_stSiteMapInfo.csLocalFolderPath,"");
	vector<CString>::iterator iter;
	for(iter=m_vecExcludeFile.begin();iter!=m_vecExcludeFile.end();++iter)
	{
		if(csFile.Find(*iter)>-1)
		{
			return TRUE;
		}
		else if( (nPos=iter->Find('*'))>-1)
		{
			CString csFileName(*iter);
			if(nPos==0)
			{
				csFileName=csFileName.Mid(nPos+_tcslen("*"));
			}
			else
			{
				csFileName=csFileName.Left(nPos);
			}

			if(csFile.Find(csFileName)>-1)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}
void CSiteMap::AddFolderSlash()
{
	vector<CString>::iterator iter;
	for(iter=m_vecExcludeFolder.begin();iter!=m_vecExcludeFolder.end();++iter)
	{
		if(iter->IsEmpty())
			continue;
		if(iter->GetAt(0)!='\\')
		{
			*iter="\\"+*iter;
		}
		if(iter->GetAt(iter->GetLength()-1)!='\\')
		{
			*iter=*iter+"\\";
		}
	}
}