#include <windows.h>
#include "winHelper.h"
#include "GameDirector.h"

LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);

//RegisterWindow
ATOM RegisterWindow(HINSTANCE hInstance)
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"WorldPainterClass";

	return RegisterClassEx(&windowClass);
}

//CreateWindow-ShowWindow-UpdateWindow
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	Director* shareDirector = Director::getInstance();
	RECT windowRect = { 0, 0, static_cast<LONG>(shareDirector->getWidth()), static_cast<LONG>(shareDirector->getHeight()) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindow(L"WorldPainterClass", shareDirector->getTitle(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		ThrowLastErrorWithBox();
		return FALSE;
	}
	shareDirector->initGameProcedure();
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_PAINT:
	{
		Director::getInstance()->onUpdate();
		Director::getInstance()->onRender();
	}
	break;
	case WM_KEYUP:
	{

	}
	break;
	case WM_KEYDOWN:
	{

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Director gameDirector(1136, 640, L"MyGame");

	RegisterWindow(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// Process any messages in the queue.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Director::getInstance()->endGame();
	return static_cast<char>(msg.wParam);;
}

