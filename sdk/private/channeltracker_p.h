#pragma once

#include "channel.h"

namespace TeamSpeakSdk {

class Channel;
class Connection;

class ChannelTracker
{
public:
    explicit ChannelTracker(Connection* connection);
    ~ChannelTracker();

    QList<Channel*> getChannels(Channel::ID id) const;
    void channelAdded(Channel* channel, uint64 parentID);
    void channelRemoved(Channel* channel);
    void channelMoved(Channel* channel, uint64 parentID);
    void checkOrder(Channel* channel);
    void reset();

private:
    class Private;
    Private* const d;

}; // class ChannelTracker

} // namespace TeamSpeakSdk

