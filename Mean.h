#pragma once
#include "IStatistics.h"

class MeanValue : public IStatistics {
public:
	MeanValue() : _mean{ 0 }, _sum{ 0 },_count{ 0 } {}
	void Update( double next ) override;
	double Evaluate() override { return _mean; }
	const char* GetName() const override { return "_mean"; }

private:
	double _mean;
	double _sum;
	size_t _count;
};