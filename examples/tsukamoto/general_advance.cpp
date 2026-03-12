#include <iostream>
#include "OmniLiteFuzzy.h"

using namespace std;

int main() {
    OmniLiteFuzzy adaptiveHeater(4, TSUKAMOTO, WEIGHTED_AVERAGE, 0, 0);

    FuzzySet coldTemp(10, 15, 20);
    FuzzySet warmTemp(18, 25, 30);
    FuzzySet fewPeople(0, 2, 5);
    FuzzySet manyPeople(4, 10, 20);

    FuzzySet heaterPower(500, 2000, 2000);

    float roomTemp = 16.0;    
    float peopleCount = 8.0;  
    
    cout << "Environment -> Temp: " << roomTemp << " C | Crowd: " << peopleCount << " people" << endl;
    float muCold = coldTemp.getMembership(roomTemp);
    float muWarm = warmTemp.getMembership(roomTemp);
    float muFew = fewPeople.getMembership(peopleCount);
    float muMany = manyPeople.getMembership(peopleCount);

    FuzzyRule rule1;
    rule1.applyAND(muCold, muFew);
    rule1.setOutputTsukamoto(&heaterPower, true);
    adaptiveHeater.addRule(rule1);

    FuzzyRule rule2;
    rule2.applyAND(muWarm, muMany);
    rule2.setOutputTsukamoto(&heaterPower, false);
    adaptiveHeater.addRule(rule2);

    FuzzyRule rule3;
    rule3.applyOR(muCold, muMany);
    rule3.setOutputTsukamoto(&heaterPower, true);
    adaptiveHeater.addRule(rule3);

    FuzzyRule rule4;
    rule4.applyAND(muWarm, muFew);
    rule4.setOutputTsukamoto(&heaterPower, false);
    adaptiveHeater.addRule(rule4);

    float targetPower = adaptiveHeater.computeOutput();
    cout << "System Action -> Heater Power Set To: " << targetPower << " Watts" << endl;

    return 0;
}