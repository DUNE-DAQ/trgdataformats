
namespace dunedaq::trgdataformats {

  // tcinfo_t is a constexpr-declarable container of pairs, each pair
  // connecting a TriggerCandidateData::Type with its name
  using tcinfo_t = std::array<std::pair<TriggerCandidateData::Type, std::string_view>,
			      static_cast<size_t>(TriggerCandidateData::Type::kNumEnums)>;
  
  inline const tcinfo_t&
  get_trigger_candidate_type_names()
  {
    // This container needs to be updated for each new TC type, as this is used
    // when configuring Trigger Bitwords, affecting trigger logic in
    // trigger::MLT
    
    static constexpr tcinfo_t names { {
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
    { TriggerCandidateData::Type::kSSPLEDCalibration, "kSSPLEDCalibration" }
      }
    };

    // Check to ensure that if a new TriggerCandidateData::Type is
    // created, this function is updated accordingly
    static_assert(names.size() == static_cast<size_t>(TriggerCandidateData::Type::kNumEnums));

    return names;
  }

  inline TriggerCandidateData::Type
  string_to_trigger_candidate_type(const std::string& name) {
    for (const auto& [type, type_name] : get_trigger_candidate_type_names()) {
      if (type_name == name)
	return type;
    }
    return TriggerCandidateData::Type::kUnknown;
  }

  inline std::string
  trigger_candidate_type_to_string(const TriggerCandidateData::Type type) {
    try {
      const auto& [dummy, type_name] { get_trigger_candidate_type_names().at(static_cast<size_t>(type)) };
      return std::string(type_name);

    } catch (std::exception &e) {
      return "kUnknown";
    }
  }

} // namespace dunedaq::trgdataformats
