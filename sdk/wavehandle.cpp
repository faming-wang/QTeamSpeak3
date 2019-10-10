#include "wavehandle.h"

#include "private/interfacemanager_p.h"

namespace TeamSpeakSdk {

class WaveHandle::Private
{
public:
    ID id = 0;
    bool paused = false;
    Connection* connection = Q_NULLPTR;

};

WaveHandle::WaveHandle(Connection* connection, ID id)
    : d(new Private)
{
    d->id = id;
    d->connection = connection;
}

WaveHandle::~WaveHandle()
{
    delete d;
}

WaveHandle::ID WaveHandle::id() const
{
    return d->id;
}

Connection* WaveHandle::connection() const
{
    return d->connection;
}

bool WaveHandle::isPaused() const
{
    return d->paused;
}

void WaveHandle::setPaused(bool value)
{
    api().pauseWaveFileHandle(this, value);
    d->paused = value;
}

void WaveHandle::close()
{
    api().closeWaveFileHandle(this);
}

void WaveHandle::set3DAttributes(const Vector3D& position)
{
    api().set3DWaveAttributes(this, &position);
}

} // namespace TeamSpeakSdk
