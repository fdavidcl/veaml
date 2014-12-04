/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_TIMELINE
#define _VEAML_TIMELINE

namespace veaml { class Clip; }

#include "resolution.h"
#include <string>
#include <vector>
#include <OpenShot.h>

namespace veaml {
  class Timeline : public Mark {
  private:
    std::vector<veaml::Clip*> tl;
    veaml::Resolution res;
    openshot::Fraction framerate;
    unsigned int audiorate = 44100;
    //unsigned int audiorate = 48000;
    unsigned int channels = 2;
    std::string filename;
    std::string audiocodec;
    std::string videocodec;

    double adjust_timing();
  public:
    Timeline(int width, int height);
    Timeline() :Timeline(0, 0) {}

    bool add(veaml::Clip& v);

    bool set(attr_t attr, std::string value);
    openshot::Timeline to_openshot();
    bool output();
  };
}

#endif