#include <stdio.h>

void print_bitboard(long board)
{
	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 7; file >= 0; file--)
		{
			long mask = (long)1 << (63 - (rank * 8) - file);
			printf("%d ", (board & mask) != 0 ? 1 : 0);
		}
		printf("\n");
	}
}

int main(void)
{
	long board = 0;
	board = board | ((long)1 << 3);
	print_bitboard(board);
}