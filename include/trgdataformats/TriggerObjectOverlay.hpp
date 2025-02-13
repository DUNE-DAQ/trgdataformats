/**
 * @file TriggerObjectOverlay.hpp
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
#include "trgdataformats/TriggerPrimitivePDS.hpp"

namespace dunedaq::trgdataformats {

template<class DataType, class InputType>
struct TriggerObjectOverlay
{
  using data_t = DataType;
  using input_t = InputType;
  data_t data;
  uint64_t n_inputs;
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpedantic"
  input_t inputs[]; // Non-standard flexible array member, but alternatives are worse
  #pragma GCC diagnostic pop
};

using TriggerActivity = TriggerObjectOverlay<TriggerActivityData, TriggerPrimitive>;
using TriggerActivityPDS = TriggerObjectOverlay<TriggerActivityData, TriggerPrimitivePDS>;
using TriggerCandidate = TriggerObjectOverlay<TriggerCandidateData, TriggerActivityData>;
using TriggerCandidatePDS = TriggerObjectOverlay<TriggerCandidateData, TriggerActivityData>;

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY_HPP_
