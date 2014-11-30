/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "video.h"

void veaml::Video::set_resolution(openshot::Clip& content) {
  tr1::shared_ptr<openshot::Frame> first = content.GetFrame(1);
  veaml::Resolution real(first->GetWidth(), first->GetHeight());
  
  if (res.width < 0 && res.height < 0) {
    res = real;
  } else {
    content.scale = SCALE_FIT;
    // Falta escalar el vídeo!!
  }
}

void veaml::Video::set_timing(openshot::Clip& content) {
  content.Position(t_start.to_f());
  content.Start(t_from.to_f());

  if (t_to.to_f() > 0)
    content.End(t_to.to_f());
  else if (t_end.to_f() > 0)
    content.End(t_from.to_f() + t_end.to_f() - t_start.to_f());
}

bool veaml::Video::dispatch_add(veaml::Timeline& container) {
  return container.add(*this);
}

openshot::Clip veaml::Video::to_openshot() {
  openshot::Clip content(filename);
  content.Reader()->Open();

  set_timing(content);
  set_resolution(content);

  return content;
}

bool veaml::Video::set(veaml::attr_t attr, std::string value) {
  switch (attr) {
    case WIDTH:
      res.width = std::stoi(value);
      return true;
    case HEIGHT:
      res.height = std::stoi(value);
      return true;
    case FROM:
      t_from = Instant(value);
      return true;
    case TO:
      t_to = Instant(value);
      return true;
    case START:
      t_start = Instant(value);
      return true;
    case END:
      t_start = Instant(value);
      return true;
    case CONTENT:
      filename = value;
      return true;
    default:
      return false;
  }
}