#include "gaussian.h"
#include <iostream>
#include <random>

#define N 5
#define M 10

using namespace Interpol;
using namespace Eigen;

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10.0, 10.0);
    std::vector<ControlPoint<M>> points;
    for (size_t i = 0; i < N; i++) {
        ControlPoint<M> p;
        p.control = Matrix<double, M, 1>::NullaryExpr(M, 1, [&](){return dis(gen);});
        p.visual = Matrix<double, 2, 1>::NullaryExpr(2, 1, [&](){return dis(gen);});
        points.push_back(p);
    }

    MatrixXd i = Gaussian::InterpolationMatrix(points, 0.25);
    std::cout << i << std::endl;

    return 0;
}
