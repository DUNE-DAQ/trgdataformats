/**
 * @file TriggerCandidateData_test.cxx TriggerCandidateData class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "trgdataformats/TriggerCandidateData.hpp"

/**
 * @brief Name of this test module
 */
#define BOOST_TEST_MODULE TriggerCandidateData_test // NOLINT

#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>

using namespace dunedaq::trgdataformats;

BOOST_AUTO_TEST_SUITE(TriggerCandidateData_test)

BOOST_AUTO_TEST_CASE(FragmentTypeConversion)
{
  BOOST_REQUIRE_EQUAL(static_cast<int>(string_to_trigger_candidate_type("kTiming")),
                      static_cast<int>(TriggerCandidateData::Type::kTiming));
  BOOST_REQUIRE_EQUAL(trigger_candidate_type_to_string(TriggerCandidateData::Type::kTiming), "kTiming");

  auto type_container = get_trigger_candidate_type_names();
  // sanity check
  for (const auto& [type, type_name] : type_container) {
    BOOST_TEST_MESSAGE("TriggerCandidateData type "
                       << int(type) << " " << type_name
                       << " with conversions: " << int(string_to_trigger_candidate_type(std::string(type_name))) << " "
                       << trigger_candidate_type_to_string(type));
    BOOST_REQUIRE_EQUAL(static_cast<int>(string_to_trigger_candidate_type(std::string(type_name))),
                        static_cast<int>(type));
    BOOST_REQUIRE_EQUAL(trigger_candidate_type_to_string(type), type_name);
  }

  BOOST_REQUIRE_EQUAL(static_cast<int>(string_to_trigger_candidate_type("thisIsABadFragmentType")),
                      static_cast<int>(TriggerCandidateData::Type::kUnknown));
  BOOST_REQUIRE_EQUAL(trigger_candidate_type_to_string(static_cast<TriggerCandidateData::Type>(-10)), "kUnknown");
}

BOOST_AUTO_TEST_SUITE_END()
