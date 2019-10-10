#pragma once

namespace TeamSpeakSdk {

template<
    class Enum,
    class EnumType = std::underlying_type_t<Enum>,
    class = std::enable_if_t<std::is_enum<Enum>::value>
> Q_OUTOFLINE_TEMPLATE 
bool operator==(Enum _enum, EnumType _type)
{
    return static_cast<EnumType>(_enum) == _type;
}

template<
    class Enum, 
    class EnumType = std::underlying_type_t<Enum>,
    class = std::enable_if_t<std::is_enum<Enum>::value>
> Q_OUTOFLINE_TEMPLATE 
bool operator!=(Enum _enum, EnumType _type)
{
    return !operator==(_enum, _type);
}

template<
    class Enum,
    class EnumType = std::underlying_type_t<Enum>,
    class = std::enable_if_t<std::is_enum<Enum>::value>
> Q_OUTOFLINE_TEMPLATE
bool operator==(EnumType _type, Enum _enum)
{
    return operator==(_enum, _type);
}

template<
    class Enum,
    class EnumType = std::underlying_type_t<Enum>,
    class = std::enable_if_t<std::is_enum<Enum>::value>
>  Q_OUTOFLINE_TEMPLATE
bool operator!=(EnumType _type, Enum _enum)
{
    return !operator==(_enum, _type);
}

namespace utils {

template<class _Time>
Q_OUTOFLINE_TEMPLATE 
QDateTime to_date_time(_Time secs)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5,8,0))
    return QDateTime::fromSecsSinceEpoch(secs);
#else
    return QDateTime::fromMSecsSinceEpoch(secs * 1000);
#endif
}

inline QByteArray to_byte(const QString& text)
{
    if (text.isEmpty())
        return QByteArray("");
    return text.toUtf8();
}

inline QByteArray to_byte(const char* pointer)
{
    if (Q_NULLPTR == pointer)
        return QByteArray();
    return QByteArray(pointer);
}

inline QString to_string(const char* pointer)
{
    return QString::fromUtf8(to_byte(pointer));
}

template<
    class Enum, 
    class EnumType = std::underlying_type_t<Enum>,
    typename = std::enable_if_t<std::is_enum<Enum>::value>
>   Q_OUTOFLINE_TEMPLATE 
EnumType underlay(Enum value)
{
    return static_cast<EnumType>(value);
}

template<
    class _Result,
    class _Input,
    class _Fn
>   Q_REQUIRED_RESULT Q_OUTOFLINE_TEMPLATE 
decltype(auto) transform(_Input&& container, _Fn function)
{
    _Result result;
    result.reserve(_Result::size_type(container.size()));
    std::transform(std::begin(container), std::end(container), std::back_inserter(result), function);
    return result;
}

template<
    template<class> class _Container,
    class _Input,
    class _Fn,
    class _Value,
    class _Result = std::decay_t<std::result_of_t<_Fn(_Value&)> >,
    class _ResultContainer = _Container<_Result>
>   Q_REQUIRED_RESULT
decltype(auto) transform(_Input&& container, _Fn function)
{
    return transform<_ResultContainer>(std::forward<_Input>(container), function);
}

template <
    class T, 
    template<class> class _Container, 
    class Base
>  Q_OUTOFLINE_TEMPLATE
_Container<T> dynamic_cast_c(const _Container<Base>& container)
{
    _Container<T> result;
    auto ins = std::back_inserter(result);
    for (auto val : container) {
        if (auto target = dynamic_cast<T>(val))
            ins = target;
    }
    return result;
}

template<
    template<class> class _Input,
    class _Value,
    class _Fn,
    class _Result = std::decay_t<std::result_of_t<_Fn(_Value&)>>
>   Q_OUTOFLINE_TEMPLATE
QVector<_Result> to_array(const _Input<_Value>& container, _Fn function)
{
    return transform<QVector<_Result>>(container, function);
}

template<
    template<class> class _Input,
    class _Value,
    class _Fn,
    class _Result = std::decay_t<std::result_of_t<_Fn(_Value&)>>
>   Q_OUTOFLINE_TEMPLATE
QList<_Result> to_list(const _Input<_Value>& container, _Fn function)
{
    return transform<QList<_Result>>(container, function);
}

template<class _Result, class _Type>
Q_OUTOFLINE_TEMPLATE 
QVector<_Result> make_vector(_Type* pointer, int size)
{
    QVector<_Result> result(size);
    for (int i = 0; i < result.size(); ++i) {
        result[i] = _Result(pointer[i]);
    }
    return result;
}

template<class _Type>
Q_OUTOFLINE_TEMPLATE
void copy_vector(QVector<_Type>& vector, _Type* pointer)
{
    ::memcpy(pointer, vector.data(), vector.size());
}

template <class _Type>
Q_OUTOFLINE_TEMPLATE 
void make_value(_Type* _pointer, _Type _value)
{
    if (!_pointer)
        return;
    *_pointer = _value;
}

template <
    class _Ptr, 
    class = std::enable_if_t<std::is_pointer<_Ptr>::value>
> Q_OUTOFLINE_TEMPLATE
bool is_null(_Ptr _pointer)
{
   return _pointer == Q_NULLPTR;
}

template <
    template<class> class _Container, 
    class _Base,
    class = std::enable_if_t<std::is_pointer<_Base>::value>
> Q_OUTOFLINE_TEMPLATE
bool has_null(_Container<_Base>&& args)
{
    for (auto arg : args)
        if (is_null(arg))
            return true;
    return false;
}

template <class ...Args>
Q_OUTOFLINE_TEMPLATE 
bool has_null(Args&& ... args)
{
    auto list = { &args... };
    return has_null(std::move(list));
}

template <
    template<class> class _Container,
    class _Base,
    class = std::enable_if_t<std::is_pointer<_Base>::value>
> Q_OUTOFLINE_TEMPLATE
bool has_null(const _Container<_Base>& args)
{
    for (auto arg : args)
        if (is_null(arg))
            return true;
    return false;
}

template <
    class _Server, 
    template<class> class _Container,
    class = std::enable_if_t<std::is_pointer<_Server>::value>
> Q_OUTOFLINE_TEMPLATE
bool is_same_server(_Server server, _Container<_Server>&& args)
{
    for (auto arg : args)
        if (!is_null(arg) && arg != server)
            return false;
    return true;
}

/// internal
template <
    class _Server, 
    class ...Args,
    class = std::enable_if_t<std::is_pointer<_Server>::value>
> Q_OUTOFLINE_TEMPLATE
bool is_same_server(_Server server, Args&& ... args)
{
    // args must has connection() function;
    auto list = { (args->connection())... };
    return is_same_server(server, std::move(list));
}

template <
    class _Server,
    template<class> class _Container,
    class _Base,
    class = std::enable_if_t<std::is_pointer<_Server>::value>,
    class = std::enable_if_t<std::is_pointer<_Base>::value>
> Q_OUTOFLINE_TEMPLATE
bool is_same_server(_Server server, const _Container<_Base>& args)
{
    for (auto arg : args)
        if (!is_null(arg) && arg->connection() != server)
            return false;
    return true;
}

} // namespace utils 

} // namespace TeamSpeakSdk 

