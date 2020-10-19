#pragma once

#include <vector>
#include <Eigen/Dense>

namespace Interpol {
    template <int M>
    struct ControlPoint {
        Eigen::Matrix<double, M, 1> control;
        Eigen::Matrix<double, 2, 1> visual;
    };

    template <int M>
    Eigen::Matrix<double, M, Eigen::Dynamic> ControlMatrix(const std::vector<ControlPoint<M>>& points) {
        Eigen::MatrixXd controls(M, points.size());
        for (size_t i = 0; i < points.size(); i++) {
            controls.col(i) = points[i].control;
        }
        return controls;
    }

    template <int N>
    Eigen::MatrixXd SolveWeights(const Eigen::Matrix<double, N, N>& imatrix, const Eigen::MatrixXd& points) {
        Eigen::MatrixXd weights(points.cols(),points.rows());
        // Make N-vector of weights for M parameters
        auto inter = imatrix.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV);

        for (size_t i = 0; i < points.rows(); i++) {
            auto key = points.row(i).transpose();
            weights.col(i) = inter.solve(key);
        }
        return weights;
    }
}
