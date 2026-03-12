#include "OmniLiteFuzzy.h"

OmniLiteFuzzy fuzzyPID(4, SUGENO, WEIGHTED_AVERAGE, 0, 0);

FuzzySet errNegative(-10, -5, 0);
FuzzySet errPositive(0, 5, 10);

FuzzySet dErrSlow(-5, 0, 5);
FuzzySet dErrFast(3, 8, 15);

const float LARGE_CORRECTION_LEFT = -50.0;
const float SMALL_CORRECTION_LEFT = -20.0;
const float SMALL_CORRECTION_RIGHT = 20.0;
const float LARGE_CORRECTION_RIGHT = 50.0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    float error = 4.5;      
    float deltaError = 6.0; 

    fuzzyPID.resetRules();

    float muErrPositive = errPositive.getMembership(error);
    float muErrNegative = errNegative.getMembership(error);
    float muDeltaFast = dErrFast.getMembership(deltaError);
    float muDeltaSlow = dErrSlow.getMembership(deltaError);

    FuzzyRule rule1;
    rule1.applyAND(muErrPositive, muDeltaFast);
    rule1.setOutputSugeno(LARGE_CORRECTION_RIGHT);
    fuzzyPID.addRule(rule1);

    FuzzyRule rule2;
    rule2.applyAND(muErrPositive, muDeltaSlow);
    rule2.setOutputSugeno(SMALL_CORRECTION_RIGHT);
    fuzzyPID.addRule(rule2);

    FuzzyRule rule3;
    rule3.applyAND(muErrNegative, muDeltaFast);
    rule3.setOutputSugeno(LARGE_CORRECTION_LEFT);
    fuzzyPID.addRule(rule3);

    FuzzyRule rule4;
    rule4.applyAND(muErrNegative, muDeltaSlow);
    rule4.setOutputSugeno(SMALL_CORRECTION_LEFT);
    fuzzyPID.addRule(rule4);

    float speedAdjustment = fuzzyPID.computeOutput();
    
    Serial.print("Error: "); 
    Serial.print(error);
    Serial.print(" | Delta: "); 
    Serial.print(deltaError);
    Serial.print(" | PWM Adjustment: "); 
    Serial.println(speedAdjustment);
    
    int baseSpeed = 100;
    int leftMotorSpeed = baseSpeed + speedAdjustment;
    int rightMotorSpeed = baseSpeed - speedAdjustment;
    
    delay(1000);
}