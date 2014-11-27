/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_CLIP
#define _VEAML_CLIP

#include "mark.h"
#include "instant.h"
#include <OpenShot.h>
#include <string>

namespace veaml {
  class Clip : public Mark {
  protected:
    std::string filename;
    veaml::Instant t_start;
    veaml::Instant t_end;

  public:
    Clip(std::string file, Instant f, Instant t) 
      :filename(file), t_start(f), t_end(t) {}
    Clip(std::string file) 
      :filename(file) {}
    Clip() {}

    const veaml::Instant& start() const { return t_start; }
    veaml::Instant& start() { return t_start; }
    
    const veaml::Instant& end() const { return t_end; }
    veaml::Instant& end() { return t_end; }

    const std::string& file() const { return filename; }
    std::string& file() { return filename; }
    
    virtual bool set(attr_t attr, std::string value) = 0;
    virtual openshot::Clip to_openshot() = 0;
  };

  struct Resolution {
    unsigned int width;
    unsigned int height;

    Resolution() :width(0), height(0) {}
    Resolution(int x, int y) :width(x), height(y) {}
  };
}

#endif