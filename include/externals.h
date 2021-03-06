/*
 * Copyright (C) 2020 Juliette Regimbal
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "interpolation.h"
#include <flext.h>

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif

class weights : public flext_base {
    FLEXT_HEADER(weights, flext_base)
  public:
    weights(float shape);

  protected:
    void m_run(int argc, t_atom *argv);
    void m_shape(float f);

    float shape;

  private:
    FLEXT_CALLBACK_V(m_run);
    FLEXT_CALLBACK_F(m_shape);
};

FLEXT_LIB_1("weights", weights, float)

class interpolate : public flext_base {
    FLEXT_HEADER(interpolate, flext_base)
  public:
    interpolate(float shape);

  protected:
    void m_interpolate(int argc, t_atom *argv);
    void m_weight(int argc, t_atom *argv);

    float shape;
    Eigen::MatrixXd weights;
    std::vector<Interpol::ControlPoint> points;

  private:
    FLEXT_CALLBACK_V(m_interpolate);
    FLEXT_CALLBACK_V(m_weight);
};

FLEXT_LIB_1("interpolate", interpolate, float)

static void lib_setup() {
    /*
    post("mmi lib (C)2020 Juliette Regimbal");
    post("weights, interpolate");
    post("");
    */
    FLEXT_SETUP(weights);
    FLEXT_SETUP(interpolate);
}

FLEXT_LIB_SETUP(mmi, lib_setup)
