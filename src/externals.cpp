#include "externals.h"
#include "gaussian.h"

using namespace Interpol;
using namespace Eigen;

imatrix::imatrix() {
    AddInList("length, size, and contorl points");
    AddOutList();

    FLEXT_ADDMETHOD(0, m_run);
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
        p.visual << GetAFloat(argv[i]), GetAFloat(argv[i + 1]);
        for (int j = 2; j < size; j++) {
            p.control(j - 2) = GetAFloat(argv[i + j]);
        }
        points.push_back(p);
    }

    MatrixXd im = Gaussian::InterpolationMatrix(points, 0.25);

    AtomList l;
    for (size_t i = 0; i < im.rows(); i++) {
        for (size_t j = 0; j < im.cols(); j++) {
            t_atom a;
            SetFloat(a, im(i, j));
            l.Append(a);
        }
    }

    ToOutList(0, l);
}
