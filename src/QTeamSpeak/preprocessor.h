#pragma once

namespace QTeamSpeak {

class Connection;

class Preprocessor : public QObject
{
public:
    explicit Preprocessor(Connection* connection);
    ~Preprocessor();

    Connection* connection() const;

    bool denoise() const;
    void setDenoise(bool value);

    bool vad() const;
    void setVad(bool value);

    float vadLevel() const;
    void setVadLevel(float value);

    int vadExtraBufferSize() const;
    void setVadExtraBufferSize(int value);

    bool agc() const;
    void setAgc(bool value);

    float agcLevel() const;
    void setAgcLevel(float value);

    int agcMaxGain() const;
    void setAgcMaxGain(int value);

    bool echoCanceling() const;
    void setEchoCanceling(bool value);

    float decibelLastPeriod() const;

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class Preprocessor

} // namespace QTeamSpeak

