#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include "EntitySetTraits.h"
#include "Distance.h"

namespace RzrNd {
namespace fcm {

class ClustersStorage
{
public:
    typedef std::vector<double> Cluster;
    typedef std::vector<Cluster> ClusterVecotor;
private:
    unsigned int clustersCounts;
    size_t clusterSize;
    ClusterVecotor clusters;

    static ClusterVecotor createClusterVector(unsigned int clustersCounts, size_t xSize)
    {
        ClusterVecotor result;
        result.reserve(clustersCounts);
        for (unsigned i = 0; i < clustersCounts; ++i) {
            result.emplace_back(xSize);
        }
        return result;
    }

    static double distance(const ClusterVecotor& a, const ClusterVecotor &b)
    {
        double result = 0.0;
        const size_t imax = a.size(),
                jmax = a[0].size();
        for (size_t i = 0; i < imax; ++i) {
            for (size_t j = 0; j < jmax; ++j) {
                result += std::fabs(a[i][j] - b[i][j]);
            }
        }
        return result;
    }

public:
    ClustersStorage(unsigned int clustersCounts, size_t xSize)
        : clustersCounts(clustersCounts),
          clusterSize(xSize),
          clusters(ClustersStorage::createClusterVector(clustersCounts, xSize))
    {        
    }

    template<class T>
    VectorX getCentersForX(const T &X, double w) const
    {
        const auto size = getSize(X);
        VectorX result;
        result.reserve(clusters.size());
        X_t numerator;
        for (auto cluster : clusters) {
            numerator = std::inner_product(begin(X), end(X), std::begin(cluster), X_t(), [] (const X_t &a, const X_t &b) {
                X_t result;
                std::transform(std::begin(a), std::end(a), std::begin(b), std::begin(result), std::plus<double>());
                return result;
            }, [w](const X_t &x, double m) {
                X_t result;
                std::transform(std::begin(x), std::end(x),
                               std::begin(result), std::bind(
                                   std::multiplies<double>(), std::placeholders::_1, std::pow(m, w)
                                   )
                               );
                return result;
            });
            const double denominator = std::accumulate(std::begin(cluster), std::end(cluster), 0.0, [w](double s, double m) {
                return s + std::pow(m, w);
            });
            std::transform(std::begin(numerator), std::end(numerator),
                           std::begin(numerator),
                           std::bind(std::divides<double>(), std::placeholders::_1, denominator));
            result.push_back(std::move(numerator));
        }
        return result;
    }

    double updatedClusterForDistances(const std::vector<DistanceCalculator::DistanceVector> &distances, double w)
    {
        ClusterVecotor newClusters = ClustersStorage::createClusterVector(clustersCounts, clusterSize);

        for (size_t i = 0; i < clustersCounts; ++i) {
            for (size_t j = 0; j < clusterSize; ++j) {
                if (std::fabs(distances[i][j]) < std::numeric_limits<double>::epsilon()) {
                    newClusters[i][j] = i == j ? 1.0 : 0.0;
                } else {
                    double s = 0.0;
                    for (size_t f = 0; f < clustersCounts; f++) {
                        s += std::pow(distances[i][j] / distances[f][j], 2.0 / (w - 1));
                    }
                    newClusters[i][j] = s;
                }
            }
        }

        std::swap(newClusters, clusters);

        return distance(newClusters, clusters);
    }
};

} /// fcm   namespace
} /// RzrNd namespace


#endif // CLUSTER_H
