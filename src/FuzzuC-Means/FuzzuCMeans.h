#ifndef FUZZUCMEANS_H
#define FUZZUCMEANS_H

#include "Distance.h"
#include "Cluster.h"

namespace RzrNd {
namespace fcm {

class FuzzuCMeans
{
    unsigned int _clustersCounts;
    double _m;
    double _epsilon;
    const Norma &_norma;
public:
    FuzzuCMeans(unsigned int clustersCounts, double m, double epsilon, const Norma &norma = EvklidDistance()) :
        _clustersCounts(clustersCounts),
        _m(m),
        _epsilon(epsilon),
        _norma(norma)
    {
    }

    template<class T>
    ClustersStorage::ClusterVecotor operator () (const T& X) const
    {
        ClustersStorage clusters(_clustersCounts, getSize(X));
        double previousDecisionValue = 0.0, currentDesisionValue = 1.0;
        DistanceCalculator distanceCalculator(_norma);
        std::vector<DistanceCalculator::DistanceVector> distancesToCenters(_clustersCounts);

        while (std::abs(currentDesisionValue - previousDecisionValue) > _epsilon) {
            std::swap(currentDesisionValue, previousDecisionValue);

            auto centers = clusters.getCentersForX(X, _m);

            std::transform(
                        std::begin(centers),
                        std::end(centers),
                        std::begin(distancesToCenters),
                        std::bind(distanceCalculator, std::placeholders::_1, X)
                        );

            currentDesisionValue = clusters.updatedClusterForDistances(distancesToCenters, _m);
        }

        return clusters.getClusters();
    }
};


} /// fcm   namespace
} /// RzrNd namespace

#endif // FUZZUCMEANS_H
