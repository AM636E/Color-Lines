#include <WindowsX.h>
#include "MessageProto.h"
#include "Moves.h"

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

int _stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmd, int nCmdShow )
{
	WNDCLASSEX wc;
	HWND	window;
	MSG message;

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_HREDRAW | CS_VREDRAW;


	wc.lpfnWndProc = WndProc;

	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;

	wc.hbrBackground = ( HBRUSH ) GetStockObject( WHITE_BRUSH );

	wc.hCursor = LoadCursor( 0, IDC_ARROW );
	wc.hIcon = LoadIcon( 0, IDI_APPLICATION );
	wc.hIconSm = 0;

	wc.hInstance = hInstance;
	wc.lpszClassName = "Class";

	wc.lpszMenuName = 0;
	///	HANDLE_MSG( window, message, 0 );
	RegisterClassEx( &wc );

	window = CreateWindow(
		"Class",
		"Window",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		500, 500,
		0,
		0,
		hInstance, 
		0
		);

	ShowWindow( window, nCmdShow );

	while( GetMessage( &message, 0, 0, 0 ) )
	{
		TranslateMessage( &message );
		DispatchMessage( &message );
	}

	return message.wParam;
}
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	HANDLE_MSG( hWnd, WM_PAINT, OnPaint );
	HANDLE_MSG( hWnd, WM_LBUTTONDOWN, OnLButtonDown );	
	case WM_DESTROY:
		{
			PostQuitMessage( 0 );

			break;
		}
	default:
		{
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
	}

	return 0;
}