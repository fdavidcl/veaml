/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "mark.h"
#include "clip.h"
#include "timeline.h"

veaml::Timeline::Timeline(int width, int height)
  :res(width, height), framerate(25, 1) { }

bool veaml::Timeline::set(attr_t attr, std::string value) {
  switch (attr) {
    case WIDTH:
      res.width = std::stoi(value);
      return true;
    case HEIGHT:
      res.height = std::stoi(value);
      return true;
    case ACODEC:
      audiocodec = value;
      return true;
    case VCODEC:
      videocodec = value;
      return true;
    case SRATE:
      audiorate = std::stoi(value);
      return true;
    case FPS:
      framerate = openshot::Fraction(std::stoi(value), 1);
      return true;
    case CONTENT:
      filename = value;
      return true;
    default:
      return false;
  }
}

bool veaml::Timeline::add(veaml::Clip& v) {
  tl.push_back(&v);
  return true;
}

double veaml::Timeline::adjust_timing() {
  Instant duration = 0;

  for (std::vector<veaml::Clip*>::iterator i = tl.begin(); i != tl.end(); ++i) {
    // from, to -> relativos al clip.
    // start, end -> relativos al timeline.

    // Ajustar los comienzos de cada vídeo si no están puestos manualmente
    if ((*i)->start() < 0)
      (*i)->start() = duration;

    // Calcular el final del vídeo
    if ((*i)->to() < 0) {
      if ((*i)->end() < 0) {
        (*i)->to() = (*i)->to_openshot().End();
        (*i)->end() = (*i)->start() + (*i)->duration();
      } else {
        (*i)->to() = (*i)->end() - (*i)->start();
      }
    } else {
      (*i)->end() = (*i)->start() + (*i)->duration();
    }

    if ((*i)->end().to_f() >= duration.to_f())
      duration = (*i)->end();
  }

  return duration;
}

bool veaml::Timeline::output() {
  double duration = adjust_timing();

  try {
    // Comprobación de parámetros!!

    openshot::Timeline out(res.width, res.height, framerate, audiorate, channels);
    std::cerr << "Procesado vídeo. Duración: " << duration << std::endl;

    for (std::vector<veaml::Clip*>::iterator i = tl.begin(); i != tl.end(); ++i) {
      std::cerr << "Añadiendo vídeo " << (*i)->file() << std::endl; 
      openshot::Clip* vid = new openshot::Clip((*i)->to_openshot());

      out.AddClip(vid);
    }

    out.Open();

    openshot::FFmpegWriter writer(filename);

    writer.SetAudioOptions(
      true,                    // has audio?
      audiocodec,              // string for audio codec
      audiorate,               // audio sample rate
      channels,                // channels (2 for stereo)
      512000                   // bitrate
    );
    
    writer.SetVideoOptions(
      true,                    // has video? 
      videocodec,              // String for video codec
      framerate,               // fps (25/1)
      res.width, res.height,   // resolution
      openshot::Fraction(1,1), // pixel ratio
      false, false,            // interlaced, top_field_first
      2000000                  // bitrate
    );

    writer.PrepareStreams();
    writer.WriteHeader();

    // Escribir todos los frames desde el Timeline
    //tr1::shared_ptr<openshot::Frame> fr = out.GetFrame(130);

    writer.WriteFrame(&out, 1, duration * framerate.ToDouble());
    
    writer.WriteTrailer();
    writer.Close();

    out.Close();

    return true;
  } catch(BaseException ex) {
    std::cout << "Error al procesar el vídeo: " << ex.what() << std::endl;
    return false;
  }
}