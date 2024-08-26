#include "Mean.h"

void MeanValue::update( double next ) {
	if ( _count == 0 ) {
		_sum = next;
		_mean = _sum;
	}
	else {
		_sum += next;
		_mean = _sum / double( _count + 1 );
	}
	_count++;
}