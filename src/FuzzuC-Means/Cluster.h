#ifndef CLUSTER_H
#define CLUSTER_H

#include "EntitySetTraits.h"
#include "Distance.h"

namespace RzrNd {
namespace fcm {

class ClustersStorage
{
public:
    ClustersStorage(unsigned int clustersCounts, size_t xSize);

    template<class T>
    VectorX getCentersForX(const T &X, double m) const;

    void updatedClusterForDistances(const std::vector<DistanceCalculator::DistanceVector> &distances);

    double getDesisionValue() const;
};

} /// fcm   namespace
} /// RzrNd namespace


#endif // CLUSTER_H
