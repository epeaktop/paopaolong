//
//  StringMgr.cpp
//
//  Created by Ruoqian, Chen on 2013/08/28
//

#include "StringMgr.h"

namespace
{
static CStringMgr *s_pStringMgr = NULL;
const char *STR_RES = "ini/strRes.ini";
}

CStringMgr::CStringMgr(void)
{
	this->Reload();
}

CStringMgr::~CStringMgr(void)
{
}

CStringMgr *CStringMgr::Instance(void)
{
	if (NULL == s_pStringMgr) {
		s_pStringMgr = new CStringMgr;
	}

	return s_pStringMgr;
}

void CStringMgr::Release(void)
{
	CC_SAFE_DELETE(s_pStringMgr);
}



const char *CStringMgr::GetStr(const char *pszIndex) const
{
	if (NULL == pszIndex) {
		return "";
	}

	std::map < std::string, std::string >::const_iterator it(m_mapString.find(pszIndex));
	if (it == m_mapString.end()) {
		return "";
	}

	return it->second.c_str();
}

const CStringMgr &CStringMgr::Singleton(void)
{
	CStringMgr *pInstance = Instance();
	
	return(*pInstance);
}

