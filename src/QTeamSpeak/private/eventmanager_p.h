#pragma once

#include "interfacemanager_p_p.h"

namespace QTeamSpeak {

class EventManager : public QObject
{
public:
    static EventManager* instance();
    ~EventManager();

    static void onConnectStatusChangeEventWrapper(quint64 connectionID, int newStatus, uint errorNumber);
    static void onServerProtocolVersionEventWrapper(quint64 connectionID, int protocolVersion);
    static void onNewChannelEventWrapper(quint64 connectionID, quint64 channelID, quint64 channelParentID);
    static void onNewChannelCreatedEventWrapper(quint64 connectionID, quint64 channelID, quint64 channelParentID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onDelChannelEventWrapper(quint64 connectionID, quint64 channelID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onChannelMoveEventWrapper(quint64 connectionID, quint64 channelID, quint64 newChannelParentID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onUpdateChannelEventWrapper(quint64 connectionID, quint64 channelID);
    static void onUpdateChannelEditedEventWrapper(quint64 connectionID, quint64 channelID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onUpdateClientEventWrapper(quint64 connectionID, quint16 clientID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onClientMoveEventWrapper(quint64 connectionID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, const char* moveMessage);
    static void onClientMoveSubscriptionEventWrapper(quint64 connectionID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility);
    static void onClientMoveTimeoutEventWrapper(quint64 connectionID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, const char* timeoutMessage);
    static void onClientMoveMovedEventWrapper(quint64 connectionID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage);
    static void onClientKickFromChannelEventWrapper(quint64 connectionID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
    static void onClientKickFromServerEventWrapper(quint64 connectionID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
    static void onClientIDsEventWrapper(quint64 connectionID, const char* uniqueClientIdentifier, quint16 clientID, const char* clientName);
    static void onClientIDsFinishedEventWrapper(quint64 connectionID);
    static void onServerEditedEventWrapper(quint64 connectionID, quint16 editerID, const char* editerName, const char* editerUniqueIdentifier);
    static void onServerUpdatedEventWrapper(quint64 connectionID);
    static void onServerErrorEventWrapper(quint64 connectionID, const char* errorMessage, uint error, const char* returnCode, const char* extraMessage);
    static void onServerStopEventWrapper(quint64 connectionID, const char* shutdownMessage);
    static void onTextMessageEventWrapper(quint64 connectionID, quint16 targetMode, quint16 toID, quint16 fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
    static void onTalkStatusChangeEventWrapper(quint64 connectionID, int status, int isReceivedWhisper, quint16 clientID);
    static void onIgnoredWhisperEventWrapper(quint64 connectionID, quint16 clientID);
    static void onConnectionInfoEventWrapper(quint64 connectionID, quint16 clientID);
    static void onServerConnectionInfoEventWrapper(quint64 connectionID);
    static void onChannelSubscribeEventWrapper(quint64 connectionID, quint64 channelID);
    static void onChannelSubscribeFinishedEventWrapper(quint64 connectionID);
    static void onChannelUnsubscribeEventWrapper(quint64 connectionID, quint64 channelID);
    static void onChannelUnsubscribeFinishedEventWrapper(quint64 connectionID);
    static void onChannelDescriptionUpdateEventWrapper(quint64 connectionID, quint64 channelID);
    static void onChannelPasswordChangedEventWrapper(quint64 connectionID, quint64 channelID);
    static void onPlaybackShutdownCompleteEventWrapper(quint64 connectionID);
    static void onSoundDeviceListChangedEventWrapper(const char* modeID, int playOrCap);
    static void onEditPlaybackVoiceDataEventWrapper(quint64 connectionID, quint16 clientID, short* samples, int sampleCount, int channels);
    static void onEditPostProcessVoiceDataEventWrapper(quint64 connectionID, quint16 clientID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
    static void onEditMixedPlaybackVoiceDataEventWrapper(quint64 connectionID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
    static void onEditCapturedVoiceDataEventWrapper(quint64 connectionID, short* samples, int sampleCount, int channels, int* edited);
    static void onCustom3dRolloffCalculationClientEventWrapper(quint64 connectionID, quint16 clientID, float distance, float* volume);
    static void onCustom3dRolloffCalculationWaveEventWrapper(quint64 connectionID, quint64 waveHandle, float distance, float* volume);
    static void onUserLoggingMessageEventWrapper(const char* logmessage, int logLevel, const char* logChannel, quint64 logID, const char* logTime, const char* completeLogString);
    static void onCustomPacketEncryptEventWrapper(char** dataToSend, uint* sizeOfData);
    static void onCustomPacketDecryptEventWrapper(char** dataReceived, uint* dataReceivedSize);
    static void onProvisioningSlotRequestResultEventWrapper(uint error, quint64 requestHandle, const char* connectionKey);
    static void onCheckServerUniqueIdentifierEventWrapper(quint64 connectionID, const char* ServerUniqueIdentifier, int* cancelConnect);
    static void onClientPasswordEncryptEventWrapper(quint64 connectionID, const char* plaintext, char* encryptedText, int encryptedTextByteSize);
    static void onFileTransferStatusEventWrapper(quint16 transferID, uint status, const char* statusMessage, quint64 remotefileSize, quint64 connectionID);
    static void onFileListEventWrapper(quint64 connectionID, quint64 channelID, const char* path, const char* name, quint64 size, quint64 datetime, int type, quint64 incompletesize, const char* returnCode);
    static void onFileListFinishedEventWrapper(quint64 connectionID, quint64 channelID, const char* path);
    static void onFileInfoEventWrapper(quint64 connectionID, quint64 channelID, const char* name, quint64 size, quint64 datetime);

    static ClientUIFunctions* clientUIFunctions();
    // What does this struct do, I can't find any explanation
    static ClientUIFunctionsRare* clientUIFunctionsRare();

private:
    explicit EventManager(QObject* parent = nullptr);
    friend class Library;
    friend class LibraryPrivate;

}; // class NativeEvents

} // namespace QTeamSpeak

