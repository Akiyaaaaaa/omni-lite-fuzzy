#include <iostream>
#include "OmniLiteFuzzy.h"

using namespace std;

int main() {
    OmniLiteFuzzy enemyAI(MAMDANI, CENTROID, 0, 100);

    FuzzySet closeDistance(0, 0, 15);
    FuzzySet mediumDistance(10, 25, 40);
    FuzzySet farDistance(30, 50, 50);

    FuzzySet lowHP(0, 0, 40);
    FuzzySet fullHP(30, 100, 100);

    FuzzySet defensive(0, 0, 40);      
    FuzzySet cautious(30, 50, 70);     
    FuzzySet aggressive(60, 100, 100);   

    float distance = 8.0;  
    float health = 20.0; 

    cout << "Player Distance: " << distance << "m | Player HP: " << health << endl;

    float muClose = closeDistance.getMembership(distance);
    float muFar = farDistance.getMembership(distance);
    float muLowHP = lowHP.getMembership(health);
    float muFullHP = fullHP.getMembership(health);

    FuzzyRule rule1;
    rule1.applyAND(muClose, muLowHP);
    rule1.setOutputMamdani(&aggressive);
    enemyAI.addRule(rule1);

    FuzzyRule rule2;
    rule2.applyAND(muClose, muFullHP);
    rule2.setOutputMamdani(&defensive);
    enemyAI.addRule(rule2);

    FuzzyRule rule3;
    rule3.firingStrength = muFar; 
    rule3.setOutputMamdani(&cautious);
    enemyAI.addRule(rule3);

    float aggressionLevel = enemyAI.computeOutput();
    cout << "Enemy AI Status -> Aggression Level: " << aggressionLevel << "%" << endl;

    if (aggressionLevel >= 70.0) {
        cout << "Action: Enemy runs and ATTACKS!" << endl;
    } else if (aggressionLevel <= 30.0) {
        cout << "Action: Enemy RETREATS to find cover." << endl;
    } else {
        cout << "Action: Enemy patrols carefully." << endl;
    }

    return 0;
}