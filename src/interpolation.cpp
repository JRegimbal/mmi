#include "interpolation.h"

using namespace Eigen;

namespace Interpol {
    MatrixXd ControlMatrix(const std::vector<ControlPoint>& points) {
        MatrixXd controls(points[0].control.rows(), points.size());
        for (size_t i = 0; i < points.size(); i++) {
            controls.col(i) = points[i].control;
        }
        return controls;
    }

    MatrixXd SolveWeights(const MatrixXd& imatrix, const MatrixXd& points) {
        MatrixXd weights(points.cols(),points.rows());
        // Make N-vector of weights for M parameters
        auto inter = imatrix.bdcSvd(ComputeThinU | ComputeThinV);

        for (size_t i = 0; i < points.rows(); i++) {
            auto key = points.row(i).transpose();
            weights.col(i) = inter.solve(key);
        }
        return weights;
    }
};
