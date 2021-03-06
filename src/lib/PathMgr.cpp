//=============================================================================
// PathMgr
//=============================================================================
#include "stdafx.h"

namespace Gura {

//-----------------------------------------------------------------------------
// PathMgr
//-----------------------------------------------------------------------------
PathMgr::~PathMgr()
{
}

void PathMgr::Register(Environment &env, PathMgr *pPathMgr)
{
	PathMgrOwner &pathMgrOwner = env.GetGlobal()->GetPathMgrOwner();
	pathMgrOwner.push_back(pPathMgr);
}

void PathMgr::SplitFileName(const char *pathName, String *pDirName, String *pFileName)
{
	const char *p = pathName + ::strlen(pathName);
	for ( ; p > pathName; p--) {
		if (IsFileSeparator(*(p - 1))) break;
	}
	if (pDirName != nullptr) *pDirName = String(pathName, p);
	if (pFileName != nullptr) *pFileName = String(p);
}

void PathMgr::SplitBottom(const char *pathName, String *pTop, String *pBottom)
{
	const char *p = pathName + ::strlen(pathName);
	if (p > pathName && IsFileSeparator(*(p - 1))) p--;
	const char *pEnd = p;
	for ( ; p > pathName; p--) {
		if (IsFileSeparator(*(p - 1))) break;
	}
	if (pTop != nullptr) *pTop = String(pathName, p);
	if (pBottom != nullptr) *pBottom = String(p, pEnd);
}

void PathMgr::SplitExtName(const char *pathName, String *pBaseName, String *pExtName)
{
	const char *p = SeekExtName(pathName);
	if (pBaseName != nullptr) *pBaseName = String(pathName, p);
	if (pExtName != nullptr) *pExtName = String(p);
}

const char *PathMgr::SeekExtName(const char *pathName)
{
	const char *pBtm = pathName + ::strlen(pathName);
	for (const char *p = pBtm; p >= pathName; p--) {
		if (*p == '.') {
			return (p == pathName || IsFileSeparator(*(p - 1)))? pBtm : p;
		}
		if (IsFileSeparator(*p)) break;
	}
	return pBtm;
}

bool PathMgr::HasWildCard(const char *pathName)
{
	for (const char *p = pathName; *p != '\0'; p++) {
		if (IsWildCardChar(*p)) return true;
	}
	return false;
}

bool PathMgr::HasFileSeparator(const char *pathName)
{
	for (const char *p = pathName; *p != '\0'; p++) {
		if (*p == OAL::FileSeparatorWin || *p == OAL::FileSeparatorUnix) return true;
	}
	return false;
}

bool PathMgr::DoesMatchName(const char *pattern, const char *fileName, bool ignoreCaseFlag)
{
	if (*pattern == '!') {
		return !DoesMatchNameSub(pattern + 1, fileName, ignoreCaseFlag);
	}
	return DoesMatchNameSub(pattern, fileName, ignoreCaseFlag);
}
	
bool PathMgr::DoesMatchNameSub(const char *pattern, const char *fileName, bool ignoreCaseFlag)
{
	if (*pattern == '\0') {
		return *fileName == '\0';
	} else if (*pattern == '*') {
		return DoesMatchNameSub(pattern + 1, fileName, ignoreCaseFlag) ||
			(*fileName != '\0' && DoesMatchNameSub(pattern, fileName + 1, ignoreCaseFlag));
	} else if (*pattern == '?') {
		return *fileName != '\0' && DoesMatchNameSub(pattern + 1, fileName + 1, ignoreCaseFlag);
	} else if (*pattern == '[') {
		pattern++;
		if (*pattern == '!') {
			pattern++;
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (CompareChar(*fileName, *pattern, ignoreCaseFlag) == 0) return false;
			}
		} else {
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (CompareChar(*fileName, *pattern, ignoreCaseFlag) != 0) return false;
			}
		}
		if (*pattern == ']') pattern++;
		return DoesMatchNameSub(pattern, fileName + 1, ignoreCaseFlag);
	} else {
		return CompareChar(*pattern, *fileName, ignoreCaseFlag) == 0 &&
						DoesMatchNameSub(pattern + 1, fileName + 1, ignoreCaseFlag);
	}
}

PathMgr *PathMgr::FindResponsible(Environment &env,
								const Directory *pParent, const char *pathName)
{
	Signal &sig = env.GetSignal();
	PathMgrOwner &pathMgrOwner = env.GetGlobal()->GetPathMgrOwner();
	// The last-registered PathMgr is searched first.
	foreach_reverse (PathMgrOwner, ppPathMgr, pathMgrOwner) {
		PathMgr *pPathMgr = *ppPathMgr;
		if (pPathMgr->IsResponsible(env, pParent, pathName)) {
			return pPathMgr;
		}
		if (sig.IsSignalled()) break;
	}
	return nullptr;
}

bool PathMgr::DoesExist(Environment &env, const char *pathName)
{
	if (*pathName == '\0') return false;
	AutoPtr<Directory> pDirectory(Directory::Open(env, pathName, NF_NoSignal));
	return !pDirectory.IsNull();
}

bool PathMgr::IsContainer(Environment &env, const char *pathName)
{
	if (*pathName == '\0') return false;
	AutoPtr<Directory> pDirectory(Directory::Open(env, pathName, NF_NoSignal));
	return !pDirectory.IsNull() && pDirectory->IsContainer();
}

//-----------------------------------------------------------------------------
// PathMgrOwner
//-----------------------------------------------------------------------------
PathMgrOwner::~PathMgrOwner()
{
	Clear();
}

void PathMgrOwner::Clear()
{
	foreach (PathMgrOwner, ppPathMgr, *this) {
		delete *ppPathMgr;
	}
	clear();
}

}
