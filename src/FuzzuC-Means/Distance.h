#ifndef DISTANCE_H
#define DISTANCE_H

#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include "EntitySetTraits.h"
#include "EntitySetIterator.h"

namespace RzrNd {
namespace fcm {

class Norma
{
public:
    double getDistance(X_t &center, const X_t &value)
    {
        return (*this)(center, value);
    }

    virtual double operator() (const X_t &center, const X_t &value) const = 0;
    virtual ~Norma() = default;
};

class EvklidDistance : public Norma
{
    struct point_difference
    {
        double operator() (double x, double y)
        {
            return std::pow(x - y, 2.0);
        }
    };

    // Norma interface
public:
    virtual double operator ()(const X_t &center, const X_t &value) const override
    {
        return std::sqrt(std::inner_product(
                             std::begin(center),
                             std::end(center),
                             std::begin(value),
                             0.0,
                             std::plus<double>(),
                             point_difference()
                             ));
    }
};

class DistanceCalculator
{
    const Norma &_norma;
public:
    typedef std::vector<double> DistanceVector;
    typedef std::function<double (const X_t &)> DistanceToCenterFunction;

    DistanceCalculator(const Norma &norma) : _norma(norma) {}

    template<class T>
    DistanceVector operator () (X_t center, const T &X) const
    {
        DistanceVector distances(getSize(X));

        //        DistanceToCenterFunction distanceFunction = std::bind(&Norma::operator(), std::cref(_norma), center);

        std::transform(fcm::begin(X), fcm::end(X), std::begin(distances), [this, center] (const X_t &x) {
            return _norma(center, x);
        });

        return distances;
    }
};


} /// fcm   namespace
} /// RzrNd namespace

#endif // DISTANCE_H
