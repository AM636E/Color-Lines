#include "Field.h"
#include "Moves.h"

#include <ctime>

void Field::Draw( HDC hDc )
{
	int left = 0, top = 0;
	HBRUSH oldBrush = 0;

	for( int i = 0; i < NUMSQUARES; i ++ )
	{
		left = 50;
		top  += SQUARE_SIZE;

		for( int j = 0; j < NUMSQUARES; j ++ )
		{
			Rectangle(
				hDc,
				left,
				top,
				left + SQUARE_SIZE,
				top + SQUARE_SIZE
				);

			if( field[ i ][ j ].isFilled )
			{
				oldBrush = ( HBRUSH ) SelectObject( hDc, CreateSolidBrush( field[ i ][ j ].color ) );

				Ellipse(
					hDc,
					left,
					top,
					left + SQUARE_SIZE,
					top + SQUARE_SIZE
					);

				SelectObject( hDc, oldBrush );
			}

			left += SQUARE_SIZE; 
		}
	}
}

bool Field::Move( HDC hDc, int fromRow, int fromCol, int destRow, int destCol )
{
	int **labirint = FormLabirintFromField( *this );
	int *way = GenerateWayToDest( *this, fromRow + 1, fromCol + 1, destRow + 1, destCol + 1 );

	if( !way )
		return false;

	int size = way[ 0 ];
	int i = 1;
	int way_i = 0;
	int row = 0, col = 0;
	int nextRow = 0, nextCol = 0;

	for( i = 1; i < size - 1; i ++ )
	{
		way_i = way[ i ];
		row = way_i / 10;
		col = way_i % 10;

		way_i = way[ i + 1 ];

		nextRow = way_i / 10;
		nextCol = way_i % 10;

		field[ row ][ col ].isFilled = false;
		field[ nextRow ][ nextCol ].color =  field[ row ][ col ].color;

		field[ nextRow ][ nextCol ].isFilled = true;

		Draw( hDc );

		Sleep( 100 );
	}

	changes[ 3 ].row = destRow;
	changes[ 3 ].col = destCol;

	return true;
}


Coordinate Field::GetFirstCircle( const Coordinate& startCoordinate, const Direction& direction )const
{
	int col = startCoordinate.row;
	int row = startCoordinate.col;

	Coordinate result;

	while( row > 0 && col > 0 &&
		field[ startCoordinate.col ][ startCoordinate.row ].color ==
		field[ row ][ col ].color &&
		field[ row ][ col ].isFilled
		)
	{
		row -= direction.plusToRow;
		col -= direction.plusToCol;
	}
	if( field[ row ][ col ].color == field[ startCoordinate.row ][ startCoordinate.col ].color && field[ row ][ col ].isFilled )
	{
		result.row = row;
		result.col = col;

		return result;
	}
	result.row = row + direction.plusToRow;
	result.col = col + direction.plusToCol;	

	return result;
}

CircleGroup Field::GetSameColoredCircles( const Coordinate& startCoordinate )const
{
	Direction dirs[ 4 ] =
	{
		Direction( 0, 1 ), // <- WEST
		Direction( 1, 1 ), // _\| NORD_WEST
		Direction( 1, 0	), // _|_ NORD
		Direction( 1, -1 ) // _|/_ NORD_EAST
	};


	Coordinate firstCircle;

	CircleGroup result;
	result.isErase = false;

	int count = 0;
	int row = 0, col = 0;
	int i = 0;
	for( i = 0; i < 4; i ++ )
	{
		firstCircle = GetFirstCircle( startCoordinate, dirs[ i ] );

		row = firstCircle.row ;
		col = firstCircle.col ;

		count = 0;

		while( field[ firstCircle.row ][ firstCircle.col ].color ==
			field[ row ][ col ].color &&
			row >= 0 && row <= NUMSQUARES &&
			col >= 0 && col < NUMSQUARES &&
			( field[ row ][ col ].isFilled == true )
			)
		{
			row += dirs[ i ].plusToRow;
			col += dirs[ i ].plusToCol;

			count ++;
		}
		if( count >= 5 )
		{
			break;
		}
	}

	result.countOfCircles = count;
	result.firstCircle = firstCircle;
	result.isErase = ( count >= 5 ) ? true : false;
	result.moveDir = dirs[ i ];	

	return result;
}

bool Field::EraseCircles( const CircleGroup& cg )
{
	if( !cg.isErase )
		return false;

	int row = cg.firstCircle.row,
		col = cg.firstCircle.col;

	numEmptySquares += cg.countOfCircles;

	for( int i = 0; i < cg.countOfCircles; i ++ )
	{
		field[ row ][ col ].isFilled = false;

		row += cg.moveDir.plusToRow;
		col += cg.moveDir.plusToCol;
	}

	return true;
}

void Field::FillWithRandColors( )
{
	srand( time( 0 ) ) ;

	int colorsAssigned = 0;

	int randRow = 0, randCol = 0, randColor = 0;

	while( colorsAssigned < 3 && numEmptySquares >= 3 )
	{
		randRow = 0 + rand( ) % NUMSQUARES;
		randCol = 0 + rand( ) % NUMSQUARES;

		if( !field[ randRow ][ randCol ].isFilled )
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

			field[ randRow ][ randCol ].color = color;
			field[ randRow ][ randCol ].isFilled = true;

			changes[ colorsAssigned ].row = randRow;
			changes[ colorsAssigned ].col = randCol;

			colorsAssigned ++;
		}
	}

	numEmptySquares -= 3;
}