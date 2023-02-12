#pragma once

namespace QTeamSpeak {

class Client;
class Connection;

class ConnectionInfo
{
public:
    ConnectionInfo(Client* client);
    ~ConnectionInfo();

    Client* client() const;
    Connection* connection() const;

    quint64 filetransferBandwidthSent() const;
    quint64 filetransferBandwidthReceived() const;

    double pingDeviation() const;

    QString clientIp() const;
    quint64 clientPort() const;

    std::chrono::milliseconds ping() const;
    std::chrono::milliseconds idleTime() const;
    std::chrono::milliseconds connectedTime() const;

    quint64 packetsSentSpeech() const;
    quint64 packetsSentKeepalive() const;
    quint64 packetsSentControl() const;
    quint64 packetsSentTotal() const;
    quint64 bytesSentSpeech() const;
    quint64 bytesSentKeepalive() const;
    quint64 bytesSentControl() const;
    quint64 bytesSentTotal() const;
    quint64 packetsReceivedSpeech() const;
    quint64 packetsReceivedKeepalive()const;
    quint64 packetsReceivedControl() const;
    quint64 packetsReceivedTotal() const;
    quint64 bytesReceivedSpeech() const;
    quint64 bytesReceivedKeepalive() const;
    quint64 bytesReceivedControl() const;
    quint64 bytesReceivedTotal() const;

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
    std::unique_ptr<Private> d;

}; // class ConnectionInfo

} // namespace QTeamSpeak

