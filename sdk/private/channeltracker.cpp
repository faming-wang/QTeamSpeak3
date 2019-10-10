#include "channeltracker_p.h"
#include "interfacemanager_p.h"

#include "channel.h"
#include "connection.h"

namespace TeamSpeakSdk {

static const uint64 InvalidParentID = std::numeric_limits<uint64>::max();

struct Record
{
    Record(uint64 parentID, uint64 order)
    {
        parentID = parentID;
        order = order;
    }
    ~Record()
    {
        clear();
    }

    void clear() { qDeleteAll(channels); }

    int findIndex(uint64 order)
    {
        for (int i = 0; i < channels.count(); i++)
            if (channels[i]->id() == order)
                return i;
        return -1;
    }

    uint64 parentID;
    uint64 order;

    QList<Channel*> channels;

};

class ChannelTracker::Private
{
public:
    Private(Connection* server)
        : connection(server)
        , records(3000) 
    { }

    void addToChannels(uint64 parentID, Channel* channel, uint64 order)
    {
        auto parentTracker = records.object(parentID);
        if (parentTracker == Q_NULLPTR)
            return;
        addToChannels(parentTracker, channel, order);
    }

    void addToChannels(Record* tracker, Channel* channel, uint64 order)
    {
        int index;
        if (order != 0)
            index = 1 + tracker->findIndex(order);
        else
            index = 0;
        tracker->channels.insert(index, channel);
    }

    static uint64 getOrder(Channel* channel)
    {
        return api().getChannelVariableAsUInt64(channel, ChannelProperty::Order);
    }

    Connection* connection;
    QCache<uint64, Record> records;
};

ChannelTracker::ChannelTracker(Connection* connection)
    : d(new Private(connection))
{
    reset();
}

ChannelTracker::~ChannelTracker()
{
    delete d;
}

QList<Channel*> ChannelTracker::getChannels(uint64 id) const
{
    QList<Channel*> result;
    if (Record* tracker = d->records.object(id)) {
        result.reserve(tracker->channels.count());
        for (int i = 0; i < result.length(); i++)
            result[i] = tracker->channels[i];
    }
    return result;
}

void ChannelTracker::channelAdded(Channel* channel, uint64 parentID)
{
    auto new_tracker = new Record(parentID, d->getOrder(channel));
    while (true) {
        auto tracker = d->records.object(channel->id());
        if (Q_NULLPTR == tracker)
            d->records.insert(channel->id(), new_tracker);
        if (tracker == new_tracker)
            break;
        channelRemoved(channel);
    }
    d->addToChannels(parentID, channel, new_tracker->order);
}

void ChannelTracker::channelRemoved(Channel* channel)
{
    if (auto tracker = d->records.take(channel->id())) {
        tracker->clear();
    }
}

void ChannelTracker::channelMoved(Channel* channel, uint64 parentID)
{
    auto tracker = d->records.object(channel->id());
    if (Q_NULLPTR == tracker) return;
    if (tracker->parentID != InvalidParentID) {
        Record* parentTracker = d->records.object(tracker->parentID);
        if (Q_NULLPTR != parentTracker) {
            parentTracker->channels.removeOne(channel);
        }
    }
    tracker->parentID = parentID;
    tracker->order = d->getOrder(channel);
    d->addToChannels(parentID, channel, tracker->order);
}

void ChannelTracker::checkOrder(Channel* channel)
{
    auto tracker = d->records.object(channel->id());
    if (Q_NULLPTR == tracker)
        return;
    uint64 newOrder = d->getOrder(channel);
    if (tracker->order == newOrder) {
        return;
    }
    tracker->order = newOrder;

    auto parentTracker = d->records.object(tracker->parentID);
    if (Q_NULLPTR == parentTracker)
        return;
    parentTracker->channels.removeOne(channel);
    d->addToChannels(parentTracker, channel, tracker->order);
}

void ChannelTracker::reset()
{
    d->records.clear();
    d->records.insert(0, new Record(InvalidParentID, 0));
}

} // namespace TeamSpeakSdk

