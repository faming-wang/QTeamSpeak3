#pragma once

namespace TeamSpeakSdk {

class QReadWriteLocker
{
public:
    enum LockMode 
    {
        LockForRead ,
        LockForWrite,
    };

    QReadWriteLocker(QReadWriteLock* lock, LockMode mode) {
        Q_ASSERT_X((reinterpret_cast<quintptr>(lock) & quintptr(1u)) == quintptr(0), "QReadWriteLocker", "QReadWriteLock pointer is misaligned");
        val = quintptr(lock);
        if (Q_LIKELY(lock)) {
            if (mode == QReadWriteLocker::LockForRead) {
                lock->lockForRead();
            } else {
                lock->lockForWrite();
            }
            val |= 1;
        }
    }

    inline ~QReadWriteLocker() { unlock(); }

    inline void unlock() noexcept
    {
        if ((val & quintptr(1u)) == quintptr(1u)) {
            val &= ~quintptr(1u);
            lock()->unlock();
        }
    }

#if defined(Q_CC_MSVC)
#pragma warning( push )
#pragma warning( disable : 4312 ) // ignoring the warning from /Wp64
#endif
    inline QReadWriteLock * lock() const
    {
        return reinterpret_cast<QReadWriteLock *>(val & ~quintptr(1u));
    }

#if defined(Q_CC_MSVC)
#pragma warning( pop )
#endif

private:
    Q_DISABLE_COPY(QReadWriteLocker)
    quintptr val;
};

template<class Key, class T>
class ThreadSafeCache
{
public:
    void insert(const Key& key, T* value)
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForWrite);
        if (impl.contains(key)) {
            delete impl[key];
        }
        impl.insert(key, value);
    }

    void remove(const Key& key)
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForWrite);
        delete impl.take(key);
    }

    T* take(const Key& key)
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForWrite);
        return impl.take(key);
    }

    bool contains(const Key& key) const
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForRead);
        return impl.contains(key);
    }

    const T* value(const Key& key) const
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForRead);
        return impl.value(key);
    }

    QList<T*> values() const
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForRead);
        return impl.values();
    }

    T* operator[](const Key& key)
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForRead);
        return impl[key];
    }

    void clear()
    {
        QReadWriteLocker locker(&lock, QReadWriteLocker::LockForWrite);
        qDeleteAll(impl);
        impl.clear();
    }

    ~ThreadSafeCache() 
    { 
        clear();
    }

protected:
    QHash<Key, T*> impl;
    mutable QReadWriteLock lock;
};

} // namespace TeamSpeakSdk
