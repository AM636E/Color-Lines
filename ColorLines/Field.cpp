#include "Field.h"
#include "Moves.h"

Field::Field( )
{
	int x = 0, y = 0;
	for( int i = 0; i < SQUARES_X ; i ++ )
	{
		y = 0;
		for( int j = 0; j < SQUARES_Y ; j ++ )
		{
			field[ i ][ j ].x = x;
			field[ i ][ j ].y = y;

			field[ i ][ j ].height = SIZE_X;
			field[ i ][ j ].width = SIZE_Y;

			y += SIZE_Y;
		}

		x += SIZE_X;
	}
}

void Field::Draw( HDC hDc )
{
	for( int i = 0; i < SQUARES_X; i ++ )
	{
		for( int j = 0; j < SQUARES_Y; j ++ )
		{
			field[ i ][ j ].Draw( hDc );
		}
		writeArray( FormLabirintFromField( *this ) );
	}
}

bool Field::IsFullyFilled( )
{
	for( int i = 0; i < SQUARES_X; i ++ )
	{
		for( int j = 0; j < SQUARES_Y; j ++ )
		{
			if( !field[ i ][ j ].isFilled )
				return false;
		}
	}

	return true;
}

BallsGroup Field::GetCountOfSameColorBalls( const int row, const int col )
{
	BallsGroup result;
	int count = 0;
	int nextCount = 0;
	
	int cRow = row;
	int cCol = col;//copy row and col for using

	int plusToRow = 0;
	int plusToCol = 0;//for knowing direction

	bool finded = 0;

	while( field[ row ][ col ].circleColor == field [ cRow -- ][ cCol ].circleColor )
	{
		plusToRow = 1;
		plusToCol = 0;

		count ++;
	}
	int beginRow = row;
	int beginCol = col;
	while( field[ row ][ col ].circleColor == field [ cRow ++ ][ cCol ].circleColor )
	{
		count ++;
	}

	if( count >= 5 )
	{
		result.beginRow = beginRow;
		result.beginCol = beginCol;
		result.plusToRow = plusToRow;
		result.plusToCol = plusToCol;
		result.countOfBalls = count;
	}

	return result;
}

