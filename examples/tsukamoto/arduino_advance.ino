#include "OmniLiteFuzzy.h"

OmniLiteFuzzy fuzzyHeater(4, TSUKAMOTO, WEIGHTED_AVERAGE, 0, 0);

FuzzySet cold(10, 15, 20);
FuzzySet warm(18, 25, 30);

FuzzySet fewPeople(0, 2, 5);
FuzzySet manyPeople(4, 10, 20);
FuzzySet heaterPower(500, 2000, 2000);

void loop() {
    float roomTemp = 16.0;
    float numPeople = 8;

    fuzzyHeater.resetRules();

    float muCold = cold.getMembership(roomTemp);
    float muWarm = warm.getMembership(roomTemp);
    float muFew = fewPeople.getMembership(numPeople);
    float muMany = manyPeople.getMembership(numPeople);

    FuzzyRule rule1;
    rule1.applyAND(muCold, muFew);
    rule1.setOutputTsukamoto(&heaterPower, true); 
    fuzzyHeater.addRule(rule1);

    FuzzyRule rule2;
    rule2.applyAND(muWarm, muMany);
    rule2.setOutputTsukamoto(&heaterPower, false); 
    fuzzyHeater.addRule(rule2);

    FuzzyRule rule3;
    rule3.applyOR(muCold, muMany);
    rule3.setOutputTsukamoto(&heaterPower, true); 
    fuzzyHeater.addRule(rule3);

    float powerOutput = fuzzyHeater.computeOutput();
}