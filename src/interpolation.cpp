#include "interpolation.h"
#include <tgmath.h>

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

    double Stress1(const std::vector<ControlPoint>& points) {
        double n = 0;
        double d = 0;
        for (size_t i = 0; i < points.size(); i++) {
            for (size_t j = i + 1; j < points.size(); j++) {
                double dij = (points[i].control - points[j].control).norm();
                double delij = (points[i].visual - points[j].visual).norm();
                n += pow(dij - delij, 2);
                d += pow(dij, 2);
            }
        }
        return sqrt(n/d);
    }
};
