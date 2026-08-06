/**
 * @file TriggerCandidateData.hpp
 *
 * This header defines the TriggerCandidateData struct, which
 * aggregates information about a found set of associated trigger
 * activities (general type of candidate, algorithm used, times
 * involved, etc.). It does *not* include per-trigger-activity
 * information, which need to be associated with TriggerCandidateData
 * in a higher level object.
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_

#include "trgdataformats/Types.hpp"

#include <array>
#include <cstdint>
#include <map>
#include <string>

namespace dunedaq::trgdataformats {

struct TriggerCandidateData
{
  // If you add an enum to TriggerCandidateData::Type, declare it
  // second-to-last (just above kFinalEnum) and ensure its value is +1
  // greater than the enum above it

  enum class Type : int
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
    kFinalEnum
  };

  enum class Algorithm : int
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

  static constexpr version_t s_trigger_candidate_version = 3;

  version_t version = s_trigger_candidate_version;
  timestamp_t time_start = TypeDefaults::s_invalid_timestamp;
  timestamp_t time_end = TypeDefaults::s_invalid_timestamp;
  timestamp_t time_candidate = TypeDefaults::s_invalid_timestamp;
  // TODO P. Rodrigues 2021-01-06: This was originally a
  // std::vector<detid_t> but that messes up the overlay scheme, so
  // I've changed it for now to be just a detid_t. Need to work out
  // what to do longer term
  detid_t detid = TypeDefaults::s_invalid_detid;
  Type type = Type::kUnknown;
  Algorithm algorithm = Algorithm::kUnknown;
};

  inline TriggerCandidateData::Type
  string_to_trigger_candidate_type(const std::string& name);

  inline std::string
  trigger_candidate_type_to_string(const TriggerCandidateData::Type type);

} // namespace dunedaq::trgdataformats

#include "detail/TriggerCandidateData.hxx"

// This static_assert is meant to alert the developer to bump the
// version if variables are added or removed in TriggerCandidateData
static_assert(
	      dunedaq::trgdataformats::TriggerCandidateData::s_trigger_candidate_version == 3 &&
	      sizeof(dunedaq::trgdataformats::TriggerCandidateData) == 48
	      );

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERCANDIDATEDATA_HPP_
