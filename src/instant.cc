/* This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/.

   Copyright (c) 2014, David Charte fdavidcl@outlook.com               */

#include "instant.h"

veaml::Instant::Instant(double secs) {
  n_sec = secs / 1;
  n_cent = ((secs-n_sec)*100)/1;
  n_min = n_sec / 60;
  n_sec -= n_min * 60;
}

int veaml::Instant::sto_i(std::string value) {
  if (value.length() == 0)
    return 0;
  else
    return std::stoi(value);
}

veaml::Instant::Instant(std::string value) {
  size_t pos = value.find(DELIM);

  if (pos != std::string::npos) {
    std::string left = value.substr(0, pos);
    std::string right = value.substr(pos + 1, std::string::npos);

    pos = right.find(DELIM);

    if (pos != std::string::npos) {
      std::string middle = right.substr(0, pos);
      right = right.substr(pos + 1, std::string::npos);

      n_min = sto_i(left);
      n_sec = sto_i(middle);
      n_cent = sto_i(right);
    } else {
      n_min = sto_i(left);
      n_sec = sto_i(right);
      n_cent = 0;
    }
  } else {
    n_min = 0;
    n_sec = sto_i(value);
    n_cent = 0;
  }
}

double veaml::Instant::to_f() {
  return n_min * 60 + n_sec + (n_cent / 100.0);
}