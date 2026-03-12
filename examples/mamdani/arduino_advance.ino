#include "OmniLiteFuzzy.h"

OmniLiteFuzzy craterMonitor(9, MAMDANI, CENTROID, 0, 60);

FuzzySet so2Low(0, 0, 3, 8);
FuzzySet so2Medium(7, 9, 10, 12);
FuzzySet so2High(11, 15, 20, 20);

FuzzySet co2Low(0, 100, 200, 400);
FuzzySet co2Medium(300, 500, 800, 1000);
FuzzySet co2High(900, 1200, 2000, 2000);

FuzzySet normalStatus(0, 0, 10, 20);
FuzzySet warningStatus(10, 20, 30, 40);
FuzzySet dangerStatus(30, 40, 50, 60);

void setup() {
    Serial.begin(9600);
    craterMonitor.setCentroidSamples(100); 
}

void loop() {
    float ppmSO2 = 8.5;
    float ppmCO2 = 450.0; 

    craterMonitor.resetRules();

    float muSO2_L = so2Low.getMembership(ppmSO2);
    float muSO2_M = so2Medium.getMembership(ppmSO2);
    float muSO2_H = so2High.getMembership(ppmSO2);
    
    float muCO2_L = co2Low.getMembership(ppmCO2);
    float muCO2_M = co2Medium.getMembership(ppmCO2);
    float muCO2_H = co2High.getMembership(ppmCO2);

    FuzzyRule rule1;
    rule1.applyAND(muSO2_L, muCO2_L);
    rule1.setOutputMamdani(&normalStatus);
    craterMonitor.addRule(rule1);

    FuzzyRule rule2;
    rule2.applyAND(muSO2_L, muCO2_M);
    rule2.setOutputMamdani(&warningStatus);
    craterMonitor.addRule(rule2);

    FuzzyRule rule3;
    rule3.applyAND(muSO2_L, muCO2_H);
    rule3.setOutputMamdani(&dangerStatus);
    craterMonitor.addRule(rule3);

    FuzzyRule rule4;
    rule4.applyAND(muSO2_M, muCO2_L);
    rule4.setOutputMamdani(&warningStatus);
    craterMonitor.addRule(rule4);

    FuzzyRule rule5;
    rule5.applyAND(muSO2_M, muCO2_M);
    rule5.setOutputMamdani(&warningStatus);
    craterMonitor.addRule(rule5);

    FuzzyRule rule6;
    rule6.applyAND(muSO2_M, muCO2_H);
    rule6.setOutputMamdani(&dangerStatus);
    craterMonitor.addRule(rule6);

    FuzzyRule rule7;
    rule7.applyAND(muSO2_H, muCO2_L);
    rule7.setOutputMamdani(&dangerStatus);
    craterMonitor.addRule(rule7);

    FuzzyRule rule8;
    rule8.applyAND(muSO2_H, muCO2_M);
    rule8.setOutputMamdani(&dangerStatus);
    craterMonitor.addRule(rule8);

    FuzzyRule rule9;
    rule9.applyAND(muSO2_H, muCO2_H);
    rule9.setOutputMamdani(&dangerStatus);
    craterMonitor.addRule(rule9);

    float dangerLevel = craterMonitor.computeOutput();
    Serial.print("SO2 PPM: "); Serial.print(ppmSO2);
    Serial.print(" | CO2 PPM: "); Serial.print(ppmCO2);
    Serial.print(" | Danger Level: ");
    Serial.println(dangerLevel);
    delay(2000);
}