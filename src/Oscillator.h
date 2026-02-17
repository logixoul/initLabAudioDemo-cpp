#pragma once
#include "AppOptions.h"
#include <cmath>

namespace AudioDemo
{
    class Oscillator
    {
    public:
        virtual float nextSample() = 0;
    };

    class SineOscillator : public Oscillator
    {
        float phase = 0;
        float frequency;
        AppOptions const *appOptions;

    public:
        SineOscillator(float frequency, AppOptions const *appOptions)
        {
            this->frequency = frequency;
            this->phase = 0;
            this->appOptions = appOptions;
        }

        float nextSample() override
        {
            float sample = std::sin(this->phase);
            this->phase += (2 * M_PI * this->frequency) / this->appOptions->sampleRate;
            return sample;
        }
    };
}