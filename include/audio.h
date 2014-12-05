/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_AUDIO
#define _VEAML_AUDIO

#include "clip.h"
#include <string>

namespace veaml {
  class Audio : public Clip {
  private:
    void set_timing(openshot::Clip& content);
  public:
    Audio() {}
    
    double duration();
    bool dispatch_add(veaml::Timeline& container);
    bool set(attr_t attr, std::string value);
    openshot::Clip to_openshot();
  };
}

#endif