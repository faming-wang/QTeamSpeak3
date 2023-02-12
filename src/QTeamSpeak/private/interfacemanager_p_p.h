#pragma once

#include "utils_p.h"

#include "library.h"
#include "namespace.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
struct ClientUIFunctionsRare;
struct ClientUIFunctions {
void (*onConnectStatusChangeEvent             )(quint64 serverID, int newStatus, uint errorNumber);
void (*onServerProtocolVersionEvent           )(quint64 serverID, int protocolVersion);
void (*onNewChannelEvent                      )(quint64 serverID, quint64 channelID, quint64 channelParentID);
void (*onNewChannelCreatedEvent               )(quint64 serverID, quint64 channelID, quint64 channelParentID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onDelChannelEvent                      )(quint64 serverID, quint64 channelID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onChannelMoveEvent                     )(quint64 serverID, quint64 channelID, quint64 newChannelParentID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onUpdateChannelEvent                   )(quint64 serverID, quint64 channelID);
void (*onUpdateChannelEditedEvent             )(quint64 serverID, quint64 channelID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onUpdateClientEvent                    )(quint64 serverID, quint16 clientID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
void (*onClientMoveEvent                      )(quint64 serverID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, const char* moveMessage);
void (*onClientMoveSubscriptionEvent          )(quint64 serverID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility);
void (*onClientMoveTimeoutEvent               )(quint64 serverID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, const char* timeoutMessage);
void (*onClientMoveMovedEvent                 )(quint64 serverID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage);
void (*onClientKickFromChannelEvent           )(quint64 serverID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
void (*onClientKickFromServerEvent            )(quint64 serverID, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
void (*onClientIDsEvent                       )(quint64 serverID, const char* uniqueClientIdentifier, quint16 clientID, const char* clientName);
void (*onClientIDsFinishedEvent               )(quint64 serverID);
void (*onServerEditedEvent                    )(quint64 serverID, quint16 editerID, const char* editerName, const char* editerUniqueIdentifier);
void (*onServerUpdatedEvent                   )(quint64 serverID);
void (*onServerErrorEvent                     )(quint64 serverID, const char* errorMessage, uint error, const char* returnCode, const char* extraMessage);
void (*onServerStopEvent                      )(quint64 serverID, const char* shutdownMessage);
void (*onTextMessageEvent                     )(quint64 serverID, quint16 targetMode, quint16 toID, quint16 fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
void (*onTalkStatusChangeEvent                )(quint64 serverID, int status, int isReceivedWhisper, quint16 clientID);
void (*onIgnoredWhisperEvent                  )(quint64 serverID, quint16 clientID);
void (*onConnectionInfoEvent                  )(quint64 serverID, quint16 clientID);
void (*onServerConnectionInfoEvent            )(quint64 serverID);
void (*onChannelSubscribeEvent                )(quint64 serverID, quint64 channelID);
void (*onChannelSubscribeFinishedEvent        )(quint64 serverID);
void (*onChannelUnsubscribeEvent              )(quint64 serverID, quint64 channelID);
void (*onChannelUnsubscribeFinishedEvent      )(quint64 serverID);
void (*onChannelDescriptionUpdateEvent        )(quint64 serverID, quint64 channelID);
void (*onChannelPasswordChangedEvent          )(quint64 serverID, quint64 channelID);
void (*onPlaybackShutdownCompleteEvent        )(quint64 serverID);
void (*onSoundDeviceListChangedEvent          )(const char* modeID, int playOrCap);
void (*onEditPlaybackVoiceDataEvent           )(quint64 serverID, quint16 clientID, short* samples, int sampleCount, int channels);
void (*onEditPostProcessVoiceDataEvent        )(quint64 serverID, quint16 clientID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
void (*onEditMixedPlaybackVoiceDataEvent      )(quint64 serverID, short* samples, int sampleCount, int channels, const uint* channelSpeakerArray, uint* channelFillMask);
void (*onEditCapturedVoiceDataEvent           )(quint64 serverID, short* samples, int sampleCount, int channels, int* edited);
void (*onCustom3dRolloffCalculationClientEvent)(quint64 serverID, quint16 clientID, float distance, float* volume);
void (*onCustom3dRolloffCalculationWaveEvent  )(quint64 serverID, quint64 waveHandle, float distance, float* volume);
void (*onUserLoggingMessageEvent              )(const char* logmessage, int logLevel, const char* logChannel, quint64 logID, const char* logTime, const char* completeLogString);
void (*onCustomPacketEncryptEvent             )(char** dataToSend, uint* sizeOfData);
void (*onCustomPacketDecryptEvent             )(char** dataReceived, uint* dataReceivedSize);
void (*onProvisioningSlotRequestResultEvent   )(uint error, quint64 requestHandle, const char* connectionKey);
void (*onCheckServerUniqueIdentifierEvent     )(quint64 serverID, const char* ServerUniqueIdentifier, int* cancelConnect);
void (*onClientPasswordEncrypt                )(quint64 serverID, const char* plaintext, char* encryptedText, int encryptedTextByteSize);
void (*onFileTransferStatusEvent              )(quint16 transferID, uint status, const char* statusMessage, quint64 remotefileSize, quint64 serverID);
void (*onFileListEvent                        )(quint64 serverID, quint64 channelID, const char* path, const char* name, quint64 size, quint64 datetime, int type, quint64 incompletesize, const char* returnCode);
void (*onFileListFinishedEvent                )(quint64 serverID, quint64 channelID, const char* path);
void (*onFileInfoEvent                        )(quint64 serverID, quint64 channelID, const char* name, quint64 size, quint64 datetime);
}; // END OF ClientUIFunctions
#ifdef __cplusplus
}
#endif // __cplusplus

namespace QTeamSpeak {
namespace ts3client {
/* Memory management */
using freeMemory = uint(*)(void* pointer);

/* Construction and Destruction */
using initClientLib             = uint(*)(const struct ClientUIFunctions* functionPointers, const struct ClientUIFunctionsRare* functionRarePointers, int usedLogTypes, const char* logFileFolder, const char* resourcesFolder);
using destroyClientLib          = uint(*)();
using getClientLibVersion       = uint(*)(char** result);
using getClientLibVersionNumber = uint(*)(quint64* result);

using spawnNewServerConnectionHandler = uint (*)(int port, quint64* result);
using destroyServerConnectionHandler  = uint (*)(quint64 serverID);

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

using openPlaybackDevice               = uint(*)(quint64 serverID, const char* modeID, const char* playbackDevice);
using openCaptureDevice                = uint(*)(quint64 serverID, const char* modeID, const char* captureDevice);
using getCurrentPlaybackDeviceName     = uint(*)(quint64 serverID, char** result, int* isDefault);
using getCurrentPlayBackMode           = uint(*)(quint64 serverID, char** result);
using getCurrentCaptureDeviceName      = uint(*)(quint64 serverID, char** result, int* isDefault);
using getCurrentCaptureMode            = uint(*)(quint64 serverID, char** result);
using initiateGracefulPlaybackShutdown = uint(*)(quint64 serverID);
using closePlaybackDevice              = uint(*)(quint64 serverID);
using closeCaptureDevice               = uint(*)(quint64 serverID);
using activateCaptureDevice            = uint(*)(quint64 serverID);

using playWaveFile        = uint(*)(quint64 serverID, const char* path);
using playWaveFileHandle  = uint(*)(quint64 serverID, const char* path, int loop, quint64* waveHandle);
using pauseWaveFileHandle = uint(*)(quint64 serverID, quint64 waveHandle, int pause);
using closeWaveFileHandle = uint(*)(quint64 serverID, quint64 waveHandle);

using registerCustomDevice      = uint(*)(const char* deviceID, const char* deviceDisplayName, int capFrequency, int capChannels, int playFrequency, int playChannels);
using unregisterCustomDevice    = uint(*)(const char* deviceID);
using processCustomCaptureData  = uint(*)(const char* deviceName, const short* buffer, int samples);
using acquireCustomPlaybackData = uint(*)(const char* deviceName, short* buffer, int samples);

using setLocalTestMode =  uint(*)(quint64 serverID, int status);

using startVoiceRecording = uint(*)(quint64 serverID);
using stopVoiceRecording  = uint(*)(quint64 serverID);

using allowWhispersFrom             = uint(*)(quint64 serverID, quint16 clID);
using removeFromAllowedWhispersFrom = uint(*)(quint64 serverID, quint16 clID);

/* 3d sound positioning */
using systemset3DListenerAttributes = uint(*)(quint64 serverID, const Vector3D* position, const Vector3D* forward, const Vector3D* up);
using set3DWaveAttributes           = uint(*)(quint64 serverID, quint64 waveHandle, const Vector3D* position);
using systemset3DSettings           = uint(*)(quint64 serverID, float distanceFactor, float rolloffScale);
using channelset3DAttributes        = uint(*)(quint64 serverID, quint16 clientID, const Vector3D* position);

/*preprocessor*/
using getPreProcessorInfoValueFloat = uint(*)(quint64 serverID, const char* ident, float* result);
using getPreProcessorConfigValue    = uint(*)(quint64 serverID, const char* ident, char** result);
using setPreProcessorConfigValue    = uint(*)(quint64 serverID, const char* ident, const char* value);

/*encoder*/
using getEncodeConfigValue = uint(*)(quint64 serverID, const char* ident, char** result);

/*playback*/
using getPlaybackConfigValueAsFloat = uint(*)(quint64 serverID, const char* ident, float* result);
using setPlaybackConfigValue        = uint(*)(quint64 serverID, const char* ident, const char* value);
using setClientVolumeModifier       = uint(*)(quint64 serverID, quint16 clientID, float value);

/*logging*/
using logMessage      = uint(*)(const char* logMessage, LogLevel severity, const char* channel, quint64 logID);
using setLogVerbosity = uint(*)(LogLevel logVerbosity);

/*error handling*/
using getErrorMessage = uint(*)(uint errorCode, char** error);

/*Interacting with the server*/
using startConnection = uint(*)(quint64 serverID, const char* identity, const char* ip, uint port, const char* nickname,
const char** defaultChannelArray, const char* defaultChannelPassword, const char* serverPassword);
using startConnectionWithChannelID = uint(*)(quint64 serverID, const char* identity, const char* ip, uint port, const char* nickname,
quint64 defaultChannelId, const char* defaultChannelPassword, const char* serverPassword);

using stopConnection               = uint(*)(quint64 serverID, const char* quitMessage);
using requestClientMove            = uint(*)(quint64 serverID, quint16 clientID, quint64 newChannelID, const char* password, const char* returnCode);
using requestClientVariables       = uint(*)(quint64 serverID, quint16 clientID, const char* returnCode);
using requestClientKickFromChannel = uint(*)(quint64 serverID, quint16 clientID, const char* kickReason, const char* returnCode);
using requestClientKickFromServer  = uint(*)(quint64 serverID, quint16 clientID, const char* kickReason, const char* returnCode);
using requestChannelDelete         = uint(*)(quint64 serverID, quint64 channelID, int force, const char* returnCode);
using requestChannelMove           = uint(*)(quint64 serverID, quint64 channelID, quint64 newChannelParentID, quint64 newChannelOrder, const char* returnCode);
using requestSendPrivateTextMsg    = uint(*)(quint64 serverID, const char* message, quint16 targetClientID, const char* returnCode);
using requestSendChannelTextMsg    = uint(*)(quint64 serverID, const char* message, quint64 targetChannelID, const char* returnCode);
using requestSendServerTextMsg     = uint(*)(quint64 serverID, const char* message, const char* returnCode);
using requestConnectionInfo        = uint(*)(quint64 serverID, quint16 clientID, const char* returnCode);
using requestClientSetWhisperList  = uint(*)(quint64 serverID, quint16 clientID, const quint64* targetChannelIDArray, const quint16* targetClientIDArray, const char* returnCode);
using requestChannelSubscribe      = uint(*)(quint64 serverID, const quint64* channelIDArray, const char* returnCode);
using requestChannelSubscribeAll   = uint(*)(quint64 serverID, const char* returnCode);
using requestChannelUnsubscribe    = uint(*)(quint64 serverID, const quint64* channelIDArray, const char* returnCode);
using requestChannelUnsubscribeAll = uint(*)(quint64 serverID, const char* returnCode);
using requestChannelDescription    = uint(*)(quint64 serverID, quint64 channelID, const char* returnCode);
using requestMuteClients           = uint(*)(quint64 serverID, const quint16* clientIDArray, const char* returnCode);
using requestUnmuteClients         = uint(*)(quint64 serverID, const quint16* clientIDArray, const char* returnCode);
using requestClientIDs             = uint(*)(quint64 serverID, const char* clientUniqueIdentifier, const char* returnCode);

/*provisioning server calls*/
using requestSlotsFromProvisioningServer       = uint(*)(const char* ip, unsigned short port, const char* serverPassword, unsigned short slots, const char* identity, const char* region, quint64* requestHandle);
using cancelRequestSlotsFromProvisioningServer = uint(*)(quint64 requestHandle);
using startConnectionWithProvisioningKey       = uint(*)(quint64 serverID, const char* identity, const char* nickname, const char* connectionKey, const char* clientMetaData);

/*retrieve information ClientLib has stored*/

/*general info*/
using getClientID = uint(*)(quint64 serverID, quint16* result);

/*client connection info*/
using getConnectionStatus           = uint(*)(quint64 serverID, int* result);
using getConnectionVariableAsUInt64 = uint(*)(quint64 serverID, quint16 clientID, size_t flag, quint64* result);
using getConnectionVariableAsDouble = uint(*)(quint64 serverID, quint16 clientID, size_t flag, double* result);
using getConnectionVariableAsString = uint(*)(quint64 serverID, quint16 clientID, size_t flag, char** result);
using cleanUpConnectionInfo         = uint(*)(quint64 serverID, quint16 clientID);

/*server connection info*/
using requestServerConnectionInfo         = uint(*)(quint64 serverID, const char* returnCode);
using getServerConnectionVariableAsUInt64 = uint(*)(quint64 serverID, size_t flag, quint64* result);
using getServerConnectionVariableAsFloat  = uint(*)(quint64 serverID, size_t flag, float* result);

/*client info*/
using getClientSelfVariableAsInt    = uint(*)(quint64 serverID, size_t flag, int* result);
using getClientSelfVariableAsString = uint(*)(quint64 serverID, size_t flag, char** result);
using setClientSelfVariableAsInt    = uint(*)(quint64 serverID, size_t flag, int value);
using setClientSelfVariableAsString = uint(*)(quint64 serverID, size_t flag, const char* value);
using flushClientSelfUpdates        = uint(*)(quint64 serverID, const char* returnCode);

using getClientVariableAsInt    = uint(*)(quint64 serverID, quint16 clientID, size_t flag, int* result);
using getClientVariableAsUInt64 = uint(*)(quint64 serverID, quint16 clientID, size_t flag, quint64* result);
using getClientVariableAsString = uint(*)(quint64 serverID, quint16 clientID, size_t flag, char** result);

using getClientList      = uint(*)(quint64 serverID, quint16** result);
using getChannelOfClient = uint(*)(quint64 serverID, quint16 clientID, quint64* result);

/*channel info*/
using getChannelVariableAsInt    = uint(*)(quint64 serverID, quint64 channelID, size_t flag, int* result);
using getChannelVariableAsUInt64 = uint(*)(quint64 serverID, quint64 channelID, size_t flag, quint64* result);
using getChannelVariableAsString = uint(*)(quint64 serverID, quint64 channelID, size_t flag, char** result);

using getChannelIDFromChannelNames = uint(*)(quint64 serverID, char** channelNameArray, quint64* result);
using setChannelVariableAsInt      = uint(*)(quint64 serverID, quint64 channelID, size_t flag, int value);
using setChannelVariableAsUInt64   = uint(*)(quint64 serverID, quint64 channelID, size_t flag, quint64 value);
using setChannelVariableAsString   = uint(*)(quint64 serverID, quint64 channelID, size_t flag, const char* value);
using flushChannelUpdates          = uint(*)(quint64 serverID, quint64 channelID, const char* returnCode);
using flushChannelCreation         = uint(*)(quint64 serverID, quint64 channelParentID, const char* returnCode);

using getChannelList            = uint(*)(quint64 serverID, quint64** result);
using getChannelClientList      = uint(*)(quint64 serverID, quint64 channelID, quint16** result);
using getParentChannelOfChannel = uint(*)(quint64 serverID, quint64 channelID, quint64* result);
using getChannelEmptySecs       = uint(*)(quint64 serverID, quint64 channelID, int* result);

/*server info*/
using getServerConnectionHandlerList = uint(*)(quint64** result);
using getServerVariableAsInt         = uint(*)(quint64 serverID, size_t flag, int* result);
using getServerVariableAsUInt64      = uint(*)(quint64 serverID, size_t flag, quint64* result);
using getServerVariableAsString      = uint(*)(quint64 serverID, size_t flag, char** result);
using requestServerVariables         = uint(*)(quint64 serverID);

/*filetransfer management*/
using getTransferFileName       = uint(*)(quint16 transferID, char** result); //The returned memory is dynamically allocated, remember to call ts3client::freeMemory() to release it
using getTransferFilePath       = uint(*)(quint16 transferID, char** result); //The returned memory is dynamically allocated, remember to call ts3client::freeMemory() to release it
using getTransferFileRemotePath = uint(*)(quint16 transferID, char** result); //The returned memory is dynamically allocated, remember to call ts3client::freeMemory() to release it
using getTransferFileSize       = uint(*)(quint16 transferID, quint64* result);
using getTransferFileSizeDone   = uint(*)(quint16 transferID, quint64* result);
using isTransferSender          = uint(*)(quint16 transferID, int* result); //1 == upload, 0 == download
using getTransferStatus         = uint(*)(quint16 transferID, int* result);
using getCurrentTransferSpeed   = uint(*)(quint16 transferID, float* result); //bytes/second within the last few seconds
using getAverageTransferSpeed   = uint(*)(quint16 transferID, float* result); //bytes/second since start of the transfer
using getTransferRunTime        = uint(*)(quint16 transferID, quint64* result);

/*Interacting with the server - file transfers*/
using sendFile                                 = uint(*)(quint64 serverID, quint64 channelID, const char* channelPW, const char* file, int overwrite, int resume, const char* sourceDirectory, quint16* result, const char* returnCode);
using requestFile                              = uint(*)(quint64 serverID, quint64 channelID, const char* channelPW, const char* file, int overwrite, int resume, const char* destinationDirectory, quint16* result, const char* returnCode);
using haltTransfer                             = uint(*)(quint64 serverID, quint16 transferID, int deleteUnfinishedFile, const char* returnCode);
using requestFileList                          = uint(*)(quint64 serverID, quint64 channelID, const char* channelPW, const char* path, const char* returnCode);
using requestFileInfo                          = uint(*)(quint64 serverID, quint64 channelID, const char* channelPW, const char* file, const char* returnCode);
using requestDeleteFile                        = uint(*)(quint64 serverID, quint64 channelID, const char* channelPW, const char** file, const char* returnCode);
using requestCreateDirectory                   = uint(*)(quint64 serverID, quint64 channelID, const char* channelPW, const char* directoryPath, const char* returnCode);
using requestRenameFile                        = uint(*)(quint64 serverID, quint64 fromChannelID, const char* fromChannelPW, quint64 toChannelID, const char* toChannelPW, const char* oldFile, const char* newFile, const char* returnCode);
using getInstanceSpeedLimitUp                  = uint(*)(quint64 *limit);
using getInstanceSpeedLimitDown                = uint(*)(quint64 *limit);
using getServerConnectionHandlerSpeedLimitUp   = uint(*)(quint64 serverID, quint64*  limit);
using getServerConnectionHandlerSpeedLimitDown = uint(*)(quint64 serverID, quint64* limit);
using getTransferSpeedLimit                    = uint(*)(quint16 transferID, quint64* limit);
using setInstanceSpeedLimitUp                  = uint(*)(quint64 newLimit);
using setInstanceSpeedLimitDown                = uint(*)(quint64 newLimit);
using setServerConnectionHandlerSpeedLimitUp   = uint(*)(quint64 serverID, quint64 newLimit);
using setServerConnectionHandlerSpeedLimitDown = uint(*)(quint64 serverID, quint64 newLimit);
using setTransferSpeedLimit                    = uint(*)(quint16 transferID, quint64 newLimit);

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

        quint64 version = 0; getClientLibVersionNumber(&version);
        if (version >= Utils::underlay(Library::Version::V_3_0_4))
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

    ts3client::freeMemory                               freeMemory                               = nullptr;
    ts3client::initClientLib                            initClientLib                            = nullptr;
    ts3client::destroyClientLib                         destroyClientLib                         = nullptr;
    ts3client::getClientLibVersion                      getClientLibVersion                      = nullptr;
    ts3client::getClientLibVersionNumber                getClientLibVersionNumber                = nullptr;
    ts3client::spawnNewServerConnectionHandler          spawnNewServerConnectionHandler          = nullptr;
    ts3client::destroyServerConnectionHandler           destroyServerConnectionHandler           = nullptr;
    ts3client::createIdentity                           createIdentity                           = nullptr;
    ts3client::identityStringToUniqueIdentifier         identityStringToUniqueIdentifier         = nullptr;
    ts3client::getPlaybackDeviceList                    getPlaybackDeviceList                    = nullptr;
    ts3client::getCaptureDeviceList                     getCaptureDeviceList                     = nullptr;
    ts3client::getPlaybackModeList                      getPlaybackModeList                      = nullptr;
    ts3client::getCaptureModeList                       getCaptureModeList                       = nullptr;
    ts3client::getDefaultPlaybackDevice                 getDefaultPlaybackDevice                 = nullptr;
    ts3client::getDefaultCaptureDevice                  getDefaultCaptureDevice                  = nullptr;
    ts3client::getDefaultPlayBackMode                   getDefaultPlayBackMode                   = nullptr;
    ts3client::getDefaultCaptureMode                    getDefaultCaptureMode                    = nullptr;
    ts3client::openPlaybackDevice                       openPlaybackDevice                       = nullptr;
    ts3client::openCaptureDevice                        openCaptureDevice                        = nullptr;
    ts3client::getCurrentPlaybackDeviceName             getCurrentPlaybackDeviceName             = nullptr;
    ts3client::getCurrentPlayBackMode                   getCurrentPlayBackMode                   = nullptr;
    ts3client::getCurrentCaptureDeviceName              getCurrentCaptureDeviceName              = nullptr;
    ts3client::getCurrentCaptureMode                    getCurrentCaptureMode                    = nullptr;
    ts3client::initiateGracefulPlaybackShutdown         initiateGracefulPlaybackShutdown         = nullptr;
    ts3client::closePlaybackDevice                      closePlaybackDevice                      = nullptr;
    ts3client::closeCaptureDevice                       closeCaptureDevice                       = nullptr;
    ts3client::activateCaptureDevice                    activateCaptureDevice                    = nullptr;
    ts3client::playWaveFile                             playWaveFile                             = nullptr;
    ts3client::playWaveFileHandle                       playWaveFileHandle                       = nullptr;
    ts3client::pauseWaveFileHandle                      pauseWaveFileHandle                      = nullptr;
    ts3client::closeWaveFileHandle                      closeWaveFileHandle                      = nullptr;
    ts3client::registerCustomDevice                     registerCustomDevice                     = nullptr;
    ts3client::unregisterCustomDevice                   unregisterCustomDevice                   = nullptr;
    ts3client::processCustomCaptureData                 processCustomCaptureData                 = nullptr;
    ts3client::acquireCustomPlaybackData                acquireCustomPlaybackData                = nullptr;
    ts3client::setLocalTestMode                         setLocalTestMode                         = nullptr;
    ts3client::startVoiceRecording                      startVoiceRecording                      = nullptr;
    ts3client::stopVoiceRecording                       stopVoiceRecording                       = nullptr;
    ts3client::allowWhispersFrom                        allowWhispersFrom                        = nullptr;
    ts3client::removeFromAllowedWhispersFrom            removeFromAllowedWhispersFrom            = nullptr;
    ts3client::systemset3DListenerAttributes            systemset3DListenerAttributes            = nullptr;
    ts3client::set3DWaveAttributes                      set3DWaveAttributes                      = nullptr;
    ts3client::systemset3DSettings                      systemset3DSettings                      = nullptr;
    ts3client::channelset3DAttributes                   channelset3DAttributes                   = nullptr;
    ts3client::getPreProcessorInfoValueFloat            getPreProcessorInfoValueFloat            = nullptr;
    ts3client::getPreProcessorConfigValue               getPreProcessorConfigValue               = nullptr;
    ts3client::setPreProcessorConfigValue               setPreProcessorConfigValue               = nullptr;
    ts3client::getEncodeConfigValue                     getEncodeConfigValue                     = nullptr;
    ts3client::getPlaybackConfigValueAsFloat            getPlaybackConfigValueAsFloat            = nullptr;
    ts3client::setPlaybackConfigValue                   setPlaybackConfigValue                   = nullptr;
    ts3client::setClientVolumeModifier                  setClientVolumeModifier                  = nullptr;
    ts3client::logMessage                               logMessage                               = nullptr;
    ts3client::setLogVerbosity                          setLogVerbosity                          = nullptr;
    ts3client::getErrorMessage                          getErrorMessage                          = nullptr;
    ts3client::startConnection                          startConnection                          = nullptr;
    ts3client::startConnectionWithChannelID             startConnectionWithChannelID             = nullptr;
    ts3client::stopConnection                           stopConnection                           = nullptr;
    ts3client::requestClientMove                        requestClientMove                        = nullptr;
    ts3client::requestClientVariables                   requestClientVariables                   = nullptr;
    ts3client::requestClientKickFromChannel             requestClientKickFromChannel             = nullptr;
    ts3client::requestClientKickFromServer              requestClientKickFromServer              = nullptr;
    ts3client::requestChannelDelete                     requestChannelDelete                     = nullptr;
    ts3client::requestChannelMove                       requestChannelMove                       = nullptr;
    ts3client::requestSendPrivateTextMsg                requestSendPrivateTextMsg                = nullptr;
    ts3client::requestSendChannelTextMsg                requestSendChannelTextMsg                = nullptr;
    ts3client::requestSendServerTextMsg                 requestSendServerTextMsg                 = nullptr;
    ts3client::requestConnectionInfo                    requestConnectionInfo                    = nullptr;
    ts3client::requestClientSetWhisperList              requestClientSetWhisperList              = nullptr;
    ts3client::requestChannelSubscribe                  requestChannelSubscribe                  = nullptr;
    ts3client::requestChannelSubscribeAll               requestChannelSubscribeAll               = nullptr;
    ts3client::requestChannelUnsubscribe                requestChannelUnsubscribe                = nullptr;
    ts3client::requestChannelUnsubscribeAll             requestChannelUnsubscribeAll             = nullptr;
    ts3client::requestChannelDescription                requestChannelDescription                = nullptr;
    ts3client::requestMuteClients                       requestMuteClients                       = nullptr;
    ts3client::requestUnmuteClients                     requestUnmuteClients                     = nullptr;
    ts3client::requestClientIDs                         requestClientIDs                         = nullptr;
    ts3client::requestSlotsFromProvisioningServer       requestSlotsFromProvisioningServer       = nullptr;
    ts3client::cancelRequestSlotsFromProvisioningServer cancelRequestSlotsFromProvisioningServer = nullptr;
    ts3client::startConnectionWithProvisioningKey       startConnectionWithProvisioningKey       = nullptr;
    ts3client::getClientID                              getClientID                              = nullptr;
    ts3client::getConnectionStatus                      getConnectionStatus                      = nullptr;
    ts3client::getConnectionVariableAsUInt64            getConnectionVariableAsUInt64            = nullptr;
    ts3client::getConnectionVariableAsDouble            getConnectionVariableAsDouble            = nullptr;
    ts3client::getConnectionVariableAsString            getConnectionVariableAsString            = nullptr;
    ts3client::cleanUpConnectionInfo                    cleanUpConnectionInfo                    = nullptr;
    ts3client::requestServerConnectionInfo              requestServerConnectionInfo              = nullptr;
    ts3client::getServerConnectionVariableAsUInt64      getServerConnectionVariableAsUInt64      = nullptr;
    ts3client::getServerConnectionVariableAsFloat       getServerConnectionVariableAsFloat       = nullptr;
    ts3client::getClientSelfVariableAsInt               getClientSelfVariableAsInt               = nullptr;
    ts3client::getClientSelfVariableAsString            getClientSelfVariableAsString            = nullptr;
    ts3client::setClientSelfVariableAsInt               setClientSelfVariableAsInt               = nullptr;
    ts3client::setClientSelfVariableAsString            setClientSelfVariableAsString            = nullptr;
    ts3client::flushClientSelfUpdates                   flushClientSelfUpdates                   = nullptr;
    ts3client::getClientVariableAsInt                   getClientVariableAsInt                   = nullptr;
    ts3client::getClientVariableAsUInt64                getClientVariableAsUInt64                = nullptr;
    ts3client::getClientVariableAsString                getClientVariableAsString                = nullptr;
    ts3client::getClientList                            getClientList                            = nullptr;
    ts3client::getChannelOfClient                       getChannelOfClient                       = nullptr;
    ts3client::getChannelVariableAsInt                  getChannelVariableAsInt                  = nullptr;
    ts3client::getChannelVariableAsUInt64               getChannelVariableAsUInt64               = nullptr;
    ts3client::getChannelVariableAsString               getChannelVariableAsString               = nullptr;
    ts3client::getChannelIDFromChannelNames             getChannelIDFromChannelNames             = nullptr;
    ts3client::setChannelVariableAsInt                  setChannelVariableAsInt                  = nullptr;
    ts3client::setChannelVariableAsUInt64               setChannelVariableAsUInt64               = nullptr;
    ts3client::setChannelVariableAsString               setChannelVariableAsString               = nullptr;
    ts3client::flushChannelUpdates                      flushChannelUpdates                      = nullptr;
    ts3client::flushChannelCreation                     flushChannelCreation                     = nullptr;
    ts3client::getChannelList                           getChannelList                           = nullptr;
    ts3client::getChannelClientList                     getChannelClientList                     = nullptr;
    ts3client::getParentChannelOfChannel                getParentChannelOfChannel                = nullptr;
    ts3client::getChannelEmptySecs                      getChannelEmptySecs                      = nullptr;
    ts3client::getServerConnectionHandlerList           getServerConnectionHandlerList           = nullptr;
    ts3client::getServerVariableAsInt                   getServerVariableAsInt                   = nullptr;
    ts3client::getServerVariableAsUInt64                getServerVariableAsUInt64                = nullptr;
    ts3client::getServerVariableAsString                getServerVariableAsString                = nullptr;
    ts3client::requestServerVariables                   requestServerVariables                   = nullptr;
    ts3client::getTransferFileName                      getTransferFileName                      = nullptr;
    ts3client::getTransferFilePath                      getTransferFilePath                      = nullptr;
    ts3client::getTransferFileRemotePath                getTransferFileRemotePath                = nullptr;
    ts3client::getTransferFileSize                      getTransferFileSize                      = nullptr;
    ts3client::getTransferFileSizeDone                  getTransferFileSizeDone                  = nullptr;
    ts3client::isTransferSender                         isTransferSender                         = nullptr;
    ts3client::getTransferStatus                        getTransferStatus                        = nullptr;
    ts3client::getCurrentTransferSpeed                  getCurrentTransferSpeed                  = nullptr;
    ts3client::getAverageTransferSpeed                  getAverageTransferSpeed                  = nullptr;
    ts3client::getTransferRunTime                       getTransferRunTime                       = nullptr;
    ts3client::sendFile                                 sendFile                                 = nullptr;
    ts3client::requestFile                              requestFile                              = nullptr;
    ts3client::haltTransfer                             haltTransfer                             = nullptr;
    ts3client::requestFileList                          requestFileList                          = nullptr;
    ts3client::requestFileInfo                          requestFileInfo                          = nullptr;
    ts3client::requestDeleteFile                        requestDeleteFile                        = nullptr;
    ts3client::requestCreateDirectory                   requestCreateDirectory                   = nullptr;
    ts3client::requestRenameFile                        requestRenameFile                        = nullptr;
    ts3client::getInstanceSpeedLimitUp                  getInstanceSpeedLimitUp                  = nullptr;
    ts3client::getInstanceSpeedLimitDown                getInstanceSpeedLimitDown                = nullptr;
    ts3client::getServerConnectionHandlerSpeedLimitUp   getServerConnectionHandlerSpeedLimitUp   = nullptr;
    ts3client::getServerConnectionHandlerSpeedLimitDown getServerConnectionHandlerSpeedLimitDown = nullptr;
    ts3client::getTransferSpeedLimit                    getTransferSpeedLimit                    = nullptr;
    ts3client::setInstanceSpeedLimitUp                  setInstanceSpeedLimitUp                  = nullptr;
    ts3client::setInstanceSpeedLimitDown                setInstanceSpeedLimitDown                = nullptr;
    ts3client::setServerConnectionHandlerSpeedLimitUp   setServerConnectionHandlerSpeedLimitUp   = nullptr;
    ts3client::setServerConnectionHandlerSpeedLimitDown setServerConnectionHandlerSpeedLimitDown = nullptr;
    ts3client::setTransferSpeedLimit                    setTransferSpeedLimit                    = nullptr;

};

} // namespace QTeamSpeak

