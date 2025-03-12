typedef struct	zob_hashes
{
	long	piece_hashes[64 * 6 *2];
	long	castling_hashes[16];
	long	side_hashes[2];
	long	en_passant_hashes[17];
}			zob_hashes;