#ifndef _VEAML_CLIP
#define _VEAML_CLIP

#include "instant.h"
#include <OpenShot.h>
#include <string>

namespace veaml {
  class Clip {
  protected:
    std::string filename;
    veaml::Instant t_from;
    veaml::Instant t_to;

  public:
    Clip(std::string file, Instant f, Instant t) 
      :filename(file), t_from(f), t_to(t) {}
    Clip(std::string file) 
      :Clip(file, 0, 0) {}

    const veaml::Instant& from() const { return t_from; }
    veaml::Instant& from() { return t_from; }
    
    const veaml::Instant& to() const { return t_to; }
    veaml::Instant& to() { return t_to; }

    const std::string& file() const { return filename; }
    std::string& file() { return filename; }
    
    virtual openshot::Clip to_openshot() = 0;
  };

  struct Resolution {
    unsigned int width;
    unsigned int height;

    Resolution() :width(0), height(0) {}
    Resolution(int x, int y) :width(x), height(y) {}
  };
}

#endif