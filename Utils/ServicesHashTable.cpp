
#include "ServicesHashTable.h"


ServicesHashTable::ServicesHashTable(unsigned int size) : _size(size)
{
    _data = new ServicesHashEntry*[_size];
    for (unsigned int i=0; i<_size; i++)
    {
        _data[i] = NULL;
    }
}

ServicesHashTable::~ServicesHashTable()
{
    delete [] _data;
}


unsigned int
ServicesHashTable::hashFunction(const char* key)
{
    unsigned int hash = 5381;

    for (unsigned int i = 0; i < strlen(key); i++)
        hash = ((hash << 5) + hash) + (unsigned int)key[i];

    hash %= _size;

    return hash;
}


void
ServicesHashTable::set(const char* key, const Service* value)
{
    std::cout << "set: ";
    ServicesHashEntry* newEntry = new ServicesHashEntry(key, value);
    unsigned int index = hashFunction(key);

    int level = 0;

    if(_data[index] != NULL)
    {
        ServicesHashEntry *p = _data[index];

        while(p != NULL)
        {
            level ++;
            p = p->getNext();
        }

        p = new ServicesHashEntry(key, value);
    } else {
        _data[index] = newEntry;
    }

    std::cout << "Final index: " << index << " , level: " << level << std::endl;

}


const Service*
ServicesHashTable::get(const char* key)
{
    std::cout << "get: ";
    unsigned int index = hashFunction(key);
    return _data[index]->getValue();
}

void
ServicesHashTable::remove(const char* key)
{
    std::cout << "remove: ";
    unsigned int index = hashFunction(key);
    _data[index] = new ServicesHashEntry(NULL, NULL);
}

