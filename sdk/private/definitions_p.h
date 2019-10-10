#pragma once

namespace TeamSpeakSdk {

enum class ChannelProperty : size_t
{
    Name           = 0, // Available for all channels that are "in view", always up-to-date
    Topic             , // Available for all channels that are "in view", always up-to-date
    Description       , // Must be requested (=> requestChannelDescription)
    Password          , // not available client side
    Codec             , // Available for all channels that are "in view", always up-to-date
    CodecQuality      , // Available for all channels that are "in view", always up-to-date
    Maxclients        , // Available for all channels that are "in view", always up-to-date
    Maxfamilyclients  , // Available for all channels that are "in view", always up-to-date
    Order             , // Available for all channels that are "in view", always up-to-date
    FlagPermanent     , // Available for all channels that are "in view", always up-to-date
    FlagSemiPermanent , // Available for all channels that are "in view", always up-to-date
    FlagDefault       , // Available for all channels that are "in view", always up-to-date
    FlagPassword      , // Available for all channels that are "in view", always up-to-date
    CodecLatencyFactor, // Available for all channels that are "in view", always up-to-date
    CodecIsUnencrypted, // Available for all channels that are "in view", always up-to-date
    SecuritySalt      , // Not available client side, not used in TeamSpeak, only SDK. Sets the options+salt for security hash.
    DeleteDelay       , // How many seconds to wait before deleting this channel
};

enum class ClientProperty : size_t
{
    UniqueIdentifier = 0  , // automatically up-to-date for any  "in view", can be used to identify this particular  installation
    Nickname              , // automatically up-to-date for any  "in view"
    Version               , // for other s than ourself, this needs to be requested (=> requestVariables)
    Platform              , // for other s than ourself, this needs to be requested (=> requestVariables)
    FlagTalking           , // automatically up-to-date for any  that can be heard (in room / whisper)
    InputMuted            , // automatically up-to-date for any  "in view", this s microphone mute status
    OutputMuted           , // automatically up-to-date for any  "in view", this s headphones/speakers/mic combined mute status
    OutputonlyMuted       , // automatically up-to-date for any  "in view", this s headphones/speakers only mute status
    InputHardware         , // automatically up-to-date for any  "in view", this s microphone hardware status (is the capture device opened?)
    OutputHardware        , // automatically up-to-date for any  "in view", this s headphone/speakers hardware status (is the playback device opened?)
    InputDeactivated      , // only usable for ourself, not propagated to the network
    IdleTime              , // internal use
    DefaultChannel        , // only usable for ourself, the default channel we used to connect on our last connection attempt
    DefaultChannelPassword, // internal use
    ServerPassword        , // internal use
    MetaData              , // automatically up-to-date for any  "in view", not used by TeamSpeak, free storage for sdk users
    IsMuted               , // only make sense on the  side locally, "1" if this  is currently muted by us, "0" if he is not
    IsRecording           , // automatically up-to-date for any  "in view"
    VolumeModificator     , // internal use
    VersionSign           , // sign
    SecurityHash          , // SDK use, not used by TeamSpeak. Hash is provided by an outside source. A channel will use the security salt + other  data to calculate a hash, which must be the same as the one provided here.
};

enum class ConnectionProperty : size_t
{
    // average latency for a round trip through and back this connection
    Ping = 0,
    // standard deviation of the above average latency
    PingDeviation,
    // how long the  exists already
    ConnectedTime,
    // how long since the last action of this client
    IdleTime,
    // IP of this client (as seen from the server side)
    ClientIp,
    // Port of this client (as seen from the server side)
    ClientPort,
    // IP of the server (seen from the client side) - only available on yourself, not for remote clients, not available server side
    ServerIp,
    // Port of the server (seen from the client side) - only available on yourself, not for remote clients, not available server side
    ServerPort,
    // how many Speech packets were sent through this connection
    PacketsSentSpeech,
    PacketsSentKeepalive,
    PacketsSentControl,

    // how many packets were sent totally (this is PACKETSSentSpeech + packetsSentKeepalive + packetsSentControl)
    PacketsSentTotal,
    BytesSentSpeech,
    BytesSentKeepalive,
    BytesSentControl,
    BytesSentTotal,
    PacketsReceivedSpeech,
    PacketsReceivedKeepalive,
    PacketsReceivedControl,
    PacketsReceivedTotal,
    BytesReceivedSpeech,
    BytesReceivedKeepalive,
    BytesReceivedControl,
    BytesReceivedTotal,
    PacketlossSpeech,
    PacketlossKeepalive,
    PacketlossControl,

    // the probability with which a packet round trip failed because a packet was lost
    PacketlossTotal,

    // the probability with which a speech packet failed from the server to the client
    Server2clientPacketlossSpeech,
    Server2clientPacketlossKeepalive,
    Server2clientPacketlossControl,
    Server2clientPacketlossTotal,
    Client2serverPacketlossSpeech,
    Client2serverPacketlossKeepalive,
    Client2serverPacketlossControl,
    Client2serverPacketlossTotal,

    // how many bytes of speech packets we sent during the last second
    BandwidthSentLastSecondSpeech,
    BandwidthSentLastSecondKeepalive,
    BandwidthSentLastSecondControl,
    BandwidthSentLastSecondTotal,

    // how many bytes/s of speech packets we sent in average during the last minute
    BandwidthSentLastMinuteSpeech,
    BandwidthSentLastMinuteKeepalive,
    BandwidthSentLastMinuteControl,
    BandwidthSentLastMinuteTotal,
    BandwidthReceivedLastSecondSpeech,
    BandwidthReceivedLastSecondKeepalive,
    BandwidthReceivedLastSecondControl,
    BandwidthReceivedLastSecondTotal,
    BandwidthReceivedLastMinuteSpeech,
    BandwidthReceivedLastMinuteKeepalive,
    BandwidthReceivedLastMinuteControl,
    BandwidthReceivedLastMinuteTotal,

    // how many bytes per second are currently being sent by file transfers
    FiletransferBandwidthSent = 62,
    // how many bytes per second are currently being received by file transfers
    FiletransferBandwidthReceived = 63,
    // how many bytes we received in total through file transfers
    FiletransferBytesReceivedTotal = 64,
    // how many bytes we sent in total through file transfers
    FiletransferBytesSentTotal = 65,
};

enum class VirtualServerProperty : size_t
{
    UniqueIdentifier = 0, // available when connected, can be used to identify this particular server installation
    Name                , // available and always up-to-date when connected
    Welcomemessage      , // available when connected, (=> requestServerVariables)
    Platform            , // available when connected
    Version             , // available when connected
    Maxclients          , // only available on request (=> requestServerVariables), stores the maximum number of clients that may currently join the server
    Password            , // not available to clients, the server password
    ClientsOnline       , // only available on request (=> requestServerVariables),
    ChannelsOnline      , // only available on request (=> requestServerVariables),
    Created             , // available when connected, stores the time when the server was created
    Uptime              , // only available on request (=> requestServerVariables), the time since the server was started
    CodecEncryptionMode , // available and always up-to-date when connected    
};

} // namespace TeamSpeakSdk
