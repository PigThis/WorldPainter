#pragma once
#include <windows.h>
#include <exception>
#include <string>
//通过窗口提示上一个错误
inline void ThrowLastErrorWithBox()
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, L"Error", MB_OK | MB_ICONINFORMATION);
	LocalFree(lpMsgBuf);
}
//抛出异常
inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
#if defined(_DEBUG)
		ThrowLastErrorWithBox();
#endif
		throw std::exception();
	}
}

inline std::wstring getAssetsPath(LPCWSTR assetName)
{
	WCHAR assetsPath[512];
	DWORD size = GetModuleFileName(nullptr, assetsPath, _countof(assetsPath));

	WCHAR* lastSlash = wcsrchr(assetsPath, L'\\');
	if (lastSlash)
	{
		*(lastSlash + 1) = L'\0';
	}
	std::wstring fullPathStr = assetsPath;
	return fullPathStr + assetName;
}
