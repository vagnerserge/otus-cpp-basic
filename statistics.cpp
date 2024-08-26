
#include "Min.h"
#include "Max.h"
#include "Mean.h"
#include "Std.h"

int main() {

	const size_t sCount = 4;
	IStatistics * statData[sCount] = { new MinValue(), new MaxValue(), new MeanValue(), new StdValue() };
	double val = 0;
	while (std::cin >> val) {
		for ( size_t i = 0; i < sCount; ++i ) {
			statData[i]->Update(val);
		}
	}
	if ( sCount > 1 )
	static_cast<StdValue *>( statData[sCount-1] )->SetMean( statData[sCount - 2]->Evaluate() );
	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < sCount; ++i) {
		std::cout << statData[i]->GetName() << " = " << statData[i]->Evaluate() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < sCount; ++i) {
		delete statData[i];
	}

	return 0;
}