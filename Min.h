#pragma once
#include "IStatistics.h"

class MinValue : public IStatistics {
public:
	MinValue() : _min{ std::numeric_limits<double>::max() } {}
	void update( double next ) override;
	double eval() override { return _min;}
	const char* name() const override { return "min";}

private:
	double _min;
};