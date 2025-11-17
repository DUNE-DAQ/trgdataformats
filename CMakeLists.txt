cmake_minimum_required(VERSION 3.12)
project(trgdataformats VERSION 2.0.2)

find_package(daq-cmake REQUIRED)

daq_setup_environment()


find_package(Boost COMPONENTS unit_test_framework REQUIRED)

##############################################################################

daq_add_library( LINK_LIBRARIES ) 

##############################################################################

daq_add_python_bindings(*.cpp )

##############################################################################

daq_add_unit_test(Trgdataformats_test LINK_LIBRARIES)
daq_add_unit_test(TriggerCandidateData_test LINK_LIBRARIES)

##############################################################################

daq_install()

