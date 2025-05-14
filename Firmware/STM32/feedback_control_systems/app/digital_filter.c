/*
 * digital_filter.c
 *
 *  Created on: May 13, 2025
 *      Author: pedrobt
 */
#include <stdlib.h>
#include <stdint.h>
#include "digital_filter.h"

const double TAPS[ORDER] =
{
	-0.005498926503157899,
	0.015086909771554665,
	-0.018460113510057274,
	-0.06953871743390073,
	0.5784108476755612,
	0.5784108476755612,
	-0.06953871743390075,
	-0.018460113510057278,
	0.015086909771554665,
	-0.005498926503157899
};


void digital_filter_init(digital_filter_t *f, const int filter_order_var, const double *filter_taps)
{
	f->history = (double *)malloc((f->filter_order)*sizeof(double));

	for(uint32_t idx = 0; idx < (f->filter_order); idx++)
		f->history[idx] = 0;

	f->taps = filter_taps;
	f->filter_order = filter_order_var;
	f->last_index = 0;
}

void digital_filter_put(digital_filter_t *f, double input)
{
	f->history[f->last_index++] = input;
	if(f->last_index == f->filter_order)
		f->last_index = 0;
}

double digital_filter_get(digital_filter_t *f)
{
	double acc = 0.0;
	uint32_t index = f->last_index, i;
	for(i = 0; i < f->filter_order; i++)
	{
		index = index != 0 ? index-1 : f->filter_order-1;
		acc += f->history[index] * f->taps[i];
	};

	return acc;
}
