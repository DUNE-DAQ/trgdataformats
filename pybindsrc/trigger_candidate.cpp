/**
 * @file trigger_primitive.cpp Python bindings for the trigger primitive formats
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "trgdataformats/TriggerObjectOverlay.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cstring>

namespace py = pybind11;

namespace dunedaq {
namespace trgdataformats {
namespace python {

/*
 Doesn't work
*/
struct TriggerCandidateHolder {


  TriggerCandidateHolder(void* ptr, size_t size) {
    m_size = size;
    m_data.reset(new uint8_t[m_size]);
    std::memcpy(m_data.get(), ptr, size);
  }

  TriggerCandidate* ptr() { return reinterpret_cast<TriggerCandidate*>(m_data.get());  }

  size_t m_size;
  std::unique_ptr<uint8_t[]> m_data;
  
};

void
register_trigger_candidate(py::module& m)
{

  m.def("string_to_fragment_type_value", &trgdataformats::string_to_fragment_type_value);


  py::class_<TriggerCandidateData> trigger_candidate_data(m, "TriggerCandidateData", py::buffer_protocol());
  trigger_candidate_data
    .def(py::init())
    .def(py::init([](py::capsule capsule) {
        auto tp = *static_cast<TriggerCandidateData*>(capsule.get_pointer());
        return tp;
		  } ))
    .def(py::init([](py::bytes bytes){
      py::buffer_info info(py::buffer(bytes).request());
      auto tp = *static_cast<TriggerCandidateData*>(info.ptr);
      return tp;
    }))
    .def_property_readonly("version", [](TriggerCandidateData& self) -> uint16_t {return self.version;})
    .def_property_readonly("time_start", [](TriggerCandidateData& self) -> uint64_t {return self.time_start;})
    .def_property_readonly("time_end", [](TriggerCandidateData& self) -> uint64_t {return self.time_end;})
    .def_property_readonly("time_candidate", [](TriggerCandidateData& self) -> uint64_t {return self.time_candidate;})
    .def_property_readonly("detid", [](TriggerCandidateData& self) -> uint16_t {return self.detid;})
    .def_property_readonly("type", [](TriggerCandidateData& self) -> TriggerCandidateData::Type {return self.type;})
    .def_property_readonly("algorithm", [](TriggerCandidateData& self) -> TriggerCandidateData::Algorithm {return self.algorithm;})
    .def_static("sizeof", [](){ return sizeof(TriggerCandidateData); })
    ;

  py::enum_<TriggerCandidateData::Type>(trigger_candidate_data, "Type")
    .value("kUnknown", TriggerCandidateData::Type::kUnknown)
    .value("kTiming", TriggerCandidateData::Type::kTiming)
    .value("kTPCLowE", TriggerCandidateData::Type::kTPCLowE)
    .value("kSupernova", TriggerCandidateData::Type::kSupernova)
    .value("kRandom", TriggerCandidateData::Type::kRandom)
    .value("kADCSimpleWindow", TriggerCandidateData::Type::kADCSimpleWindow)
    .value("kHorizontalMuon", TriggerCandidateData::Type::kHorizontalMuon)
    .value("kMichelElectron", TriggerCandidateData::Type::kMichelElectron)
    .value("kPlaneCoincidence", TriggerCandidateData::Type::kPlaneCoincidence);

  py::enum_<TriggerCandidateData::Algorithm>(trigger_candidate_data, "Algorithm")
    .value("kUnknown", TriggerCandidateData::Algorithm::kUnknown)
    .value("kSupernova", TriggerCandidateData::Algorithm::kSupernova)
    .value("kHSIEventToTriggerCandidate", TriggerCandidateData::Algorithm::kHSIEventToTriggerCandidate)
    .value("kPrescale", TriggerCandidateData::Algorithm::kPrescale)
    .value("kADCSimpleWindow", TriggerCandidateData::Algorithm::kADCSimpleWindow)
    .value("kHorizontalMuon", TriggerCandidateData::Algorithm::kHorizontalMuon)
    .value("kPlaneCoincidence", TriggerCandidateData::Algorithm::kPlaneCoincidence)
    .value("kCustom", TriggerCandidateData::Algorithm::kCustom);

  py::class_<TriggerCandidate>(m, "TriggerCandidateOverlay", py::buffer_protocol())
      .def(py::init())
      .def(py::init([](py::capsule capsule) {
        auto tp = *static_cast<TriggerCandidate*>(capsule.get_pointer());
        return tp;
		  } ))
      .def_property_readonly("data", [](TriggerCandidate& self) -> TriggerCandidateData& {return self.data;})
      .def("__len__", [](TriggerCandidate& self){ return self.n_inputs; })
      .def("sizeof", [](TriggerCandidate& self){ return sizeof(TriggerCandidate)+self.n_inputs*sizeof(TriggerPrimitive); })
    ;


    py::class_<TriggerCandidateHolder>(m, "TriggerCandidate", py::buffer_protocol())
      .def(py::init([](py::bytes bytes){
          py::buffer_info info(py::buffer(bytes).request());

          TriggerCandidateHolder tch(info.ptr, info.size);

          return tch;
        }))

      .def("get_bytes",
          [](TriggerCandidateHolder& tch) -> py::bytes {
            return py::bytes(reinterpret_cast<char*>(tch.ptr()), tch.m_size);
          }, py::return_value_policy::reference_internal
      )
      .def_property_readonly("data", [](TriggerCandidateHolder& self) -> TriggerCandidateData& {return self.ptr()->data;})
      .def("n_inputs", [](TriggerCandidateHolder& self){ return self.ptr()->n_inputs; })
      .def("__len__", [](TriggerCandidateHolder& self){ return self.ptr()->n_inputs; })
      .def("__getitem__",
            [](TriggerCandidateHolder &self, size_t i) -> const TriggerActivityData& {
                if (i >= self.ptr()->n_inputs) {
                    throw py::index_error();
                }
                return self.ptr()->inputs[i];
            }, py::return_value_policy::reference_internal)
      .def("sizeof", [](TriggerCandidateHolder& self){ return self.m_size; })
      ;
}

} // namespace python
} // namespace trgdataformats
} // namespace dunedaq
