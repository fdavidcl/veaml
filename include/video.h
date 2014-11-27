#ifndef _VEAML_VIDEO
#define _VEAML_VIDEO

#include "clip.h"
#include <string>

namespace veaml {
  class Video : public Clip {
  private:
    veaml::Resolution real_r;
    veaml::Resolution res;

    void set_timing(openshot::Clip& content);
    void set_resolution(openshot::Clip& content, int width = -1, int height = -1);
  public:
    Video(std::string file) :Clip(file) {}
    Video(std::string file, veaml::Instant f, veaml::Instant t) :Clip(file, f, t) {}
    //Video(std::string file, veaml::Resolution r);
    //Video(std::string file, veaml::Instant f, veaml::Instant t, veaml::Resolution r);

    openshot::Clip to_openshot();
  };
}

#endif