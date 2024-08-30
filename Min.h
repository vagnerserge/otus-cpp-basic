#pragma once
#include "IStatistics.h"

class MinValue : public IStatistics {
public:
	MinValue() : _min{ std::numeric_limits<double>::max() } {}
	void Update( double next ) override;
	double Evaluate() override { return _min;}
	const char* GetName() const override { return "min";}

private:
	double _min;
};