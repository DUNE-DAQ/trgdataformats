/**
 * @file Types.hpp
 *
 * This header defines the types used in this package for various
 * kinds of data (timestamps, channels, etc.). It also contains some
 * predefined constants representing invalid values as well as a "read
 * out the whole detector" value.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TYPES_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TYPES_HPP_

#include <cstdint>
#include <limits>

// NOLINTBEGIN(build/unsigned)

namespace dunedaq::trgdataformats {

// TODO John Freeman (jcfree@fnal.gov), Jul-16-2026

// In the next month, determine if we can get enough buy in to add
// dependence on the relevant headers from daqdataformats, which will
// address Phil Rodrigues's concerns from five years ago. There's some
// hope for this to the extent Tom Junk emailed me in the spring
// saying this wouldn't be a problem.


  
// timestamp_t represents a data timestamp in timing system clock
// ticks (50 MHz for ProtoDUNE-I, 62.5 MHz for ProtoDUNE-II and DUNE
// FD). If/when we depend on daqdataformats, we can get these from
// there
using timestamp_t = uint64_t;
using timestamp_diff_t = int64_t;

// A logical region of the detector from which DS objects may be
// formed, eg an APA or a module
//
// TODO P. Rodrigues 2021-06-01: it would be nice to have this be just
// daqdataformats::GeoID, if/when we can depend on the daqdataformats
// package
  
using detid_t = uint8_t;

// TODO P. Rodrigues 2021-06-14: it would be nice to have this be just
// daqdataformats::trigger_number_t, if/when we can depend on the daqdataformats
// package
using trigger_number_t = uint64_t;


using channel_t = uint32_t;
using channel_diff_t = int32_t;

using version_t = uint8_t;

struct TypeDefaults
{
  static constexpr timestamp_t s_invalid_timestamp { std::numeric_limits<timestamp_t>::max() };
  static constexpr detid_t s_invalid_detid { std::numeric_limits<detid_t>::max() };
  static constexpr trigger_number_t s_invalid_trigger_number { std::numeric_limits<trigger_number_t>::max() };
};

// A detid representing a request to read out the whole detector
  constexpr detid_t g_whole_detector {std::numeric_limits<detid_t>::max() - 1};

  
} // namespace dunedaq::trgdataformats

static_assert(dunedaq::trgdataformats::g_whole_detector != dunedaq::trgdataformats::TypeDefaults::s_invalid_detid);

// NOLINTEND(build/unsigned)

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TYPES_HPP_
