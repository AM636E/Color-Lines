#include "Moves.h"
#include <fstream>
using namespace std;

const int WALL = -1;
const int WAY = 0;

int**	FormLabirintFromField(
	const Field& field 
	)
{
	int **labirint = new int* [ NUMSQUARES + 2 ];

	for( int i = 1; i <= NUMSQUARES; i ++ )
	{
		labirint[ i ] = new int[ NUMSQUARES + 2 ];

		for( int j = 1; j <= NUMSQUARES; j ++ )
		{
			if( field.Get( i - 1, j - 1 ).isFilled )
				labirint[ i ][ j ] = WALL;
			else
				labirint[ i ][ j ] = WAY;
		}
	}

	labirint[ 0 ] = new int[ NUMSQUARES + 2 ];
	labirint[ NUMSQUARES + 1 ] = new int[ NUMSQUARES + 2 ];

	for( int i = 0; i < NUMSQUARES + 2; i ++ )
	{
		labirint[ 0 ][ i ] = WALL;
		labirint[ i ][ 0 ] = WALL;
		labirint[ NUMSQUARES + 1 ][ i ] = WALL;
		labirint[ i ][ NUMSQUARES + 1 ] = WALL;
	}

	return labirint;
}

int name = 0;

void writeArray( int **arr )
{
	char *buf = new char[ 10 ];
	//ofstream cout( strcat( buf = itoa( name ++, buf, 10 ), ".lab" ) );
	ofstream cout( "one.lab" );

	for( int i = 0; i <= SQUARES_X + 1; i ++ )
	{
		for( int j = 0; j <= SQUARES_Y + 1; j ++ )
		{
			cout << "|" << arr[ i ][ j ] << "|";
		}

		cout << endl;
	}

	cout.close( );
}
bool	FindWay(
	int **labirint,
	int startRow,
	int startCol,
	int destRow, 
	int destCol
	)
{
	if( labirint[ destRow ][ destCol ] == WALL )
		return false;

	int n = WAY + 1;

	labirint[ destRow ][ destCol ] = n;

	int count = 0;

	while( labirint[ startRow ][ startCol ] == WAY )
	{
		count = 0;
		for( int i = 1; i <= SQUARES_X ; i ++ )
		{
			for( int j = 1; j <= SQUARES_Y ; j ++ )
			{
				if( labirint[ i ][ j ] == n )
				{
					if( labirint[ i + 1 ][ j ] == WAY )
					{
						labirint[ i + 1 ][ j ] = n + 1;

						count ++;
					}

					if( labirint[ i - 1 ][ j ] == WAY )
					{
						labirint[ i - 1 ][ j ] = n + 1;

						count ++;
					}

					if( labirint[ i ][ j - 1 ] == WAY )
					{
						labirint[ i ][ j - 1 ] = n + 1;

						count ++;
					}

					if( labirint[ i ][ j + 1 ] == WAY )
					{
						labirint[ i ][ j + 1 ] = n + 1;

						count ++;
					}

				}
			}
		}

		if( count == 0 )
		{
//			writeArray( labirint );
			return false;
		}

		n ++;
	}
//	writeArray( labirint );
	return true;
}

int *	GenerateWayToDest(
	const Field& field,
	int startRow,
	int startCol,
	int destRow,
	int destCol
	)
{
	int **labirint = FormLabirintFromField( field );
	labirint[ startRow ][ startCol ] = 0;
	writeArray( labirint );
	if( !FindWay(
		labirint, 
		startRow, 
		startCol, 
		destRow, 
		destCol
		)
		)
	{
		return 0;
	}

	int size = labirint[ startRow ][ startCol ];

	int *way = new int [ size + 2 ];
	way[ 0 ] = size + 1;

	int i = 1;

	while( i < size )
	{
		while( ( labirint[ startRow ][ startCol ] - labirint[ startRow - 1 ][ startCol ] ) == 1 )
		{
			way[ i ] = startRow - 1;
			way[ i ] *= 10;
			way[ i ] += startCol - 1;

			startRow --;
			i ++;
		}
		while( ( labirint[ startRow ][ startCol ] - labirint[ startRow  ][ startCol - 1 ] ) == 1 )
		{
			way[ i ] = startRow - 1;
			way[ i ] *= 10;
			way[ i ] += startCol - 1;

			startCol --;
			i ++;
		}
		while( ( labirint[ startRow ][ startCol ] - labirint[ startRow + 1 ][ startCol ] ) == 1 )
		{
			way[ i ] = startRow - 1;
			way[ i ] *= 10;
			way[ i ] += startCol - 1;

			startRow ++;
			i ++;
		}

		while( ( labirint[ startRow ][ startCol ] - labirint[ startRow ][ startCol + 1 ] ) == 1 )
		{
			way[ i ] = startRow - 1;
			way[ i ] *= 10;
			way[ i ] += startCol - 1;

			startCol ++;
			i ++;
		}
	}

	way[ size ] = destRow - 1;
	way[ size ] *= 10;
	way[ size ] += destCol - 1;

	return way;
}

//int *	GenerateWay(
//	const Field& field,
//	const Square& start,
//	const Square& dest
//	)
//{
//	int startX = start.x / SIZE_X + 1;
//	int startY = start.y / SIZE_Y + 1;
//
//	int destX = dest.x / SIZE_X + 1;
//	int destY = dest.y / SIZE_Y + 1;
//
//	return GenerateWayToDest( field, startX, startY , destX , destY );
//}