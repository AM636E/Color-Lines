#include "Square.h"

void Square::Draw( HDC hDc )
{
	Rectangle( hDc, x, y, x + width, y + height );

	if( isFilled )
	{
		HBRUSH old = ( HBRUSH )SelectObject( hDc, CreateSolidBrush( circleColor ) );

		Ellipse( hDc, x, y, x + width, y + height );

		DeleteObject( SelectObject( hDc, old ) );
	}
}