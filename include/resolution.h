/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_RES
#define _VEAML_RES

namespace veaml {
  struct Resolution {
    unsigned int width;
    unsigned int height;

    Resolution() :width(0), height(0) {}
    Resolution(int x, int y) :width(x), height(y) {}
  };
}

#endif