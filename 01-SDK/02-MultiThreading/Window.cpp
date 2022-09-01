// header files
#include <windows.h>

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

// global variable declarations

// Entry Point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	// code
	// WNDCLASSEX initialisation
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	// Creating the window
	hwnd = CreateWindow(
	szAppName,
	TEXT("KP : Window"),
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	NULL,
	NULL,
	hInstance,
	NULL);

	// Show window
	ShowWindow(hwnd, iCmdShow);

	// Update Window
	UpdateWindow(hwnd);

	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Local Variable Declarations
	HDC hdc;
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;
	int i;
	TCHAR str[255];


	// code

	switch (iMsg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcOne,
			(LPVOID)hwnd,
			0,
			NULL
		);
		hThreadOne = CreateThread(
			NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd,
			0,
			NULL
		);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		// PostQuitMessage(0);
		PostMessage(hwnd, WM_QUIT, 0, 0L);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID Param)
{
	// variable declarations
	HDC hdc;
	int i;
	TCHAR str[255];

	// code

	hdc = GetDC((HWND)Param);
	SetTextColor(RGB(255, 255, 0));
	
	for(i = 0; i < 32767; i++)

	return 0;

}

