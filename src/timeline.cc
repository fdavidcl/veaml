#include "timeline.h"

veaml::Timeline::Timeline(int width, int height)
  :tl(width, height, openshot::Fraction(24, 1), 24, 2) { }

bool veaml::Timeline::add(veaml::Video& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Audio& v) {
  return true;
}
bool veaml::Timeline::add(veaml::Image& v) {
  return true;
}