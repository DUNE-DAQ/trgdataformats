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
  uint64_t version : 8 = 2, flag : 8, detid : 8; // 24 out of 64 bits.

  uint64_t channel : 24, time_peak : 16;  // Locations. Fills the remaining bits.
  uint64_t time_start : 64;
  uint64_t time_over_threshold : 16, adc_integral : 32, adc_peak : 16;
};

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
