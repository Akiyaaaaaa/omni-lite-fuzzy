# OmniLiteFuzzy 🪶

<p align="left">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino">
  <img src="https://img.shields.io/badge/Embedded-Systems-black?style=for-the-badge&logo=cpu-fill&logoColor=white" alt="Embedded Systems">
  <img src="https://img.shields.io/badge/Pure%20STL-Zero--Dependency-orange?style=for-the-badge" alt="Zero Dependency">
</p>

---

**A blazing fast, memory-safe, and pure C++ Fuzzy Logic library supporting Mamdani, Sugeno, and Tsukamoto inference methods.**

OmniLiteFuzzy is designed specifically for embedded systems, microcontrollers (like Arduino, ESP8266, ESP32, STM32), and resource-constrained environments. By avoiding continuous dynamic memory allocation (`new`/`malloc`), it completely eliminates the risk of heap fragmentation—a common issue in long-running IoT devices.

Since it is written in **Pure C++** with zero framework dependencies, you can compile it for desktop applications, game engines, or even WebAssembly (WASM).

## ✨ Key Features

- **Multi-Method Engine:** Natively supports Mamdani, Sugeno (Zero-Order), and Tsukamoto fuzzy inference systems.
- **Memory Safe:** Allocates memory exactly once during initialization. No dynamic allocation in your main loop.
- **Pure C++:** Completely framework-agnostic. No `#include <Arduino.h>` required.
- **Lightweight Defuzzification:** \* High-precision discrete Centroid (Center of Gravity) for Mamdani.
  - Ultra-fast Weighted Average for Sugeno and Tsukamoto.
- **Intuitive OOP API:** Easy to read, easy to write, and easy to maintain.

---

## 📦 Installation

**For Arduino IDE:**

1. Download this repository as a `.zip` file.
2. Open Arduino IDE.
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**
4. Select the downloaded `.zip` file.

**For Standard C++ / CMake Projects:**
Simply copy `OmniLiteFuzzy.h` and `OmniLiteFuzzy.cpp` from the `src/` folder into your project directory and compile them alongside your main code.

---

## 💡 Quick Start Example (Mamdani)

Here is a simple example of a tipping system (calculating tip percentage based on food quality):

```cpp
#include <iostream>
#include "OmniLiteFuzzy.h"

int main() {
    // 1. Initialize: Max 3 Rules, Mamdani Method, Centroid Defuzzification, Output Range 5-25%
    OmniLiteFuzzy fuzzyTip(3, MAMDANI, CENTROID, 5, 25);

    // 2. Define Input Sets (Food Quality: 0 - 10)
    FuzzySet badFood(0, 0, 4);
    FuzzySet goodFood(3, 7, 10);
    FuzzySet perfectFood(8, 10, 10);

    // 3. Define Output Sets (Tip Percentage: 5% - 25%)
    FuzzySet lowTip(5, 5, 12);
    FuzzySet mediumTip(10, 15, 20);
    FuzzySet highTip(18, 25, 25);

    // 4. Input the crisp value
    float foodScore = 8.5;

    // 5. Fuzzification
    float muBad = badFood.getMembership(foodScore);
    float muGood = goodFood.getMembership(foodScore);
    float muPerfect = perfectFood.getMembership(foodScore);

    // 6. Build Rules & Inference
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

    // 7. Defuzzification
    float recommendedTip = fuzzyTip.computeOutput();
    std::cout << "Recommended Tip: " << recommendedTip << " %" << std::endl;

    return 0;
}
```

## 🛠️ Supported Methods & Implementation

1. **Mamdani**
   - **Output**: Fuzzy Sets (Triangles/Trapezoids).
   - **Defuzzification**: Discrete Centroid (CENTROID).
   - **Usage**: setOutputMamdani(&outputSet)

2. **Sugeno**
   - **Output**: Crisp Constants (Floats).
   - **Defuzzification**: Weighted Average (WEIGHTED_AVERAGE).
   - **Usage**: setOutputSugeno(constantValue)

3. **Tsukamoto**
   - **Output**: Monotonic Lines (Up or Down).
   - **Defuzzification**: Weighted Average (WEIGHTED_AVERAGE).
   - **Usage**: setOutputTsukamoto(&outputSet, isMonotonicUp) (where isMonotonicUp is true for rising lines, false for falling lines).

## 📂 File Structure

```
OmniLiteFuzzy/
├── src/
│   ├── OmniLiteFuzzy.h       # Main Header (Class Definitions)
│   ├── OmniLiteFuzzy.cpp     # Core Logic (Implementation)
│   └── .vscode/settings.json # VSCode Configuration
├── examples/
│   ├── mamdani/
│   │   ├── general_simple.cpp
│   │   └── general_advance.cpp
│   ├── sugeno/
│   │   ├── general_simple.cpp
│   │   └── general_advance.cpp
│   └── tsukamoto/
│       ├── general_simple.cpp
│       └── general_advance.cpp
├── library.properties        # Arduino Library Metadata
├── README.md                 # Documentation (This File)
└── .gitignore                # Build Artifacts
```

## 📄 License

This project is open-source and available under the MIT License. You are free to copy, modify, and use it in both personal and commercial projects.
