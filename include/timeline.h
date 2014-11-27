/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_TIMELINE
#define _VEAML_TIMELINE

#include "mark.h"
#include "video.h"
#include <vector>
#include <OpenShot.h>

namespace veaml {
  class Audio;
  class Image;

  class Timeline : public Mark {
  private:
    std::vector<Clip*> v;
    Resolution res;

  public:
    Timeline(int width, int height);
    Timeline() :Timeline(0, 0) {}
    bool add(veaml::Video& v);
    bool add(veaml::Audio& v);
    bool add(veaml::Image& v);

    bool set(attr_t attr, std::string value);
    openshot::Timeline to_openshot();
  };

  class Audio {
    
  };
  class Image {
    
  };
}

#endif