#include "OmniLiteFuzzy.h"

OmniLiteFuzzy fanControl(2, MAMDANI, CENTROID, 0, 255);

FuzzySet coldTemp(0, 15, 25);
FuzzySet hotTemp(20, 35, 50);

FuzzySet slowFan(0, 50, 100);
FuzzySet fastFan(100, 255, 255);

void setup() {
    Serial.begin(9600);

    FuzzyRule rule1;
    rule1.firingStrength = coldTemp.getMembership(22.0);
    rule1.setOutputMamdani(&slowFan);
    fanControl.addRule(rule1);

    FuzzyRule rule2;
    rule2.firingStrength = hotTemp.getMembership(22.0);
    rule2.setOutputMamdani(&fastFan);
    fanControl.addRule(rule2);
}

void loop() {
    float fanPWM = fanControl.computeOutput();
    Serial.println(fanPWM);
    delay(1000);
}