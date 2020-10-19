#pragma once

#include <Eigen/Dense>

namespace Interpol {
    template <int M>
    struct ControlPoint {
        Eigen::Matrix<double, M, 1> control;
        Eigen::Matrix<double, 2, 1> visual;
    };
}
