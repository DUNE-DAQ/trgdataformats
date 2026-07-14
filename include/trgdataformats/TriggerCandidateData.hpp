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
    kCTBBeamChkvHL = 15,
    kCTBCustomD = 16,
    kCTBCustomE = 17,
    kCTBCustomF = 18,
    kCTBCustomG = 19,
    kCTBBeamChkvHLx = 20,
    kCTBBeamChkvHxL = 21,
    kCTBBeamChkvHxLx = 22,
    kNeutronSourceCalib = 23,
    kChannelAdjacency = 24,
    kCIBFakeTrigger = 25,
    kCIBLaserTriggerP1 = 26,
    kCIBLaserTriggerP2 = 27,
    kCIBLaserTriggerP3 = 28,
    kCTBOffSpillSnapshot = 29,
    kCTBOffSpillCosmicJura = 30,
    kCTBOffSpillCRTCosmic= 31,
    kCTBBeamSpillStart = 32,
    kCTBBeamSpillSnapshot = 33,
    kCTBCustomC = 34,
    kCTBCustomPulseTrain = 35,
    kDTSPulser = 36,
    kDTSCosmic = 37,
    kSSPLEDCalibration = 38,
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
  static constexpr version_t s_trigger_candidate_version = 3; // NOLINT(build/unsigned)

  version_t version = s_trigger_candidate_version; // NOLINT(build/unsigned)
  timestamp_t time_start = TypeDefaults::s_invalid_timestamp;
  timestamp_t time_end = TypeDefaults::s_invalid_timestamp;
  timestamp_t time_candidate = TypeDefaults::s_invalid_timestamp;
  // TODO P. Rodrigues 2021-01-06: This was originally a
  // std::vector<detid_t> but that messes up the overlay scheme, so
  // I've changed it for now to be just a detid_t. Need to work out
  // what to do longer term
  detid_t detid; // NOLINT(build/unsigned)
  Type type = Type::kUnknown;
  Algorithm algorithm = Algorithm::kUnknown; // NOLINT(build/unsigned)
};

// This map needs to be updated for each new TC type, as this is used when configuring Trigger Bitwords, affecting
// trigger logic in trigger::MLT
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
    { TriggerCandidateData::Type::kDBSCAN, "kDBSCAN" },
    { TriggerCandidateData::Type::kChannelDistance, "kChannelDistance" },
    { TriggerCandidateData::Type::kBundle, "kBundle" },
    { TriggerCandidateData::Type::kCTBFakeTrigger, "kCTBFakeTrigger" },
    { TriggerCandidateData::Type::kCTBBeam, "kCTBBeam" },
    { TriggerCandidateData::Type::kCTBBeamChkvHL, "kCTBBeamChkvHL" },
    { TriggerCandidateData::Type::kCTBCustomD, "kCTBCustomD" },
    { TriggerCandidateData::Type::kCTBCustomE, "kCTBCustomE" },
    { TriggerCandidateData::Type::kCTBCustomF, "kCTBCustomF" },
    { TriggerCandidateData::Type::kCTBCustomG, "kCTBCustomG" },
    { TriggerCandidateData::Type::kCTBBeamChkvHLx, "kCTBBeamChkvHLx" },
    { TriggerCandidateData::Type::kCTBBeamChkvHxL, "kCTBBeamChkvHxL" },
    { TriggerCandidateData::Type::kCTBBeamChkvHxLx, "kCTBBeamChkvHxLx" },
    { TriggerCandidateData::Type::kNeutronSourceCalib, "kNeutronSourceCalib" },
    { TriggerCandidateData::Type::kChannelAdjacency, "kChannelAdjacency" },
    { TriggerCandidateData::Type::kCIBFakeTrigger, "kCIBFakeTrigger" },
    { TriggerCandidateData::Type::kCIBLaserTriggerP1, "kCIBLaserTriggerP1" },
    { TriggerCandidateData::Type::kCIBLaserTriggerP2, "kCIBLaserTriggerP2" },
    { TriggerCandidateData::Type::kCIBLaserTriggerP3, "kCIBLaserTriggerP3" },
    { TriggerCandidateData::Type::kCTBOffSpillSnapshot, "kCTBOffSpillSnapshot" },
    { TriggerCandidateData::Type::kCTBOffSpillCosmicJura, "kCTBOffSpillCosmicJura" },
    { TriggerCandidateData::Type::kCTBOffSpillCRTCosmic, "kCTBOffSpillCRTCosmic" },
    { TriggerCandidateData::Type::kCTBBeamSpillStart, "kCTBBeamSpillStart" },
    { TriggerCandidateData::Type::kCTBBeamSpillSnapshot, "kCTBBeamSpillSnapshot" },
    { TriggerCandidateData::Type::kCTBCustomC, "kCTBCustomC" },
    { TriggerCandidateData::Type::kCTBCustomPulseTrain, "kCTBCustomPulseTrain" },
    { TriggerCandidateData::Type::kDTSPulser, "kDTSPulser" },
    { TriggerCandidateData::Type::kDTSCosmic, "kDTSCosmic" },
    { TriggerCandidateData::Type::kSSPLEDCalibration, "kSSPLEDCalibration" },
  };
}

inline int
string_to_trigger_candidate_type(const std::string& name)
{
  for (auto& it : get_trigger_candidate_type_names()) {
    if (it.second == name)
      return static_cast<int>(it.first);
  }
  return static_cast<int>(TriggerCandidateData::Type::kUnknown);
}

inline std::string
trigger_candidate_type_to_string(const TriggerCandidateData::Type& type)
{
  try {
    return get_trigger_candidate_type_names().at(type);
  }
  catch(std::exception &e) {
  }
  return "kUnknown";
}

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_
