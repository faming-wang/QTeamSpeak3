#pragma once

#include <QTeamSpeak/object.h>

namespace QTeamSpeak {

class Connection;

class WaveHandle : public Object
{
    Q_OBJECT
    Q_PROPERTY(ID id READ id)
public:
    using ID = quint64;

    explicit WaveHandle(Connection* connection, ID id);
    ~WaveHandle();

    ID id() const;
    Connection* connection() const;

    bool isPaused() const;
    void setPaused(bool value);

    void close();
    void set3DAttributes(const Vector3D& position);

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class WaveHandle

} // namespace QTeamSpeak

