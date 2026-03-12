#include "OmniLiteFuzzy.h"

OmniLiteFuzzy fuzzyPump(2, TSUKAMOTO, WEIGHTED_AVERAGE, 0, 0);

FuzzySet drySoil(0, 20, 40);
FuzzySet wetSoil(30, 60, 100);
FuzzySet pumpDuration(0, 60, 60); 

void loop() {
    float moisture = 25.0;

    fuzzyPump.resetRules();

    FuzzyRule rule1;
    rule1.firingStrength = drySoil.getMembership(moisture);
    rule1.setOutputTsukamoto(&pumpDuration, true); 
    fuzzyPump.addRule(rule1);
    
    FuzzyRule rule2;
    rule2.firingStrength = wetSoil.getMembership(moisture);
    rule2.setOutputTsukamoto(&pumpDuration, false); 
    fuzzyPump.addRule(rule2);

    float activeDuration = fuzzyPump.computeOutput();
    Serial.print("Pump runs for (seconds): ");
    Serial.println(activeDuration);
}