#include <flext.h>

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif

class imatrix : public flext_base {
    FLEXT_HEADER(imatrix, flext_base)
  public:
    imatrix(float shape);

  protected:
    void m_run(int argc, t_atom *argv);
    void m_shape(float f);

    float shape;

  private:
    FLEXT_CALLBACK_V(m_run);
    FLEXT_CALLBACK_F(m_shape);
};

FLEXT_LIB_1("imatrix", imatrix, float);

static void lib_setup() {
    post("mmi lib (C)2020 Juliette Regimbal");
    post("imatrix");
    post("");

    FLEXT_SETUP(imatrix);
}

FLEXT_LIB_SETUP(mmi, lib_setup);
