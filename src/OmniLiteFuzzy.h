#ifndef OMNILITEFUZZY_H
#define OMNILITEFUZZY_H

template <typename T>
inline T omni_min(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
inline T omni_max(T a, T b) {
    return (a > b) ? a : b;
}

enum FuzzyMethod { MAMDANI, SUGENO, TSUKAMOTO };
enum DefuzzMethod { CENTROID, WEIGHTED_AVERAGE };

class FuzzySet {
  public:
    float a, b, c, d;
    bool isTrapezoid;

    FuzzySet();
    FuzzySet(float p_a, float p_b, float p_c);
    FuzzySet(float p_a, float p_b, float p_c, float p_d);

    float getMembership(float x);
    float getInverse(float alpha, bool isMonotonicUp); 
};

class FuzzyRule {
  public:
    float firingStrength; 
    
    FuzzySet* mamdaniOutputSet;
    float sugenoConstant;
    
    FuzzySet* tsukamotoSet; 
    bool tsukamotoIsUp;

    FuzzyRule();
    void applyAND(float membership1, float membership2);
    void applyOR(float membership1, float membership2);

    void setOutputMamdani(FuzzySet* outputSet);
    void setOutputSugeno(float constantValue);
    void setOutputTsukamoto(FuzzySet* outputSet, bool isUp);
};

class OmniLiteFuzzy {
  private:
    FuzzyMethod currentMethod;
    DefuzzMethod defuzzMethod;
    
    float outputMin;
    float outputMax;
    
    FuzzyRule* rules; 
    int maxRules;     
    int ruleCount;

    int centroidSamples;
  public:
    OmniLiteFuzzy(int max_rules = 20, FuzzyMethod method = MAMDANI, DefuzzMethod dMethod = CENTROID, float outMin = 0, float outMax = 255);
    ~OmniLiteFuzzy();
    void setMethod(FuzzyMethod method);
    void setMethod(FuzzyMethod method, DefuzzMethod dMethod);
    void setCentroidSamples(int samples);
    void addRule(FuzzyRule rule);
    void resetRules();

    float computeOutput();

  private:
    float defuzzifyCentroid();        
    float defuzzifyWeightedAverage(); 
};

#endif