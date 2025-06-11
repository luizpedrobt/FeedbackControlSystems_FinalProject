/*
 * payload_composer.h
 *
 *  Created on: Jun 11, 2025
 *      Author: pedrobt
 */

#ifndef PAYLOAD_COMPOSER_H_
#define PAYLOAD_COMPOSER_H_

#define START_BYTE 0x7E
#define STOP_BYTE 0X7F

#define PAYLOAD_LENGTH (5)

#define TX_BUFF_LENGTH (1 + 1 + 5 + 1 + 1) // Start byte -> Length -> Payload -> Checksum -> Stop byte

void compose_data(uint8_t *payload, uint8_t *tx_buffer);

#endif /* PAYLOAD_COMPOSER_H_ */
