#include <iostream>
#include "OmniLiteFuzzy.h"

using namespace std;

int main() {
    OmniLiteFuzzy fuzzyTip(MAMDANI, CENTROID, 5, 25);

    FuzzySet badFood(0, 0, 4);
    FuzzySet goodFood(3, 7, 10);
    FuzzySet perfectFood(8, 10, 10);

    FuzzySet lowTip(5, 5, 12);
    FuzzySet mediumTip(10, 15, 20);
    FuzzySet highTip(18, 25, 25);

    float foodScore = 8.5; 
    cout << "Food Score: " << foodScore << "/10" << endl;

    float muBad = badFood.getMembership(foodScore);
    float muGood = goodFood.getMembership(foodScore);
    float muPerfect = perfectFood.getMembership(foodScore);

    FuzzyRule rule1;
    rule1.firingStrength = muBad; 
    rule1.setOutputMamdani(&lowTip);
    fuzzyTip.addRule(rule1);

    FuzzyRule rule2;
    rule2.firingStrength = muGood;
    rule2.setOutputMamdani(&mediumTip);
    fuzzyTip.addRule(rule2);

    FuzzyRule rule3;
    rule3.firingStrength = muPerfect;
    rule3.setOutputMamdani(&highTip);
    fuzzyTip.addRule(rule3);

    float recommendedTip = fuzzyTip.computeOutput();
    cout << "Recommended Tip: " << recommendedTip << "%" << endl;

    return 0;
}