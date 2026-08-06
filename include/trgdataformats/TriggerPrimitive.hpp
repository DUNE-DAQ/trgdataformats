/**
 * @file TriggerPrimitive.hpp
 *
 * This header defines an overlay struct for trigger primitives, a
 * single energy deposition on a TPC or PDS channel.
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
  static constexpr version_t s_trigger_primitive_version = 2;
  static constexpr std::size_t s_expected_bytes = 24;

  static constexpr uint16_t s_invalid_samples_over_threshold = std::numeric_limits<uint16_t>::max();
  static constexpr uint16_t s_invalid_samples_to_peak = std::numeric_limits<uint16_t>::max();
  static constexpr channel_t s_invalid_tp_channel = 0xFFFFFF; // TP channel limit is at 24 bytes

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

  // Despite this being a struct, the getter and setter for timestamp
  // brings the struct closer into compliance with the standard
  // overlay

  timestamp_t get_timestamp() const
  {
    return time_start;
  }

  void set_timestamp(timestamp_t ts)
  {
    time_start = ts;
  }

  bool operator<(const TriggerPrimitive& other) const {
    return std::tie(time_start, channel) < std::tie(other.time_start, other.channel);
  }
};

// Basic checks that the bits are arranged as we hope they're arranged

// TODO John Freeman (jcfree@fnal.gov), Aug-1-2026

// In the next two months, take these static_asserts and write up a
// concept which encompasses them - something like
// SafeBitLayoutConcept - and figure out the right package to put it
// in, so that both this and the far detector-specific overlay classes
// can use them
  
static_assert(sizeof(TriggerPrimitive) == TriggerPrimitive::s_expected_bytes,
	      "The actual size of the TriggerPrimitive isn't the expected size; the compiler is likely inserting padding");

static_assert(std::endian::native == std::endian::little,
              "The TriggerPrimitive bitfield layout assumes little-endian architecture");

static_assert(std::is_standard_layout_v<TriggerPrimitive>);
static_assert(std::is_trivially_copyable_v<TriggerPrimitive>);

} // namespace dunedaq::trgdataformats

// NOLINTEND(build/unsigned)

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
