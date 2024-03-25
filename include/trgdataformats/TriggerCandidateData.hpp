/**
 * @file TriggerCandidate.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_

#include "trgdataformats/Types.hpp"

#include <cstdint>
#include <map>
#include <string>

namespace dunedaq::trgdataformats {

struct TriggerCandidateData
{
  enum class Type
  {
    kUnknown = 0,
    kTiming = 1,
    kTPCLowE = 2,
    kSupernova = 3,
    kRandom = 4,
    kPrescale = 5,
    kADCSimpleWindow = 6,
    kHorizontalMuon = 7,
    kMichelElectron = 8,
    kPlaneCoincidence = 9,
    kDBSCAN = 10,
    kChannelDistance = 11,
    kBundle = 12,
    kTrackFinding = 13,
  };

  enum class Algorithm
  {
    kUnknown = 0,
    kSupernova = 1,
    kHSIEventToTriggerCandidate = 2,
    kPrescale = 3,
    kADCSimpleWindow = 4,
    kHorizontalMuon = 5,
    kMichelElectron = 6, 
    kPlaneCoincidence = 7,    
    kCustom = 8, 
    kDBSCAN = 9,
    kChannelDistance = 10,
    kBundle = 11,
    kTrackFinding = 12,
  };

  // Update this version number if there are any changes to the in-memory representation of this class!
  static constexpr version_t s_trigger_candidate_version = 1; // NOLINT(build/unsigned)

  version_t version = s_trigger_candidate_version;       // NOLINT(build/unsigned)
  timestamp_t time_start = INVALID_TIMESTAMP;
  timestamp_t time_end = INVALID_TIMESTAMP;
  timestamp_t time_candidate = INVALID_TIMESTAMP;
  // TODO P. Rodrigues 2021-01-06: This was originally a
  // std::vector<detid_t> but that messes up the overlay scheme, so
  // I've changed it for now to be just a detid_t. Need to work out
  // what to do longer term
  detid_t detid; // NOLINT(build/unsigned)
  Type type = Type::kUnknown;
  Algorithm algorithm = Algorithm::kUnknown; // NOLINT(build/unsigned)
};

// This map needs to be updated for each new TC type, as this is used when configuring Trigger Bitwords, affecting trigger logic in trigger::MLT
inline std::map<TriggerCandidateData::Type, std::string>
get_trigger_candidate_type_names()
{
  return {
    { TriggerCandidateData::Type::kUnknown, "kUnknown" },
    { TriggerCandidateData::Type::kTiming, "kTiming" },
    { TriggerCandidateData::Type::kTPCLowE, "kTPCLowE" },
    { TriggerCandidateData::Type::kSupernova, "kSupernova" },
    { TriggerCandidateData::Type::kRandom, "kRandom" },
    { TriggerCandidateData::Type::kPrescale, "kPrescale" },
    { TriggerCandidateData::Type::kADCSimpleWindow, "kADCSimpleWindow" },
    { TriggerCandidateData::Type::kHorizontalMuon, "kHorizontalMuon" },
    { TriggerCandidateData::Type::kMichelElectron, "kMichelElectron" },
    { TriggerCandidateData::Type::kPlaneCoincidence, "kPlaneCoincidence" },
    { TriggerCandidateData::Type::kBundle, "kBundle" },
    { TriggerCandidateData::Type::kChannelDistance, "kChannelDistance" },
    { TriggerCandidateData::Type::kDBSCAN, "kDBSCAN" },
    { TriggerCandidateData::Type::kTrackFinding, "kTrackFinding" },
  };
}

inline int
string_to_fragment_type_value(const std::string& name)
{
  for (auto& it : get_trigger_candidate_type_names()) {
    if (it.second == name)
      return static_cast<int>(it.first);
  }
  return static_cast<int>(TriggerCandidateData::Type::kUnknown);
}

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_
