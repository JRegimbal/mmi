#include <flext.h>

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif

class imatrix : public flext_base {
    FLEXT_HEADER(imatrix, flext_base)
  public:
    imatrix();

  protected:
    void m_run(int argc, t_atom *argv);

  private:
    FLEXT_CALLBACK_V(m_run);
};

FLEXT_LIB("imatrix", imatrix);

static void lib_setup() {
    post("mmi lib (C)2020 Juliette Regimbal");
    post("imatrix");
    post("");

    FLEXT_SETUP(imatrix);
}

FLEXT_LIB_SETUP(mmi, lib_setup);
