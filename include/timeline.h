#ifndef _VEAML_TIMELINE
#define _VEAML_TIMELINE

#include "video.h"
#include <vector>
#include <OpenShot.h>

namespace veaml {
  class Audio;
  class Image;

  class Timeline {
  private:
    std::vector<Clip*> v;
    Resolution res;

  public:
    Timeline(int width, int height);
    bool add(veaml::Video& v);
    bool add(veaml::Audio& v);
    bool add(veaml::Image& v);

    openshot::Timeline to_openshot();
  };

  class Audio {
    
  };
  class Image {
    
  };
}

#endif