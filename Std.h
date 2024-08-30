#pragma once
#include "IStatistics.h"

class StdValue : public IStatistics {
public:
	StdValue() : _data(), _std{ 0 }, _mean{ 0 } {}
	void Update( double next ) override { _data.push_back(next); }
	double Evaluate() override;
	const char * GetName() const override { return "std"; }
  void SetMean( double me ){ _mean = me;}

private:
	std::vector<double> _data;
	double _std;
	double _mean;
};