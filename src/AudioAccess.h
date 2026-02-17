#pragma once
#include <raylib.h>
#include "NoteManager.h"
#include <atomic>
#include <cstdint>

namespace AudioDemo {
    class AudioAccess {
        static const int MAX_SAMPLES_PER_UPDATE = 512;
        static AudioStream mStream;
        static NoteManager* mNoteManager;
        static bool mIsReady;
        static std::atomic<std::uint64_t> mCallbackHits;
    public:
        static void init(NoteManager* nm) {
            mIsReady = false;
            mCallbackHits.store(0, std::memory_order_relaxed);
            mNoteManager = nm;
            InitAudioDevice();
            if (!IsAudioDeviceReady()) {
                TraceLog(LOG_ERROR, "AUDIO: InitAudioDevice failed - audio callback will not run");
                return;
            }

            SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);
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
        static std::uint64_t callbackHitCount() { return mCallbackHits.load(std::memory_order_relaxed); }
        // static because RayLib expects a C-style function pointer, so it can't be a member function
        static void audioCallback(void* buffer, unsigned int sampleCount) {
            mCallbackHits.fetch_add(1, std::memory_order_relaxed);
            float *d = (float *)buffer;
            if (mNoteManager == nullptr) {
                for (unsigned int i = 0; i < sampleCount; i++) d[i] = 0.0f;
                return;
            }
            for (unsigned int i = 0; i < sampleCount; i++)
            {
                d[i] = mNoteManager->nextSample();
            }
        }
    };
}
