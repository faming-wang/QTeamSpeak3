#include "wavehandle.h"

#include "private/interfacemanager_p.h"

namespace QTeamSpeak {

class WaveHandle::Private
{
public:
    ID id = 0;
    bool paused = false;
};

WaveHandle::WaveHandle(Connection* connection, ID id)
    : Object(connection)
    , d(new Private)
{
    d->id = id;
}

WaveHandle::~WaveHandle()
{

}

WaveHandle::ID WaveHandle::id() const
{
    return d->id;
}

Connection* WaveHandle::connection() const
{
    return qobject_cast<Connection*>(parent());
}

bool WaveHandle::isPaused() const
{
    return d->paused;
}

void WaveHandle::setPaused(bool value)
{
    api()->pauseWaveFileHandle(this, value);
    d->paused = value;
}

void WaveHandle::close()
{
    api()->closeWaveFileHandle(this);
}

void WaveHandle::set3DAttributes(const Vector3D& position)
{
    api()->set3DWaveAttributes(this, &position);
}

} // namespace QTeamSpeak
