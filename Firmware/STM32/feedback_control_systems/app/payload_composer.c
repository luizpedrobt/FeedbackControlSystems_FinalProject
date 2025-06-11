/*
 * payload_composer.c
 *
 *  Created on: Jun 11, 2025
 *      Author: pedrobt
 */

#include <stdint.h>
#include <string.h>
#include "payload_composer.h"
#include "checksum.h"

void compose_data(uint8_t *payload, uint8_t *tx_buffer)
{
	uint8_t chk_sum = checksum(payload, PAYLOAD_LENGTH);

	tx_buffer[0] = START_BYTE;
	tx_buffer[1] = PAYLOAD_LENGTH;
	memcpy(&tx_buffer[2], payload, PAYLOAD_LENGTH);
	tx_buffer[6] = chk_sum;
	tx_buffer[7] = STOP_BYTE;
}
