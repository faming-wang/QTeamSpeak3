#pragma once

#include <QTeamSpeak/namespace.h>

namespace QTeamSpeak {

class Exception : public QException
{
public:
    inline explicit Exception(ReturnCode errorCode, const QString& message = QString())
    {
        _errorCode = errorCode;
        _message = message;
    }
    inline Exception(const Exception& other) { *this = other; }
    inline Exception& operator=(const Exception& other)
    {
        if (this != &other) {
            _errorCode = other._errorCode;
            _message = other._message;
            _extraMessage = other._extraMessage;
        }
        return *this;
    }

    inline void raise() const override { throw* this; }
    inline Exception* clone() const override { return new Exception(*this); }

    inline ReturnCode errorCode() const { return _errorCode; }
    inline void setErrorCode(ReturnCode value) { _errorCode = value; }

    inline QString message() const { return _message; }
    inline void setMessage(const QString& value) { _message = value; }

    inline QString extraMessage() const { return _extraMessage; }
    inline void setExtraMessage(const QString& value) { _extraMessage = value; }

private:
    ReturnCode _errorCode;
    QString _message;
    QString _extraMessage;

}; // class Exception

class ArgumentException : public QException
{
public:
    inline ArgumentException(const QString& message)
    {
        _message = message;
    }
    inline ArgumentException(const QString& message, const QString& paramName)
    {
        _message = message;
        _paramName = paramName;
    }
    inline ArgumentException(const ArgumentException& other) { *this = other; }
    inline ArgumentException& operator=(const ArgumentException& other)
    {
        if (this != &other) {
            _paramName = other._paramName;
            _message = other._message;
        }
        return *this;
    }
    inline void raise() const override { throw* this; }
    inline ArgumentException* clone() const override { return new ArgumentException(*this); }
    inline virtual QString paramName() const { return _paramName; }
    inline virtual QString message() const { return _message; }

protected:
    QString _paramName;
    QString _message;
};

} // namespace QTeamSpeak

