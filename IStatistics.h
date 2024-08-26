#pragma once
#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}
	virtual void Update( double next ) = 0;
	virtual double Evaluate() = 0;
	virtual const char* GetName() const = 0;
};