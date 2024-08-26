#pragma once
#include "IStatistics.h"

class MeanValue : public IStatistics {
public:
	MeanValue() : _mean{ 0 }, _sum{ 0 },_count{ 0 } {}
	void update( double next ) override;
	double eval() override { return _mean; }
	const char* name() const override { return "_mean"; }

private:
	double _mean;
	double _sum;
	size_t _count;
};