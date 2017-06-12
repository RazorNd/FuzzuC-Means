#include <QString>
#include <QtTest>
#include <FuzzuCMeans.h>
#include "xvector.h"
#include "ximage.h"

using namespace RzrNd::fcm;

class ClusterTest : public QObject
{
    Q_OBJECT

public:
    ClusterTest();

private Q_SLOTS:        
    void getCentersForX();    
};

ClusterTest::ClusterTest()
{
}

void ClusterTest::getCentersForX()
{
    QImage image("://test_image.jpg");
    ClustersStorage storage(4, getSize(image));
    VectorX res;
    QBENCHMARK {
        res = storage.getCentersForX(image, 0.8);
    }
    QVERIFY(res.size() == 4);
}

QTEST_APPLESS_MAIN(ClusterTest)

#include "tst_clustertest.moc"
