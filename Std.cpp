#include"Std.h"

double StdValue::eval() {
	size_t size = _data.size();
	double m_step_sum = 0;

	for ( size_t i = 0; i < size; ++i )
		m_step_sum += pow( _data[i] - _mean, 2 );

	if ( size > 0 )
	  _std = sqrt( m_step_sum / double(size) );

	return _std;

}