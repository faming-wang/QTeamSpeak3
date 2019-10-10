#pragma once

#include "private/interfacemanager_p_p.h"

namespace TeamSpeakSdk {

class EventManager : public QObject
{
public:
    static EventManager* instance();
    ~EventManager();

    static void onConnectStatusChangeEventWrapper(uint64 connectionID, int newStatus, uint errorNumber);
    static void onServerProtocolVersionEventWrapper(uint64 connectionID, int protocolVersion);
    static void onNewChannelEventWrapper(uint64 connectionID, uint64 channelID, uint64 channelParentID);
    static void onNewChannelCreatedEventWrapper(uint64 connectionID, uint64 channelID, uint64 channelParentID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onDelChannelEventWrapper(uint64 connectionID, uint64 channelID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onChannelMoveEventWrapper(uint64 connectionID, uint64 channelID, uint64 newChannelParentID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onUpdateChannelEventWrapper(uint64 connectionID, uint64 channelID);
    static void onUpdateChannelEditedEventWrapper(uint64 connectionID, uint64 channelID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onUpdateClientEventWrapper(uint64 connectionID, uint16 clientID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
    static void onClientMoveEventWrapper(uint64 connectionID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
    static void onClientMoveSubscriptionEventWrapper(uint64 connectionID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility);
    static void onClientMoveTimeoutEventWrapper(uint64 connectionID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
    static void onClientMoveMovedEventWrapper(uint64 connectionID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage);
    static void onClientKickFromChannelEventWrapper(uint64 connectionID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
    static void onClientKickFromServerEventWrapper(uint64 connectionID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
    static void onClientIDsEventWrapper(uint64 connectionID, const char* uniqueClientIdentifier, uint16 clientID, const char* clientName);
    static void onClientIDsFinishedEventWrapper(uint64 connectionID);
    static void onServerEditedEventWrapper(uint64 connectionID, uint16 editerID, const char* editerName, const char* editerUniqueIdentifier);
    static void onServerUpdatedEventWrapper(uint64 connectionID);
    static void onServerErrorEventWrapper(uint64 connectionID, const char* errorMessage, uint error, const char* returnCode, const char* extraMessage);
    static void onServerStopEventWrapper(uint64 connectionID, const char* shutdownMessage);
    static void onTextMessageEventWrapper(uint64 connectionID, uint16 targetMode, uint16 toID, uint16 fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
    static void onTalkStatusChangeEventWrapper(uint64 connectionID, int status, int isReceivedWhisper, uint16 clientID);
    static void onIgnoredWhisperEventWrapper(uint64 connectionID, uint16 clientID);
    static void onConnectionInfoEventWrapper(uint64 connectionID, uint16 clientID);
    static void onServerConnectionInfoEventWrapper(uint64 connectionID);
    static void onChannelSubscribeEventWrapper(uint64 connectionID, uint64 channelID);
    static void onChannelSubscribeFinishedEventWrapper(uint64 connectionID);
    static void onChannelUnsubscribeEventWrapper(uint64 connectionID, uint64 channelID);
    static void onChannelUnsubscribeFinishedEventWrapper(uint64 connectionID);
    static void onChannelDescriptionUpdateEventWrapper(uint64 connectionID, uint64 channelID);
    static void onChannelPasswordChangedEventWrapper(uint64 connectionID, uint64 channelID);
    static void onPlaybackShutdownCompleteEventWrapper(uint64 connectionID);
    static void onSoundDeviceListChangedEventWrapper(const char* modeID, int playOrCap);
    static void onEditPlaybackVoiceDataEventWrapper(uint64 connectionID, uint16 clientID, short* samples, int sampleCount, int channels);
    static void onEditPostProcessVoiceDataEventWrapper(uint64 connectionID, uint16 clientID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
    static void onEditMixedPlaybackVoiceDataEventWrapper(uint64 connectionID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
    static void onEditCapturedVoiceDataEventWrapper(uint64 connectionID, short* samples, int sampleCount, int channels, int* edited);
    static void onCustom3dRolloffCalculationClientEventWrapper(uint64 connectionID, uint16 clientID, float distance, float* volume);
    static void onCustom3dRolloffCalculationWaveEventWrapper(uint64 connectionID, uint64 waveHandle, float distance, float* volume);
    static void onUserLoggingMessageEventWrapper(const char* logmessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString);
    static void onCustomPacketEncryptEventWrapper(char** dataToSend, uint* sizeOfData);
    static void onCustomPacketDecryptEventWrapper(char** dataReceived, uint* dataReceivedSize);
    static void onProvisioningSlotRequestResultEventWrapper(uint error, uint64 requestHandle, const char* connectionKey);
    static void onCheckServerUniqueIdentifierEventWrapper(uint64 connectionID, const char* ServerUniqueIdentifier, int* cancelConnect);
    static void onClientPasswordEncryptEventWrapper(uint64 connectionID, const char* plaintext, char* encryptedText, int encryptedTextByteSize);
    static void onFileTransferStatusEventWrapper(uint16 transferID, uint status, const char* statusMessage, uint64 remotefileSize, uint64 connectionID);
    static void onFileListEventWrapper(uint64 connectionID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char* returnCode);
    static void onFileListFinishedEventWrapper(uint64 connectionID, uint64 channelID, const char* path);
    static void onFileInfoEventWrapper(uint64 connectionID, uint64 channelID, const char* name, uint64 size, uint64 datetime);

    static ClientUIFunctions* clientUIFunctions();
    // What does this struct do, I can't find any explanation
    static ClientUIFunctionsRare* clientUIFunctionsRare();

private:
    explicit EventManager(QObject* parent = Q_NULLPTR);
    friend void __init_event_manager();

}; // class NativeEvents

} // namespace TeamSpeakSdk

