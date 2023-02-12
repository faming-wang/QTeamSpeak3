#pragma once

#include "library.h"
#include "connection.h"
#include "private/definition_p.h"
#include "private/interfacemanager_p.h"

namespace QTeamSpeak {

class InterfaceManager
{
public:
    static InterfaceManager* instance();
    ~InterfaceManager();

    void setLibrary(QLibrary* lib);

    // Construction and Destruction
    bool initClientLib(LogTypes usedLogTypes, const QString& logFileFolder, const QString& resourcesFolder);
    bool destroyClientLib();

    QString getClientLibVersion();
    Library::Version getClientLibVersionNumber();

    quint64 spawnNewServerConnectionHandler(int port);
    ReturnCode destroyServerConnectionHandler(const Connection* server);

    // Identity management
    QString createIdentity();
    QString identityStringToUniqueIdentifier(const QString& identityString);

    // sound
    QList<ISoundDevice*> getPlaybackDeviceList(const QString& modeID);
    QList<ISoundDevice*> getCaptureDeviceList(const QString& modeID);
    QStringList getPlaybackModeList();
    QStringList getCaptureModeList();

    ISoundDevice* getDefaultPlaybackDevice(const QString& modeID);
    ISoundDevice* getDefaultCaptureDevice(const QString& modeID);

    QString getDefaultPlayBackMode();
    QString getDefaultCaptureMode();

    bool openPlaybackDevice(const Connection* server, const ISoundDevice* playbackDevice = nullptr);
    bool openCaptureDevice(const Connection* server, const ISoundDevice* captureDevice = nullptr);

    QString getCurrentPlaybackDeviceName(const Connection* server, bool* isDefault = nullptr);
    QString getCurrentPlayBackMode(const Connection* server);

    QString getCurrentCaptureDeviceName(const Connection* server, bool* isDefault = nullptr);
    QString getCurrentCaptureMode(const Connection* server);

    bool initiateGracefulPlaybackShutdown(const Connection* server);
    bool closePlaybackDevice(const Connection* server);
    bool closeCaptureDevice(const Connection* server);
    bool activateCaptureDevice(const Connection* server);

    bool playWaveFile(const Connection* server, const QString& path);
    WaveHandle* playWaveFileHandle(const Connection* server, const QString& path, bool loop);
    bool pauseWaveFileHandle(const WaveHandle* waveHandle, bool pause);
    bool closeWaveFileHandle( const WaveHandle* waveHandle);

    bool registerCustomDevice(const CustomDevice* device);
    bool unregisterCustomDevice(const CustomDevice* device);

    bool processCustomCaptureData(const QString& deviceName, QVector<short>& buffer);
    bool acquireCustomPlaybackData(const QString& deviceName, QVector<short>& buffer);

    bool setLocalTestMode(const Connection* server, TestMode status);

    bool startVoiceRecording(const Connection* server);
    bool stopVoiceRecording(const Connection* server);

    bool allowWhispersFrom(const Client* client);
    bool removeFromAllowedWhispersFrom(const Client* client);

    // 3d sound positioning
    bool systemset3DListenerAttributes(const Connection* server, const Vector3D* position, const Vector3D* forward, const Vector3D* up);
    bool set3DWaveAttributes(const WaveHandle* waveHandle, const Vector3D* position);
    bool systemset3DSettings(const Connection* server, float distanceFactor, float rolloffScale);
    bool channelset3DAttributes(const Client* client, const Vector3D* position);

    // preprocessor
    float getPreProcessorInfoValueFloat(const Connection* server, const QString& ident);
    QString getPreProcessorConfigValue(const Connection* server, const QString& ident);
    bool setPreProcessorConfigValue(const Connection* server, const QString& ident, const QString& value);

    // encoder
    QString getEncodeConfigValue(const Connection* server, const QString& ident);

    // playback
    float getPlaybackConfigValueAsFloat(const Connection* server, const QString& ident);
    bool setPlaybackConfigValue(const Connection* server, const QString& ident, const QString& value);
    bool setClientVolumeModifier(const Client* client, float value);

    // logging
    bool logMessage(const QString& logMessage, LogLevel severity, const QString& channel, const Connection* server = nullptr);
    bool setLogVerbosity(LogLevel logVerbosity);

    // error handling
    QString getErrorMessage(ReturnCode errorCode);

