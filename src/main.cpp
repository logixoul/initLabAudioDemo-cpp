#include "ui.h"
#include "AudioAccess.h"
#include "NoteManager.h"

int main()
{
    AudioDemo::NoteManager noteManager;
    AudioDemo::AudioAccess::init(&noteManager);

    AudioDemo::Ui ui(&noteManager);
    ui.mainLoop();
}