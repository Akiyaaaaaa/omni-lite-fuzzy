#include "OmniLiteFuzzy.h"

OmniLiteFuzzy fuzzyLamp(2, SUGENO, WEIGHTED_AVERAGE, 0, 0);

FuzzySet dark(0, 0, 500);
FuzzySet bright(400, 1023, 1023);

void setup() {
    Serial.begin(9600);
}

void loop() {
    float ldrValue = 300; 

    fuzzyLamp.resetRules();

    FuzzyRule rule1;
    rule1.firingStrength = dark.getMembership(ldrValue);
    rule1.setOutputSugeno(255.0); 
    fuzzyLamp.addRule(rule1);

    FuzzyRule rule2;
    rule2.firingStrength = bright.getMembership(ldrValue);
    rule2.setOutputSugeno(0.0);
    fuzzyLamp.addRule(rule2);

    float outputPWM = fuzzyLamp.computeOutput();
    Serial.println(outputPWM);
    
    delay(500);
}