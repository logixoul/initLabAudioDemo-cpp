#pragma once
#include <string>

namespace AudioDemo {

class AppOptions {
public:
    float sampleRate = 44100;

    float filterCutoff = .5;
    std::string oscillatorClassName = "SineOscillator";
    std::string filterClassName = "ExpLowPassFilter";
    float echoDelay = 0.5;
};

}