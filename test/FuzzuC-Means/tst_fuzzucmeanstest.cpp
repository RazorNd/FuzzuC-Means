#include <QString>
#include <QtTest>
#include <FuzzuCMeans.h>
#include <ximage.h>

using namespace RzrNd::fcm;

class FuzzuCMeansTest : public QObject
{
    Q_OBJECT

public:
    FuzzuCMeansTest();

private Q_SLOTS:
    void operatorTest();
};

FuzzuCMeansTest::FuzzuCMeansTest()
{
}

QImage clusterToImage(const ClustersStorage::Cluster &cluster, const int width)
{
    size_t k = cluster.size();
    QImage result(width, k / width, QImage::Format_Alpha8);

    for (size_t i = 0; i < k; ++i) {
        double gray = cluster[i];
        const int y = static_cast<int>(i / width),
                x = static_cast<int>(i % width);
        result.setPixel(x, y, gray * 255);
    }
    return result;
}

void setAlpha(QImage &image, const ClustersStorage::Cluster &cluster)
{
    size_t size = cluster.size();
    size_t width = static_cast<size_t>(image.width());
    QImage alpha = image.alphaChannel();

    for (size_t i = 0; i < size; ++i) {
        const int y = static_cast<int>(i / width),
                x = static_cast<int>(i % width);
        alpha.setPixel(x, y, cluster[i] * 255);
    }
    image.setAlphaChannel(alpha);
}

void FuzzuCMeansTest::operatorTest()
{
    QImage image("://test_image.jpg");
    FuzzuCMeans f(4, 0.7, 0.0001);
    ClustersStorage::ClusterVecotor r;

    r = f(image);

    for (int i = 0; i < 4; i++) {
        QImage clustered = image.copy();
        clustered.setAlphaChannel(clusterToImage(r[i], image.width()));
        QVERIFY(clustered.save(QString("cluster %1.png").arg(i + 1)));
    }
}

QTEST_APPLESS_MAIN(FuzzuCMeansTest)

#include "tst_fuzzucmeanstest.moc"
