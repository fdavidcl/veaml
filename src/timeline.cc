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
  //try {
    // Comprobación de parámetros!!
    openshot::Timeline out(res.width, res.height, framerate, audiorate, channels);

    for (std::vector<veaml::Clip*>::iterator i = tl.begin(); i != tl.end(); ++i) {
      openshot::Clip* vid = new openshot::Clip((*i)->to_openshot());

      std::cerr << "Añadiendo vídeo " << (*i)->file() << std::endl; 
      
      vid->Reader()->Open();
      out.AddClip(vid);
    }

    out.Open();

    openshot::FFmpegWriter writer(filename);

    // Set options
    writer.SetAudioOptions(true, audiocodec, audiorate, channels, 128000); // Sample Rate: 44100, Channels: 2, Bitrate: 128000
    writer.SetVideoOptions(true, videocodec, framerate, res.width, res.height, openshot::Fraction(1,1), false, false, 300000); // FPS: 24, Size: 720x480, Pixel Ratio: 1/1, Bitrate: 300000

    // Prepare Streams
    writer.PrepareStreams();
    // Write header
    writer.WriteHeader();

    // Write all frames from the reader
    writer.WriteFrame(&out, 1, out.info.video_length);
    // Write Footer
    writer.WriteTrailer();
    // Close the reader & writer
    writer.Close();

    return true;
  /*} catch(BaseException ex) {
    return false;
  }*/
}

/*
bool veaml::Timeline::add(veaml::Audio& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Image& v) {
  return true;
}*/