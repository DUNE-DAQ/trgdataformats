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
    kCTBFakeTrigger = 13,
    kCTBBeam = 14,
    kCTBBeamHiLoPressChkv = 15,
    kCTBBeamLoPressChkv = 16,
    kCTBBeamHiPressChkv = 17,
    kCTBOffSpillCosmic = 18,
    kCTBCosmic = 19,
    kCTBBeamNoChkv = 20,
    kCTBCosmicJura = 21,
    kCTBCosmicSaleve = 22,
    kNeutronSourceCalib = 23,
    kChannelAdjacency = 24,
    kCIBFakeTrigger =25,
    kCIBLaserTriggerP1 = 26,
    kCIBLaserTriggerP2 = 27,
    kCIBLaserTriggerP3 = 28,
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
    kChannelAdjacency = 12,
  };

  // Update this version number if there are any changes to the in-memory representation of this class!
  static constexpr version_t s_trigger_candidate_version = 2; // NOLINT(build/unsigned)

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
    { TriggerCandidateData::Type::kUnknown,              "kUnknown" },
    { TriggerCandidateData::Type::kTiming,               "kTiming" },
    { TriggerCandidateData::Type::kTPCLowE,              "kTPCLowE" },
    { TriggerCandidateData::Type::kSupernova,            "kSupernova" },
    { TriggerCandidateData::Type::kRandom,               "kRandom" },
    { TriggerCandidateData::Type::kPrescale,             "kPrescale" },
    { TriggerCandidateData::Type::kADCSimpleWindow,      "kADCSimpleWindow" },
    { TriggerCandidateData::Type::kHorizontalMuon,       "kHorizontalMuon" },
    { TriggerCandidateData::Type::kMichelElectron,       "kMichelElectron" },
    { TriggerCandidateData::Type::kPlaneCoincidence,     "kPlaneCoincidence" },
    { TriggerCandidateData::Type::kDBSCAN,               "kDBSCAN" },
    { TriggerCandidateData::Type::kChannelDistance,      "kChannelDistance" },
    { TriggerCandidateData::Type::kBundle,               "kBundle" },
    { TriggerCandidateData::Type::kCTBFakeTrigger,       "kCTBFakeTrigger" },
    { TriggerCandidateData::Type::kCTBBeam,              "kCTBBeam" },
    { TriggerCandidateData::Type::kCTBBeamHiLoPressChkv, "kCTBBeamHiLoPressChkv" },
    { TriggerCandidateData::Type::kCTBBeamLoPressChkv,   "kCTBBeamLoPressChkv" },
    { TriggerCandidateData::Type::kCTBBeamHiPressChkv,   "kCTBBeamHiPressChkv" },
    { TriggerCandidateData::Type::kCTBOffSpillCosmic,    "kCTBOffSpillCosmic" },
    { TriggerCandidateData::Type::kCTBCosmic,            "kCTBCosmic" },
    { TriggerCandidateData::Type::kCTBBeamNoChkv,        "kCTBBeamNoChkv" },
    { TriggerCandidateData::Type::kCTBCosmicJura,        "kCTBCosmicJura" },
    { TriggerCandidateData::Type::kCTBCosmicSaleve,      "kCTBCosmicSaleve" },
    { TriggerCandidateData::Type::kNeutronSourceCalib,   "kNeutronSourceCalib" },
    { TriggerCandidateData::Type::kChannelAdjacency,     "kChannelAdjacency" },
    { TriggerCandidateData::Type::kCIBFakeTrigger,       "kCIBFakeTrigger" },
    { TriggerCandidateData::Type::kCIBLaserTriggerP1,    "kCIBLaserTriggerP1" },
    { TriggerCandidateData::Type::kCIBLaserTriggerP2,    "kCIBLaserTriggerP2" },
    { TriggerCandidateData::Type::kCIBLaserTriggerP3,    "kCIBLaserTriggerP3" },
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
