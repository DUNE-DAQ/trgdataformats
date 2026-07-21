/**
 * @file TriggerDataStructures_test.cxx
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "trgdataformats/TriggerActivityData.hpp"
#include "trgdataformats/TriggerCandidateData.hpp"
#include "trgdataformats/TriggerObjectOverlay.hpp"
#include "trgdataformats/TriggerPrimitive.hpp"
#include "trgdataformats/Types.hpp"

#define BOOST_TEST_MODULE TriggerDataStructures_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

using namespace dunedaq::trgdataformats;

BOOST_AUTO_TEST_SUITE(TriggerDataStructures_test)

BOOST_AUTO_TEST_CASE(TriggerPrimitive_DefaultValues_And_Timestamp)
{
  TriggerPrimitive tp;

  BOOST_REQUIRE_EQUAL(tp.version, TriggerPrimitive::s_trigger_primitive_version);
  BOOST_REQUIRE_EQUAL(tp.flag, 0);
  BOOST_REQUIRE_EQUAL(tp.detid, TypeDefaults::s_invalid_detid);
  BOOST_REQUIRE_EQUAL(tp.channel, TriggerPrimitive::s_invalid_tp_channel);
  BOOST_REQUIRE_EQUAL(tp.samples_over_threshold, TriggerPrimitive::s_invalid_samples_over_threshold);
  BOOST_REQUIRE_EQUAL(tp.time_start, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(tp.samples_to_peak, TriggerPrimitive::s_invalid_samples_to_peak);
  BOOST_REQUIRE_EQUAL(tp.adc_integral, 0);
  BOOST_REQUIRE_EQUAL(tp.adc_peak, 0);

  constexpr timestamp_t test_ts = 0x12345678ULL;
  tp.set_timestamp(test_ts);
  BOOST_REQUIRE_EQUAL(tp.get_timestamp(), test_ts);
  BOOST_REQUIRE_EQUAL(tp.time_start, test_ts);
}

BOOST_AUTO_TEST_CASE(TriggerPrimitive_Ordering)
{
  TriggerPrimitive a;
  TriggerPrimitive b;
  TriggerPrimitive c;

  a.time_start = 100;
  a.channel = 10;

  b.time_start = 100;
  b.channel = 8;

  c.time_start = 99;
  c.channel = 20;

  std::vector<TriggerPrimitive> tps{ a, b, c };
  std::sort(tps.begin(), tps.end());

  BOOST_REQUIRE_EQUAL(tps[0].time_start, 99);
  BOOST_REQUIRE_EQUAL(tps[0].channel, 20);

  BOOST_REQUIRE_EQUAL(tps[1].time_start, 100);
  BOOST_REQUIRE_EQUAL(tps[1].channel, 8);

  BOOST_REQUIRE_EQUAL(tps[2].time_start, 100);
  BOOST_REQUIRE_EQUAL(tps[2].channel, 10);
}

BOOST_AUTO_TEST_CASE(TriggerActivityData_DefaultValues)
{
  TriggerActivityData ta;

  BOOST_REQUIRE_EQUAL(ta.version, TriggerActivityData::s_trigger_activity_version);
  BOOST_REQUIRE_EQUAL(ta.time_start, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(ta.time_end, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(ta.time_peak, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(ta.time_activity, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(ta.channel_start, TriggerActivityData::s_invalid_channel);
  BOOST_REQUIRE_EQUAL(ta.channel_end, TriggerActivityData::s_invalid_channel);
  BOOST_REQUIRE_EQUAL(ta.channel_peak, TriggerActivityData::s_invalid_channel);
  BOOST_REQUIRE_EQUAL(ta.adc_integral, 0);
  BOOST_REQUIRE_EQUAL(ta.adc_peak, 0);
  BOOST_REQUIRE_EQUAL(ta.detid, TypeDefaults::s_invalid_detid);
  BOOST_REQUIRE_EQUAL(static_cast<int>(ta.type), static_cast<int>(TriggerActivityData::Type::kUnknown));
  BOOST_REQUIRE_EQUAL(static_cast<int>(ta.algorithm), static_cast<int>(TriggerActivityData::Algorithm::kUnknown));
}

BOOST_AUTO_TEST_CASE(TriggerCandidateData_DefaultValues)
{
  TriggerCandidateData tc{};

  BOOST_REQUIRE_EQUAL(tc.version, TriggerCandidateData::s_trigger_candidate_version);
  BOOST_REQUIRE_EQUAL(tc.time_start, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(tc.time_end, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(tc.time_candidate, TypeDefaults::s_invalid_timestamp);
  BOOST_REQUIRE_EQUAL(static_cast<int>(tc.type), static_cast<int>(TriggerCandidateData::Type::kUnknown));
  BOOST_REQUIRE_EQUAL(static_cast<int>(tc.algorithm), static_cast<int>(TriggerCandidateData::Algorithm::kUnknown));

  // This expectation is intentionally strict to catch missing default-initialization policy.
  BOOST_REQUIRE_EQUAL(tc.detid, TypeDefaults::s_invalid_detid);
}

BOOST_AUTO_TEST_CASE(TriggerCandidateData_TypeMapCompleteness)
{
  const auto type_map = get_trigger_candidate_type_names();
  BOOST_REQUIRE_EQUAL(type_map.size(), 39);

  std::set<std::string> names;
  for (const auto& kv : type_map) {
    const auto inserted = names.insert(kv.second).second;
    BOOST_REQUIRE(inserted);
    BOOST_REQUIRE_EQUAL(trigger_candidate_type_to_string(kv.first), kv.second);
    BOOST_REQUIRE_EQUAL(static_cast<int>(string_to_trigger_candidate_type(kv.second)), static_cast<int>(kv.first));
  }

  BOOST_REQUIRE_EQUAL(type_map.at(TriggerCandidateData::Type::kUnknown), "kUnknown");
  BOOST_REQUIRE_EQUAL(type_map.at(TriggerCandidateData::Type::kSSPLEDCalibration), "kSSPLEDCalibration");
}

BOOST_AUTO_TEST_CASE(Types_DefaultConstants)
{
  BOOST_REQUIRE_EQUAL(TypeDefaults::s_invalid_timestamp, std::numeric_limits<timestamp_t>::max());
  BOOST_REQUIRE_EQUAL(TypeDefaults::s_invalid_detid, std::numeric_limits<detid_t>::max());
  BOOST_REQUIRE_EQUAL(TypeDefaults::s_invalid_trigger_number, std::numeric_limits<trigger_number_t>::max());
  BOOST_REQUIRE(g_whole_detector != TypeDefaults::s_invalid_detid);
  BOOST_REQUIRE_EQUAL(g_whole_detector,
                      static_cast<detid_t>(std::numeric_limits<detid_t>::max() - static_cast<detid_t>(1)));
}

BOOST_AUTO_TEST_CASE(TriggerObjectOverlay_AliasesAndLayout)
{
  BOOST_REQUIRE((std::is_same_v<TriggerActivity::data_t, TriggerActivityData>));
  BOOST_REQUIRE((std::is_same_v<TriggerActivity::input_t, TriggerPrimitive>));
  BOOST_REQUIRE((std::is_same_v<TriggerCandidate::data_t, TriggerCandidateData>));
  BOOST_REQUIRE((std::is_same_v<TriggerCandidate::input_t, TriggerActivityData>));

  BOOST_REQUIRE_EQUAL(offsetof(TriggerActivity, n_inputs), sizeof(TriggerActivityData));
  BOOST_REQUIRE_EQUAL(offsetof(TriggerCandidate, n_inputs), sizeof(TriggerCandidateData));
}

BOOST_AUTO_TEST_SUITE_END()
