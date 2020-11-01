/*
 * Copyright (C) 2020 Juliette Regimbal
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "externals.h"
#include "gaussian.h"

using namespace Interpol;
using namespace Eigen;

weights::weights(float shape) : shape(shape) {
    AddInList("length, size, and contorl points");
    AddInFloat("gaussian shape parameter");
    AddOutList();

    FLEXT_ADDMETHOD(0, m_run);
    FLEXT_ADDMETHOD(1, m_shape);
}

void weights::m_run(int argc, t_atom *argv) {
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
        p.visual(1) = GetAFloat(argv[i + 1]);
        if (p.control.size() < size - 2) {
            p.control.resize(size - 2);
        }
        for (int j = 2; j < size; j++) {
            p.control(j - 2) = GetAFloat(argv[i + j]);
        }
        points.push_back(p);
    }

    MatrixXd im = Gaussian::InterpolationMatrix(points, shape);
    MatrixXd controls = ControlMatrix(points);
    MatrixXd weights = SolveWeights(im, controls);

    int length = weights.size();
    t_atom *list = new t_atom[length];
    for (size_t i = 0; i < weights.rows(); i++) {
        for (size_t j = 0; j < weights.cols(); j++) {
            SetFloat(list[j + i * weights.cols()], weights(i, j));
        }
    }

    ToOutList(0, length, list);
}

void weights::m_shape(float f) { shape = f; }
