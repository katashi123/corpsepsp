#ifndef __LZSS_H
#define __LZSS_H

#include "types.h"

#define N		 4096	/* size of ring buffer */
#define F		   16	/* upper limit for match_length */
//16 for Corpse Party variant
#define THRESHOLD	2   /* encode string into position and length
						   if match_length is greater than this */
#define NIL			N	/* index for root of binary search trees */

int LzssEncode(u8* &dest, u8* src, int src_size);
int LzssDecode(u8* &dest, u8* src, int src_size);

#endif	// __LZSS_H
