#pragma once
#include "IStatistics.h"

class MaxValue : public IStatistics {
public:
	MaxValue() : _max{ std::numeric_limits<double>::lowest() } {}
	void Update( double next ) override;
	double Evaluate() override { return _max; }
	const char* GetName() const override { return "max"; }

private:
	double _max;
};