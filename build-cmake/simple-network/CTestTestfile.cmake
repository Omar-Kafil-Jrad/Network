# CMake generated Testfile for 
# Source directory: /home/omarjrad/dumux/Fluidics-network/simple-network
# Build directory: /home/omarjrad/dumux/Fluidics-network/build-cmake/simple-network
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simple_network "/home/omarjrad/dumux/Fluidics-network/build-cmake/simple-network/simple_network")
set_tests_properties(simple_network PROPERTIES  LABELS "simp" PROCESSORS "1" REQUIRED_FILES "/home/omarjrad/dumux/Fluidics-network/build-cmake/simple-network/simple_network" SKIP_RETURN_CODE "77" TIMEOUT "300" WORKING_DIRECTORY "/home/omarjrad/dumux/Fluidics-network/build-cmake/simple-network" _BACKTRACE_TRIPLES "/home/omarjrad/dumux/dune-common/cmake/modules/DuneTestMacros.cmake;414;_add_test;/home/omarjrad/dumux/dumux/cmake/modules/DumuxTestMacros.cmake;210;dune_add_test;/home/omarjrad/dumux/Fluidics-network/simple-network/CMakeLists.txt;5;dumux_add_test;/home/omarjrad/dumux/Fluidics-network/simple-network/CMakeLists.txt;0;")
