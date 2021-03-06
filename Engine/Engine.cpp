//*****************************************************************************
//
// エンジンコアファイル [Engine.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine.h"

//*****************************************************************************
//
// local(Shift_JIS) to utf-8
//
//*****************************************************************************
string localStrToUTF8(const wstring ws)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const wchar_t* wchSrc = ws.c_str();
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	char *chDest = new char[nDestSize];
	memset(chDest, 0, nDestSize);
	wcstombs(chDest, wchSrc, nDestSize);
	std::string strResult = chDest;
	delete[]chDest;
	setlocale(LC_ALL, strLocale.c_str());
	return strResult;
}

//*****************************************************************************
//
// local(Shift_JIS) to utf-8
//
//*****************************************************************************
wstring localStrToUTF8(const string s)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const char* chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[]wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return wstrResult;
}

//*****************************************************************************
//
// utf-8
// string to wstring
//
//*****************************************************************************
wstring stringToWstring(const string s)
{
	// wchar_t文字列の長さを取得
	int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);

	// wchar_t文字列バッファを設定
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));

	// コード変更
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	
	// wchar_t文字列をwstringに入れる
	wstring wstr;
	wstr = (wchar_t*)pUnicode;

	// 臨時ポインタをリリース
	delete pUnicode;

	return wstr;
}

//*****************************************************************************
//
// utf-8
// wstring to string
//
//*****************************************************************************
string wstringToString(const wstring ws)
{
	// wchar_t文字列の長さを取得
	int utfLen = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);

	// char_t文字列バッファを設定
	char* elementText;
	elementText = new char[utfLen + 1];
	memset((void*)elementText, 0, sizeof(char)*(utfLen + 1));

	// コード変更
	WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, elementText, utfLen, NULL, NULL);

	// char文字列をstringに入れる
	string str;
	str = elementText;

	// 臨時ポインタをリリース
	delete[] elementText;

	return str;
}

//*****************************************************************************
//
// パスからファイル名を取得
//
//*****************************************************************************
wstring pathToFileName(const wstring path)
{
	wstring fileName = path.substr(path.find_last_of(L'\\') + 1, path.find_first_of(L'.'));		// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	fileName = fileName.substr(0, fileName.find_first_of(L'.'));								// exp: ccc.fbx -> ccc

	return fileName;
}