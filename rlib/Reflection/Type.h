#ifndef TYPE_H
#define TYPE_H

#include <type_traits>
#include <typeinfo>

namespace rlib
{
    template<typename Base, typename Derived>
    bool isDerivedFrom()
    {
        return std::is_base_of_v<Base, Derived>;
    }

    template<class T>
    T* asType(void* _ptr)
    {
        return dynamic_cast<T*>(_ptr);
    }

    template<class T>
    const T* asType(const void* _ptr)
    {
        return dynamic_cast<const T*>(_ptr);
    }

    template<class T>
    bool isType(const void* _ptr)
    {
        return dynamic_cast<const T*>(_ptr) != nullptr;
    }
}

#endif // TYPE_H