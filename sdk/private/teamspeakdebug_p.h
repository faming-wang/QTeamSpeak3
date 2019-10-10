#pragma once

namespace TeamSpeakSdk {

class Debug : public QDebug
{
public:
    Debug(const QString& name)
        : QDebug(qDebug())
        , _process(name)
    {
        *this << "["<< _process << "] Process Starting...\n";
        _timer.start();
    }

    ~Debug()
    {
        *this << "[" << _process << "] Process Done.\n";
        *this << "[" << _process << "] Process Elapsed " << _timer.elapsed() << "milliseconds.\n";
    }

private:
    QString _process;
    QElapsedTimer _timer;
};

} // namespace TeamSpeakSdk
