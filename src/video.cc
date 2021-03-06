/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "video.h"

int veaml::Video::layers = 1;

void veaml::Video::set_resolution(openshot::Clip& content, int canvas_x, int canvas_y) {
  tr1::shared_ptr<openshot::Frame> first = content.GetFrame(1);
  veaml::Resolution real(first->GetWidth(), first->GetHeight());
  
  content.scale = SCALE_FIT;
  
  if (res.width < 0 && res.height < 0) {
    res = real;
  } else {
    if (res.width < 0) {
      res.width = real.width / (double)real.height * res.height;
    } else if (res.height < 0) {
      res.height = real.height / (double)real.width * res.width;
    }

    content.scale_x.AddPoint(1, res.width / (double)canvas_x);
    content.scale_y.AddPoint(1, res.height / (double)canvas_y);
  }
}

void veaml::Video::set_position(openshot::Clip& content, int canvas_x, int canvas_y) {
  content.gravity = GRAVITY_TOP_LEFT;
  content.crop_gravity = GRAVITY_TOP_LEFT;
  content.crop_width.AddPoint(1, 1);
  content.crop_height.AddPoint(1, 1);
  content.location_x.AddPoint(1, pos.width / (double)canvas_x);
  content.location_y.AddPoint(1, pos.height / (double)canvas_y);
}

void veaml::Video::set_timing(openshot::Clip& content) {
  content.Position(t_start);
  content.Start(t_from);
  content.End(t_to);
}

bool veaml::Video::dispatch_add(veaml::Timeline& container) {
  return container.add(*this);
}

openshot::Clip veaml::Video::to_openshot(int canvas_x, int canvas_y) {
  openshot::Clip content(filename);
  content.Reader()->Open();
  content.Layer(layers++);
  content.volume.AddPoint(1, volume);

  if (decoder.length() > 0)
    content.Reader()->info.vcodec = decoder;

  set_resolution(content, canvas_x, canvas_y);
  set_position(content, canvas_x, canvas_y);
  set_timing(content);
  
  std::cout << "Añadiendo vídeo " << filename << " decodificado por "
    << content.Reader()->info.vcodec << std::endl << " comenzando en "
    << t_start << " desde " << t_from << " hasta " << t_to << std::endl 
    << " a resolución " << res.width << "x" << res.height
    << " y con volumen " << volume << std::endl << std::endl;

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
    case TOP:
      pos.height = std::stoi(value);
      return true;
    case LEFT:
      pos.width = std::stoi(value);
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

double veaml::Video::duration() {
  return t_to - t_from;
}