/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "audio.h"

void veaml::Audio::set_timing(openshot::Clip& content) {
  content.Position(t_start);
  content.Start(t_from);
  content.End(t_to);
}

bool veaml::Audio::dispatch_add(veaml::Timeline& container) {
  return container.add(*this);
}

openshot::Clip veaml::Audio::to_openshot(int canvas_x, int canvas_y) {
  openshot::Clip content(filename);
  content.Reader()->Open();
  
  if (decoder.length() > 0)
    content.Reader()->info.acodec = decoder;

  content.Layer(0);
  content.volume.AddPoint(1, volume);

  set_timing(content);

  std::cout << "Añadiendo audio " << filename << " decodificado por "
    << content.Reader()->info.acodec << std::endl << " comenzando en "
    << t_start << " desde " << t_from << " hasta " << t_to << std::endl
    << " y con volumen " << volume << std::endl << std::endl;

  return content;
}

bool veaml::Audio::set(veaml::attr_t attr, std::string value) {
  switch (attr) {
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
    case VOLUME:
      volume = std::stod(value) / 100.0;

      if (volume > 1)
        volume = 1;
      if (volume < 0)
        volume = 0;
      
      return true;
    case CODEC:
      decoder = value;
      return true;
    case CONTENT:
      filename = value;
      return true;
    default:
      return false;
  }
}

double veaml::Audio::duration() {
  return t_to - t_from;
}