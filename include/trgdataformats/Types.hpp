/**
 * @file Types.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TYPES_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TYPES_HPP_

#include <cstdint>
#include <limits>

namespace dunedaq::trgdataformats {

// A data timestamp in timing system clock ticks (50 MHz for
// ProtoDUNE-I, 62.5 MHz for ProtoDUNE-II and DUNE FD). If/when we
// depend on daqdataformats, we can get these from there
using timestamp_t = uint64_t; // NOLINT
using timestamp_diff_t = int64_t;

// A logical region of the detector from which DS objects may be
// formed, eg an APA or a module
//
// TODO P. Rodrigues 2021-06-01: it would be nice to have this be just
// daqdataformats::GeoID, if/when we can depend on the daqdataformats
// package
using detid_t = uint8_t;

// A trigger number
// TODO P. Rodrigues 2021-06-14: it would be nice to have this be just
// daqdataformats::trigger_number_t, if/when we can depend on the daqdataformats
// package
using trigger_number_t = uint64_t;

// A channel number
using channel_t = uint32_t;
using channel_diff_t = int32_t;

  // A version number of an object
using version_t = uint8_t;

//constexpr version_t INVALID_VERSION = std::numeric_limits<version_t>::max();

struct TypeDefaults
{
  static constexpr timestamp_t s_invalid_timestamp { std::numeric_limits<timestamp_t>::max() };
  static constexpr detid_t s_invalid_detid { std::numeric_limits<detid_t>::max() };
  static constexpr trigger_number_t s_invalid_trigger_number { std::numeric_limits<trigger_number_t>::max() };
};

// A detid representing a request to read out the whole detector
  constexpr detid_t g_whole_detector {std::numeric_limits<detid_t>::max() - 1};

  
} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TYPES_HPP_
