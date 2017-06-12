#ifndef XVECTOR_H
#define XVECTOR_H

#include <FuzzuCMeans.h>

namespace RzrNd {
namespace fcm {

template<>
size_t getSize(const VectorX& X)
{
    return X.size();
}

template<>
X_t getValue(const VectorX& X, size_t k)
{
    return X[k];
}

} /// fcm   namespace
} /// RzrNd namespace

#endif // XVECTOR_H