    // Interacting with the server
    ReturnCode startConnection(
        const Connection* server, 
        const QString& identity, 
        const QString& ip, 
        uint port, 
        const QString& nickname,
        const QStringList& defaultChannelArray,
        const QString& defaultChannelPassword, 
        const QString& serverPassword
    );
    ReturnCode startConnection(
        const Connection* server, 
        const QString& identity, 
        const QString& ip, 
        uint port, 
        const QString& nickname,
        quint64 defaultChannelId, 
        const QString& defaultChannelPassword, 
        const QString& serverPassword
    );
    ReturnCode stopConnection(const Connection* server, const QString& quitMessage);

    ReturnCode requestClientMove(const Client* client, const Channel* newChannel, const QString& password, const QString& returnCode);
    ReturnCode requestClientVariables(const Client* client, const QString& returnCode);
    ReturnCode requestClientKickFromChannel(const Client* client, const QString& kickReason, const QString& returnCode);
    ReturnCode requestClientKickFromServer(const Client* client, const QString& kickReason, const QString& returnCode);
    ReturnCode requestChannelDelete(const Channel* channel, bool force, const QString& returnCode);
    ReturnCode requestChannelMove(const Channel* channel, const Channel* newChannelParent, const Channel* newChannelOrder, const QString& returnCode);
    
    ReturnCode requestSendPrivateTextMsg(const Client* targetClient, const QString& message, const QString& returnCode);
    ReturnCode requestSendChannelTextMsg(const Channel* targetChannel, const QString& message, const QString& returnCode);
    ReturnCode requestSendServerTextMsg(const Connection* targetServer, const QString& message, const QString& returnCode);
    
    ReturnCode requestConnectionInfo(const Client* client, const QString& returnCode);
    ReturnCode requestClientSetWhisperList(const Client* client, const QList<Channel*>& targetChannels, const QList<Client*>& targetClients, const QString& returnCode);
    ReturnCode requestChannelSubscribe(const QList<Channel*>& channels, const QString& returnCode);
    ReturnCode requestChannelSubscribeAll(const Connection* server, const QString& returnCode);
    ReturnCode requestChannelUnsubscribe(const QList<Channel*>& channels, const QString& returnCode);
    ReturnCode requestChannelUnsubscribeAll(const Connection* server, const QString& returnCode);
    ReturnCode requestChannelDescription(const Channel* channel, const QString& returnCode);
    ReturnCode requestMuteClients(const QList<Client*>& clients, const QString& returnCode);
    ReturnCode requestUnmuteClients(const QList<Client*>& clients, const QString& returnCode);
    ReturnCode requestClientIDs(const Connection* server, const QString& clientUniqueIdentifier, const QString& returnCode);

    // provisioning server calls
    // ReturnCode requestSlotsFromProvisioningServer(const QString& ip, ushort port, const QString& serverPassword, ushort slots, const QString& identity, const QString& region, quint64* requestHandle);
    // ReturnCode cancelRequestSlotsFromProvisioningServer(quint64 requestHandle);
    // ReturnCode startConnectionWithProvisioningKey(const Connection* server, const QString& identity, const QString& nickname, const QString& connectionKey, const QString& clientMetaData);

    // retrieve information ClientLib has stored

    // general info
    Client::ID getClientID(const Connection* server);

    // client connection info
    ConnectStatus getConnectionStatus(const Connection* server);
    quint64 getConnectionVariableAsUInt64(const Client* client, ConnectionProperty flag);
    double getConnectionVariableAsDouble(const Client* client, ConnectionProperty flag);
    QString getConnectionVariableAsString(const Client* client, ConnectionProperty flag);
    bool cleanUpConnectionInfo(const Client* client);

    // server connection info
    // ReturnCode requestServerConnectionInfo(const Connection* server, const QString& returnCode);
    // quint64 getServerConnectionVariableAsUInt64(const Connection* server, size_t flag);
    // float getServerConnectionVariableAsFloat(const Connection* server, size_t flag);

    // client info
    int getClientSelfVariableAsInt(const Connection* server, ClientProperty flag);
    QString getClientSelfVariableAsString(const Connection* server, ClientProperty flag);
    bool setClientSelfVariableAsInt(const Connection* server, ClientProperty flag, int value);
    bool setClientSelfVariableAsString(const Connection* server, ClientProperty flag, const QString& value);
    ReturnCode flushClientSelfUpdates(const Connection* server, const QString& returnCode);

    int getClientVariableAsInt(const Client* client, ClientProperty flag);
    quint64 getClientVariableAsUInt64(const Client* client, ClientProperty flag);
    QString getClientVariableAsString(const Client* client, ClientProperty flag);

    QList<Client*> getClientList(const Connection* server);
    Channel* getChannelOfClient(const Client* client);

