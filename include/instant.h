#ifndef _VEAML_INSTANT
#define _VEAML_INSTANT

namespace veaml {
  class Instant {
  private:
    int n_min;
    int n_sec;
    int n_cent;

  public:
    Instant()                        :n_min(0),  n_sec(0),  n_cent(0)  {}
    Instant(int ns)                  :n_min(0),  n_sec(ns), n_cent(0)  {}
    Instant(int nm, int ns)          :n_min(nm), n_sec(ns), n_cent(0)  {}
    Instant(int nm, int ns, int nc)  :n_min(nm), n_sec(ns), n_cent(nc) {}
    Instant(float secs)
      :n_sec{secs/1}, n_cent{((secs-n_sec)*100)/1}, n_min{n_sec/60} {
      n_sec -= n_min * 60;
    }

    const int& min() const { return n_min; }
    int& min() { return n_min; }

    const int& sec() const { return n_sec; }
    int& sec() { return n_sec; }

    const int& cent() const { return n_cent; }
    int& cent() { return n_cent; }

    float to_f() {
      return n_min * 60 + n_sec + (n_cent / 100.0);
    }
  };
}

#endif