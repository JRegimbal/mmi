/*
 * Copyright (C) 2020 Juliette Regimbal
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "interpolation.h"

#include <Eigen/Dense>
#include <vector>

namespace Interpol {
namespace Gaussian {
double rbf(double r, double shape);

Eigen::MatrixXd InterpolationMatrix(const std::vector<ControlPoint> &points,
                                    double shape);

Eigen::VectorXd Interpolate(const Eigen::MatrixXd &weightMatrix,
                            const Eigen::Vector2d &visual,
                            const std::vector<ControlPoint> &points,
                            double shape);
} // namespace Gaussian
} // namespace Interpol
