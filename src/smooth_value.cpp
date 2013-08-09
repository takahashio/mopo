/* Copyright 2013 Little IO
 *
 * laf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * laf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with laf.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "smooth_value.h"

#include <math.h>

#define SMOOTH_CUTOFF 0.5

namespace laf {

  SmoothValue::SmoothValue(laf_sample value) :
      Value(value), target_value_(value) {
    setSampleRate(DEFAULT_SAMPLE_RATE);
  }

  void SmoothValue::setSampleRate(int sample_rate) {
    decay_ = 1 - exp(-2.0 * PI * SMOOTH_CUTOFF / sample_rate);
  }

  void SmoothValue::process() {
    for (int i = 0; i < BUFFER_SIZE; ++i)
      outputs_[0]->buffer[i] = tick();
  }

  inline laf_sample SmoothValue::tick() {
    value_ = INTERPOLATE(value_, target_value_, decay_);
    return value_;
  }
} // namespace laf