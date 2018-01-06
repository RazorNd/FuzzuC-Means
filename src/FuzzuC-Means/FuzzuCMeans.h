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

    typedef std::vector<DistanceCalculator::DistanceVector> V_t;
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
        V_t distancesToCenters(_clustersCounts);

        while (std::abs(currentDesisionValue - previousDecisionValue) > _epsilon) {
            std::swap(currentDesisionValue, previousDecisionValue);

            auto centers = clusters.getCentersForX(X, _m);

            std::transform(
                        std::begin(centers),
                        std::end(centers),
                        std::begin(distancesToCenters),
                        std::bind(distanceCalculator, std::placeholders::_1, X)
                        );

            clusters.updatedClusterForDistances(distancesToCenters, _m);


            currentDesisionValue = calculateDecisionValue(clusters.getClusters(), centers, X);
        }

        return clusters.getClusters();
    }

private:
    template<class T>
    double calculateDecisionValue(const ClustersStorage::ClusterVecotor &clusters, const VectorX &V, const T& X) const
    {
        auto c = V.size();
        auto l = clusters.size();

        double result = 0.0;

        for (size_t i = 0; i < c; i++) {
            for (size_t j = 0; j < l; j++) {
                auto distance = _norma(V[i], getValue(X, j));
                result += std::pow(clusters[i][j], _m) * (distance * distance);
            }
        }

        return result;
    }
};


} /// fcm   namespace
} /// RzrNd namespace

#endif // FUZZUCMEANS_H
