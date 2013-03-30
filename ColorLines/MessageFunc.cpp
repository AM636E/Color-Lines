#include "MessageProto.h"
#include "Moves.h"

#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;

//TODO make int completely and improve bug second selection bug

enum ColorIndex
{
	I_BLUE,
	I_RED,
	I_GREEN,
	I_YELLOW,
	I_AQUA,
	I_BLACK
};

enum Color
{
	BLUE	= 0x0000FF00,	
	RED		= 0xFF000000,
	GREEN	= 0x00FF0000,
	YELLOW	= 0xFFFF0000,
	AQUA	= 0x00FFFF00,
	BLACK	= 0x00000000
};

map< ColorIndex, Color >colors;

HDC hDc;
PAINTSTRUCT ps;
static Field field;
static Square from;
static Square to;
char *bif= new char[ 100 ];

int click_counter = 0;

void OnPaint( HWND hWnd )
{	
	hDc = BeginPaint( hWnd, &ps );

	field[ 0 ][ 0 ].isFilled = true;

	field.Draw( hDc );

	EndPaint ( hWnd, &ps );
}

bool IsInRect( const POINT& point, const RECT &rect )
{
	if( (  ( point.x >= rect.left ) && ( point.y >= rect.top ) )
		&&
		( ( point.x <= rect.right ) && point.y <= rect.bottom )
		)
	{
		return true;
	}

	return false;
}

Square GetClickedSquare( const Field& field, POINT coords )
{
	for( int i = 0; i < SQUARES_X; i ++ )
	{
		for( int j = 0; j < SQUARES_Y; j ++ )
		{
			if( IsInRect( coords, field.GetSquare( i, j ) ) )
			{						
				return field.GetSquare( i, j );

				break;
			}
		}
	}
}

bool is_add_balls = true;

void MoveInField( HDC hDevice, Field &fieldToMove, const Square& from, const Square& to )
{
	int *way = GenerateWay( fieldToMove, from, to );

	if( !way )
	{
		is_add_balls = false;
		return ;
	}

	is_add_balls = true;

	if( from == to )
		is_add_balls = false;

	int i = 1;
	int size = way[ 0 ];

	int row = 0, col = 0, nextRow = 0, nextCol = 0;
	int el = 0;

	while( i < size - 1 )
	{
		el = way[ i ];
		row = el / 10;
		col = el % 10;

		el = way[ i + 1 ];
		nextRow = el / 10;
		nextCol = el % 10;

		field[ nextRow ][ nextCol ].circleColor = field[ row ][ col ].circleColor;
		field[ row ][ col ].isFilled = false;
		field[ nextRow ][ nextCol ].isFilled = true;

		fieldToMove.Draw( hDevice );

		i ++;
	}
}

void OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{	
	hDc = GetDC( hWnd );	
	srand( time( 0 ) );

	POINT pt;
	pt.x = x;
	pt.y = y;

	if( click_counter == 0 )
	{
		from = GetClickedSquare( field, pt );

		click_counter ++;
	}
	else
	{
		to = GetClickedSquare( field, pt );

		click_counter ++;
	}

	int ballsAssigned = 0;
	int randomRow = 0;
	int randomCol = 0;
	int colorIndex = 0;

	if( click_counter >= 2 )
	{			
		MoveInField( hDc, field, from, to );

		if( is_add_balls )
		{
			while( ballsAssigned < 3 && !field.IsFullyFilled( ) )
			{
				randomRow = 0 + rand( ) % 9;
				randomCol = 0 + rand( ) % 9;

				if( !field[ randomRow ][ randomCol ].isFilled )
				{
					colorIndex = 0 + rand( ) % 5;

					Color color;
					switch( colorIndex )
					{
					case 0:
						color = BLUE;
						break;
					case 1:
						color = RED;
						break;
					case 2:
						color = AQUA;
						break;
					case 3:
						color = YELLOW;
						break;
					case 4:
						color = GREEN;
						break;
					case 5:
						color = BLACK;
					}

					field[ randomRow ][ randomCol ].circleColor = color;
					field[ randomRow ][ randomCol ].isFilled = true;

					ballsAssigned ++;
				}

				field.Draw( hDc );
			}
		}
		field.Draw( hDc );

		click_counter = 0;
	}			

	ReleaseDC( hWnd, hDc );
}