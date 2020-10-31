#include "externals.h"
#include "gaussian.h"

using namespace Interpol;
using namespace Eigen;

imatrix::imatrix(float shape) : shape(shape) {
    AddInList("length, size, and contorl points");
    AddInFloat("gaussian shape parameter");
    AddOutList();

    FLEXT_ADDMETHOD(0, m_run);
    FLEXT_ADDMETHOD(1, m_shape);
}

void imatrix::m_run(int argc, t_atom *argv) {
    if (argc < 2) {
        post("%s - Size of inputs not specified!", thisName());
        return;
    }
    int number = GetAInt(argv[0]);
    int size = GetAInt(argv[1]);

    // Check if total size matches expected.
    if (argc != number * size + 2) {
        post("%s - Expected a message of length %d but got %d!", thisName(),
             number * size + 2, argc);
        return;
    }

    // Start loading in values...
    std::vector<ControlPoint> points;
    for (int i = 2; i < argc; i += size) {
        ControlPoint p;
        p.visual(0) = GetAFloat(argv[i]);
        p.visual(1) = GetAFloat(argv[i+1]);
        if (p.control.size() < size - 2) {
            p.control.resize(size - 2);
        }
        for (int j = 2; j < size; j++) {
            p.control(j - 2) = GetAFloat(argv[i + j]);
        }
        points.push_back(p);
    }

    MatrixXd im = Gaussian::InterpolationMatrix(points, shape);

    int length = im.size();
    t_atom * list = new t_atom[length];
    for (size_t i = 0; i < im.rows(); i++) {
        for (size_t j = 0; j < im.cols(); j++) {
            post("Have %f", im(i,j));
            SetFloat(list[j + i*im.cols()], im(i, j));
        }
    }

    ToOutList(0, length, list);
}

void imatrix::m_shape(float f) {
    shape = f;
}
