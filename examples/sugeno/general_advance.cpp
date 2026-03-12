#include <iostream>
#include "OmniLiteFuzzy.h"

using namespace std;

int main() {
    OmniLiteFuzzy autoBrake(4, SUGENO, WEIGHTED_AVERAGE, 0, 0);

    FuzzySet distanceClose(0, 0, 20);
    FuzzySet distanceFar(15, 50, 100);
    FuzzySet speedSlow(0, 0, 40);
    FuzzySet speedFast(30, 80, 120);

    const float BRAKE_NONE = 0.0;
    const float BRAKE_LIGHT = 30.0;
    const float BRAKE_MEDIUM = 60.0;
    const float BRAKE_HARD = 100.0;
    float currentDistance = 18.0; 
    float currentSpeed = 75.0;    
    
    cout << "Telemetry -> Distance: " << currentDistance << "m | Speed: " << currentSpeed << "km/h" << endl;
    float muClose = distanceClose.getMembership(currentDistance);
    float muFar = distanceFar.getMembership(currentDistance);
    float muSlow = speedSlow.getMembership(currentSpeed);
    float muFast = speedFast.getMembership(currentSpeed);

    FuzzyRule rule1;
    rule1.applyAND(muClose, muFast);
    rule1.setOutputSugeno(BRAKE_HARD);
    autoBrake.addRule(rule1);

    FuzzyRule rule2;
    rule2.applyAND(muClose, muSlow);
    rule2.setOutputSugeno(BRAKE_MEDIUM);
    autoBrake.addRule(rule2);

    FuzzyRule rule3;
    rule3.applyAND(muFar, muFast);
    rule3.setOutputSugeno(BRAKE_LIGHT);
    autoBrake.addRule(rule3);

    FuzzyRule rule4;
    rule4.applyAND(muFar, muSlow);
    rule4.setOutputSugeno(BRAKE_NONE);
    autoBrake.addRule(rule4);

    float appliedBrakeForce = autoBrake.computeOutput();
    cout << "System Action -> Applied Braking Force: " << appliedBrakeForce << " %" << endl;

    return 0;
}