#ifndef SINGLETON_INL
#define SINGLETON_INL

namespace rlib
{
    template <typename T>
    class Singleton
    {
    protected:
        static T* s_instance;

        Singleton() = default;
        virtual ~Singleton() = default;
    public:
        static T* getInstance()
        {
            if (s_instance == nullptr)
                s_instance = new T();

            return s_instance;
        }

        static void deleteInstance()
        {
            if (s_instance != nullptr)
            {
                delete s_instance;
                s_instance = nullptr;
            }
        }
    };

    template <typename T>
    T* Singleton<T>::s_instance = nullptr;
} // namespace rlib

#endif // SINGLETON_INL