#include "preprocessor.h"

#include "exception.h"
#include "private/interfacemanager_p.h"


namespace TeamSpeakSdk {

class Preprocessor::Private
{
public:
    bool getBool(const QString& ident) const
    {
        const auto value = api().getPreProcessorConfigValue(connection, ident);
  
        if (value == "true")
            return true;
        else if (value == "false")
            return false;
        else
            throw Exception(ReturnCode::Undefined);
    }

    int getInt(const QString& ident) const
    {
        const auto value = api().getPreProcessorConfigValue(connection, ident);
        bool ok;
        int result = value.toInt(&ok);
        if (ok == false)
            throw Exception(ReturnCode::Undefined);
        return result;
    }

    float getFloat(const QString& ident) const
    {
        const auto value = api().getPreProcessorConfigValue(connection, ident);
        bool ok;
        float result = value.toFloat(&ok);
        if (ok == false)
            throw Exception(ReturnCode::Undefined);
        return result;
    }

    void setBool(const QString& ident, bool value)
    {
        api().setPreProcessorConfigValue(connection, ident, value ? "true" : "false");
    }

    void setInt(const QString& ident, int value)
    {
        api().setPreProcessorConfigValue(connection, ident, QString::number(value));
    }

    void setFloat(const QString& ident, float value)
    {
        api().setPreProcessorConfigValue(connection, ident, QString::number(value));
    }

    Connection* connection = Q_NULLPTR;
};

/*!
* Parameter of the microphone preprocessor.
*/
Preprocessor::Preprocessor(Connection* connection)
    : d(new Private)
{
    d->connection = connection;
}

Preprocessor::~Preprocessor()
{
    delete d;
}

/*!
* Enable or disable noise suppression. Enabled by default.
*/
bool Preprocessor::denoise() const
{
    return d->getBool("denoise");
}

void Preprocessor::setDenoise(bool value)
{
    d->setBool("denoise", value);
}

/*!
* Enable or disable Voice Activity Detection. Enabled by default.
*/
bool Preprocessor::vad() const
{
    return d->getBool("vad");
}

void Preprocessor::setVad(bool value)
{
    d->setBool("vad", value);
}

/*!
* Voice Activity Detection level in decibel. A high voice activation level
* means you have to speak louder into the microphone in order to start transmitting.
* Reasonable values range from -50 to 50. Default is 0.
* To adjust the VAD level in your client, you can query 
* \sa decibelLastPeriod() over a period of time to query.
*/
float Preprocessor::vadLevel() const
{
    return d->getFloat("voiceactivation_level");
}

void Preprocessor::setVadLevel(float value)
{
    d->setFloat("voiceactivation_level", value);
}

/*!
* Voice Activity Detection extra buffer size. Should be 0 to 8, defaults to 2. 
* Lower value means faster transmission, higher value means better VAD quality but higher latency.
*/
int Preprocessor::vadExtraBufferSize() const
{
    return d->getInt("vad_extrabuffersize");
}

void Preprocessor::setVadExtraBufferSize(int value)
{
    d->setInt("vad_extrabuffersize", value);
}

/*!
* Enable or disable Automatic Gain Control. Enabled by default.
*/
bool Preprocessor::agc() const
{
    return d->getBool("agc");
}

void Preprocessor::setAgc(bool value)
{
    d->setBool("agc", value);
}

/*!
* AGC level. Default is 16000.
*/
float Preprocessor::agcLevel() const
{
    return d->getFloat("agc_level");
}

void Preprocessor::setAgcLevel(float value)
{
    d->setFloat("agc_level", value);
}

/*!
* AGC max gain. Default is 30
*/
int Preprocessor::agcMaxGain() const
{
    return d->getInt("agc_max_gain");
}

void Preprocessor::setAgcMaxGain(int value)
{
    d->setInt("agc_max_gain", value);
}

/*!
* Checks if echo canceling is enabled
*/
bool Preprocessor::echoCanceling() const
{
    return d->getBool("echo_canceling");
}

void Preprocessor::setEchoCanceling(bool value)
{
    d->setBool("echo_canceling", value);
}

/*!
* the current voice input level
*/
float Preprocessor::decibelLastPeriod() const
{
    return api().getPreProcessorInfoValueFloat(connection(), "decibel_last_period");
}

Connection* Preprocessor::connection() const
{
    return d->connection;
}

} // namespace TeamSpeakSdk

