#pragma once
#include "IStatistics.h"

class StdValue : public IStatistics {
public:
	StdValue() : _data(), _std{ 0 }, _mean{ 0 } {}
	void update( double next ) override { _data.push_back(next); }
	double eval() override;
	const char * name() const override { return "std"; }
  void SetMean( double me ){ _mean = me;}

private:
	std::vector<double> _data;
	double _std;
	double _mean;
};