#include <iostream>
#include <string.h>


template <class T>
class Hash
{
    public:
        Hash(unsigned int size);
        ~Hash();

        void set(const char* key, const T& value);
        T get(const char* key);

    private:
        unsigned int hashFunction(const char* key);
        const unsigned int _size;
        T* _data;
};


template <class T>
Hash<T>::Hash(unsigned int size) : _size(size)
{
    _data = new T[_size];
}


template <class T>
Hash<T>::~Hash()
{
    delete [] _data;
}


template <class T>
unsigned int
Hash<T>::hashFunction(const char* key)
{
    unsigned int hash = 5381;

    for (unsigned int i = 0; i < strlen(key); i++)
        hash = ((hash << 5) + hash) + (unsigned int)key[i];

    return hash % _size;

}


template <class T>
void
Hash<T>::set(const char* key, const T& value)
{
    unsigned int index = hashFunction(key);
    _data[index] = value;
}


template <class T>
T
Hash<T>::get(const char* key)
{
    unsigned int index = hashFunction(key);
    return _data[index];
}

