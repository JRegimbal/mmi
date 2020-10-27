#include "gaussian.h"
#include <assert.h>
#include <tgmath.h>

using namespace Eigen;

namespace Interpol {
namespace Gaussian {
double rbf(double r, double shape) { return exp(-pow(r * shape, 2)); }

MatrixXd InterpolationMatrix(const std::vector<ControlPoint> &points,
                             double shape) {
    size_t N = points.size();
    MatrixXd interpolation(N, N);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = i; j < N; j++) {
            interpolation(i, j) =
                rbf((points[i].visual - points[j].visual).norm(), shape);
            if (i != j) {
                interpolation(j, i) = interpolation(i, j);
            }
        }
    }
    return interpolation;
}

VectorXd Interpolate(const MatrixXd &weightMatrix, const Vector2d &visual,
                     const std::vector<ControlPoint> &points, double shape) {
    // Weight matrix goes column by column for each parameter. I.e., column 0
    // are weights for parameter 0.
    assert(weightMatrix.rows() == points.size());
    assert(weightMatrix.cols() == points.at(0).control.rows());
    double *rbfresult = new double[points.size()];
    VectorXd result(weightMatrix.cols());
    for (size_t param = 0; param < weightMatrix.cols(); param++) {
        double partial = 0;
        for (size_t point = 0; point < points.size(); point++) {
            if (param == 0) {
                rbfresult[point] =
                    rbf((points.at(point).visual - visual).norm(), shape);
            }
            partial += weightMatrix(point, param) * rbfresult[point];
        }
        result(param) = partial;
    }
    return result;
}
} // namespace Gaussian
} // namespace Interpol
