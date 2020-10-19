#include <tgmath.h>
#include "gaussian.h"

namespace Interpol {
    namespace Gaussian {
        double rbf(double r, double shape) {
            return exp(-pow(r * shape, 2));
        }
    }
}
