#include "Max.h"

void MaxValue::Update( double next ) {	
	if ( next > _max )
		_max = next;
}