#include "autil/mem_pool/PoolString.h"

#include <algorithm>
#include <iosfwd>

#include "autil/Log.h"

namespace autil {
namespace mem_pool {

using namespace std;

PoolString::PoolString(Pool *pool) {
    reset(pool);
    expand();
    _data[0] = '\0';
}

PoolString::PoolString(Pool *pool, const char* str) {
    reset(pool);
    size_t len = strlen(str);
    expand(len + 1);
    strCopy(_data, str, len);
    _size = len;
}

PoolString::PoolString(Pool *pool, const char* str, size_t size) {
    reset(pool);
    expand(size + 1);
    strCopy(_data, str, size);
    _size = size;
}

PoolString::PoolString(const PoolString &other) {
    reset(other._pool);
    expand(other._size + 1);
    strCopy(_data, other._data, other._size);
    _size = other._size;
}

PoolString::~PoolString() {
    _pool->deallocate(_data, _capacity);
}

PoolString& PoolString::operator = (const PoolString &other) {
    _size = 0;
    expand(other._size + 1);
    strCopy(_data, other._data, other._size);
    _size = other._size;
    return *this;
}

PoolString& PoolString::operator = (const char* str) {
    size_t len = strlen(str);
    _size = 0;
    expand(len + 1);
    strCopy(_data, str, len);
    _size = len;
    return *this;
}

bool PoolString::operator < (const PoolString& other) const {
    if (compare(other) < 0) {
        return true;
    } else {
        return false;
    }
}

PoolString& PoolString::append(const char* str) {
    size_t len = strlen(str);
    return doAppend(str, len);
}

PoolString& PoolString::append(const char* str, size_t size) {
    return doAppend(str, size);
}

PoolString& PoolString::append(const PoolString& other) {
    size_t len = other.size();
    return doAppend(other._data, len);
}

int PoolString::compare(const PoolString& other) const {
    int res = strncmp(_data, other._data, min(_size, other._size));
    if (res != 0) {
        return res;
    } else {
        return _size - other._size;
    }
}

}
}

