/*
 * @file TriggerPrimitivePDS.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2024.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVEPDS_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVEPDS_HPP_

#include "trgdataformats/Types.hpp"

//#include "fddetdataformats/DAPHNEFrame.hpp"

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace dunedaq::trgdataformats {


/**
 * @brief A single energy deposition on a PDS channel
 */
struct TriggerPrimitivePDS
{	
  /**
   * @brief The type of a TriggerPrimitive
   */
  enum class Type
  {
    kUnknown = 0,
    kTPC = 1,
    kPDS = 2,
  };

  /**
   * @brief The algorithm used to form a TriggerPrimitive
   */
  enum class Algorithm
  {
    kUnknown = 0,
    kSimpleThreshold = 1,
    kAbsRunningSum = 2,
    kRunningSum = 3
  };

  /**
   * @brief A bitmask of flags from PrimitiveFlagsBits OR'ed together
   *
   * (a std::bitset<> would be nicer, but we don't have code to serialize it yet)
   */
  using Flags = uint16_t;

  // Update this version number if there are any changes to the in-memory representation of this class!
  static constexpr version_t s_trigger_primitive_version = 1; // NOLINT(build/unsigned)

  version_t version = s_trigger_primitive_version; // NOLINT(build/unsigned)
  timestamp_t time_start = INVALID_TIMESTAMP;
  timestamp_t time_peak = INVALID_TIMESTAMP;
  timestamp_t time_over_threshold = INVALID_TIMESTAMP;
  channel_t channel = INVALID_CHANNEL;
  uint32_t adc_integral = { 0 }; // NOLINT(build/unsigned)
  uint16_t adc_peak = { 0 };     // NOLINT(build/unsigned)
  detid_t detid = INVALID_DETID;
  Type type = Type::kUnknown;
  Algorithm algorithm = Algorithm::kUnknown;

  uint8_t num_peak_ub=0; // # of peaks under the baseline
  uint8_t num_peak_ob=0; // # of peaks under the baseline
  
  TriggerPrimitivePDS(){
    type = Type::kPDS;
  }
  void set_channel(channel_t ch){channel=ch;}
  void set_num_peak_ub(uint8_t par) {num_peak_ub=par;}
  void set_num_peak_ob(uint8_t par) {num_peak_ob=par;}
  void set_adc_integral(uint32_t p){adc_integral=p;}
  void set_adc_peak(uint16_t p){adc_peak=p;}
  void set_time_peak(timestamp_t par){time_peak=par;}
  void set_time_start(timestamp_t par){time_start=par;}
  void set_time_over_threshold(timestamp_t par) {time_over_threshold=par;}

  channel_t get_channel(){return channel;}
  uint8_t get_num_peak_ub() {return num_peak_ub;}
  uint8_t get_num_peak_ob() {return num_peak_ob;}
  uint32_t get_adc_integral(){return adc_integral;}
  uint16_t get_adc_peak(){return adc_peak;}
  timestamp_t get_time_peak(){return time_peak;}
  timestamp_t get_time_start(){return time_start;}
  timestamp_t get_time_over_threshold() {return time_over_threshold;}
  
  void Print()
  {
    std::cout << "TP-PDS - ch: " << get_channel()
     << ", adc_integral: " << get_adc_integral()
     << ", adc_peak: " << get_adc_peak()
     << ", time_peak: " << get_time_peak()
     << ", time_start: " << get_time_start()
     << ", time_over_threshold: " << get_time_over_threshold()
     << ", num_peak_ub: " << get_num_peak_ub()
     << ", num_peak_oo: " << get_num_peak_ob() << std::endl;
  }
};



} // namespace dunedaq::trgdataformats 

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE_HPP_
