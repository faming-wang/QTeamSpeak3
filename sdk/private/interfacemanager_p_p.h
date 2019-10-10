#pragma once

#include <qglobal.h>
#include "library.h"

using uint16 = quint16;
using uint64 = quint64;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
struct ClientUIFunctionsRare;
struct ClientUIFunctions {
void (*onConnectStatusChangeEvent             )(uint64 serverID, int newStatus, uint errorNumber);
void (*onServerProtocolVersionEvent           )(uint64 serverID, int protocolVersion);
void (*onNewChannelEvent                      )(uint64 serverID, uint64 channelID, uint64 channelParentID);
void (*onNewChannelCreatedEvent               )(uint64 serverID, uint64 channelID, uint64 channelParentID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onDelChannelEvent                      )(uint64 serverID, uint64 channelID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onChannelMoveEvent                     )(uint64 serverID, uint64 channelID, uint64 newChannelParentID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onUpdateChannelEvent                   )(uint64 serverID, uint64 channelID);
void (*onUpdateChannelEditedEvent             )(uint64 serverID, uint64 channelID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onUpdateClientEvent                    )(uint64 serverID, uint16 clientID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onClientMoveEvent                      )(uint64 serverID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
void (*onClientMoveSubscriptionEvent          )(uint64 serverID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility);
void (*onClientMoveTimeoutEvent               )(uint64 serverID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
void (*onClientMoveMovedEvent                 )(uint64 serverID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage);
void (*onClientKickFromChannelEvent           )(uint64 serverID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
void (*onClientKickFromServerEvent            )(uint64 serverID, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
void (*onClientIDsEvent                       )(uint64 serverID, const char* uniqueClientIdentifier, uint16 clientID, const char* clientName);
void (*onClientIDsFinishedEvent               )(uint64 serverID);
void (*onServerEditedEvent                    )(uint64 serverID, uint16 editerID, const char* editerName, const char* editerUniqueIdentifier);
void (*onServerUpdatedEvent                   )(uint64 serverID);
void (*onServerErrorEvent                     )(uint64 serverID, const char* errorMessage, uint error, const char* returnCode, const char* extraMessage);
void (*onServerStopEvent                      )(uint64 serverID, const char* shutdownMessage);
void (*onTextMessageEvent                     )(uint64 serverID, uint16 targetMode, uint16 toID, uint16 fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
void (*onTalkStatusChangeEvent                )(uint64 serverID, int status, int isReceivedWhisper, uint16 clientID);
void (*onIgnoredWhisperEvent                  )(uint64 serverID, uint16 clientID);
void (*onConnectionInfoEvent                  )(uint64 serverID, uint16 clientID);
void (*onServerConnectionInfoEvent            )(uint64 serverID);
void (*onChannelSubscribeEvent                )(uint64 serverID, uint64 channelID);
void (*onChannelSubscribeFinishedEvent        )(uint64 serverID);
void (*onChannelUnsubscribeEvent              )(uint64 serverID, uint64 channelID);
void (*onChannelUnsubscribeFinishedEvent      )(uint64 serverID);
void (*onChannelDescriptionUpdateEvent        )(uint64 serverID, uint64 channelID);
void (*onChannelPasswordChangedEvent          )(uint64 serverID, uint64 channelID);
void (*onPlaybackShutdownCompleteEvent        )(uint64 serverID);
void (*onSoundDeviceListChangedEvent          )(const char* modeID, int playOrCap);
void (*onEditPlaybackVoiceDataEvent           )(uint64 serverID, uint16 clientID, short* samples, int sampleCount, int channels);
void (*onEditPostProcessVoiceDataEvent        )(uint64 serverID, uint16 clientID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
void (*onEditMixedPlaybackVoiceDataEvent      )(uint64 serverID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
void (*onEditCapturedVoiceDataEvent           )(uint64 serverID, short* samples, int sampleCount, int channels, int* edited);
void (*onCustom3dRolloffCalculationClientEvent)(uint64 serverID, uint16 clientID, float distance, float* volume);
void (*onCustom3dRolloffCalculationWaveEvent  )(uint64 serverID, uint64 waveHandle, float distance, float* volume);
void (*onUserLoggingMessageEvent              )(const char* logmessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString);
void (*onCustomPacketEncryptEvent             )(char** dataToSend, uint* sizeOfData);
void (*onCustomPacketDecryptEvent             )(char** dataReceived, uint* dataReceivedSize);
void (*onProvisioningSlotRequestResultEvent   )(uint error, uint64 requestHandle, const char* connectionKey);
void (*onCheckServerUniqueIdentifierEvent     )(uint64 serverID, const char* ServerUniqueIdentifier, int* cancelConnect);
void (*onClientPasswordEncrypt                )(uint64 serverID, const char* plaintext, char* encryptedText, int encryptedTextByteSize);
void (*onFileTransferStatusEvent              )(uint16 transferID, uint status, const char* statusMessage, uint64 remotefileSize, uint64 serverID);
void (*onFileListEvent                        )(uint64 serverID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char* returnCode);
void (*onFileListFinishedEvent                )(uint64 serverID, uint64 channelID, const char* path);
void (*onFileInfoEvent                        )(uint64 serverID, uint64 channelID, const char* name, uint64 size, uint64 datetime);
}; // END OF ClientUIFunctions
#ifdef __cplusplus
}
#endif // __cplusplus

namespace TeamSpeakSdk {
namespace ts3client {
/* Memory management */
using freeMemory = uint(*)(void* pointer);

/* Construction and Destruction */
using initClientLib             = uint(*)(const struct ClientUIFunctions* functionPointers, const struct ClientUIFunctionsRare* functionRarePointers, int usedLogTypes, const char* logFileFolder, const char* resourcesFolder);
using destroyClientLib          = uint(*)();
using getClientLibVersion       = uint(*)(char** result);
using getClientLibVersionNumber = uint(*)(uint64* result);

using spawnNewServerConnectionHandler = uint (*)(int port, uint64* result);
using destroyServerConnectionHandler  = uint (*)(uint64 serverID);

/*Identity management*/
using createIdentity = uint(*)(char** result);
using identityStringToUniqueIdentifier = uint(*)(const char* identityString, char** result);

/* sound */
using getPlaybackDeviceList     = uint(*)(const char* modeID, char**** result);
using getCaptureDeviceList      = uint(*)(const char* modeID, char**** result);
using getPlaybackModeList       = uint(*)(char*** result);
using getCaptureModeList        = uint(*)(char*** result);
using getDefaultPlaybackDevice  = uint(*)(const char* modeID, char*** result);
using getDefaultCaptureDevice   = uint(*)(const char* modeID, char*** result);
using getDefaultPlayBackMode    = uint(*)(char** result);
using getDefaultCaptureMode     = uint(*)(char** result);

using openPlaybackDevice               = uint(*)(uint64 serverID, const char* modeID, const char* playbackDevice);
using openCaptureDevice                = uint(*)(uint64 serverID, const char* modeID, const char* captureDevice);
using getCurrentPlaybackDeviceName     = uint(*)(uint64 serverID, char** result, int* isDefault);
using getCurrentPlayBackMode           = uint(*)(uint64 serverID, char** result);
using getCurrentCaptureDeviceName      = uint(*)(uint64 serverID, char** result, int* isDefault);
using getCurrentCaptureMode            = uint(*)(uint64 serverID, char** result);
using initiateGracefulPlaybackShutdown = uint(*)(uint64 serverID);
using closePlaybackDevice              = uint(*)(uint64 serverID);
using closeCaptureDevice               = uint(*)(uint64 serverID);
using activateCaptureDevice            = uint(*)(uint64 serverID);

using playWaveFile        = uint(*)(uint64 serverID, const char* path);
using playWaveFileHandle  = uint(*)(uint64 serverID, const char* path, int loop, uint64* waveHandle);
using pauseWaveFileHandle = uint(*)(uint64 serverID, uint64 waveHandle, int pause);
using closeWaveFileHandle = uint(*)(uint64 serverID, uint64 waveHandle);

using registerCustomDevice      = uint(*)(const char* deviceID, const char* deviceDisplayName, int capFrequency, int capChannels, int playFrequency, int playChannels);
using unregisterCustomDevice    = uint(*)(const char* deviceID);
using processCustomCaptureData  = uint(*)(const char* deviceName, const short* buffer, int samples);
using acquireCustomPlaybackData = uint(*)(const char* deviceName, short* buffer, int samples);

using setLocalTestMode =  uint(*)(uint64 serverID, int status);

using startVoiceRecording = uint(*)(uint64 serverID);
using stopVoiceRecording  = uint(*)(uint64 serverID);

using allowWhispersFrom             = uint(*)(uint64 serverID, uint16 clID);
using removeFromAllowedWhispersFrom = uint(*)(uint64 serverID, uint16 clID);

/* 3d sound positioning */
using systemset3DListenerAttributes = uint(*)(uint64 serverID, const Vector3D* position, const Vector3D* forward, const Vector3D* up);
using set3DWaveAttributes           = uint(*)(uint64 serverID, uint64 waveHandle, const Vector3D* position);
using systemset3DSettings           = uint(*)(uint64 serverID, float distanceFactor, float rolloffScale);
using channelset3DAttributes        = uint(*)(uint64 serverID, uint16 clientID, const Vector3D* position);

/*preprocessor*/
using getPreProcessorInfoValueFloat = uint(*)(uint64 serverID, const char* ident, float* result);
using getPreProcessorConfigValue    = uint(*)(uint64 serverID, const char* ident, char** result);
using setPreProcessorConfigValue    = uint(*)(uint64 serverID, const char* ident, const char* value);

/*encoder*/
using getEncodeConfigValue = uint(*)(uint64 serverID, const char* ident, char** result);

/*playback*/
using getPlaybackConfigValueAsFloat = uint(*)(uint64 serverID, const char* ident, float* result);
using setPlaybackConfigValue        = uint(*)(uint64 serverID, const char* ident, const char* value);
using setClientVolumeModifier       = uint(*)(uint64 serverID, uint16 clientID, float value);

/*logging*/
using logMessage      = uint(*)(const char* logMessage, LogLevel severity, const char* channel, uint64 logID);
using setLogVerbosity = uint(*)(LogLevel logVerbosity);

/*error handling*/
using getErrorMessage = uint(*)(uint errorCode, char** error);

/*Interacting with the server*/
using startConnection = uint(*)(uint64 serverID, const char* identity, const char* ip, uint port, const char* nickname,
const char** defaultChannelArray, const char* defaultChannelPassword, const char* serverPassword);
using startConnectionWithChannelID = uint(*)(uint64 serverID, const char* identity, const char* ip, uint port, const char* nickname,
uint64 defaultChannelId, const char* defaultChannelPassword, const char* serverPassword);

using stopConnection               = uint(*)(uint64 serverID, const char* quitMessage);
using requestClientMove            = uint(*)(uint64 serverID, uint16 clientID, uint64 newChannelID, const char* password, const char* returnCode);
using requestClientVariables       = uint(*)(uint64 serverID, uint16 clientID, const char* returnCode);
using requestClientKickFromChannel = uint(*)(uint64 serverID, uint16 clientID, const char* kickReason, const char* returnCode);
using requestClientKickFromServer  = uint(*)(uint64 serverID, uint16 clientID, const char* kickReason, const char* returnCode);
using requestChannelDelete         = uint(*)(uint64 serverID, uint64 channelID, int force, const char* returnCode);
using requestChannelMove           = uint(*)(uint64 serverID, uint64 channelID, uint64 newChannelParentID, uint64 newChannelOrder, const char* returnCode);
using requestSendPrivateTextMsg    = uint(*)(uint64 serverID, const char* message, uint16 targetClientID, const char* returnCode);
using requestSendChannelTextMsg    = uint(*)(uint64 serverID, const char* message, uint64 targetChannelID, const char* returnCode);
using requestSendServerTextMsg     = uint(*)(uint64 serverID, const char* message, const char* returnCode);
using requestConnectionInfo        = uint(*)(uint64 serverID, uint16 clientID, const char* returnCode);
using requestClientSetWhisperList  = uint(*)(uint64 serverID, uint16 clientID, const uint64* targetChannelIDArray, const uint16* targetClientIDArray, const char* returnCode);
using requestChannelSubscribe      = uint(*)(uint64 serverID, const uint64* channelIDArray, const char* returnCode);
using requestChannelSubscribeAll   = uint(*)(uint64 serverID, const char* returnCode);
using requestChannelUnsubscribe    = uint(*)(uint64 serverID, const uint64* channelIDArray, const char* returnCode);
using requestChannelUnsubscribeAll = uint(*)(uint64 serverID, const char* returnCode);
using requestChannelDescription    = uint(*)(uint64 serverID, uint64 channelID, const char* returnCode);
using requestMuteClients           = uint(*)(uint64 serverID, const uint16* clientIDArray, const char* returnCode);
using requestUnmuteClients         = uint(*)(uint64 serverID, const uint16* clientIDArray, const char* returnCode);
using requestClientIDs             = uint(*)(uint64 serverID, const char* clientUniqueIdentifier, const char* returnCode);

/*provisioning server calls*/
using requestSlotsFromProvisioningServer       = uint(*)(const char* ip, unsigned short port, const char* serverPassword, unsigned short slots, const char* identity, const char* region, uint64* requestHandle);
using cancelRequestSlotsFromProvisioningServer = uint(*)(uint64 requestHandle);
using startConnectionWithProvisioningKey       = uint(*)(uint64 serverID, const char* identity, const char* nickname, const char* connectionKey, const char* clientMetaData);

/*retrieve information ClientLib has stored*/

/*general info*/
using getClientID = uint(*)(uint64 serverID, uint16* result);

/*client connection info*/
using getConnectionStatus           = uint(*)(uint64 serverID, int* result);
using getConnectionVariableAsUInt64 = uint(*)(uint64 serverID, uint16 clientID, size_t flag, uint64* result);
using getConnectionVariableAsDouble = uint(*)(uint64 serverID, uint16 clientID, size_t flag, double* result);
using getConnectionVariableAsString = uint(*)(uint64 serverID, uint16 clientID, size_t flag, char** result);
using cleanUpConnectionInfo         = uint(*)(uint64 serverID, uint16 clientID);

/*server connection info*/
using requestServerConnectionInfo         = uint(*)(uint64 serverID, const char* returnCode);
using getServerConnectionVariableAsUInt64 = uint(*)(uint64 serverID, size_t flag, uint64* result);
using getServerConnectionVariableAsFloat  = uint(*)(uint64 serverID, size_t flag, float* result);

/*client info*/
using getClientSelfVariableAsInt    = uint(*)(uint64 serverID, size_t flag, int* result);
using getClientSelfVariableAsString = uint(*)(uint64 serverID, size_t flag, char** result);
using setClientSelfVariableAsInt    = uint(*)(uint64 serverID, size_t flag, int value);
using setClientSelfVariableAsString = uint(*)(uint64 serverID, size_t flag, const char* value);
using flushClientSelfUpdates        = uint(*)(uint64 serverID, const char* returnCode);

using getClientVariableAsInt    = uint(*)(uint64 serverID, uint16 clientID, size_t flag, int* result);
using getClientVariableAsUInt64 = uint(*)(uint64 serverID, uint16 clientID, size_t flag, uint64* result);
using getClientVariableAsString = uint(*)(uint64 serverID, uint16 clientID, size_t flag, char** result);

using getClientList      = uint(*)(uint64 serverID, uint16** result);
using getChannelOfClient = uint(*)(uint64 serverID, uint16 clientID, uint64* result);

/*channel info*/
using getChannelVariableAsInt    = uint(*)(uint64 serverID, uint64 channelID, size_t flag, int* result);
using getChannelVariableAsUInt64 = uint(*)(uint64 serverID, uint64 channelID, size_t flag, uint64* result);
using getChannelVariableAsString = uint(*)(uint64 serverID, uint64 channelID, size_t flag, char** result);

using getChannelIDFromChannelNames = uint(*)(uint64 serverID, char** channelNameArray, uint64* result);
using setChannelVariableAsInt      = uint(*)(uint64 serverID, uint64 channelID, size_t flag, int value);
using setChannelVariableAsUInt64   = uint(*)(uint64 serverID, uint64 channelID, size_t flag, uint64 value);
using setChannelVariableAsString   = uint(*)(uint64 serverID, uint64 channelID, size_t flag, const char* value);
using flushChannelUpdates          = uint(*)(uint64 serverID, uint64 channelID, const char* returnCode);
using flushChannelCreation         = uint(*)(uint64 serverID, uint64 channelParentID, const char* returnCode);

using getChannelList            = uint(*)(uint64 serverID, uint64** result);
using getChannelClientList      = uint(*)(uint64 serverID, uint64 channelID, uint16** result);
using getParentChannelOfChannel = uint(*)(uint64 serverID, uint64 channelID, uint64* result);
using getChannelEmptySecs       = uint(*)(uint64 serverID, uint64 channelID, int* result);

/*server info*/
using getServerConnectionHandlerList = uint(*)(uint64** result);
using getServerVariableAsInt         = uint(*)(uint64 serverID, size_t flag, int* result);
using getServerVariableAsUInt64      = uint(*)(uint64 serverID, size_t flag, uint64* result);
using getServerVariableAsString      = uint(*)(uint64 serverID, size_t flag, char** result);
using requestServerVariables         = uint(*)(uint64 serverID);

/*filetransfer management*/
using getTransferFileName       = uint(*)(uint16 transferID, char** result); //The returned memory is dynamically allocated, remember to call ts3client::freeMemory() to release it
using getTransferFilePath       = uint(*)(uint16 transferID, char** result); //The returned memory is dynamically allocated, remember to call ts3client::freeMemory() to release it
using getTransferFileRemotePath = uint(*)(uint16 transferID, char** result); //The returned memory is dynamically allocated, remember to call ts3client::freeMemory() to release it
using getTransferFileSize       = uint(*)(uint16 transferID, uint64* result);
using getTransferFileSizeDone   = uint(*)(uint16 transferID, uint64* result);
using isTransferSender          = uint(*)(uint16 transferID, int* result); //1 == upload, 0 == download
using getTransferStatus         = uint(*)(uint16 transferID, int* result);
using getCurrentTransferSpeed   = uint(*)(uint16 transferID, float* result); //bytes/second within the last few seconds
using getAverageTransferSpeed   = uint(*)(uint16 transferID, float* result); //bytes/second since start of the transfer
using getTransferRunTime        = uint(*)(uint16 transferID, uint64* result);

/*Interacting with the server - file transfers*/
using sendFile                                 = uint(*)(uint64 serverID, uint64 channelID, const char* channelPW, const char* file, int overwrite, int resume, const char* sourceDirectory, uint16* result, const char* returnCode);
using requestFile                              = uint(*)(uint64 serverID, uint64 channelID, const char* channelPW, const char* file, int overwrite, int resume, const char* destinationDirectory, uint16* result, const char* returnCode);
using haltTransfer                             = uint(*)(uint64 serverID, uint16 transferID, int deleteUnfinishedFile, const char* returnCode);
using requestFileList                          = uint(*)(uint64 serverID, uint64 channelID, const char* channelPW, const char* path, const char* returnCode);
using requestFileInfo                          = uint(*)(uint64 serverID, uint64 channelID, const char* channelPW, const char* file, const char* returnCode);
using requestDeleteFile                        = uint(*)(uint64 serverID, uint64 channelID, const char* channelPW, const char** file, const char* returnCode);
using requestCreateDirectory                   = uint(*)(uint64 serverID, uint64 channelID, const char* channelPW, const char* directoryPath, const char* returnCode);
using requestRenameFile                        = uint(*)(uint64 serverID, uint64 fromChannelID, const char* fromChannelPW, uint64 toChannelID, const char* toChannelPW, const char* oldFile, const char* newFile, const char* returnCode);
using getInstanceSpeedLimitUp                  = uint(*)(uint64 *limit);
using getInstanceSpeedLimitDown                = uint(*)(uint64 *limit);
using getServerConnectionHandlerSpeedLimitUp   = uint(*)(uint64 serverID, uint64*  limit);
using getServerConnectionHandlerSpeedLimitDown = uint(*)(uint64 serverID, uint64* limit);
using getTransferSpeedLimit                    = uint(*)(uint16 transferID, uint64* limit);
using setInstanceSpeedLimitUp                  = uint(*)(uint64 newLimit);
using setInstanceSpeedLimitDown                = uint(*)(uint64 newLimit);
using setServerConnectionHandlerSpeedLimitUp   = uint(*)(uint64 serverID, uint64 newLimit);
using setServerConnectionHandlerSpeedLimitDown = uint(*)(uint64 serverID, uint64 newLimit);
using setTransferSpeedLimit                    = uint(*)(uint16 transferID, uint64 newLimit);

} // namespace ts3client 

struct InterfaceManagerPrivate
{
    void setLibrary(QLibrary* value)
    {
        handle = value;
        set_library_method(QT_STRINGIFY(ts3client_freeMemory                      ), freeMemory                      );
        set_library_method(QT_STRINGIFY(ts3client_initClientLib                   ), initClientLib                   );
        set_library_method(QT_STRINGIFY(ts3client_destroyClientLib                ), destroyClientLib                );
        set_library_method(QT_STRINGIFY(ts3client_getClientLibVersion             ), getClientLibVersion             );
        set_library_method(QT_STRINGIFY(ts3client_getClientLibVersionNumber       ), getClientLibVersionNumber       );
        set_library_method(QT_STRINGIFY(ts3client_spawnNewServerConnectionHandler ), spawnNewServerConnectionHandler );
        set_library_method(QT_STRINGIFY(ts3client_destroyServerConnectionHandler  ), destroyServerConnectionHandler  );
        set_library_method(QT_STRINGIFY(ts3client_createIdentity                  ), createIdentity                  );
        set_library_method(QT_STRINGIFY(ts3client_identityStringToUniqueIdentifier), identityStringToUniqueIdentifier);
        set_library_method(QT_STRINGIFY(ts3client_getPlaybackDeviceList           ), getPlaybackDeviceList           );
        set_library_method(QT_STRINGIFY(ts3client_getCaptureDeviceList            ), getCaptureDeviceList            );
        set_library_method(QT_STRINGIFY(ts3client_getPlaybackModeList             ), getPlaybackModeList             );
        set_library_method(QT_STRINGIFY(ts3client_getCaptureModeList              ), getCaptureModeList              );
        set_library_method(QT_STRINGIFY(ts3client_getDefaultPlaybackDevice        ), getDefaultPlaybackDevice        );
        set_library_method(QT_STRINGIFY(ts3client_getDefaultCaptureDevice         ), getDefaultCaptureDevice         );
        set_library_method(QT_STRINGIFY(ts3client_getDefaultPlayBackMode          ), getDefaultPlayBackMode          );
        set_library_method(QT_STRINGIFY(ts3client_getDefaultCaptureMode           ), getDefaultCaptureMode           );
        set_library_method(QT_STRINGIFY(ts3client_openPlaybackDevice              ), openPlaybackDevice              );
        set_library_method(QT_STRINGIFY(ts3client_openCaptureDevice               ), openCaptureDevice               );
        set_library_method(QT_STRINGIFY(ts3client_getCurrentPlaybackDeviceName    ), getCurrentPlaybackDeviceName    );
        set_library_method(QT_STRINGIFY(ts3client_getCurrentPlayBackMode          ), getCurrentPlayBackMode          );
        set_library_method(QT_STRINGIFY(ts3client_getCurrentCaptureDeviceName     ), getCurrentCaptureDeviceName     );
        set_library_method(QT_STRINGIFY(ts3client_getCurrentCaptureMode           ), getCurrentCaptureMode           );
        set_library_method(QT_STRINGIFY(ts3client_initiateGracefulPlaybackShutdown), initiateGracefulPlaybackShutdown);
        set_library_method(QT_STRINGIFY(ts3client_closePlaybackDevice             ), closePlaybackDevice             );
        set_library_method(QT_STRINGIFY(ts3client_closeCaptureDevice              ), closeCaptureDevice              );
        set_library_method(QT_STRINGIFY(ts3client_activateCaptureDevice           ), activateCaptureDevice           );
        set_library_method(QT_STRINGIFY(ts3client_playWaveFile                    ), playWaveFile                    );
        set_library_method(QT_STRINGIFY(ts3client_playWaveFileHandle              ), playWaveFileHandle              );
        set_library_method(QT_STRINGIFY(ts3client_pauseWaveFileHandle             ), pauseWaveFileHandle             );
        set_library_method(QT_STRINGIFY(ts3client_closeWaveFileHandle             ), closeWaveFileHandle             );
        set_library_method(QT_STRINGIFY(ts3client_registerCustomDevice            ), registerCustomDevice            );
        set_library_method(QT_STRINGIFY(ts3client_unregisterCustomDevice          ), unregisterCustomDevice          );
        set_library_method(QT_STRINGIFY(ts3client_processCustomCaptureData        ), processCustomCaptureData        );
        set_library_method(QT_STRINGIFY(ts3client_acquireCustomPlaybackData       ), acquireCustomPlaybackData       );
        set_library_method(QT_STRINGIFY(ts3client_setLocalTestMode                ), setLocalTestMode                );
        set_library_method(QT_STRINGIFY(ts3client_startVoiceRecording             ), startVoiceRecording             );
        set_library_method(QT_STRINGIFY(ts3client_stopVoiceRecording              ), stopVoiceRecording              );
        set_library_method(QT_STRINGIFY(ts3client_allowWhispersFrom               ), allowWhispersFrom               );
        set_library_method(QT_STRINGIFY(ts3client_removeFromAllowedWhispersFrom   ), removeFromAllowedWhispersFrom   );
        set_library_method(QT_STRINGIFY(ts3client_systemset3DListenerAttributes   ), systemset3DListenerAttributes   );
        set_library_method(QT_STRINGIFY(ts3client_set3DWaveAttributes             ), set3DWaveAttributes             );
        set_library_method(QT_STRINGIFY(ts3client_systemset3DSettings             ), systemset3DSettings             );
        set_library_method(QT_STRINGIFY(ts3client_channelset3DAttributes          ), channelset3DAttributes          );
        set_library_method(QT_STRINGIFY(ts3client_getPreProcessorInfoValueFloat   ), getPreProcessorInfoValueFloat   );
        set_library_method(QT_STRINGIFY(ts3client_getPreProcessorConfigValue      ), getPreProcessorConfigValue      );
        set_library_method(QT_STRINGIFY(ts3client_setPreProcessorConfigValue      ), setPreProcessorConfigValue      );
        set_library_method(QT_STRINGIFY(ts3client_getEncodeConfigValue            ), getEncodeConfigValue            );
        set_library_method(QT_STRINGIFY(ts3client_getPlaybackConfigValueAsFloat   ), getPlaybackConfigValueAsFloat   );
        set_library_method(QT_STRINGIFY(ts3client_setPlaybackConfigValue          ), setPlaybackConfigValue          );
        set_library_method(QT_STRINGIFY(ts3client_setClientVolumeModifier         ), setClientVolumeModifier         );
        set_library_method(QT_STRINGIFY(ts3client_logMessage                      ), logMessage                      );
        set_library_method(QT_STRINGIFY(ts3client_setLogVerbosity                 ), setLogVerbosity                 );
        set_library_method(QT_STRINGIFY(ts3client_getErrorMessage                 ), getErrorMessage                 );
        set_library_method(QT_STRINGIFY(ts3client_startConnection                 ), startConnection                 );

        uint64 version = 0; getClientLibVersionNumber(&version);
        if (version >= utils::underlay(Library::Version::V_3_0_4))
            set_library_method(QT_STRINGIFY(ts3client_startConnectionWithChannelID), startConnectionWithChannelID);

        set_library_method(QT_STRINGIFY(ts3client_stopConnection                          ), stopConnection                          );
        set_library_method(QT_STRINGIFY(ts3client_requestClientMove                       ), requestClientMove                       );
        set_library_method(QT_STRINGIFY(ts3client_requestClientVariables                  ), requestClientVariables                  );
        set_library_method(QT_STRINGIFY(ts3client_requestClientKickFromChannel            ), requestClientKickFromChannel            );
        set_library_method(QT_STRINGIFY(ts3client_requestClientKickFromServer             ), requestClientKickFromServer             );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelDelete                    ), requestChannelDelete                    );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelMove                      ), requestChannelMove                      );
        set_library_method(QT_STRINGIFY(ts3client_requestSendPrivateTextMsg               ), requestSendPrivateTextMsg               );
        set_library_method(QT_STRINGIFY(ts3client_requestSendChannelTextMsg               ), requestSendChannelTextMsg               );
        set_library_method(QT_STRINGIFY(ts3client_requestSendServerTextMsg                ), requestSendServerTextMsg                );
        set_library_method(QT_STRINGIFY(ts3client_requestConnectionInfo                   ), requestConnectionInfo                   );
        set_library_method(QT_STRINGIFY(ts3client_requestClientSetWhisperList             ), requestClientSetWhisperList             );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelSubscribe                 ), requestChannelSubscribe                 );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelSubscribeAll              ), requestChannelSubscribeAll              );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelUnsubscribe               ), requestChannelUnsubscribe               );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelUnsubscribeAll            ), requestChannelUnsubscribeAll            );
        set_library_method(QT_STRINGIFY(ts3client_requestChannelDescription               ), requestChannelDescription               );
        set_library_method(QT_STRINGIFY(ts3client_requestMuteClients                      ), requestMuteClients                      );
        set_library_method(QT_STRINGIFY(ts3client_requestUnmuteClients                    ), requestUnmuteClients                    );
        set_library_method(QT_STRINGIFY(ts3client_requestClientIDs                        ), requestClientIDs                        );
        set_library_method(QT_STRINGIFY(ts3client_requestSlotsFromProvisioningServer      ), requestSlotsFromProvisioningServer      );
        set_library_method(QT_STRINGIFY(ts3client_cancelRequestSlotsFromProvisioningServer), cancelRequestSlotsFromProvisioningServer);
        set_library_method(QT_STRINGIFY(ts3client_startConnectionWithProvisioningKey      ), startConnectionWithProvisioningKey      );
        set_library_method(QT_STRINGIFY(ts3client_getClientID                             ), getClientID                             );
        set_library_method(QT_STRINGIFY(ts3client_getConnectionStatus                     ), getConnectionStatus                     );
        set_library_method(QT_STRINGIFY(ts3client_getConnectionVariableAsUInt64           ), getConnectionVariableAsUInt64           );
        set_library_method(QT_STRINGIFY(ts3client_getConnectionVariableAsDouble           ), getConnectionVariableAsDouble           );
        set_library_method(QT_STRINGIFY(ts3client_getConnectionVariableAsString           ), getConnectionVariableAsString           );
        set_library_method(QT_STRINGIFY(ts3client_cleanUpConnectionInfo                   ), cleanUpConnectionInfo                   );
        set_library_method(QT_STRINGIFY(ts3client_requestServerConnectionInfo             ), requestServerConnectionInfo             );
        set_library_method(QT_STRINGIFY(ts3client_getServerConnectionVariableAsUInt64     ), getServerConnectionVariableAsUInt64     );
        set_library_method(QT_STRINGIFY(ts3client_getServerConnectionVariableAsFloat      ), getServerConnectionVariableAsFloat      );
        set_library_method(QT_STRINGIFY(ts3client_getClientSelfVariableAsInt              ), getClientSelfVariableAsInt              );
        set_library_method(QT_STRINGIFY(ts3client_getClientSelfVariableAsString           ), getClientSelfVariableAsString           );
        set_library_method(QT_STRINGIFY(ts3client_setClientSelfVariableAsInt              ), setClientSelfVariableAsInt              );
        set_library_method(QT_STRINGIFY(ts3client_setClientSelfVariableAsString           ), setClientSelfVariableAsString           );
        set_library_method(QT_STRINGIFY(ts3client_flushClientSelfUpdates                  ), flushClientSelfUpdates                  );
        set_library_method(QT_STRINGIFY(ts3client_getClientVariableAsInt                  ), getClientVariableAsInt                  );
        set_library_method(QT_STRINGIFY(ts3client_getClientVariableAsUInt64               ), getClientVariableAsUInt64               );
        set_library_method(QT_STRINGIFY(ts3client_getClientVariableAsString               ), getClientVariableAsString               );
        set_library_method(QT_STRINGIFY(ts3client_getClientList                           ), getClientList                           );
        set_library_method(QT_STRINGIFY(ts3client_getChannelOfClient                      ), getChannelOfClient                      );
        set_library_method(QT_STRINGIFY(ts3client_getChannelVariableAsInt                 ), getChannelVariableAsInt                 );
        set_library_method(QT_STRINGIFY(ts3client_getChannelVariableAsUInt64              ), getChannelVariableAsUInt64              );
        set_library_method(QT_STRINGIFY(ts3client_getChannelVariableAsString              ), getChannelVariableAsString              );
        set_library_method(QT_STRINGIFY(ts3client_getChannelIDFromChannelNames            ), getChannelIDFromChannelNames            );
        set_library_method(QT_STRINGIFY(ts3client_setChannelVariableAsInt                 ), setChannelVariableAsInt                 );
        set_library_method(QT_STRINGIFY(ts3client_setChannelVariableAsUInt64              ), setChannelVariableAsUInt64              );
        set_library_method(QT_STRINGIFY(ts3client_setChannelVariableAsString              ), setChannelVariableAsString              );
        set_library_method(QT_STRINGIFY(ts3client_flushChannelUpdates                     ), flushChannelUpdates                     );
        set_library_method(QT_STRINGIFY(ts3client_flushChannelCreation                    ), flushChannelCreation                    );
        set_library_method(QT_STRINGIFY(ts3client_getChannelList                          ), getChannelList                          );
        set_library_method(QT_STRINGIFY(ts3client_getChannelClientList                    ), getChannelClientList                    );
        set_library_method(QT_STRINGIFY(ts3client_getParentChannelOfChannel               ), getParentChannelOfChannel               );
        set_library_method(QT_STRINGIFY(ts3client_getChannelEmptySecs                     ), getChannelEmptySecs                     );
        set_library_method(QT_STRINGIFY(ts3client_getServerConnectionHandlerList          ), getServerConnectionHandlerList          );
        set_library_method(QT_STRINGIFY(ts3client_getServerVariableAsInt                  ), getServerVariableAsInt                  );
        set_library_method(QT_STRINGIFY(ts3client_getServerVariableAsUInt64               ), getServerVariableAsUInt64               );
        set_library_method(QT_STRINGIFY(ts3client_getServerVariableAsString               ), getServerVariableAsString               );
        set_library_method(QT_STRINGIFY(ts3client_requestServerVariables                  ), requestServerVariables                  );
        set_library_method(QT_STRINGIFY(ts3client_getTransferFileName                     ), getTransferFileName                     );
        set_library_method(QT_STRINGIFY(ts3client_getTransferFilePath                     ), getTransferFilePath                     );
        set_library_method(QT_STRINGIFY(ts3client_getTransferFileRemotePath               ), getTransferFileRemotePath               );
        set_library_method(QT_STRINGIFY(ts3client_getTransferFileSize                     ), getTransferFileSize                     );
        set_library_method(QT_STRINGIFY(ts3client_getTransferFileSizeDone                 ), getTransferFileSizeDone                 );
        set_library_method(QT_STRINGIFY(ts3client_isTransferSender                        ), isTransferSender                        );
        set_library_method(QT_STRINGIFY(ts3client_getTransferStatus                       ), getTransferStatus                       );
        set_library_method(QT_STRINGIFY(ts3client_getCurrentTransferSpeed                 ), getCurrentTransferSpeed                 );
        set_library_method(QT_STRINGIFY(ts3client_getAverageTransferSpeed                 ), getAverageTransferSpeed                 );
        set_library_method(QT_STRINGIFY(ts3client_getTransferRunTime                      ), getTransferRunTime                      );
        set_library_method(QT_STRINGIFY(ts3client_sendFile                                ), sendFile                                );
        set_library_method(QT_STRINGIFY(ts3client_requestFile                             ), requestFile                             );
        set_library_method(QT_STRINGIFY(ts3client_haltTransfer                            ), haltTransfer                            );
        set_library_method(QT_STRINGIFY(ts3client_requestFileList                         ), requestFileList                         );
        set_library_method(QT_STRINGIFY(ts3client_requestFileInfo                         ), requestFileInfo                         );
        set_library_method(QT_STRINGIFY(ts3client_requestDeleteFile                       ), requestDeleteFile                       );
        set_library_method(QT_STRINGIFY(ts3client_requestCreateDirectory                  ), requestCreateDirectory                  );
        set_library_method(QT_STRINGIFY(ts3client_requestRenameFile                       ), requestRenameFile                       );
        set_library_method(QT_STRINGIFY(ts3client_getInstanceSpeedLimitUp                 ), getInstanceSpeedLimitUp                 );
        set_library_method(QT_STRINGIFY(ts3client_getInstanceSpeedLimitDown               ), getInstanceSpeedLimitDown               );
        set_library_method(QT_STRINGIFY(ts3client_getServerConnectionHandlerSpeedLimitUp  ), getServerConnectionHandlerSpeedLimitUp  );
        set_library_method(QT_STRINGIFY(ts3client_getServerConnectionHandlerSpeedLimitDown), getServerConnectionHandlerSpeedLimitDown);
        set_library_method(QT_STRINGIFY(ts3client_getTransferSpeedLimit                   ), getTransferSpeedLimit                   );
        set_library_method(QT_STRINGIFY(ts3client_setInstanceSpeedLimitUp                 ), setInstanceSpeedLimitUp                 );
        set_library_method(QT_STRINGIFY(ts3client_setInstanceSpeedLimitDown               ), setInstanceSpeedLimitDown               );
        set_library_method(QT_STRINGIFY(ts3client_setServerConnectionHandlerSpeedLimitUp  ), setServerConnectionHandlerSpeedLimitUp  );
        set_library_method(QT_STRINGIFY(ts3client_setServerConnectionHandlerSpeedLimitDown), setServerConnectionHandlerSpeedLimitDown);
        set_library_method(QT_STRINGIFY(ts3client_setTransferSpeedLimit                   ), setTransferSpeedLimit                   );
    }

    template <class T>
    inline void set_library_method(const char* name, T& method)
    {
        method = (T)(handle->resolve(name));
    }

    QLibrary* handle = nullptr;

    ts3client::freeMemory                               freeMemory                               = Q_NULLPTR;
    ts3client::initClientLib                            initClientLib                            = Q_NULLPTR;
    ts3client::destroyClientLib                         destroyClientLib                         = Q_NULLPTR;
    ts3client::getClientLibVersion                      getClientLibVersion                      = Q_NULLPTR;
    ts3client::getClientLibVersionNumber                getClientLibVersionNumber                = Q_NULLPTR;
    ts3client::spawnNewServerConnectionHandler          spawnNewServerConnectionHandler          = Q_NULLPTR;
    ts3client::destroyServerConnectionHandler           destroyServerConnectionHandler           = Q_NULLPTR;
    ts3client::createIdentity                           createIdentity                           = Q_NULLPTR;
    ts3client::identityStringToUniqueIdentifier         identityStringToUniqueIdentifier         = Q_NULLPTR;
    ts3client::getPlaybackDeviceList                    getPlaybackDeviceList                    = Q_NULLPTR;
    ts3client::getCaptureDeviceList                     getCaptureDeviceList                     = Q_NULLPTR;
    ts3client::getPlaybackModeList                      getPlaybackModeList                      = Q_NULLPTR;
    ts3client::getCaptureModeList                       getCaptureModeList                       = Q_NULLPTR;
    ts3client::getDefaultPlaybackDevice                 getDefaultPlaybackDevice                 = Q_NULLPTR;
    ts3client::getDefaultCaptureDevice                  getDefaultCaptureDevice                  = Q_NULLPTR;
    ts3client::getDefaultPlayBackMode                   getDefaultPlayBackMode                   = Q_NULLPTR;
    ts3client::getDefaultCaptureMode                    getDefaultCaptureMode                    = Q_NULLPTR;
    ts3client::openPlaybackDevice                       openPlaybackDevice                       = Q_NULLPTR;
    ts3client::openCaptureDevice                        openCaptureDevice                        = Q_NULLPTR;
    ts3client::getCurrentPlaybackDeviceName             getCurrentPlaybackDeviceName             = Q_NULLPTR;
    ts3client::getCurrentPlayBackMode                   getCurrentPlayBackMode                   = Q_NULLPTR;
    ts3client::getCurrentCaptureDeviceName              getCurrentCaptureDeviceName              = Q_NULLPTR;
    ts3client::getCurrentCaptureMode                    getCurrentCaptureMode                    = Q_NULLPTR;
    ts3client::initiateGracefulPlaybackShutdown         initiateGracefulPlaybackShutdown         = Q_NULLPTR;
    ts3client::closePlaybackDevice                      closePlaybackDevice                      = Q_NULLPTR;
    ts3client::closeCaptureDevice                       closeCaptureDevice                       = Q_NULLPTR;
    ts3client::activateCaptureDevice                    activateCaptureDevice                    = Q_NULLPTR;
    ts3client::playWaveFile                             playWaveFile                             = Q_NULLPTR;
    ts3client::playWaveFileHandle                       playWaveFileHandle                       = Q_NULLPTR;
    ts3client::pauseWaveFileHandle                      pauseWaveFileHandle                      = Q_NULLPTR;
    ts3client::closeWaveFileHandle                      closeWaveFileHandle                      = Q_NULLPTR;
    ts3client::registerCustomDevice                     registerCustomDevice                     = Q_NULLPTR;
    ts3client::unregisterCustomDevice                   unregisterCustomDevice                   = Q_NULLPTR;
    ts3client::processCustomCaptureData                 processCustomCaptureData                 = Q_NULLPTR;
    ts3client::acquireCustomPlaybackData                acquireCustomPlaybackData                = Q_NULLPTR;
    ts3client::setLocalTestMode                         setLocalTestMode                         = Q_NULLPTR;
    ts3client::startVoiceRecording                      startVoiceRecording                      = Q_NULLPTR;
    ts3client::stopVoiceRecording                       stopVoiceRecording                       = Q_NULLPTR;
    ts3client::allowWhispersFrom                        allowWhispersFrom                        = Q_NULLPTR;
    ts3client::removeFromAllowedWhispersFrom            removeFromAllowedWhispersFrom            = Q_NULLPTR;
    ts3client::systemset3DListenerAttributes            systemset3DListenerAttributes            = Q_NULLPTR;
    ts3client::set3DWaveAttributes                      set3DWaveAttributes                      = Q_NULLPTR;
    ts3client::systemset3DSettings                      systemset3DSettings                      = Q_NULLPTR;
    ts3client::channelset3DAttributes                   channelset3DAttributes                   = Q_NULLPTR;
    ts3client::getPreProcessorInfoValueFloat            getPreProcessorInfoValueFloat            = Q_NULLPTR;
    ts3client::getPreProcessorConfigValue               getPreProcessorConfigValue               = Q_NULLPTR;
    ts3client::setPreProcessorConfigValue               setPreProcessorConfigValue               = Q_NULLPTR;
    ts3client::getEncodeConfigValue                     getEncodeConfigValue                     = Q_NULLPTR;
    ts3client::getPlaybackConfigValueAsFloat            getPlaybackConfigValueAsFloat            = Q_NULLPTR;
    ts3client::setPlaybackConfigValue                   setPlaybackConfigValue                   = Q_NULLPTR;
    ts3client::setClientVolumeModifier                  setClientVolumeModifier                  = Q_NULLPTR;
    ts3client::logMessage                               logMessage                               = Q_NULLPTR;
    ts3client::setLogVerbosity                          setLogVerbosity                          = Q_NULLPTR;
    ts3client::getErrorMessage                          getErrorMessage                          = Q_NULLPTR;
    ts3client::startConnection                          startConnection                          = Q_NULLPTR;
    ts3client::startConnectionWithChannelID             startConnectionWithChannelID             = Q_NULLPTR;
    ts3client::stopConnection                           stopConnection                           = Q_NULLPTR;
    ts3client::requestClientMove                        requestClientMove                        = Q_NULLPTR;
    ts3client::requestClientVariables                   requestClientVariables                   = Q_NULLPTR;
    ts3client::requestClientKickFromChannel             requestClientKickFromChannel             = Q_NULLPTR;
    ts3client::requestClientKickFromServer              requestClientKickFromServer              = Q_NULLPTR;
    ts3client::requestChannelDelete                     requestChannelDelete                     = Q_NULLPTR;
    ts3client::requestChannelMove                       requestChannelMove                       = Q_NULLPTR;
    ts3client::requestSendPrivateTextMsg                requestSendPrivateTextMsg                = Q_NULLPTR;
    ts3client::requestSendChannelTextMsg                requestSendChannelTextMsg                = Q_NULLPTR;
    ts3client::requestSendServerTextMsg                 requestSendServerTextMsg                 = Q_NULLPTR;
    ts3client::requestConnectionInfo                    requestConnectionInfo                    = Q_NULLPTR;
    ts3client::requestClientSetWhisperList              requestClientSetWhisperList              = Q_NULLPTR;
    ts3client::requestChannelSubscribe                  requestChannelSubscribe                  = Q_NULLPTR;
    ts3client::requestChannelSubscribeAll               requestChannelSubscribeAll               = Q_NULLPTR;
    ts3client::requestChannelUnsubscribe                requestChannelUnsubscribe                = Q_NULLPTR;
    ts3client::requestChannelUnsubscribeAll             requestChannelUnsubscribeAll             = Q_NULLPTR;
    ts3client::requestChannelDescription                requestChannelDescription                = Q_NULLPTR;
    ts3client::requestMuteClients                       requestMuteClients                       = Q_NULLPTR;
    ts3client::requestUnmuteClients                     requestUnmuteClients                     = Q_NULLPTR;
    ts3client::requestClientIDs                         requestClientIDs                         = Q_NULLPTR;
    ts3client::requestSlotsFromProvisioningServer       requestSlotsFromProvisioningServer       = Q_NULLPTR;
    ts3client::cancelRequestSlotsFromProvisioningServer cancelRequestSlotsFromProvisioningServer = Q_NULLPTR;
    ts3client::startConnectionWithProvisioningKey       startConnectionWithProvisioningKey       = Q_NULLPTR;
    ts3client::getClientID                              getClientID                              = Q_NULLPTR;
    ts3client::getConnectionStatus                      getConnectionStatus                      = Q_NULLPTR;
    ts3client::getConnectionVariableAsUInt64            getConnectionVariableAsUInt64            = Q_NULLPTR;
    ts3client::getConnectionVariableAsDouble            getConnectionVariableAsDouble            = Q_NULLPTR;
    ts3client::getConnectionVariableAsString            getConnectionVariableAsString            = Q_NULLPTR;
    ts3client::cleanUpConnectionInfo                    cleanUpConnectionInfo                    = Q_NULLPTR;
    ts3client::requestServerConnectionInfo              requestServerConnectionInfo              = Q_NULLPTR;
    ts3client::getServerConnectionVariableAsUInt64      getServerConnectionVariableAsUInt64      = Q_NULLPTR;
    ts3client::getServerConnectionVariableAsFloat       getServerConnectionVariableAsFloat       = Q_NULLPTR;
    ts3client::getClientSelfVariableAsInt               getClientSelfVariableAsInt               = Q_NULLPTR;
    ts3client::getClientSelfVariableAsString            getClientSelfVariableAsString            = Q_NULLPTR;
    ts3client::setClientSelfVariableAsInt               setClientSelfVariableAsInt               = Q_NULLPTR;
    ts3client::setClientSelfVariableAsString            setClientSelfVariableAsString            = Q_NULLPTR;
    ts3client::flushClientSelfUpdates                   flushClientSelfUpdates                   = Q_NULLPTR;
    ts3client::getClientVariableAsInt                   getClientVariableAsInt                   = Q_NULLPTR;
    ts3client::getClientVariableAsUInt64                getClientVariableAsUInt64                = Q_NULLPTR;
    ts3client::getClientVariableAsString                getClientVariableAsString                = Q_NULLPTR;
    ts3client::getClientList                            getClientList                            = Q_NULLPTR;
    ts3client::getChannelOfClient                       getChannelOfClient                       = Q_NULLPTR;
    ts3client::getChannelVariableAsInt                  getChannelVariableAsInt                  = Q_NULLPTR;
    ts3client::getChannelVariableAsUInt64               getChannelVariableAsUInt64               = Q_NULLPTR;
    ts3client::getChannelVariableAsString               getChannelVariableAsString               = Q_NULLPTR;
    ts3client::getChannelIDFromChannelNames             getChannelIDFromChannelNames             = Q_NULLPTR;
    ts3client::setChannelVariableAsInt                  setChannelVariableAsInt                  = Q_NULLPTR;
    ts3client::setChannelVariableAsUInt64               setChannelVariableAsUInt64               = Q_NULLPTR;
    ts3client::setChannelVariableAsString               setChannelVariableAsString               = Q_NULLPTR;
    ts3client::flushChannelUpdates                      flushChannelUpdates                      = Q_NULLPTR;
    ts3client::flushChannelCreation                     flushChannelCreation                     = Q_NULLPTR;
    ts3client::getChannelList                           getChannelList                           = Q_NULLPTR;
    ts3client::getChannelClientList                     getChannelClientList                     = Q_NULLPTR;
    ts3client::getParentChannelOfChannel                getParentChannelOfChannel                = Q_NULLPTR;
    ts3client::getChannelEmptySecs                      getChannelEmptySecs                      = Q_NULLPTR;
    ts3client::getServerConnectionHandlerList           getServerConnectionHandlerList           = Q_NULLPTR;
    ts3client::getServerVariableAsInt                   getServerVariableAsInt                   = Q_NULLPTR;
    ts3client::getServerVariableAsUInt64                getServerVariableAsUInt64                = Q_NULLPTR;
    ts3client::getServerVariableAsString                getServerVariableAsString                = Q_NULLPTR;
    ts3client::requestServerVariables                   requestServerVariables                   = Q_NULLPTR;
    ts3client::getTransferFileName                      getTransferFileName                      = Q_NULLPTR;
    ts3client::getTransferFilePath                      getTransferFilePath                      = Q_NULLPTR;
    ts3client::getTransferFileRemotePath                getTransferFileRemotePath                = Q_NULLPTR;
    ts3client::getTransferFileSize                      getTransferFileSize                      = Q_NULLPTR;
    ts3client::getTransferFileSizeDone                  getTransferFileSizeDone                  = Q_NULLPTR;
    ts3client::isTransferSender                         isTransferSender                         = Q_NULLPTR;
    ts3client::getTransferStatus                        getTransferStatus                        = Q_NULLPTR;
    ts3client::getCurrentTransferSpeed                  getCurrentTransferSpeed                  = Q_NULLPTR;
    ts3client::getAverageTransferSpeed                  getAverageTransferSpeed                  = Q_NULLPTR;
    ts3client::getTransferRunTime                       getTransferRunTime                       = Q_NULLPTR;
    ts3client::sendFile                                 sendFile                                 = Q_NULLPTR;
    ts3client::requestFile                              requestFile                              = Q_NULLPTR;
    ts3client::haltTransfer                             haltTransfer                             = Q_NULLPTR;
    ts3client::requestFileList                          requestFileList                          = Q_NULLPTR;
    ts3client::requestFileInfo                          requestFileInfo                          = Q_NULLPTR;
    ts3client::requestDeleteFile                        requestDeleteFile                        = Q_NULLPTR;
    ts3client::requestCreateDirectory                   requestCreateDirectory                   = Q_NULLPTR;
    ts3client::requestRenameFile                        requestRenameFile                        = Q_NULLPTR;
    ts3client::getInstanceSpeedLimitUp                  getInstanceSpeedLimitUp                  = Q_NULLPTR;
    ts3client::getInstanceSpeedLimitDown                getInstanceSpeedLimitDown                = Q_NULLPTR;
    ts3client::getServerConnectionHandlerSpeedLimitUp   getServerConnectionHandlerSpeedLimitUp   = Q_NULLPTR;
    ts3client::getServerConnectionHandlerSpeedLimitDown getServerConnectionHandlerSpeedLimitDown = Q_NULLPTR;
    ts3client::getTransferSpeedLimit                    getTransferSpeedLimit                    = Q_NULLPTR;
    ts3client::setInstanceSpeedLimitUp                  setInstanceSpeedLimitUp                  = Q_NULLPTR;
    ts3client::setInstanceSpeedLimitDown                setInstanceSpeedLimitDown                = Q_NULLPTR;
    ts3client::setServerConnectionHandlerSpeedLimitUp   setServerConnectionHandlerSpeedLimitUp   = Q_NULLPTR;
    ts3client::setServerConnectionHandlerSpeedLimitDown setServerConnectionHandlerSpeedLimitDown = Q_NULLPTR;
    ts3client::setTransferSpeedLimit                    setTransferSpeedLimit                    = Q_NULLPTR;

};

} // namespace TeamSpeakSdk

