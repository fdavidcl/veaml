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
    veaml::Instant t_from;
    veaml::Instant t_to;

    void set_timing(openshot::Clip& content);
    void set_resolution(openshot::Clip& content);
  public:
    Video() {}
    Video(std::string file) :Clip(file) {}
    Video(std::string file, veaml::Instant f, veaml::Instant t) :Clip(file, f, t) {}
    //Video(std::string file, veaml::Resolution r);
    //Video(std::string file, veaml::Instant f, veaml::Instant t, veaml::Resolution r);
    
    bool dispatch_add(veaml::Timeline& container);
    bool set(attr_t attr, std::string value);
    openshot::Clip to_openshot();
  };
}

#endif