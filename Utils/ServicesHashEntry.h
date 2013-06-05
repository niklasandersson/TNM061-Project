#ifndef SERVICESHASHENTRY_H
#define SERVICESHASHENTRY_H

#include "../Services/Service.h"

class ServicesHashEntry
{
    public:
        ServicesHashEntry(const char* key, const Service* value);
        const char* getKey() const;
        const Service* getValue() const;
        ServicesHashEntry* getNext() const;

    private:
        const char* _key;
        const Service* _value;
        ServicesHashEntry* _next;
};
#endif
s