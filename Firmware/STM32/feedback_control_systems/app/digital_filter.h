/*
 * digital_filter.h
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */

#ifndef DIGITAL_FILTER_H_
#define DIGITAL_FILTER_H_

#define ORDER 10

typedef struct digital_filter_s
{
	double *history;
	const double *taps;
	uint32_t last_index;
	uint32_t filter_order;
}digital_filter_t;

/**
 * @brief Initializes a digital filter with a defined order and taps
 * @param [in] f pointer to digital filter struct
 * @param [in] filter_order_var filter order
 * @param [in] filter_taps pointer to taps array
 * */
void digital_filter_init(digital_filter_t *f, const int filter_order_var, const double *filter_taps);

/**
 * @brief Computes the algorithm of the digital filter with a defined value
 * @param [in] f pointer to digital filter struct
 * @param [in] input value of the adc raeading
 * */
void digital_filter_put(digital_filter_t *f, double input);

/**
 * @brief Returns the value of the filtered signal
 * @param [in] f pointer to digital filter struct
 * @returns The value of the signal after the filter
 * */
double digital_filter_get(digital_filter_t *f);

#endif /* DIGITAL_FILTER_H_ */
