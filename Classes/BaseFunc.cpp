//
//  BaseFunc.cpp
//
//  Created by Ruoqian, Chen on 2013/07/11
//


#include "StringMgr.h"
#include "BaseFunc.h"
#include "BaseDef.h"
#include <iostream>
#include <map>
const char *DOC_EXT = ".data";



std::vector<std::string> StringSplit(const char *pszStr, char cSep)
{
	std::vector<std::string> vecRet;
	if (NULL == pszStr) {
		return vecRet;
	}

	std::string str = pszStr ? pszStr : "";
	std::string::size_type stEnd = 0;
	std::string::size_type stBegin = 0;
	while (true) {
		stBegin = str.find_first_not_of(cSep, stEnd);
		if (std::string::npos == stBegin) {
			return vecRet;
		}

		stEnd = str.find_first_of(cSep, stBegin);
		vecRet.push_back(str.substr(stBegin, stEnd - stBegin));

		if (stEnd == std::string::npos) {
			return vecRet;
		}
	}
}

std::vector<int> StringSplitInt(const char *pszStr, char cSep)
{
	auto vecStr = StringSplit(pszStr, cSep);
	std::vector<int> vecRet;
	for (auto itStr(vecStr.begin()); itStr != vecStr.end(); ++itStr) {
		int nData = 0;
		if (1 == sscanf(itStr->c_str(), "%d", &nData)) {
			vecRet.push_back(nData);
		}
	}

	return vecRet;
}

std::string ReplaceString(const char *pszOrg, const char *pszOld, const char *pszNew)
{
	const std::string strOrg = pszOrg ? pszOrg : "";
	if (NULL == pszOld || pszOld[0] == 0) {
		return strOrg;
	}

	int nModelLength = strlen(pszOld);
	std::string::size_type stBegin = 0;
	std::string::size_type stFind = 0;

	std::string strRet;
	while (true) {
		stFind = strOrg.find(pszOld, stBegin);
		if (std::string::npos == stFind) {
			strRet += strOrg.substr(stBegin);
			return strRet;
		}

		if (stFind > stBegin) {
			strRet += strOrg.substr(stBegin, stFind - stBegin);
		}

		if (pszNew && pszNew[0]) {
			strRet += pszNew;
		}

		stBegin = stFind + nModelLength;
	}
}

void ReplaceStdString(std::string &str, const std::string &strSrc, const std::string &strDest)
{
	str = ReplaceString(str.c_str(), strSrc.c_str(), strDest.c_str());
}

void TestReplaceString(void)
{
	std::string strRet;
	strRet = ReplaceString(NULL, NULL, "test");
	strRet = ReplaceString("aa", "a", "aa");
	strRet = ReplaceString("abba", "ab", "a");
	strRet = ReplaceString("abc\\n", "\\n", "\n");
}

bool GetLineFromData(char* szBuf, int nBufSize, unsigned char*& pPos, unsigned char *pData, int nDataSize)
{
	unsigned char *pDataEnd = pData + nDataSize;
	if (pPos >= pDataEnd) {
		return false;
	}

	int i = 0;
	for (; i < nBufSize && pPos < pDataEnd; ++i, ++pPos) {
		szBuf[i] = *pPos;
		if (*pPos == '\n') {
			break;
		}
	}

	for (; pPos < pDataEnd && *pPos != '\n'; ++pPos);
	if (i == nBufSize) {
		--i;
	}

	szBuf[i] = 0;
	++pPos;
	return true;
}


std::string Value2Str( long long i64Value )
{
	char szTmp[32] = { 0 };
#ifdef WIN32
	sprintf(szTmp, "%I64d", i64Value);
#else
	sprintf(szTmp, "%lld", i64Value);
#endif
	const int PART_LENTH = 3;
	int nOrgLength = strlen(szTmp);
	int nSeps = (nOrgLength - 1) / PART_LENTH;
	int nNewLength = nOrgLength + nSeps;
	int nFillTag = PART_LENTH;
	--nNewLength;
	--nOrgLength;
	while (nNewLength >= 0) {
		if (!nFillTag) {
			nFillTag = PART_LENTH;
			szTmp[nNewLength--] = ',';
			continue;
		}

		--nFillTag;
		szTmp[nNewLength--] = szTmp[nOrgLength--];
	}

	return std::string(szTmp);
}

void TestValue2Str( void )
{
	std::string strRet;
	strRet = Value2Str(0);
	strRet = Value2Str(1);
	strRet = Value2Str(12);
	strRet = Value2Str(123);
	strRet = Value2Str(1234);
	strRet = Value2Str(12345);
	strRet = Value2Str(123456);
	strRet = Value2Str(1234567);
	strRet = Value2Str(12345678);
	strRet = Value2Str(9223372036854775807);
}

