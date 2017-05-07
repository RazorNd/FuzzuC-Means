#ifndef ENTITYTRAITS_H
#define ENTITYTRAITS_H

#include <array>
#include <vector>

namespace RzrNd {
namespace fcm {

const unsigned int X_Number_Measurements = 3;

typedef std::array<double, X_Number_Measurements> X_t;

typedef std::vector<X_t> VectorX;

template<class T>
size_t getSize(const T& X);

template<class T>
X_t getValue(const T& X, size_t k);


} /// fcm   namespace
} /// RzrNd namespace

#endif // ENTITYTRAITS_H
