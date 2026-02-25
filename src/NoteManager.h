#pragma once
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include "Note.h"
#include "Oscillator.h"
#include "AppOptions.h"
#include "ITCMessagePort.h"

namespace AudioDemo {

    class NoteManager {
    public:
        struct NotePressedMessage { int id; };
        struct NoteReleasedMessage { int id;};
        struct UpdateMessage {};

        using MessageVariant = std::variant<NotePressedMessage, NoteReleasedMessage, UpdateMessage>;

    private:
        std::vector<NotePtr> activeNotes;
        std::map<int, NotePtr> noteInstanceThatIsCurrentlyPressed;
        AppOptions* mOptions;
        
        ITCMessagePort<NoteManager> mMessagePort;
    public:
        NoteManager(AppOptions* options) : mMessagePort(this) {
            mOptions = options;
        }

        // call this from the UI thread to post messages to the audio thread
        void postMessage(const MessageVariant& msg) {
            mMessagePort.push(msg);
        }

        // call this from the audio thread to handle pending messages from the UI thread
        void handlePendingMessages() {
            mMessagePort.handlePendingMessages();
        }

        // call this from the audio thread to get the next audio sample
        float nextSample() {
            float sum = 0.0f;
            for( auto& note : activeNotes) {
                sum += note->nextSample();
            }
            return sum;
        }



        // overloaded operator() for usage with std::visit - don't call manually.
        void operator()(NotePressedMessage const& msg) {
            addNote(msg.id);
        }
        void operator()(NoteReleasedMessage const& msg) {
            handleNoteRelease(msg.id);
        }
        void operator()(UpdateMessage const& msg) {
            update();
        }


    private:
        void addNote(int noteId) {
            const float noteFreq = 440.0f * std::pow(2.0f, (noteId - 69) / 12.0f);
            const auto osc = std::make_shared<SineOscillator>(noteFreq, mOptions);
            NotePtr note = std::make_shared<Note>(osc, noteId);
            this->activeNotes.push_back(note);
            this->noteInstanceThatIsCurrentlyPressed[note->mNoteId] = note;
        }
        void handleNoteRelease(int noteId) {
            if (this->noteInstanceThatIsCurrentlyPressed.find(noteId) != this->noteInstanceThatIsCurrentlyPressed.end()) {
                this->noteInstanceThatIsCurrentlyPressed[noteId]->handleNoteRelease();
                this->noteInstanceThatIsCurrentlyPressed.erase(noteId);
            }
        }
        void removeFinishedNotes() {
            std::vector<NotePtr> newActiveNotes;
            for( auto& note : activeNotes) {
                if (!note->isFinished()) {
                    newActiveNotes.push_back(note);
                }
            }
            this->activeNotes = newActiveNotes;
        }
        void update() {
            removeFinishedNotes();
        }
        void audioCallback(float* output, int sampleCount) {
            for (int i = 0; i < sampleCount; i++) {
                output[i] = nextSample();
            }
        }

    };

}