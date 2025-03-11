#include "../include/types.h"

int	main(void)
{
	printf("sizeof(int): %d\n", sizeof(int));
	printf("sizeof(long): %d\n", sizeof(long));
	printf("sizeof(long long): %d\n", sizeof(long long));
/*
	1 bit  for check (bool)
	1 bit  for capture (bool)
	3 bits for captured piece type
	3 bits for piece type
	8 bits for to_square
	8 bits for from_square
	3 bits for promotion type
	*/

	/*
	AND-GATE   &
	1, 1 = 1
	1, 0 = 0
	0, 1 = 0
	0, 0 = 0

	OR-GATE    |
	1, 1 = 1
	1, 0 = 1
	0, 1 = 1
	0, 0 = 0

	XOR-GATE   ^
	1, 1 = 0
	1, 0 = 1
	0, 1 = 1
	0, 0 = 0
	*/
	// for (int i = 0; i < 1000000000; i++) {
	// 	int a = 0;
	// 	int b = 0;
	// 	int c = 0;
	// 	int d = 0;
	// 	int e = 0;
	// 	int f = 0;
	// 	int g = 0;
	// 	a = 5;
	// 	b = 8;
	// 	c = 7;
	// 	d = 3;
	// 	e = 1;
	// 	f = 53;
	// 	g = 60;
	// }
	// int move = 0;
	// for (int i = 0; i < 1000000000; i++) {
	// 	move = move | (1 << 0); // is check = true
	// 	move = move | (1 << 1); // is capture = true
	// 	move = move | (5 << 2); // is piece = queen
	// 	move = move | (2 << 5); // is piece = knight
	// 	move = move | (63 << 8); // is to_square
	// 	move = move | (34 << 14); // is from_square
	// 	move = move | (0 << 20); // promotion type
	// }
	// printf("Move is check: %d\n", (move >> 0) & 1);
	// printf("Move is capture: %d\n", (move >> 1) & 1);
	// printf("piece: %d\n", (move >> 2) & 7);
	// printf("piece: %d\n", (move >> 5) & 7);
	// printf("to square: %d\n", (move >> 8) & 63);
	// printf("from square: %d\n", (move >> 14) & 63);
	// printf("from square: %d\n", (move >> 20) & 7);
	// // 7 == 0111
	printf("%d\n", RELATIVESQUARE(49, 9));
}