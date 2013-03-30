#include "Field.h"

#include <cstdlib>
#include <ctime>

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wPara, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmd, int nCmdShow )
{
	WNDCLASSEX wc;
	HWND window;
	MSG message;

	static LPCSTR szAppName = { "Color Lines XP " };

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateHatchBrush( HS_DIAGCROSS, RGB( 12, 150, 255 ) );
	wc.hCursor = LoadCursor( 0, IDC_ARROW );
	wc.hIcon = LoadIcon( 0, IDI_APPLICATION );
	wc.hIconSm = LoadIcon( 0, IDI_APPLICATION );
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = szAppName;
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx( &wc );

	window = CreateWindow( 
		szAppName,
		"Color Lines XP",
		WS_OVERLAPPEDWINDOW,
		0, 0,
		( NUMSQUARES + 2 ) * ( SQUARE_SIZE + 2 ) , ( NUMSQUARES + 2 ) * ( SQUARE_SIZE + 2 ),
		0,
		0,
		hInstance,
		0 );

	ShowWindow( window, nCmdShow );

	while( GetMessage( &message, 0, 0, 0 ) )
	{
		TranslateMessage( &message );
		DispatchMessage( &message );
	}

	return message.wParam;
}

void FillWithRandColors( Field& field )
{
	srand( time( 0 ) ) ;

	int colorsAssigned = 0;

	int randRow = 0, randCol = 0, randColor = 0;

	while( colorsAssigned < 3 )
	{
		randRow = 0 + rand( ) % NUMSQUARES - 1;
		randCol = 0 + rand( ) % NUMSQUARES - 1;

		if( !field.Get( randRow, randCol ).isFilled )
		{
			randColor = 0 + rand( ) % 5;
			Color color = BLACK;
			switch( randColor )
			{
			case 0:
				color = BLUE;
				break;
			case 1:
				color = RED;
				break;
			case 2:
				color = GREEN;
				break;
			case 3:
				color = YELLOW;
				break;
			case 4 :
				color = AQUA;
			}

			field.SetColor( randRow, randCol, color );

			colorsAssigned ++;
		}
	}
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static Field field;
	HDC hDc;
	PAINTSTRUCT ps;

	static POINT from;
	static POINT to;

	static int a = 0;

	switch( message )
	{
	case WM_PAINT:
		{
			HDC mem = CreateCompatibleDC( 0 );
			hDc = BeginPaint( hWnd, &ps );

			field.Draw( hDc );

			if( a >= 2 )
			{
				int fromCol = from.x / SQUARE_SIZE - 1;
				int fromRow = from.y / SQUARE_SIZE - 1;
				int destCol = to.x / SQUARE_SIZE - 1;
				int destRow = to.y / SQUARE_SIZE - 1;

			//	if( !field.Get( fromRow, fromCol ).isFilled )
			//		return 0;

				bool isSucMove = field.Move( hDc, fromRow, fromCol, destRow, destCol );

				Coordinate coordinate;
				coordinate.row = destCol;
				coordinate.col = destRow; 
				CircleGroup cg;

				cg = field.GetSameColoredCircles( coordinate  );
				if( !field.EraseCircles( cg ) && isSucMove && 
					(
					 ( fromCol != destCol )
					 &&
					 ( fromRow != destRow )
					)
					)
				{
					field.FillWithRandColors( );
				}

				a = 0;
			}

			field.Draw( hDc );
			EndPaint( hWnd, &ps );

			break;
		}
	case WM_LBUTTONDOWN:
		{
			if( a == 0 )
			{
				from.x = LOWORD( lParam );
				from.y = HIWORD( lParam );				
			}
			else
			{
				to.x = LOWORD( lParam );
				to.y = HIWORD( lParam );

				InvalidateRect( hWnd, 0, TRUE );
			}
			a ++;
			break;
		}
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
