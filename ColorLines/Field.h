#pragma once

#include "Square.h"
#include "definit.h"

struct BallsGroup
{
	int beginRow, beginCol;		// coordinates of group in matrix
	int plusToRow, plusToCol;	// for direction of move in matrix
	int countOfBalls;			//count of balls int group
};

class Field
{
	Square				field[ SQUARES_X ][ SQUARES_Y ];
public:
	

	Field( );

	void				Draw( HDC hDc );

	bool				IsFullyFilled( );

	Square*				operator [ ]( int index ){ return field[ index ]; }
	Square&				GetSq( int row, int col ){ return field[ row ][ col ]; }
	Square				GetSquare( int row, int col )const { return field[ row ][ col ]; }

	BallsGroup			GetCountOfSameColorBalls( const int row, const int col );
};