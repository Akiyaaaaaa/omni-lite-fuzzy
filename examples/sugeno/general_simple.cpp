#include <iostream>
#include "OmniLiteFuzzy.h"

using namespace std;

int main() {
    OmniLiteFuzzy smartAC(2, SUGENO, WEIGHTED_AVERAGE, 0, 0);

    FuzzySet coldTemp(15, 20, 24);
    FuzzySet hotTemp(22, 28, 35);

    const float COMPRESSOR_OFF = 0.0;
    const float COMPRESSOR_FULL = 100.0;

    float currentTemp = 26.5; 
    cout << "Current Room Temperature: " << currentTemp << " C" << endl;

    float muCold = coldTemp.getMembership(currentTemp);
    float muHot = hotTemp.getMembership(currentTemp);

    FuzzyRule rule1;
    rule1.firingStrength = muCold;
    rule1.setOutputSugeno(COMPRESSOR_OFF);
    smartAC.addRule(rule1);

    FuzzyRule rule2;
    rule2.firingStrength = muHot;
    rule2.setOutputSugeno(COMPRESSOR_FULL);
    smartAC.addRule(rule2);

    float acPower = smartAC.computeOutput();
    cout << "AC Compressor Power: " << acPower << " %" << endl;

    return 0;
}