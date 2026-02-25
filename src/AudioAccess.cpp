#include "AudioAccess.h"

namespace AudioDemo {
    AudioStream AudioAccess::mStream;
    NoteManager * AudioAccess::mNoteManager;
    bool AudioAccess::mIsReady = false;
}
