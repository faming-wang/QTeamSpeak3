#include "connectioninfo.h"

#include "private/interfacemanager_p.h"

namespace QTeamSpeak {

class ConnectionInfo::Private
{
public:
    Client* q_ptr = nullptr;

public:
    Private(Client* q) : q_ptr(q) {
    
    }

    quint64 getUInt64(ConnectionProperty flag) const
    {
        return api()->getConnectionVariableAsUInt64(q_ptr, flag);
    }

    double getDouble(ConnectionProperty flag) const
    {
        return api()->getConnectionVariableAsDouble(q_ptr, flag);
    }

    QString getString(ConnectionProperty flag) const
    {
        return api()->getConnectionVariableAsString(q_ptr, flag);
    }
};

/*!
* \class ConnectionInfo
*
* \brief
*/
ConnectionInfo::ConnectionInfo(Client* client)
    : d(new Private(client))
{

}

ConnectionInfo::~ConnectionInfo()
{

}

/*!
* How many bytes per second are currently being received by file transfers
*/
quint64 ConnectionInfo::filetransferBandwidthSent() const
{
    return d->getUInt64(ConnectionProperty::FiletransferBandwidthSent);
}

/*!
* How many bytes per second are currently being received by file transfers
*/
quint64 ConnectionInfo::filetransferBandwidthReceived() const
{
    return d->getUInt64(ConnectionProperty::FiletransferBandwidthReceived);
}

/*!
* Average latency for a round trip through and back this connection.
*/
std::chrono::milliseconds ConnectionInfo::ping() const
{
    const auto time = d->getUInt64(ConnectionProperty::Ping);
    return std::chrono::milliseconds(time);
}

/*!
* Standard deviation of the above average latency
*/
double ConnectionInfo::pingDeviation() const
{
    return d->getDouble(ConnectionProperty::PingDeviation);
}

/*!
* How long since the last action of this client
*/
std::chrono::milliseconds ConnectionInfo::idleTime() const
{
    const auto time = d->getUInt64(ConnectionProperty::IdleTime);
    return std::chrono::milliseconds(time);
}

/*!
* IP of this client (as seen from the server side)
*/
QString ConnectionInfo::clientIp() const
{
    return d->getString(ConnectionProperty::ClientIp);
}

/*!
* Port of this client (as seen from the server side)
*/
quint64 ConnectionInfo::clientPort() const
{
    return d->getUInt64(ConnectionProperty::ClientPort);
}

/*!
* How long the connection exists already
*/
std::chrono::milliseconds ConnectionInfo::connectedTime() const
{
    const auto time = d->getUInt64(ConnectionProperty::ConnectedTime);
    return std::chrono::milliseconds(time);
}

/*!
* How many Speech packets were sent through this connection
*/
quint64 ConnectionInfo::packetsSentSpeech() const
{
    return d->getUInt64(ConnectionProperty::PacketsSentSpeech);
}

/*!
* How many Keepalive packets were sent through this connection
*/
quint64 ConnectionInfo::packetsSentKeepalive() const
{
    return d->getUInt64(ConnectionProperty::PacketsSentKeepalive);
}

/*!
* How many Control packets were sent through this connection
*/
quint64 ConnectionInfo::packetsSentControl() const
{
    return d->getUInt64(ConnectionProperty::PacketsSentControl);
}

/*!
* How many packets were sent totally 
(this is \sa packetsSentSpeech() + \sa packetsSentKeepalive() + \sa packetsSentControl())
*/
quint64 ConnectionInfo::packetsSentTotal() const
{
    return d->getUInt64(ConnectionProperty::PacketsSentTotal);
}

/*!
* How many bytes worth of Speech packets were sent through this connection
*/
quint64 ConnectionInfo::bytesSentSpeech() const
{
    return d->getUInt64(ConnectionProperty::BytesSentSpeech);
}

/*!
* How many bytes worth of Keepalive packets were sent through this connection
*/
quint64 ConnectionInfo::bytesSentKeepalive() const
{
    return d->getUInt64(ConnectionProperty::BytesSentKeepalive);
}

/*!
* How many bytes worth of Sent packets were sent through this connection
*/
quint64 ConnectionInfo::bytesSentControl() const
{
    return d->getUInt64(ConnectionProperty::BytesSentControl);
}

/*!
* How many bytes were sent through this connection
*/
quint64 ConnectionInfo::bytesSentTotal() const
{
    return d->getUInt64(ConnectionProperty::BytesSentTotal);
}

/*!
* How many Speech packets were received through this connection
*/
quint64 ConnectionInfo::packetsReceivedSpeech() const
{
    return d->getUInt64(ConnectionProperty::PacketsReceivedSpeech);
}

/*!
* How many Keepalive packets were received through this connection
*/
quint64 ConnectionInfo::packetsReceivedKeepalive() const
{
    return d->getUInt64(ConnectionProperty::PacketsReceivedKeepalive);
}

/*!
* How many Control packets were received through this connection
*/
quint64 ConnectionInfo::packetsReceivedControl() const
{
    return d->getUInt64(ConnectionProperty::PacketsReceivedControl);
}

/*!
* How many packets were received through this connection
*/
quint64 ConnectionInfo::packetsReceivedTotal() const
{
    return d->getUInt64(ConnectionProperty::PacketsReceivedTotal);
}

/*!
* How many bytes worth of Speech packets were received through this connection
*/
quint64 ConnectionInfo::bytesReceivedSpeech() const
{
    return d->getUInt64(ConnectionProperty::BytesReceivedSpeech);
}

/*!
* How many bytes worth of Keepalive packets were received through this connection
*/
quint64 ConnectionInfo::bytesReceivedKeepalive() const
{
    return d->getUInt64(ConnectionProperty::BytesReceivedKeepalive);
}

/*!
* How many bytes worth of Control packets were received through this connection
*/
quint64 ConnectionInfo::bytesReceivedControl() const
{
    return d->getUInt64(ConnectionProperty::BytesReceivedControl);
}

/*!
* How many bytes were received through this connection
*/
quint64 ConnectionInfo::bytesReceivedTotal() const
{
    return d->getUInt64(ConnectionProperty::BytesReceivedTotal);
}

/*!
* The probability with which speech packet round trip failed because a packet was lost
*/
double ConnectionInfo::packetlossSpeech() const
{
    return d->getDouble(ConnectionProperty::PacketlossSpeech);
}

/*!
* The probability with which keepalive packet round trip failed because a packet was lost
*/
double ConnectionInfo::packetlossKeepalive() const
{
    return d->getDouble(ConnectionProperty::PacketlossKeepalive);
}

/*!
* The probability with which control packet round trip failed because a packet was lost
*/
double ConnectionInfo::packetlossControl() const
{
    return d->getDouble(ConnectionProperty::PacketlossControl);
}

/*!
* The probability with which a packet round trip failed because a packet was lost
*/
double ConnectionInfo::packetlossTotal() const
{
    return d->getDouble(ConnectionProperty::PacketlossTotal);
}

/*!
* The probability with which a speech packet failed from the server to the client
*/
double ConnectionInfo::serverToClientPacketlossSpeech() const
{
    return d->getDouble(ConnectionProperty::Server2clientPacketlossSpeech);
}

/*!
* The probability with which a keepalive packet failed from the server to the client
*/
double ConnectionInfo::serverToClientPacketlossKeepalive() const
{
    return d->getDouble(ConnectionProperty::Server2clientPacketlossKeepalive);
}

/*!
* The probability with which a control packet failed from the server to the client
*/
double ConnectionInfo::serverToClientPacketlossControl() const
{
    return d->getDouble(ConnectionProperty::Server2clientPacketlossControl);
}

/*!
* The probability with which a packet failed from the client to the server
*/
double ConnectionInfo::serverToClientPacketlossTotal() const
{
    return d->getDouble(ConnectionProperty::Server2clientPacketlossTotal);
}

/*!
* The probability with which a Speech packet failed from the client to the server
*/
double ConnectionInfo::clientToServerPacketlossSpeech() const
{
    return d->getDouble(ConnectionProperty::Client2serverPacketlossSpeech);
}

/*!
* The probability with which a Keepalive packet failed from the client to the server
*/
double ConnectionInfo::clientToServerPacketlossKeepalive() const
{
    return d->getDouble(ConnectionProperty::Client2serverPacketlossKeepalive);
}

/*!
* The probability with which a Control packet failed from the client to the server
*/
double ConnectionInfo::clientToServerPacketlossControl() const
{
    return d->getDouble(ConnectionProperty::Client2serverPacketlossControl);
}

/*!
* The probability with which a packet failed from the client to the server
*/
double ConnectionInfo::clientToServerPacketlossTotal() const
{
    return d->getDouble(ConnectionProperty::Client2serverPacketlossTotal);
}

/*!
* How many bytes of speech packets we sent during the last second
*/
double ConnectionInfo::bandwidthSentLastSecondSpeech() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastSecondSpeech);
}

