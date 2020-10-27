#pragma once

#include <Eigen/Dense>
#include <vector>

namespace Interpol {
struct ControlPoint {
    Eigen::VectorXd control;
    Eigen::Vector2d visual;
};

Eigen::MatrixXd ControlMatrix(const std::vector<ControlPoint> &points);

Eigen::MatrixXd SolveWeights(const Eigen::MatrixXd &imatrix,
                             const Eigen::MatrixXd &points);

double Stress1(const std::vector<ControlPoint> &points);
} // namespace Interpol
