/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_INSTANT
#define _VEAML_INSTANT

#include <string>
#include <iostream>

namespace veaml {
  class Instant {
  private:
    int n_min;
    int n_sec;
    int n_cent;
    static const char DELIM = '.';

    int sto_i(std::string);
  public:
    Instant()                        :n_min(0),  n_sec(0),  n_cent(0)  {}
    Instant(int ns)                  :n_min(0),  n_sec(ns), n_cent(0)  {}
    Instant(int nm, int ns)          :n_min(nm), n_sec(ns), n_cent(0)  {}
    Instant(int nm, int ns, int nc)  :n_min(nm), n_sec(ns), n_cent(nc) {}
    Instant(double secs);
    /*
      Creates an Instant from a string following the pattern
      1.20.50
    */
    Instant(std::string value);

    const int& min() const { return n_min; }
    int& min() { return n_min; }

    const int& sec() const { return n_sec; }
    int& sec() { return n_sec; }

    const int& cent() const { return n_cent; }
    int& cent() { return n_cent; }

    double to_f();
  };
}

#endif