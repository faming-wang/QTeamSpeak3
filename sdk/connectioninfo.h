#pragma once

namespace TeamSpeakSdk {

class Client;
class Connection;

class TEAMSPEAKSDK_EXPORT ConnectionInfo
{
public:
    ConnectionInfo(Client* client);
    ~ConnectionInfo();

    Client* client() const;
    Connection* connection() const;

    uint64 filetransferBandwidthSent() const;
    uint64 filetransferBandwidthReceived() const;

    double pingDeviation() const;

    QString clientIp() const;
    uint64 clientPort() const;

    time::milliseconds ping() const;
    time::milliseconds idleTime() const;
    time::milliseconds connectedTime() const;

    uint64 packetsSentSpeech() const;
    uint64 packetsSentKeepalive() const;
    uint64 packetsSentControl() const;
    uint64 packetsSentTotal() const;
    uint64 bytesSentSpeech() const;
    uint64 bytesSentKeepalive() const;
    uint64 bytesSentControl() const;
    uint64 bytesSentTotal() const;
    uint64 packetsReceivedSpeech() const;
    uint64 packetsReceivedKeepalive()const;
    uint64 packetsReceivedControl() const;
    uint64 packetsReceivedTotal() const;
    uint64 bytesReceivedSpeech() const;
    uint64 bytesReceivedKeepalive() const;
    uint64 bytesReceivedControl() const;
    uint64 bytesReceivedTotal() const;

    double packetlossSpeech() const;
    double packetlossKeepalive() const;
    double packetlossControl() const;
    double packetlossTotal() const;
    double serverToClientPacketlossSpeech() const;
    double serverToClientPacketlossKeepalive() const;
    double serverToClientPacketlossControl() const;
    double serverToClientPacketlossTotal() const;
    double clientToServerPacketlossSpeech() const;
    double clientToServerPacketlossKeepalive() const;
    double clientToServerPacketlossControl() const;
    double clientToServerPacketlossTotal() const;
    double bandwidthSentLastSecondSpeech() const;
    double bandwidthSentLastSecondKeepalive() const;
    double bandwidthSentLastSecondControl() const;
    double bandwidthSentLastSecondTotal() const;
    double bandwidthSentLastMinuteSpeech() const;
    double bandwidthSentLastMinuteKeepalive() const;
    double bandwidthSentLastMinuteControl() const;
    double bandwidthSentLastMinuteTotal() const;
    double bandwidthReceivedLastSecondSpeech() const;
    double bandwidthReceivedLastSecondKeepalive() const;
    double bandwidthReceivedLastSecondControl() const;
    double bandwidthReceivedLastSecondTotal() const;
    double bandwidthReceivedLastMinuteSpeech() const;
    double bandwidthReceivedLastMinuteKeepalive() const;
    double bandwidthReceivedLastMinuteControl() const;
    double bandwidthReceivedLastMinuteTotal() const;

    void refresh();
    void cleanUp();

private:
    class Private;
    Private* const d = Q_NULLPTR;

}; // class ConnectionInfo

} // namespace TeamSpeakSdk

