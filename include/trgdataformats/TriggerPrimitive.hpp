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
  static constexpr uint8_t s_trigger_primitive_version = 2;

  // Metadata.
  uint64_t version : 8 = s_trigger_primitive_version;
  uint64_t flag : 8 = 0;
  uint64_t detid : 8;

  // Physics data.
  uint64_t channel : 24;

  uint64_t time_start : 64;
  uint64_t time_peak : 16;
  uint64_t time_over_threshold : 16;

  uint64_t adc_integral : 32;
  uint64_t adc_peak : 16;
};

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
