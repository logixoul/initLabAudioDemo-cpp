#include "AudioAccess.h"

namespace AudioDemo {
    AudioStream AudioAccess::mStream;
    NoteManager * AudioAccess::mNoteManager;
    bool AudioAccess::mIsReady = false;
    std::atomic<std::uint64_t> AudioAccess::mCallbackHits{0};
}
