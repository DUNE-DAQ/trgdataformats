/**
 * @file module.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "registrators.hpp"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

namespace dunedaq::trgdataformats::python {

PYBIND11_MODULE(_daq_trgdataformats_py, m)
{

  m.doc() = "C++ implementation of the trgdataformats modules";

  register_types(m);
  register_trigger_primitive(m);
  // register_trigger_bitwords(m);
  register_trigger_activity(m);
  register_trigger_candidate(m);
}

} // namespace dunedaq::trgdataformats::python
