/**************************************************************************

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at http://mozilla.org/MPL/2.0/.

Copyright (c) 2014, David Charte fdavidcl@outlook.com

***************************************************************************/

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