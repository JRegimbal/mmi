#pragma once

#include "interpolation.h"

#include <vector>
#include <Eigen/Dense>

namespace Interpol {
    namespace Gaussian {
        double rbf(double r, double shape);

        Eigen::MatrixXd InterpolationMatrix(const std::vector<ControlPoint>&  points, double shape);
    }
}
