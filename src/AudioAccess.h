#pragma once
#include <raylib.h>
#include "NoteManager.h"

namespace AudioDemo {
    class AudioAccess {
        static const int BUFFER_SIZE = 512;
        static AudioStream mStream;
        static NoteManager* mNoteManager;
        static bool mIsReady;
    public:
        static void init(NoteManager* nm) {
            mIsReady = false;
            mNoteManager = nm;
            InitAudioDevice();
            if (!IsAudioDeviceReady()) {
                TraceLog(LOG_ERROR, "AUDIO: InitAudioDevice failed - audio callback will not run");
                return;
            }

            SetAudioStreamBufferSizeDefault(BUFFER_SIZE);
            mStream = LoadAudioStream(
                44100, // sample rate
                32, // 32-bit float
                1 // mono sound for simplicity
            );
            if (!IsAudioStreamValid(mStream)) {
                TraceLog(LOG_ERROR, "AUDIO: LoadAudioStream failed - callback will not run");
                return;
            }

            SetAudioStreamCallback(mStream, audioCallback);
            PlayAudioStream(mStream);
            mIsReady = IsAudioStreamPlaying(mStream);

            if (!mIsReady) {
                TraceLog(LOG_ERROR, "AUDIO: Stream failed to start playback");
            }
        }
        static bool isReady() { return mIsReady; }
        // static because RayLib expects a C-style function pointer, so it can't be a member function
        static void audioCallback(void* buffer, unsigned int sampleCount) {
            float *d = (float *)buffer;
            if (mNoteManager == nullptr) {
                for (unsigned int i = 0; i < sampleCount; i++) d[i] = 0.0f;
                return;
            }
            for (unsigned int i = 0; i < sampleCount; i++)
            {
                d[i] = mNoteManager->nextSample();
            }
            mNoteManager->handlePendingMessages();
        }
    };
}
