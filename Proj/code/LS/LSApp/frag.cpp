/**
 * @file frag.cpp
 * @author Jose Pires
 * @date 2022-02-03
 *
 * @brief Implementation file for Fragrance class
 *
 * detailed
 */

#include "frag.h"
#include <sstream>

namespace Frag {

/**< Constructors/Destructors */
Fragrance::Fragrance(int id, Intensity intensity, int vol_max, int vol_level) {

  _id = id;
  _vol_max = vol_max;
  _vol_level = vol_level;

  /**< Set Intensity */
  setIntensity(intensity);
}
    Fragrance::~Fragrance(){
    }

void Fragrance::calcDurations(Intensity intensity) {

    int durationOn, durationOff;
    switch(intensity){
    case Intensity::LOW:
        durationOn = 5000;
        durationOff = durationOn * 5;
        break;
    case Intensity::MEDIUM:
        durationOn = 10000;
        durationOff = durationOn;
        break;
    case Intensity::HIGH:
        durationOn = 20000;
        durationOff = durationOn/2;
        break;
    }

    _duration_on = durationOn;
    _duration_off = durationOff;
}

void Fragrance::setIntensity(Intensity intensity) {
  if (intensity < Intensity::LOW || intensity > Intensity::HIGH)
    intensity = Intensity::LOW;

  /**< Assign value */
  _intensity = intensity;

  /**< Calculate On and Off durations */
  calcDurations(intensity);
}

void Fragrance::serialize(std::string &s) {

    s = "";
    std::stringstream ss;

    ss << _id << " "
       << _intensity << " "
       << _vol_max << " "
       << _vol_level << " "
       << _duration_on << " "
       << _duration_off;

    s = ss.str();
}

void Fragrance::deserialize(const std::string &s) {
    std::stringstream ss;
    ss.str( s );

    int intensity;

    ss >> _id;
    ss >> intensity;
    _intensity = (Intensity)intensity;
    ss >> _vol_max;
    ss >> _vol_level;
    ss >> _duration_on;
    ss >> _duration_off;
}

}; // namespace Frag
