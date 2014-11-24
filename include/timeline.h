#include <OpenShot.h>

namespace veaml {
  class Video;
  class Audio;
  class Image;

  class Timeline {
  private:
    openshot::Timeline tl;

  public:
    Timeline(int width, int height);
    bool add(veaml::Video& v);
    bool add(veaml::Audio& v);
    bool add(veaml::Image& v);
  };

  class Video {
    
  };
  class Audio {
    
  };
  class Image {
    
  };
}