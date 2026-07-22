/**
 * @file registrators.hpp
 *
 * Declaration of functions to register Python bindings to C++ objects
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */


#ifndef TRGDATAFORMATS_PYBINDSRC_REGISTRATORS_HPP_
#define TRGDATAFORMATS_PYBINDSRC_REGISTRATORS_HPP_

#include <pybind11/pybind11.h>

namespace dunedaq::trgdataformats::python {

  void register_types(pybind11::module &);
  void register_trigger_primitive(pybind11::module &);
  // void register_trigger_bitwords(pybind11::module &);
  void register_trigger_activity(pybind11::module &);
  void register_trigger_candidate(pybind11::module &);

}

#endif // TRGDATAFORMATS_PYBINDSRC_REGISTRATORS_HPP_
