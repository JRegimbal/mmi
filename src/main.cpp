/*
 * Copyright (C) 2020 Juliette Regimbal
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "gaussian.h"
#include <iostream>
#include <random>

#define N 5
#define M 4

using namespace Interpol;
using namespace Eigen;

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10.0, 10.0);
    std::vector<ControlPoint> points;
    std::cout << "Using " << N << " samples with " << M << " DoF.\n";
    for (size_t i = 0; i < N; i++) {
        ControlPoint p;
        p.control = VectorXd::NullaryExpr(
            M, 1, [&]() { return (double)(int)dis(gen); });
        p.visual = Vector2d::NullaryExpr(
            2, 1, [&]() { return (double)(int)dis(gen); });
        points.push_back(p);
    }

    std::cout << "Random values have stress " << Stress1(points) << std::endl;

    MatrixXd i = Gaussian::InterpolationMatrix(points, 0.25);
    std::cout << i << std::endl;
    std::cout << "Get weights..." << std::endl;
    MatrixXd controls = ControlMatrix(points);
    std::cout << "Control points:\n";
    std::cout << controls << std::endl;
    MatrixXd visual(2, N);
    for (size_t j = 0; j < points.size(); j++) {
        visual.col(j) = points.at(j).visual;
    }
    std::cout << "Visual points:\n";
    std::cout << visual << std::endl;
    Matrix<double, N, M> weights = SolveWeights(i, controls);
    std::cout << "Weights matrix:\n";
    std::cout << weights << std::endl;

    Vector2d vis =
        Vector2d::NullaryExpr(2, 1, [&]() { return (double)(int)dis(gen); });
    std::cout << "Interpolating from point (" << vis(0) << ", " << vis(1)
              << "):\n";
    VectorXd interpolated = Gaussian::Interpolate(weights, vis, points, 0.25);
    std::cout << interpolated << std::endl;
    return 0;
}
