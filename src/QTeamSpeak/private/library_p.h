#pragma once

#include "eventmanager_p.h"
#include "interfacemanager_p.h"

namespace QTeamSpeak {

class LibraryPrivate
{
public:
    LibraryPrivate()
        : eventManager(new EventManager)
        , interfaceManager(new InterfaceManager)
    {

    }

    inline bool releaseHandle()
    {
        bool result = true;
        try {
            api()->destroyClientLib();
        } catch (...) {
            result = false;
        }
        try {
            handle->unload();
        } catch (...) {
            result = false;
        }
        return result;
    }

public:
    LogTypes usedLogTypes;
    LogLevel logLevel;
    QString nativeBinary;
    QString logFileFolder;
    QString resourcesFolder;

    QList<CustomDevice*> customdevices;

    QHash<Connection::ID, Connection*> servers;

    CustomPacketEncryptHandler   customPacketEncryptHandler;
    CustomPacketDecryptHandler   customPacketDecryptHandler;
    ClientPasswordEncryptHandler clientPasswordEncryptHandler;
    EditPlaybackVoiceDataHandler            editPlaybackVoiceDataHandler;
    EditPostProcessVoiceDataHandler         editPostProcessVoiceDataHandler;
    EditMixedPlaybackVoiceDataHandler       editMixedPlaybackVoiceDataHandler;
    EditCapturedVoiceDataHandler            editCapturedVoiceDataHandler;
    Custom3dRolloffCalculationClientHandler custom3dRolloffCalculationClientHandler;
    Custom3dRolloffCalculationWaveHandler   custom3dRolloffCalculationWaveHandler;
    CheckUniqueIdentifierHandler            checkUniqueIdentifierHandler;

    std::unique_ptr<QLibrary> handle;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<InterfaceManager> interfaceManager;
};

} // namespace QTeamSpeak

