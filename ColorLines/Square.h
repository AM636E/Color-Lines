#pragma once
#include <Windows.h>
class Square
{
public:
	bool			isFilled;
	COLORREF		circleColor;
	int				x, y;
	int				width, height;

	Square( ): isFilled( false ), circleColor( RGB( 0, 0, 0 ) ), x ( -1 ), y ( -1 ), width( 0 ), height( 0 ){}
	Square( int x, int y, int width, int height ): isFilled( false ), circleColor( RGB( 0, 0, 0 ) ), x ( x ), y ( y ), width( width ), height( height ){}

	void			Draw( HDC hDc );

	bool			operator == ( const Square& compared )const
	{
		return ( x == compared.x && y == compared.y );
	}

	operator		RECT( )
	{
		RECT rect;

		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y + height;

		return rect;
	}
};