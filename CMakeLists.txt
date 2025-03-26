cmake_minimum_required(VERSION 3.12)
project(trgdataformats VERSION 1.4.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()


find_package(Boost COMPONENTS unit_test_framework REQUIRED)

##############################################################################

daq_add_library( LINK_LIBRARIES ) 

##############################################################################

daq_add_python_bindings(*.cpp LINK_LIBRARIES ${PROJECT_NAME} )

##############################################################################

daq_add_unit_test(Trgdataformats_test LINK_LIBRARIES)
daq_add_unit_test(TriggerCandidateData_test LINK_LIBRARIES)

##############################################################################

daq_install()

