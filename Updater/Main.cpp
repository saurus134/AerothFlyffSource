//#include <windows.h>
#include <stdio.h>
#include <afx.h>

//#include <afxwin.h>         // MFC core and standard components


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Aeonsoft");
LPCTSTR lpszWindowName = TEXT("Updater");
CString g_strCmdLine;

void Update();
void ErrorMsg();

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	TCHAR szArg1[64] = {0, }; 
	TCHAR szArg2[64] = {0, }; 
	TCHAR szArg3[64] = {0, }; 
	TCHAR szArg4[64] = {0, };

//	AfxMessageBox( lpszCmdParam );

	sscanf( lpszCmdParam, "%s %s %s %s", szArg1, szArg2, szArg3, szArg4 );
	if( strcmpi( szArg1, "myunglang" ) )
	{
		return 0; 
	}

	g_strCmdLine.Format("%s %s %s", szArg2, szArg3, szArg4);

	HWND hWnd;

	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszWindowName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	//ShowWindow(hWnd,nCmdShow);
	hWndMain=hWnd;
	
	while(GetMessage(&Message,0,0,0)) 
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static DWORD ProcID = 0;
	static HANDLE hProc = 0;
	DWORD ExitCode;

	switch(iMessage) 
	{
	case ( WM_USER + 2 ): // recv SEND_PROCESSID from PatchMfcClient
		ProcID = wParam;
		hProc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, ProcID );
		GetExitCodeProcess( hProc, &ExitCode );
		if( ExitCode != STILL_ACTIVE )
		{
			// 무효
			MessageBox( hWndMain, "종료시킬 핸들 없음", "에러", MB_OK );
			//SetWindowText( hWndMain, "죽었음" );
		}
		else
		{
			// 유효 - 강제 종료
			//MessageBox( hWndMain, "핸들 종료", "성공", MB_OK );
			//SetWindowText( hWndMain, "죽일것임" );
			TerminateProcess( hProc, 0 );
			//char msg[100]; wsprintf( msg, "%d", ret );
			WaitForSingleObject( hProc, INFINITE );
			Sleep(1500);
			CloseHandle( hProc );

//			MessageBox( hWndMain, "정상이다", "에러", MB_OK );
		}
		Update();
		return 0;
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

void Update()
{
	/*
	while( TRUE )
	{
		// 패치 클라이언트가 아직도 실행 중인지 알아 보기 위함
		HANDLE hPatchStopEvent = OpenEvent( EVENT_MODIFY_STATE, FALSE, "PatchStopEvent" );
		if( NULL != hPatchStopEvent )
		{
			SetEvent( hPatchStopEvent );
			Sleep( 1000 );
			continue;
		}
		else
		{
			break;
		}
	}
	*/
	
	DWORD dwFileAttributes	= GetFileAttributes( "NewFlyff.exe" );
	if( 0xFFFFFFFF != dwFileAttributes )
	{
		dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( "NewFlyff.exe", dwFileAttributes );
	}
	dwFileAttributes	= GetFileAttributes( "Flyff.exe" );
	if( 0xFFFFFFFF != dwFileAttributes )
	{
		dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( "Flyff.exe", dwFileAttributes );
	}

	// 새로 받은 패치클라이언트가 있는가
	HANDLE hNewFile = CreateFile( "NewFlyff.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( INVALID_HANDLE_VALUE == hNewFile )
	{
		ErrorMsg();
		//MessageBox( hWndMain, "NewPatchClinetn.exe 파일 없음", "에러", MB_OK );
		PostQuitMessage( 0 );
		return;
	}
	CloseHandle( hNewFile );

	// 기존 패치클라이언트는 삭제
	if( FALSE == DeleteFile( "Flyff.exe" ) )
	{
		ErrorMsg();
		MessageBox( hWndMain, "Flyff.exe", "에러", MB_OK );
		PostQuitMessage( 0 );
		return;
	}

	// 새로 받은 패치클라이언트의 파일명 변경
	if( 0 != rename( "NewFlyff.exe", "Flyff.exe" ) )
	{
		ErrorMsg();
		//MessageBox( hWndMain, "파일을 변경할 수 없습니다", "에러", MB_OK );
		PostQuitMessage( 0 );
		return;
	}

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	
	// 패치 클라이언트 재 실행
//	if( FALSE == CreateProcess( NULL, "Flyff.exe 1", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
	CString strCmd;
	strCmd.Format("Flyff.exe %s", g_strCmdLine);

//	AfxMessageBox( strCmd );

	if( FALSE == CreateProcess( NULL, strCmd.GetBuffer(0), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) )
	{
		//MessageBox( hWndMain, "Masquerade.exe 실행 못함", "에러", MB_OK );
		ErrorMsg();
		PostQuitMessage( 0 );
		return;
	}

	PostQuitMessage( 0 );
}

void ErrorMsg()
{
	char szMsg[1024];
	char szErrorMsg[1024];
	
	DWORD dwErr = GetLastError();
	
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErr, 0, szErrorMsg, 1024, NULL );
	wsprintf( szMsg, "에러코드 : %d, 메시지 : %s", dwErr, szErrorMsg );
	MessageBox( hWndMain, szMsg, "에러", MB_OK );
}