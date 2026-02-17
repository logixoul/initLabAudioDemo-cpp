#pragma once
#include <raylib.h>
#include "NoteManager.h"
#include <cstdlib>

namespace AudioDemo {
    class AudioAccess {
        static const int MAX_SAMPLES_PER_UPDATE = 512;
        static AudioStream mStream;
        static NoteManager* mNoteManager;
    public:
        static void init(NoteManager* nm) {
            mNoteManager = nm;
            InitAudioDevice();

            SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);
            mStream = LoadAudioStream(
                44100, // sample rate
                32, // 32-bit float
                1 // mono sound for simplicity
            );
            SetAudioStreamCallback(mStream, audioCallback);
            PlayAudioStream(mStream);
        }
        // static because RayLib expects a C-style function pointer, so it can't be a member function
        static void audioCallback(void* buffer, unsigned int sampleCount) {
            float *d = (float *)buffer;
            for (unsigned int i = 0; i < sampleCount; i++)
            {
                d[i] = mNoteManager->nextSample();
                d[i] += std::rand() / (float)RAND_MAX * 0.5f; //dbg
            }
        }
    };
}