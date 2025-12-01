#pragma once

template <class T>
class ObjectPool 
{
private:
    std::queue<T*> pool;
    std::vector<T*> pool;
    std::list<T*> pool;

public:
    ObjectPool(size_t initialSize) { 
        // Populate the object pool
    }

    T* Get() {
        // Get an object from the pool
    }

    void Release(T* _object) {
        // Put the object back in the pool
    }
};

