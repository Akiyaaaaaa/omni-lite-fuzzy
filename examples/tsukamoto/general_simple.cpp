#include <iostream>
#include "OmniLiteFuzzy.h"

using namespace std;

int main() {
    OmniLiteFuzzy smartIrrigation(2, TSUKAMOTO, WEIGHTED_AVERAGE, 0, 0);

    FuzzySet drySoil(0, 20, 40);
    FuzzySet wetSoil(30, 60, 100);

    FuzzySet pumpDuration(0, 60, 60);

    float currentMoisture = 25.0; 
    cout << "Sensor Reading -> Soil Moisture: " << currentMoisture << " %" << endl;

    float muDry = drySoil.getMembership(currentMoisture);
    float muWet = wetSoil.getMembership(currentMoisture);

    FuzzyRule rule1;
    rule1.firingStrength = muDry;
    rule1.setOutputTsukamoto(&pumpDuration, true); 
    smartIrrigation.addRule(rule1);

    FuzzyRule rule2;
    rule2.firingStrength = muWet;
    rule2.setOutputTsukamoto(&pumpDuration, false); 
    smartIrrigation.addRule(rule2);

    float duration = smartIrrigation.computeOutput();
    cout << "System Action -> Water pump will run for: " << duration << " seconds" << endl;

    return 0;
}