/*!
* How many bytes of keepalive packets we sent during the last second
*/
double ConnectionInfo::bandwidthSentLastSecondKeepalive() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastSecondKeepalive);
}

/*!
* How many bytes of control packets we sent during the last second
*/
double ConnectionInfo::bandwidthSentLastSecondControl() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastSecondControl);
}

/*!
* How many bytes of packets we sent during the last second
*/
double ConnectionInfo::bandwidthSentLastSecondTotal() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastSecondTotal);
}

/*!
* How many bytes/s of speech packets we sent in average during the last minute
*/
double ConnectionInfo::bandwidthSentLastMinuteSpeech() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastMinuteSpeech);
}

/*!
* How many bytes/s of keepalive packets we sent in average during the last minute
*/
double ConnectionInfo::bandwidthSentLastMinuteKeepalive() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastMinuteKeepalive);
}

/*!
* How many bytes/s of control packets we sent in average during the last minute
*/
double ConnectionInfo::bandwidthSentLastMinuteControl() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastMinuteControl);
}

/*!
* How many bytes/s of packets we received in average during the last minute
*/
double ConnectionInfo::bandwidthSentLastMinuteTotal() const
{
    return d->getDouble(ConnectionProperty::BandwidthSentLastMinuteTotal);
}

/*!
* How many bytes/s of Speech packets we received in average during the last second
*/
double ConnectionInfo::bandwidthReceivedLastSecondSpeech() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastSecondSpeech);
}

