/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "timeline.h"

veaml::Timeline::Timeline(int width, int height)
  :res(width, height) { }

bool veaml::Timeline::set(attr_t attr, std::string value) {
  return true;
}

bool veaml::Timeline::add(veaml::Video& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Audio& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Image& v) {
  return true;
}