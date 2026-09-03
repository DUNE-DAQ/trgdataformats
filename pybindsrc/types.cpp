/**
 * @file types.cpp Python bindings for common trgdataformats scalar aliases/constants
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "trgdataformats/Types.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq::trgdataformats::python {

void
register_types(py::module& m)
{
  py::class_<TypeDefaults>(m, "TypeDefaults")
    .def_property_readonly_static("s_invalid_timestamp", [](py::object /*self*/) { return TypeDefaults::s_invalid_timestamp; })
    .def_property_readonly_static("s_invalid_detid", [](py::object /*self*/) { return TypeDefaults::s_invalid_detid; })
    .def_property_readonly_static("s_invalid_trigger_number", [](py::object /*self*/) { return TypeDefaults::s_invalid_trigger_number; });

  m.attr("g_whole_detector") = py::int_(g_whole_detector);
}

} // namespace dunedaq::trgdataformats::python
