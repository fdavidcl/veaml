/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#ifndef _VEAML_CLIP
#define _VEAML_CLIP

#include "mark.h"
#include "instant.h"
#include "timeline.h"
#include <OpenShot.h>
#include <string>

namespace veaml {
  class Clip : public Mark {
  protected:
    std::string filename;
    std::string decoder;
    veaml::Instant t_start;
    veaml::Instant t_end;
    veaml::Instant t_from;
    veaml::Instant t_to;

  public:
    Clip() :t_start(-1), t_end(-1), t_from(0), t_to(-1) {}

    const veaml::Instant& start() const { return t_start; }
    veaml::Instant& start() { return t_start; }
    
    const veaml::Instant& end() const { return t_end; }
    veaml::Instant& end() { return t_end; }

    const veaml::Instant& from() const { return t_from; }
    veaml::Instant& from() { return t_from; }
    
    const veaml::Instant& to() const { return t_to; }
    veaml::Instant& to() { return t_to; }

    const std::string& file() const { return filename; }
    std::string& file() { return filename; }
    
    virtual double duration() = 0;
    virtual bool dispatch_add(veaml::Timeline& container) = 0;
    virtual bool set(attr_t attr, std::string value) = 0;
    virtual openshot::Clip to_openshot(int canvas_x = 0, int canvas_y = 0) = 0;
  };
}

#endif