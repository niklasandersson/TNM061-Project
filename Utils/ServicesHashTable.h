#ifndef SERVICESHASHTABLE_H
#define SERVICESHASHTABLE_H

#include <iostream>
#include <string.h>

//#include "../Services/Locator.h"
#include "../Services/Service.h"
#include "../Utils/ServicesHashEntry.h"

class ServicesHashTable
{
    public:
        ServicesHashTable(unsigned int size);
        ~ServicesHashTable();

        void set(const char* key, const Service* value);
        const Service* get(const char* key);
        void remove(const char* key);

    private:
        unsigned int hashFunction(const char* key);
        const unsigned int _size;
        ServicesHashEntry** _data;
};

#endif

