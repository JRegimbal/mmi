#include <flext.h>

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif

class mmi : public flext_base {
    FLEXT_HEADER(mmi, flext_base)
  public:
    mmi();
};

class imatrix : public mmi {
    FLEXT_HEADER(imatrix, flext_base)
  public:
    imatrix();

  protected:
    void m_run(int argc, t_atom *argv);

  private:
    FLEXT_CALLBACK_V(m_run);
};

FLEXT_NEW("imatrix", imatrix);
