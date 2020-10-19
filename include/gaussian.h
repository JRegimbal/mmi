#pragma once

#include "interpolation.h"

#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

namespace Interpol {
    namespace Gaussian {
        double rbf(double r, double shape);

        template <int M>
        Eigen::MatrixXd InterpolationMatrix(const std::vector<ControlPoint<M>>&  points, double shape) {
            size_t N = points.size();
            Eigen::MatrixXd interpolation(N,N);
            for (size_t i = 0; i < N; i++) {
                for (size_t j = i; j < N; j++) {
                    interpolation(i,j) = rbf((points[i].control - points[j].control).norm(), shape);
                    if (i != j) {
                        interpolation(j,i) = interpolation(i,j);
                    }
                }
            }
            return interpolation;
        }
    }
}
