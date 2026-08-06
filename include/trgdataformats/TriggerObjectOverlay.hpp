/**
 * @file TriggerObjectOverlay.hpp
 *
 * This header defines the "TriggerActivity" and "TriggerCandidate"
 * structs, which are instantiations of the TriggerObjectOverlay
 * template. Continguous in memory, a TriggerActivity instance is an
 * instance of TriggerActivityData followed by n_inputs
 * TriggerPrimitive instances. Likewise, a TriggerCandidate instance
 * is an instance of TriggerCandidateData followed by n_inputs
 * TriggerActivityData (not to be confused with TriggerActivity)
 * instances.
 *
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY_HPP_

#include "trgdataformats/TriggerActivityData.hpp"
#include "trgdataformats/TriggerCandidateData.hpp"
#include "trgdataformats/TriggerPrimitive.hpp"

#include <algorithm>
#include <span>

namespace dunedaq::trgdataformats {

template<class DataType, class InputType>
struct TriggerObjectOverlay
{
  using data_t = DataType;
  using input_t = InputType;
  data_t data;
  uint64_t n_inputs; // NOLINT(build/unsigned)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpedantic"
  input_t inputs[]; // Non-standard flexible array member, but alternatives are worse
  #pragma GCC diagnostic pop

  void set_inputs(std::span<const input_t> in)
  {
    n_inputs = static_cast<uint64_t>(in.size());
    std::copy(in.begin(), in.end(), inputs);
  }
};

using TriggerActivity = TriggerObjectOverlay<TriggerActivityData, TriggerPrimitive>;

using TriggerCandidate = TriggerObjectOverlay<TriggerCandidateData, TriggerActivityData>;

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY_HPP_
