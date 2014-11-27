/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "video.h"

void veaml::Video::set_resolution(openshot::Clip& content, int width, int height) {
  if (width < 0 && height < 0) {
    content.Reader()->Open();

    tr1::shared_ptr<openshot::Frame> first = content.GetFrame(1);
    res = veaml::Resolution(first->GetWidth(), first->GetHeight());
  } else {

  }
}

void veaml::Video::set_timing(openshot::Clip& content) {
  content.Position(0.0);
  content.Start(t_from.to_f());
  content.End(t_to.to_f());
}

openshot::Clip veaml::Video::to_openshot() {
  openshot::Clip content(new FFmpegReader(filename));


  set_timing(content);
  set_resolution(content, res.width, res.height);

  return content;
}

bool veaml::Video::set(veaml::attr_t attr, std::string value) {
  return true;
}