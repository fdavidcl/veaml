/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_VIDEO
#define _VEAML_VIDEO

#include "clip.h"
#include <string>

namespace veaml {
  class Video : public Clip {
  private:
    veaml::Resolution res;
    double volume;
    static int layers;

    void set_timing(openshot::Clip& content);
    void set_resolution(openshot::Clip& content);
  public:
    Video() :volume(1) {}
    
    double duration();
    bool dispatch_add(veaml::Timeline& container);
    bool set(attr_t attr, std::string value);
    openshot::Clip to_openshot();
  };
}

#endif