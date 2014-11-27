/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_MARK
#define _VEAML_MARK

#include <string>

namespace veaml {
  enum attr_t {
    /* Timing attributes */
    FROM,
    TO,
    START,
    END,

    /* Size and position attributes *
     * (for videos and pictures)    */
    WIDTH,
    HEIGHT,
    TOP,
    LEFT
  };

  class Mark {
  public:
    virtual bool set(attr_t, std::string) = 0;
  };
}

#endif