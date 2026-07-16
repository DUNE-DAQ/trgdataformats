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

// NOLINTBEGIN(build/unsigned)

namespace dunedaq::trgdataformats {

/**
 * @brief A single energy deposition on a TPC or PDS channel
 */
struct TriggerPrimitive
{
  static constexpr uint8_t s_trigger_primitive_version = 2;
  static constexpr uint16_t s_invalid_samples_over_threshold = std::numeric_limits<uint16_t>::max();
  static constexpr uint16_t s_invalid_samples_to_peak = std::numeric_limits<uint16_t>::max();
  static constexpr channel_t s_invalid_tp_channel = 0xFFFFFF; // TP channel limit is at 24 b
  
  // Metadata.
  uint64_t version : 8;
  uint64_t flag : 8;
  uint64_t detid : 8;

  // Physics data.
  uint64_t channel : 24;

  uint64_t samples_over_threshold : 16;
  uint64_t time_start : 64;
  uint64_t samples_to_peak : 16;

  uint64_t adc_integral : 32;
  uint64_t adc_peak : 16;

  TriggerPrimitive()
    : version(s_trigger_primitive_version)
    , flag(0)
    , detid(TypeDefaults::s_invalid_detid)
    , channel(s_invalid_tp_channel)
    , samples_over_threshold(s_invalid_samples_over_threshold)
    , time_start(TypeDefaults::s_invalid_timestamp)
    , samples_to_peak(s_invalid_samples_to_peak)
    , adc_integral(0)
    , adc_peak(0)
  {}
};

} // namespace dunedaq::trgdataformats

// NOLINTEND(build/unsigned)

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
