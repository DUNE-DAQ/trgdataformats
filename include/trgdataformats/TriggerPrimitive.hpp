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
#include <limits>
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
  uint64_t detid : 8 = INVALID_DETID;

  // Physics data.
  uint64_t channel : 24 = (1 << 24) - 1;  // Requires an awkward limit definition.

  uint64_t samples_over_threshold : 16 = std::numeric_limits<uint16_t>::max();
  uint64_t time_start : 64 = INVALID_TIMESTAMP;
  uint64_t samples_to_peak : 16 = std::numeric_limits<uint16_t>::max();

  uint64_t adc_integral : 32 = std::numeric_limits<uint32_t>::max();
  uint64_t adc_peak : 16 = std::numeric_limits<uint16_t>::max();
};

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