std::string UTF8ToAnsi(const std::string &strIn)
{
	std::string strOut;

#ifdef  WIN32
	WCHAR *strSrc = NULL;
	char* szRes = NULL;
	int i = MultiByteToWideChar(CP_UTF8, 0, strIn.c_str(), -1, NULL, 0);

	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, strIn.c_str(), -1, strSrc, i);

	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);

	szRes = new char[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	strOut = szRes;

	delete[] strSrc;
	delete[] szRes;
#else
	strOut = strIn;
#endif

	return strOut;
}

void MyTrace(const char* pszFormat, ... )
{
	char szExtraMsg[1024];
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szExtraMsg, sizeof(szExtraMsg), pszFormat, ap);
	va_end(ap);
	
	szExtraMsg[sizeof(szExtraMsg) - 1] = 0;

	
}

void ConTrace( const char *pszFormat, ... )
{
	char szExtraMsg[1024];
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szExtraMsg, sizeof(szExtraMsg), pszFormat, ap);
	va_end(ap);
	
	szExtraMsg[sizeof(szExtraMsg) - 1] = 0;
	std::string strInfo = szExtraMsg;

#if WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut) {
		DWORD dwTmp = 0;
		WriteConsole(hOut, strInfo.c_str(), strInfo.length(), &dwTmp, NULL);
	} else {
		//OutputDebugString(strInfo.c_str());
	}
#else
	//Log("%s", strInfo.c_str());
#endif
}


void LogIntVec( const std::vector<int>& rVec, const char* pszFormat, ... )
{
	char szExtraMsg[1024];
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szExtraMsg, sizeof(szExtraMsg), pszFormat, ap);
	va_end(ap);
	
	szExtraMsg[sizeof(szExtraMsg) - 1] = 0;
	int nSize = rVec.size();
	MyTrace("----- \n %s Vec size %d", szExtraMsg, nSize);
	for (int i = 0; i < nSize; ++i) {
		MyTrace("%d ", rVec[i]);
	}
	//OutputDebugString("\n");
}

bool IsTouchInNode( cocos2d::Node *pNode, cocos2d::Touch *touch )
{
	if (NULL == pNode) {
		return false;
	}

    auto pt = pNode->convertTouchToNodeSpace(touch);
	cocos2d::Size size = pNode->getContentSize();
	cocos2d::Rect rect(0, 0, size.width, size.height);
	return rect.containsPoint(pt);
}

void SetAllChildCascadeOpacityEnabled(cocos2d::Node* pNode, bool able)
{

}





void MyTrim( std::string& str )
{
	int nBegin = 0;
	int nEnd = str.length();

	if (nEnd == 0) {
		return;
	}

	bool bFind = false;
	for (; nBegin < nEnd; ++nBegin) {
		switch (str[nBegin])
		{
		case '\r':
		case '\n':
		case '\t':
		case ' ':
			break;
		default:
			bFind = true;
			break;
		}

		if (bFind) {
			break;
		}
	}

	bFind = false;

	for (--nEnd; nEnd > nBegin; --nEnd) {
		switch (str[nEnd])
		{
		case '\r':
		case '\n':
		case '\t':
		case ' ':
			break;
		default:
			bFind = true;
			break;
		}

		if (bFind) {
			break;
		}
	}

	str = str.substr(nBegin, nEnd - nBegin + 1);
}





int GetDateValue( void )
{
    time_t tTime;
    time(&tTime);
    struct tm *pTime  = localtime(&tTime);
	int nValue = (pTime->tm_year + 1900) * 10000 + (pTime->tm_mon + 1) * 100 + pTime->tm_mday;
    return nValue;
}

int MyCeil( double dValue )
{
	double dRet = ceil(dValue);
	return (int) dRet;
}

int MyFloor( double dValue )
{
	double dRet = floor(dValue);
	return (int) dRet;
}

long long MyFloorLL( double dValue )
{
	double dRet = floor(dValue);
	return (long long) dRet;
}

int MyRound( double dValue )
{
	double dRet = floor(dValue + 0.5);
	return (int) dRet;
}

int CmpFloat( float fValue1, float fValue2 )
{
	const float FLOAT_EPSILON = 0.0001f; 
	if (fabs(fValue1 - fValue2) < FLOAT_EPSILON) {
		return 0;
	}

	if (fValue1 < fValue2) {
		return -1;
	}

	if (fValue1 > fValue2) {
		return 1;
	}

	return 0;
}



void ConTraceLn( const char *pszFormat, ... )
{
	char szExtraMsg[1024];
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szExtraMsg, sizeof(szExtraMsg), pszFormat, ap);
	va_end(ap);

	szExtraMsg[sizeof(szExtraMsg) - 1] = 0;

	char *pLE = strstr(szExtraMsg, "\n");
#ifndef WIN32
	if (pLE) {
		*pLE = ' ';
	}