    // channel info
    int getChannelVariableAsInt(const Channel* channel, ChannelProperty flag);
    quint64 getChannelVariableAsUInt64(const Channel* channel, ChannelProperty flag);
    QString getChannelVariableAsString(const Channel* channel, ChannelProperty flag);
    // quint64 getChannelsFromChannelNames(const Connection* server, const QStringList& channelNames);
    bool setChannelVariableAsInt(const Channel* channel, ChannelProperty flag, int value);
    bool setChannelVariableAsUInt64(const Channel* channel, ChannelProperty flag, quint64 value);
    bool setChannelVariableAsString(const Channel* channel, ChannelProperty flag, const QString& value);

    ReturnCode flushChannelUpdates(const Channel* channel, const QString& returnCode);
    ReturnCode flushChannelCreation(const Connection* server, const Channel* channelParent, const QString& returnCode);

    QList<Channel*> getChannelList(const Connection* server);
    QList<Client*> getChannelClientList(const Channel* channel);
    Channel* getParentChannelOfChannel(const Channel* channel);
    int getChannelEmptySecs(const Channel* channel);

    // server info
    QList<Connection*> getServerConnectionHandlerList();
    int getServerVariableAsInt(const Connection* server, VirtualServerProperty flag);
    quint64 getServerVariableAsUInt64(const Connection* server, VirtualServerProperty flag);
    QString getServerVariableAsString(const Connection* server, VirtualServerProperty flag);
    bool requestServerVariables(const Connection* server);

    // filetransfer management
    QString getTransferFileName(const FileTransfer* transfer);
    QString getTransferFilePath(const FileTransfer* transfer); //The returned memory is dynamically allocated, remember to call ts3client_freeMemory() to release it
    QString getTransferFileRemotePath(const FileTransfer* transfer); //The returned memory is dynamically allocated, remember to call ts3client_freeMemory() to release it
    quint64 getTransferFileSize(const FileTransfer* transfer);
    quint64 getTransferFileSizeDone(const FileTransfer* transfer);
    bool isTransferSender(const FileTransfer* transfer); // 1 == upload, 0 == download
    FileTransfer::State getTransferStatus(const FileTransfer* transfer);
    float getCurrentTransferSpeed(const FileTransfer* transfer); // bytes/second within the last few seconds
    float getAverageTransferSpeed(const FileTransfer* transfer); // bytes/second since start of the transfer
    quint64 getTransferRunTime(const FileTransfer* transfer);

    // Interacting with the server - file transfers
    FileTransfer* sendFile(const Channel* channel, const QString& channelPW, const QString& file, bool overwrite, bool resume, const QString& sourceDirectory, const QString& returnCode);
    FileTransfer* requestFile(const Channel* channel, const QString& channelPW, const QString& file, bool overwrite, bool resume, const QString& destinationDirectory, const QString& returnCode);
    ReturnCode haltTransfer(const FileTransfer* transfer, bool deleteUnfinishedFile, const QString& returnCode);

    ReturnCode requestFileList(const Channel* channel, const QString& channelPW, const QString& path, const QString& returnCode);
    ReturnCode requestFileInfo(const Channel* channel, const QString& channelPW, const QString& file, const QString& returnCode);
    ReturnCode requestDeleteFile(const Channel* channel, const QString& channelPW, const QStringList& files, const QString& returnCode);
    ReturnCode requestCreateDirectory(const Channel* channel, const QString& channelPW, const QString& directoryPath, const QString& returnCode);
    ReturnCode requestRenameFile(const Channel* fromChannel, const QString& fromChannelPW, const Channel* toChannel, const QString& toChannelPW, const QString& oldFile, const QString& newFile, const QString& returnCode);

    quint64 getInstanceSpeedLimitUp();
    quint64 getInstanceSpeedLimitDown();
    quint64 getServerConnectionHandlerSpeedLimitUp(const Connection* server);
    quint64 getServerConnectionHandlerSpeedLimitDown(const Connection* server);
    quint64 getTransferSpeedLimit(const FileTransfer* transfer);
    bool setInstanceSpeedLimitUp(quint64 newLimit);
    bool setInstanceSpeedLimitDown(quint64 newLimit);
    bool setServerConnectionHandlerSpeedLimitUp(const Connection* server, quint64 newLimit);
    bool setServerConnectionHandlerSpeedLimitDown(const Connection* server, quint64 newLimit);
    bool setTransferSpeedLimit(const FileTransfer* transfer, quint64 newLimit);

private:
    InterfaceManager();
    friend class Library;
    friend class LibraryPrivate;
};

inline InterfaceManager* api() { return InterfaceManager::instance(); }

} // namespace QTeamSpeak

