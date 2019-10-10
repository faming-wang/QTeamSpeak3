#pragma once

#include "connection.h"
#include "teamspeakevents.h"

namespace TeamSpeakSdk {

class Client;
class Channel;
class Connection;
class WaveHandle;
class ISoundDevice;
class CustomDevice;

class TEAMSPEAKSDK_EXPORT Library : public QObject
{
    Q_OBJECT

public:
    enum class Version : uint64
    {
        V_3_0_3_2 = 1433933257,
        V_3_0_4   = 1488208851,
    };

    static Library* instance();
    ~Library();

    static bool initialize(const LibraryOption& options, QString* error = nullptr);
    static bool isInitialized();
    static void destroy();

    static QString nativeBinary();
    static QString logFileFolder();
    static QString resourcesFolder();
    static LogTypes usedLogTypes();

    static CustomPacketEncryptHandler customPacketEncryptHandler();
    static CustomPacketDecryptHandler customPacketDecryptHandler();
    static void setCustomPacketEncryptHandler(const CustomPacketEncryptHandler& handler);
    static void setCustomPacketDecryptHandler(const CustomPacketDecryptHandler& handler);

    static ClientPasswordEncryptHandler clientPasswordEncryptHandler();
    static void setClientPasswordEncryptHandler(const ClientPasswordEncryptHandler& handler);

    static EditPlaybackVoiceDataHandler editPlaybackVoiceDataHandler();
    static void setEditPlaybackVoiceDataHandler(const EditPlaybackVoiceDataHandler& handler);

    static EditPostProcessVoiceDataHandler editPostProcessVoiceDataHandler();
    static void setEditPostProcessVoiceDataHandler(const EditPostProcessVoiceDataHandler& handler);

    static EditMixedPlaybackVoiceDataHandler editMixedPlaybackVoiceDataHandler();
    static void setEditMixedPlaybackVoiceDataHandler(const EditMixedPlaybackVoiceDataHandler& handler);

    static EditCapturedVoiceDataHandler editCapturedVoiceDataHandler();
    static void setEditCapturedVoiceDataHandler(const EditCapturedVoiceDataHandler& handler);

    static Custom3dRolloffCalculationClientHandler custom3dRolloffCalculationClientHandler();
    static void setCustom3dRolloffCalculationClientHandler(const Custom3dRolloffCalculationClientHandler& handler);

    static Custom3dRolloffCalculationWaveHandler custom3dRolloffCalculationWaveHandler();
    static void setCustom3dRolloffCalculationWaveHandler(const Custom3dRolloffCalculationWaveHandler& handler);

    static CheckUniqueIdentifierHandler checkUniqueIdentifierHandler();
    static void setCheckUniqueIdentifierHandler(const CheckUniqueIdentifierHandler& handler);

    static QList<Connection*> connections();

    static QStringList getPlaybackModes();
    static QStringList getCaptureModes();
    static QList<ISoundDevice*> getPlaybackDevices(const QString& mode);
    static QList<ISoundDevice*> getCaptureDevices(const QString& mode);
    static QList<CustomDevice*> getCustomDevices();

    static uint64 speedLimitUp();
    static void setSpeedLimitUp(uint64 value);

    static uint64 speedLimitDown();
    static void setSpeedLimitDown(uint64 value);

    static QString version();
    static Version versionNumber();

    static QString createIdentity();
    static QString identityToUniqueIdentifier(const QString& identity);

    static Connection* spawnNewConnection(int port = 0);
    static CustomDevice* createCustomDevice(const QString& name, SamplingRate captureRate = SamplingRate::Hz48000, int captureChannels = 1, SamplingRate playbackRate = SamplingRate::Hz48000, int playbackChannels = 1);

    static void log(const QString& message, LogLevel severity, const QString& channel, const Connection* connection);
    
    static LogLevel logLevel();
    static void setLogLevel(LogLevel value);

    static QString getErrorMessage(ReturnCode error);

    static Connection* getServer(Connection::ID id);
    static void addServer(Connection* connection);
    static void removeServer(Connection::ID id);

    // QObject override
    bool event(QEvent* e) override;

protected:
    void soundDeviceListChangedEvent(SoundDeviceListChangedEvent* event);
    void userLoggingMessageEvent(UserLoggingMessageEvent* event);

private:
    explicit Library(QObject* parent = Q_NULLPTR);
    friend void __init_library();

}; // class Library

inline Library& lib() { return *Library::instance(); }

} // namespace TeamSpeakSdk