#endif
	
	std::string strInfo = szExtraMsg;

#if WIN32 && !FIGHT_PREDICT_DEBUG
	if (NULL == pLE) {
		strInfo += "\n";
	}

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut) {
		DWORD dwTmp = 0;
		WriteConsole(hOut, strInfo.c_str(), strInfo.length(), &dwTmp, NULL);
	} else {
		//OutputDebugString(strInfo.c_str());
	}
#else
	//Log("%s", strInfo.c_str());
#endif
}



void GetNodeAllChild( CCNode *pNode, std::vector<CCNode*>& rVecNodeChild )
{

}

void TestMyTrim( void )
{



}

float GetKeyFrameTime( int nKeyFrame )
{
	return (nKeyFrame - 1) / 24.0f;
}

float GetKeyFrameInterval( int nKeyFrameBegin, int nKeyFrameEnd )
{
	return (nKeyFrameEnd - nKeyFrameBegin) / 24.0f;
}

std::string SimNewParagraphTab(const char *pszFont, int nFontSize)
{
	const char *pszTab = g_objStrMgr.GetStr("STR_NEW_PARAGRAPH_TAB");
	auto* pLabelTab = CCLabelTTF::create(pszTab, pszFont, nFontSize);
	float fWidthTab = pLabelTab ? pLabelTab->getContentSize().width : 0;
	
	const char *pszFill = " ";
	auto* pLabelFill = CCLabelTTF::create(pszFill, pszFont, nFontSize);
	float fWidthFill = pLabelFill ? pLabelFill->getContentSize().width : 0;

	std::string strFill;
	if (fWidthFill > 0) {
		int nCount = MyRound(fWidthTab / fWidthFill);
		strFill = std::string(nCount, pszFill[0]);
	}
	
	return strFill;
}

std::string GetObjType( CCObject* pObj )
{
	std::string strType = typeid(*pObj).name();
	ReplaceStdString(strType, "class ", "");
	ReplaceStdString(strType, "eb::", "");
	ReplaceStdString(strType, "cmwar::", "");
	return strType;
}

void NodeSetText( CCLabelTTF* pNode, int nValue, bool bShowZero /*= true*/, bool bNeedSign /*= false*/ )
{
	if (NULL == pNode) {
		return;
	}

	if (!nValue && !bShowZero) {
		pNode->setString("");
		return;
	}

	if (nValue > 0 && bNeedSign) {
		auto* pStr = CCString::createWithFormat("+%d", nValue);
		pNode->setString(pStr->getCString());
		return;
	}

	auto* pStr = CCString::createWithFormat("%d", nValue);
	pNode->setString(pStr->getCString());
}


std::string GetImageFileName( const char *pszFileName )
{
	std::string strFileName = pszFileName ? pszFileName : "";
	std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName);
	bool bExist = CCFileUtils::sharedFileUtils()->isFileExist(strPath.c_str());
	if (!bExist) {
		auto nPos = strFileName.find_last_of('.');
		if (nPos != std::string::npos) {
			strFileName = strFileName.substr(0, nPos);
			strFileName += ".jpg";
		}
	}

	return strFileName;
}

Action* RunCommonShakeAction( Node* pNode,float fScale, float fDelay /*= 0*/)
{
	CCArray* pArrAction = CCArray::create();
    
	auto a = DelayTime::create(fDelay);
    auto b = JumpTo::create(0.3f, ccp(0, 0), 4.0f * fScale, 4.0f);
    
//	pArrAction->addObject(CCMoveTo::create(0.04, ccp(0, -4*fScale)));
//	pArrAction->addObject(CCMoveTo::create(0.08f, CCPointZero));
//	pArrAction->addObject(CCMoveTo::create(0.08f, ccp(0, -4*fScale)));
//	pArrAction->addObject(CCMoveTo::create(0.08f, CCPointZero));
    auto pSeq = Sequence::create(a, b, nullptr);
	pNode->runAction(pSeq);

	return pSeq;
}

Scale9Sprite* Scale9SpriteCreate( const char *pszName )
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszName);
	if (pFrame) {
		return Scale9Sprite::createWithSpriteFrameName(pszName);
	}

	return Scale9Sprite::create(pszName);
}

CCSprite* SpriteCreate( const char *pszName )
{
	if (NULL == pszName || pszName[0] == 0) {
		return CCSprite::create();
	}

	return CCSprite::create(pszName);
}

bool ScreenShot( const char *pszFileName )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height, kCCTexture2DPixelFormat_RGBA8888);      
	texture->setPosition(ccp(size.width/2, size.height/2));      
	texture->begin();  
	CCDirector::sharedDirector()->getRunningScene()->visit();  
	texture->end();
	return texture->saveToFile(pszFileName, kCCImageFormatJPEG);   
}
