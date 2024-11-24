#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <iomanip>

struct Circle {
    double x, y, r;
};

bool isInsideCircle(double px, double py, const Circle& circle) {
    double dx = px - circle.x;
    double dy = py - circle.y;
    return dx * dx + dy * dy <= circle.r * circle.r;
}

bool isInsideIntersection(double px, double py, const std::vector<Circle>& circles) {
    for (const auto& circle : circles) {
        if (!isInsideCircle(px, py, circle)) {
            return false;
        }
    }
    return true;
}

double monteCarloEstimate(const std::vector<Circle>& circles, int numPoints) {
    double minX = 2 - sqrt(5) / 2, minY = 1.5 - sqrt(5) / 2, maxX = 2, maxY = 2;
    std::mt19937 gen(101);
    std::uniform_real_distribution<double> distX(minX, maxX);
    std::uniform_real_distribution<double> distY(minY, maxY);
    int insideCount = 0;
    for (int i = 0; i < numPoints; ++i) {
        double px = distX(gen);
        double py = distY(gen);
        if (isInsideIntersection(px, py, circles)) {
            ++insideCount;
        }
    }
    double areaRectangle = (maxX - minX) * (maxY - minY);
    return areaRectangle * insideCount / numPoints;
}

int main() {
    std::vector<Circle> circles = {
        {1, 1, 1},
        {1.5, 2, std::sqrt(5) / 2},
        {2, 1.5, std::sqrt(5) / 2}
    };
    const int step = 500;
    const int maxPoints = 100000;
    for (int numPoints = 100; numPoints <= maxPoints; numPoints += step) {
        double estimatedArea = monteCarloEstimate(circles, numPoints);
        std::cout << numPoints << " " << std::fixed << std::setprecision(6) << estimatedArea << std::endl;
    }

    return 0;
}
