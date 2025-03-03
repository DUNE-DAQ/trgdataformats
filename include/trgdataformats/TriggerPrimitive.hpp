/**
 * @file TriggerPrimitive.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_

#include "trgdataformats/Types.hpp"

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace dunedaq::trgdataformats {

/**
 * @brief A single energy deposition on a TPC or PDS channel
 */
struct TriggerPrimitive
{
  uint8_t flag;
  uint16_t time_peak;
  uint16_t time_over_threshold;
  uint16_t adc_peak;
  uint32_t adc_integral;
  uint32_t channel;
  uint64_t time_start;
};

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
