#include "OmniLiteFuzzy.h"

FuzzySet::FuzzySet() {
    a = b = c = d = 0.0;
    isTrapezoid = false;
}

FuzzySet::FuzzySet(float p_a, float p_b, float p_c) {
    a = p_a; b = p_b; c = p_c; d = 0.0;
    isTrapezoid = false;
}

FuzzySet::FuzzySet(float p_a, float p_b, float p_c, float p_d) {
    a = p_a; b = p_b; c = p_c; d = p_d;
    isTrapezoid = true;
}

float FuzzySet::getMembership(float x) {
    if (!isTrapezoid) { 
        if (x <= a || x >= c) return 0.0;
        if (x == b) return 1.0;
        if (x > a && x < b) return (x - a) / (b - a);
        if (x > b && x < c) return (c - x) / (c - b);
    } else { 
        if (x <= a || x >= d) return 0.0;
        if (x >= b && x <= c) return 1.0;
        if (x > a && x < b) return (x - a) / (b - a);
        if (x > c && x < d) return (d - x) / (d - c);
    }
    return 0.0;
}

float FuzzySet::getInverse(float alpha, bool isMonotonicUp) {
    if (isMonotonicUp) return a + (alpha * (b - a));
    else return b - (alpha * (b - a));
}

FuzzyRule::FuzzyRule() {
    firingStrength = 0.0;
    mamdaniOutputSet = nullptr;
    tsukamotoSet = nullptr;
    sugenoConstant = 0.0;
    tsukamotoOutput = 0.0;
}

// MENGGUNAKAN OMNI_MIN
void FuzzyRule::applyAND(float membership1, float membership2) {
    firingStrength = omni_min(membership1, membership2);
}

// MENGGUNAKAN OMNI_MAX
void FuzzyRule::applyOR(float membership1, float membership2) {
    firingStrength = omni_max(membership1, membership2);
}

void FuzzyRule::setOutputMamdani(FuzzySet* outputSet) {
    mamdaniOutputSet = outputSet;
}

void FuzzyRule::setOutputSugeno(float constantValue) {
    sugenoConstant = constantValue;
}

void FuzzyRule::setOutputTsukamoto(FuzzySet* outputSet, bool isUp) {
    tsukamotoSet = outputSet;
    tsukamotoIsUp = isUp;
}

OmniLiteFuzzy::OmniLiteFuzzy(int max_rules, FuzzyMethod method, DefuzzMethod dMethod, float outMin, float outMax) {
    maxRules = max_rules;
    rules = new FuzzyRule[maxRules];
    currentMethod = method;
    defuzzMethod = dMethod;
    outputMin = outMin;
    outputMax = outMax;
    ruleCount = 0;
    centroidSamples = 50;
}

OmniLiteFuzzy::~OmniLiteFuzzy() {
    delete[] rules; 
}

void OmniLiteFuzzy::setMethod(FuzzyMethod method) {
    currentMethod = method;
}

void OmniLiteFuzzy::setMethod(FuzzyMethod method, DefuzzMethod dMethod) {
    currentMethod = method;
    defuzzMethod = dMethod;
}

void OmniLiteFuzzy::setCentroidSamples(int samples) {
    if (samples > 0) {
        centroidSamples = samples;
    }
}

void OmniLiteFuzzy::addRule(FuzzyRule rule) {
    if (ruleCount < maxRules) {
        rules[ruleCount] = rule;
        ruleCount++;
    }
}

void OmniLiteFuzzy::resetRules() {
    ruleCount = 0;
}

float OmniLiteFuzzy::computeOutput() {
    if (ruleCount == 0) return 0.0;

    if (currentMethod == MAMDANI && defuzzMethod == CENTROID) {
        return defuzzifyCentroid();
    } else {
        return defuzzifyWeightedAverage();
    }
}

float OmniLiteFuzzy::defuzzifyCentroid() {
    float step = (outputMax - outputMin) / centroidSamples;
    float pembilang = 0.0;
    float penyebut = 0.0;

    for (float x = outputMin; x <= outputMax; x += step) {
        float maxAlphaForX = 0.0; 

        for (int i = 0; i < ruleCount; i++) {
            if (rules[i].mamdaniOutputSet != nullptr) {
                float mu = rules[i].mamdaniOutputSet->getMembership(x);
                float clippedMu = omni_min(mu, rules[i].firingStrength);
                maxAlphaForX = omni_max(maxAlphaForX, clippedMu);
            }
        }
        
        pembilang += (x * maxAlphaForX);
        penyebut += maxAlphaForX;
    }

    if (penyebut == 0.0) return 0.0;
    return pembilang / penyebut;
}

float OmniLiteFuzzy::defuzzifyWeightedAverage() {
    float pembilang = 0.0;
    float penyebut = 0.0;

    for (int i = 0; i < ruleCount; i++) {
        float alpha = rules[i].firingStrength;
        float zValue = 0.0;

        if (currentMethod == SUGENO) {
            zValue = rules[i].sugenoConstant;
        } 
        else if (currentMethod == TSUKAMOTO) {
            if (rules[i].tsukamotoSet != nullptr) {
                zValue = rules[i].tsukamotoSet->getInverse(alpha, rules[i].tsukamotoIsUp);
            }
        }
        else if (currentMethod == MAMDANI) {
             if (rules[i].mamdaniOutputSet != nullptr) {
                zValue = rules[i].mamdaniOutputSet->b; 
            }
        }

        pembilang += (alpha * zValue);
        penyebut += alpha;
    }

    if (penyebut == 0.0) return 0.0;
    return pembilang / penyebut;
}