#pragma once

namespace TeamSpeakSdk {

template<class Key, class T>
class ThreadSafeCache
{
public:
    void insert(const Key& key, T* value)
    {
        // Locker locker(&lock, // Locker::LockForWrite);
        if (impl.contains(key)) {
            delete impl[key];
        }
        impl.insert(key, value);
    }

    void remove(const Key& key)
    {
        // Locker locker(&lock, // Locker::LockForWrite);
        delete impl.take(key);
    }

    T* take(const Key& key)
    {
        // Locker locker(&lock, // Locker::LockForWrite);
        return impl.take(key);
    }

    bool contains(const Key& key) const
    {
        // Locker locker(const_cast<QReadWriteLock*>(&lock), // Locker::LockForRead);
        return impl.contains(key);
    }

    const T* value(const Key& key) const
    {
        // Locker locker(const_cast<QReadWriteLock*>(&lock), // Locker::LockForRead);
        return impl.value(key);
    }

    QList<T*> values() const
    {
        // Locker locker(const_cast<QReadWriteLock*>(&lock), // Locker::LockForRead);
        return impl.values();
    }

    T* operator[](const Key& key)
    {
        // Locker locker(&lock, // Locker::LockForRead);
        return impl[key];
    }

    void clear()
    {
        // Locker locker(&lock, // Locker::LockForWrite);
        qDeleteAll(impl);
        impl.clear();
    }

    ~ThreadSafeCache() 
    { 
        clear();
    }

protected:
    QHash<Key, T*> impl;
};

} // namespace TeamSpeakSdk
