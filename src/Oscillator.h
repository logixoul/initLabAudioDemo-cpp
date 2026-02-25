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
            float sample = std::sin(this->phase * 2 * M_PI);
            this->phase += this->frequency / this->appOptions->sampleRate;
            if (this->phase >= 1.0f)
                this->phase -= 1.0f;
            return sample;
        }
    };

    class SquareOscillator : public Oscillator
    {
        float phase = 0;
        float frequency;
        AppOptions const *appOptions;

    public:
        SquareOscillator(float frequency, AppOptions const *appOptions)
        {
            this->frequency = frequency;
            this->phase = 0;
            this->appOptions = appOptions;
        }

        float nextSample() override
        {
            float sample = this->phase < .5 ? 1 : -1;
            this->phase += this->frequency / this->appOptions->sampleRate;
            if (this->phase >= 1.0f)
                this->phase -= 1.0f;
            return sample;
        }
    };
}