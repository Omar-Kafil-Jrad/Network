if(NOT Fluidics-network_FOUND)
# Whether this module is installed or not
set(Fluidics-network_INSTALLED OFF)

# Settings specific to the module

# Package initialization
# Set prefix to source dir
set(PACKAGE_PREFIX_DIR /home/omarjrad/dumux/Fluidics-network)
macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

#report other information
set_and_check(Fluidics-network_PREFIX "${PACKAGE_PREFIX_DIR}")
set_and_check(Fluidics-network_INCLUDE_DIRS "/home/omarjrad/dumux/Fluidics-network")
set(Fluidics-network_CXX_FLAGS "-std=c++17 ")
set(Fluidics-network_CXX_FLAGS_DEBUG "-O0 -g -ggdb -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare")
set(Fluidics-network_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(Fluidics-network_CXX_FLAGS_RELEASE " -fdiagnostics-color=always -fno-strict-aliasing -fstrict-overflow -fno-finite-math-only -DNDEBUG=1 -O3 -march=native -funroll-loops -g0 -Wall -Wunused -Wmissing-include-dirs -Wcast-align -Wno-missing-braces -Wmissing-field-initializers -Wno-sign-compare")
set(Fluidics-network_CXX_FLAGS_RELWITHDEBINFO " -fdiagnostics-color=always -fno-strict-aliasing -fstrict-overflow -fno-finite-math-only -DNDEBUG=1 -O3 -march=native -funroll-loops -g0 -Wall -Wunused -Wmissing-include-dirs -Wcast-align -Wno-missing-braces -Wmissing-field-initializers -Wno-sign-compare -g -ggdb -Wall")
set(Fluidics-network_DEPENDS "dumux")
set(Fluidics-network_SUGGESTS "")
set(Fluidics-network_MODULE_PATH "/home/omarjrad/dumux/Fluidics-network/cmake/modules")
set(Fluidics-network_LIBRARIES "")
set(Fluidics-network_HASPYTHON 0)
set(Fluidics-network_PYTHONREQUIRES "")

# Lines that are set by the CMake build system via the variable DUNE_CUSTOM_PKG_CONFIG_SECTION


#import the target
if(Fluidics-network_LIBRARIES)
  get_filename_component(_dir "${CMAKE_CURRENT_LIST_FILE}" PATH)
  include("${_dir}/Fluidics-network-targets.cmake")
endif()

endif()
