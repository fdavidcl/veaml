/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "mark.h"
#include "clip.h"
#include "timeline.h"

veaml::Timeline::Timeline(int width, int height)
  :res(width, height) { }

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
      framerate = std::stoi(value);
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

  for (auto& cl : tl) {
    // from, to -> relativos al clip.
    // start, end -> relativos al timeline.

    // Ajustar los comienzos de cada vídeo si no están puestos manualmente
    if (cl->start() < 0)
      cl->start() = duration;

    // Calcular el final del vídeo
    if (cl->to() < 0) {
      if (cl->end() < 0) {
        cl->to() = cl->to_openshot().End();
        cl->end() = cl->start() + cl->duration();
      } else {
        cl->to() = cl->end() - cl->start();
      }
    } else {
      cl->end() = cl->start() + cl->duration();
    }

    if (cl->end().to_f() >= duration.to_f())
      duration = cl->end();
  }

  return duration;
}

bool veaml::Timeline::output() {
  double duration = adjust_timing();

  try {
    openshot::Timeline out(
      res.width, 
      res.height, 
      openshot::Fraction(framerate, 1), 
      audiorate, 
      channels
    );

    std::cout << "Construyendo Timeline. Duración total: " << duration
      << std::endl << " Tendremos un framerate de " << framerate << "fps y sample rate "
      << audiorate << "." << std::endl << std::endl;

    for (auto& cl : tl) {
      openshot::Clip* vid = new openshot::Clip(cl->to_openshot(res.width, res.height));
      out.AddClip(vid);
    }

    out.Open();

    openshot::FFmpegWriter writer(filename);

    writer.OutputStreamInfo();

    writer.SetAudioOptions(
      true,                    // has audio?
      audiocodec,              // string for audio codec
      audiorate,               // audio sample rate
      channels,                // channels (2 for stereo)
      openshot::ChannelLayout(),
      aubitrate                // bitrate
    );

    // writer.ResampleAudio(44100, 2);
    
    writer.SetVideoOptions(
      true,                    // has video? 
      videocodec,              // String for video codec
      openshot::Fraction(framerate, 1),      // fps
      res.width, res.height,   // resolution
      openshot::Fraction(1,1), // pixel ratio
      false, false,            // interlaced, top_field_first
      vidbitrate               // bitrate
    );

    writer.PrepareStreams();
    writer.WriteHeader();

    // Escribir todos los frames desde el Timeline
    writer.WriteFrame(&out, 1, duration * framerate);
    
    writer.WriteTrailer();
    writer.Close();

    out.Close();

    return true;
  } catch(OutOfBoundsFrame& ex) {
    std::cerr << "Error: Marco fuera de límites (límite " << ex.MaxFrames 
      << ", se solicitó " << ex.FrameRequested << ")." << std::endl;
    return false;
  } catch(InvalidCodec& ex) {
    std::cerr << "Error al procesar el vídeo: " << ex.what() << " (archivo " 
      << ex.file_path << ")." << std::endl;
    return false;
  } catch(BaseException& ex) {
    std::cerr << "Error al procesar el vídeo: " << ex.what() << std::endl;
    return false;
  }
}
