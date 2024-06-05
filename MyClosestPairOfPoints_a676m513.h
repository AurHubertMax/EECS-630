#ifndef _MY_CLOSEST_PAIR_POINTS_H_
#define _MY_CLOSEST_PAIR_POINTS_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <algorithm>

typedef 
    struct 
    {
        unsigned int ID;    // the ID of the point
        float x;              // the x-coordinate of the point
        float y;              // the y-coordinate of the point
    }
PointType;

struct Result {
    float distance;
    PointType p1;
    PointType p2;
};

float distance(const PointType& p1, const PointType& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Result bruteForce(const std::vector<PointType>& points) {
    Result result;
    result.distance = FLT_MAX;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            float d = distance(points[i], points[j]);
            if (d < result.distance) {
                result.distance = d;
                result.p1 = points[i];
                result.p2 = points[j];
            }
        }
    }
    return result;
}

Result stripClosest(const std::vector<PointType>& strip, float d) {
    Result result;
    result.distance = d;
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++) {
            float d = distance(strip[i], strip[j]);
            if (d < result.distance) {
                result.distance = d;
                result.p1 = strip[i];
                result.p2 = strip[j];
            }
        }
    }
    return result;
}

Result closestUtil(const std::vector<PointType>& points) {
    if (points.size() <= 3) {
        return bruteForce(points);
    }

    size_t mid = points.size() / 2;
    PointType midPoint = points[mid];

    std::vector<PointType> left(points.begin(), points.begin() + mid);
    std::vector<PointType> right(points.begin() + mid, points.end());

    Result leftResult = closestUtil(left);
    Result rightResult = closestUtil(right);

    Result result = leftResult.distance < rightResult.distance ? leftResult : rightResult;

    std::vector<PointType> strip;
    for (size_t i = 0; i < points.size(); i++) {
        if (abs(points[i].x - midPoint.x) < result.distance) {
            strip.push_back(points[i]);
        }
    }

    std::sort(strip.begin(), strip.end(), [](const PointType& p1, const PointType& p2) {
        return p1.y < p2.y;
    });

    Result stripResult = stripClosest(strip, result.distance);
    return stripResult.distance < result.distance ? stripResult : result;
}

/*------------------------------------------------------------------------------
    ClosestPairOfPoints: find the closest pair of points from a set of points in a 2D plane 
    
        points: the set of points
        p1: the first point of the closest pair of points; should have a smaller ID
        p2: the second point of the closest pair of points; should have a larger ID
        
        returns the distance between the two points (round to 3-digit precision)
------------------------------------------------------------------------------*/
float ClosestPairOfPoints
(
    const std::vector<PointType> & points,
    PointType & p1,
    PointType & p2
)
{
  /*------ CODE BEGINS ------*/
    std::vector<PointType> sortedPoints(points);
    std::sort(sortedPoints.begin(), sortedPoints.end(), [](const PointType& p1, const PointType& p2) {
        return p1.x < p2.x;
    });

    Result result = closestUtil(sortedPoints);

    if (result.p1.ID > result.p2.ID) {
        std::swap(result.p1, result.p2);
    }

    p1 = result.p1;
    p2 = result.p2;

    float rounded = std::round(result.distance * 1000) / 1000.0;
    return rounded;

  /*------ CODE ENDS ------*/
}



#endif
