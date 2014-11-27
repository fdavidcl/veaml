#include "timeline.h"

veaml::Timeline::Timeline(int width, int height)
  :res(width, height) { }

bool veaml::Timeline::add(veaml::Video& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Audio& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Image& v) {
  return true;
}