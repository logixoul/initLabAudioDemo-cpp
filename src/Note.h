#pragma once
#include <memory>
#include "Oscillator.h"

namespace AudioDemo {
    class Note
    {
        std::shared_ptr<Oscillator> osc;
        bool _isFinished = false;
        bool _isReleased = false;
        float volume;
public:
        int mNoteIndex;
        Note(std::shared_ptr<Oscillator> oscillator, int noteIndex, float volume = 1)
        {
            this->osc = oscillator;
            this->mNoteIndex = noteIndex;
            this->volume = volume;
        }
        void handleNoteRelease()
        {
            this->_isReleased = true;
        }
        float nextSample()
        {
            if (this->_isReleased)
                this->_isFinished = true;
            return this->osc->nextSample() * this->volume;
        }
        bool isFinished()
        {
            return this->_isFinished;
        }
    };
}