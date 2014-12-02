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

bool veaml::Timeline::output() {
  try {
    // Comprobación de parámetros!!
    int duration = 0;

    openshot::Timeline out(res.width, res.height, framerate, audiorate, channels);

    for (std::vector<veaml::Clip*>::iterator i = tl.begin(); i != tl.end(); ++i) {
      openshot::Clip* vid = new openshot::Clip((*i)->to_openshot());

      int this_duration = (*i)->start().to_f() + (*i)->duration();
      if (this_duration > duration) duration = this_duration;

      std::cerr << "Añadiendo vídeo " << (*i)->file() << std::endl; 
      
      vid->Reader()->Open();
      out.AddClip(vid);
    }

    out.Open();

    openshot::FFmpegWriter writer(filename);

    writer.SetAudioOptions(
      true,                    // has audio?
      audiocodec,              // string for audio codec
      audiorate,               // audio sample rate
      channels,                // channels (2 for stereo)
      128000                   // bitrate
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