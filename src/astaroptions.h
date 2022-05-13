#ifndef ANONYMOUSMAPF_ASTAROPTIONS_H
#define ANONYMOUSMAPF_ASTAROPTIONS_H

enum MetricType {
    Euclidean, Manhattan, Chebyshev, DiagonalDistance
};

class AStarOptions{
public:
    MetricType METRIC_TYPE;

    AStarOptions(MetricType _metric_type);

};
#endif //ANONYMOUSMAPF_ASTAROPTIONS_H