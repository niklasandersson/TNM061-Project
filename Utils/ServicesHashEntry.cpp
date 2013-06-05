
#include "ServicesHashEntry.h"

ServicesHashEntry::ServicesHashEntry(const char* key, const Service* value)
: _key(key), _value(value)
{
    _next = NULL;
}

const char*
ServicesHashEntry::getKey() const
{
    return _key;
}


const Service*
ServicesHashEntry::getValue() const
{
    return _value;
}

ServicesHashEntry*
ServicesHashEntry::getNext() const
{
    return _next;
}
