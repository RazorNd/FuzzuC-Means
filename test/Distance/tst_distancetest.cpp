#include <QString>
#include <QtTest>
#include <algorithm>
#include <FuzzuCMeans.h>
#include "xvector.h"
#include "ximage.h"

using namespace RzrNd::fcm;

class DistanceTest : public QObject
{
    Q_OBJECT

public:

private Q_SLOTS:
    void testEvklidDistance();
    void testDistanceCalc();
    void testDistanceCalcForImage();
};

void DistanceTest::testEvklidDistance()
{
    X_t x{2.0, 1.0, 0.0};
    X_t y{0.0, 1.0, 0.0};
    double result = 2.0;

    EvklidDistance distance;

    double current = distance(x, y);
    QCOMPARE(current, result);
}

void DistanceTest::testDistanceCalc()
{
    VectorX X{{1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}};
    X_t c{0.0, 0.0, 0.0};

    DistanceCalculator calc = DistanceCalculator(EvklidDistance());

    QBENCHMARK {
        calc(c, X);
    }
}

void DistanceTest::testDistanceCalcForImage()
{
    QImage image("://test_image.jpg");

    X_t c{0.0, 0.0, 0.0};

    DistanceCalculator calc = DistanceCalculator(EvklidDistance());

    QBENCHMARK {
        calc(c, image);
    }
}

QTEST_APPLESS_MAIN(DistanceTest)

#include "tst_distancetest.moc"