/*!
* How many bytes/s of Keepalive packets we received in average during the last second
*/
double ConnectionInfo::bandwidthReceivedLastSecondKeepalive() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastSecondKeepalive);
}

/*!
* How many bytes/s of Control packets we received in average during the last second
*/
double ConnectionInfo::bandwidthReceivedLastSecondControl() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastSecondControl);
}

/*!
* How many bytes/s of packets we received in average during the last second
*/
double ConnectionInfo::bandwidthReceivedLastSecondTotal() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastSecondTotal);
}

/*!
* How many bytes/s of Speed packets we received in average during the last minute
*/
double ConnectionInfo::bandwidthReceivedLastMinuteSpeech() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastMinuteSpeech);
}

/*!
* How many bytes/s of Keepalive packets we received in average during the last minute
*/
double ConnectionInfo::bandwidthReceivedLastMinuteKeepalive() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastMinuteKeepalive);
}

/*!
* How many bytes/s of Control packets we received in average during the last minute
*/
double ConnectionInfo::bandwidthReceivedLastMinuteControl() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastMinuteControl);
}

/*!
* How many bytes/s of packets we received in average during the last minute
*/
double ConnectionInfo::bandwidthReceivedLastMinuteTotal() const
{
    return d->getDouble(ConnectionProperty::BandwidthReceivedLastMinuteTotal);
}

/*!
* The \sa Client
*/
Client* ConnectionInfo::client() const
{
    return d->q_ptr;
}

/*!
* The \sa Client::connection()
*/
Connection* ConnectionInfo::connection() const
{
    return client()->connection();
}

/*!
* Request more up to date information from the TeamSpeak-Server
* Returns \c A task that represents the asynchronous operation.
*/
void ConnectionInfo::refresh()
{
    quint64 result = d->getUInt64(ConnectionProperty::ConnectedTime);
}

void ConnectionInfo::cleanUp()
{
    api()->cleanUpConnectionInfo(d->q_ptr);
}

} // namespace QTeamSpeak

