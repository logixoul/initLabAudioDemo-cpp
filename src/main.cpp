#include "ui.h"
#include "AudioAccess.h"
#include "NoteManager.h"
#include "AppOptions.h"

int main()
{
    AudioDemo::AppOptions options;
    AudioDemo::NoteManager noteManager(&options);
    AudioDemo::AudioAccess::init(&noteManager);

    AudioDemo::Ui ui(&noteManager);
    ui.mainLoop();
}