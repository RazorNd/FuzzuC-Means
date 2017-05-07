#ifndef ENTITYSETITERATOR_H
#define ENTITYSETITERATOR_H


#include <iterator>
#include "EntitySetTraits.h"

namespace RzrNd {
namespace fcm {

template<class T>
class XIterator : public std::iterator<std::input_iterator_tag, X_t>
{
    const T &_X;
    size_t _position = 0;
public:
    XIterator(const T &X) : _X(X) {}
    XIterator(const T &X, size_t position) : _X(X), _position(position) {}

    bool operator != (XIterator<T> other)
    {
        return _position != other._position;
    }

    X_t operator * ()
    {
        return getValue(_X, _position);
    }

    XIterator<T> &operator ++ ()
    {
        _position++;
        return *this;
    }
};

template<class T>
XIterator<T> begin(const T &X)
{
    return XIterator<T>(X);
}

template<class T>
XIterator<T> end(const T &X)
{
    return XIterator<T>(X, getSize(X));
}


} /// fcm   namespace
} /// RzrNd namespace

#endif // ENTITYSETITERATOR_H
