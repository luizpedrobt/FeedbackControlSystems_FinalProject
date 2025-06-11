/*
 * checksum.c
 *
 *  Created on: Jun 11, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include "checksum.h"

uint8_t checksum(uint8_t *p_buf, uint8_t length)
{
	uint8_t idx = 0;
	uint8_t chk_sum = 0;

	for(idx = 0;idx < length;idx++)
	{
		chk_sum += (*p_buf);
		p_buf++;
	}

	return chk_sum;
}
