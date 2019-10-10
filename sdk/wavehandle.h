#pragma once

namespace TeamSpeakSdk {

class Connection;

class TEAMSPEAKSDK_EXPORT WaveHandle
{
public:
    using ID = uint64;

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
    Private* const d = Q_NULLPTR;

}; // class WaveHandle

} // namespace TeamSpeakSdk

