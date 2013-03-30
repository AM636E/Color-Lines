#pragma once
#ifndef FIELD_H
#define FIELD_H

#include <Windows.h>

#include "globals.h"

struct Square
{
	COLORREF color;
	bool	 isFilled;

	Square( ): color( 0 ), isFilled( 0 ){};
};

struct Coordinate
{
	int row, col;

	Coordinate( ): row( 0 ), col ( 0 ) {};
};

struct Direction
{
	int	plusToRow, plusToCol;

	Direction( ): plusToRow( 0 ), plusToCol( 0 ){};
	Direction( int plusToRow, int plusToCol ):
	plusToRow( plusToRow ), plusToCol( plusToCol )
	{};
};

struct CircleGroup
{
	Coordinate 	firstCircle;			// coordinates of first circle
	Direction	moveDir;	// direction to move on group
	int			countOfCircles;
	bool		isErase;
};

class Field
{
	Square				field[ NUMSQUARES ][ NUMSQUARES ];

public:

	void				Draw( HDC hDc );

	void				SetColor( int row, int col, COLORREF color ){ field[ row ][ col ].color = color; }
	void				SetIsFilled( int row, int col, bool value ){ field[ row ][ col ].isFilled = value; }
	
	Square				Get( int row, int col )const{ return field[ row ][ col ]; }

	int*				MakeWay( int fromRow, int fromCol, int destRow, int destCol );
	void				Move( HDC hDc, int fromRow, int fromCol, int destRow, int destCol );

	Coordinate			GetFirstCircle( const Coordinate& startCoordinate, const Direction& direction ) const;
	CircleGroup			GetSameColoredCircles( const Coordinate& startCoordinate )const;
	bool				EraseCircles( const CircleGroup& circleGroup );
	void				FillWithRandColors( );
};

#endif FIELD_H