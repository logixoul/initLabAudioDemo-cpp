#pragma once
#include <vector>
#include <memory>
#include "Note.h"

namespace AudioDemo {

    class NoteManager {
        std::vector<Note> activeNotes;
        std::map<int, Note> noteInstanceThatIsCurrentlyPressed;

    public:
        NoteManager() {
            
        }
        void addNote(int noteIndex) {
            const float noteFreq = 440.0f * std::pow(2.0f, (noteIndex - 69) / 12.0f);
            const auto osc = std::make_shared<SineOscillator>(noteFreq, nullptr);
            Note note(osc, noteIndex);
            this->activeNotes.push_back(note);
            this->noteInstanceThatIsCurrentlyPressed[note.mNoteIndex] = note;
        }
        void removeNote(int noteIndex) {
            for (auto& note : activeNotes) {
                if (note.mNoteIndex == noteIndex) {
                    note.handleNoteRelease();
                }
            }
        }
        float nextSample() {
            float sum = 0.0f;
            for( auto& note : activeNotes) {
                sum += note.nextSample();
            }
            return sum;
        }
        void removeFinishedNotes() {
            std::vector<Note> newActiveNotes;
            for( auto& note : activeNotes) {
                if (!note.isFinished()) {
                    newActiveNotes.push_back(note);
                }
            }
            this->activeNotes = newActiveNotes;
        }
        void audioCallback(float* output, int sampleCount) {
            for (int i = 0; i < sampleCount; i++) {
                output[i] = nextSample();
                for( auto& note : activeNotes) {
                    output[i] += note.nextSample();
                }
            }
            removeFinishedNotes();
        }
    };

}