/**
 * @file trigger_primitive.cpp Python bindings for the trigger primitive formats
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "trgdataformats/TriggerPrimitive.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq::trgdataformats::python {

void
register_trigger_primitive(py::module& m)
{


  py::class_<TriggerPrimitive> trigger_primitive(m, "TriggerPrimitive", py::buffer_protocol());
  trigger_primitive
    .def(py::init())
    .def(py::init([](py::capsule capsule) {
        auto tp = *static_cast<TriggerPrimitive*>(capsule.get_pointer());
        return tp;
		  } ))
    .def_property_readonly("version", [](TriggerPrimitive& self) -> uint16_t {return self.version;})
    .def_property_readonly("time_start", [](TriggerPrimitive& self) -> uint64_t {return self.time_start;})
    .def_property_readonly("time_peak", [](TriggerPrimitive& self) -> uint64_t {return self.time_peak;})
    .def_property_readonly("time_over_threshold", [](TriggerPrimitive& self) -> uint64_t {return self.time_over_threshold;})
    .def_property_readonly("channel", [](TriggerPrimitive& self) -> int32_t {return self.channel;})
    .def_property_readonly("adc_integral", [](TriggerPrimitive& self) -> uint32_t {return self.adc_integral;})
    .def_property_readonly("adc_peak", [](TriggerPrimitive& self) -> uint32_t {return self.adc_peak;})
    .def_property_readonly("detid", [](TriggerPrimitive& self) -> uint16_t {return self.detid;})
    .def_property_readonly("type", [](TriggerPrimitive& self) -> TriggerPrimitive::Type {return self.type;})
    .def_property_readonly("algorithm", [](TriggerPrimitive& self) -> TriggerPrimitive::Algorithm {return self.algorithm;})
    .def_property_readonly("flag", [](TriggerPrimitive& self) -> uint16_t {return self.flag;})
    .def_static("sizeof", [](){ return sizeof(TriggerPrimitive); })
    ;

  py::enum_<TriggerPrimitive::Type>(trigger_primitive, "Type")
    .value("kUnknown", TriggerPrimitive::Type::kUnknown)
    .value("kTPC", TriggerPrimitive::Type::kTPC)
    .value("kPDS", TriggerPrimitive::Type::kPDS);

  py::enum_<TriggerPrimitive::Algorithm>(trigger_primitive, "Algorithm")
    .value("kUnknown", TriggerPrimitive::Algorithm::kUnknown)
    .value("kSimpleThreshold", TriggerPrimitive::Algorithm::kSimpleThreshold)
    .value("kAbsRunningSum", TriggerPrimitive::Algorithm::kAbsRunningSum)
    .value("kRunningSum", TriggerPrimitive::Algorithm::kRunningSum);

}

} // namespace dunedaq::trgdataformats::python
