/* config.h.  Generated from config_collected.h.cmake by CMake.
   It was generated from config_collected.h.cmake which in turn is generated automatically
   from the config.h.cmake files of modules this module depends on. */

/* Define to 1 if you have module Fluidics-network available */
#cmakedefine01 HAVE_FLUIDICS_NETWORK


/* Define to 1 if you have module dune-common available */
#cmakedefine01 HAVE_DUNE_COMMON


/* Define to 1 if you have module dune-uggrid available */
#cmakedefine01 HAVE_DUNE_UGGRID


/* Define to 1 if you have module dune-geometry available */
#cmakedefine01 HAVE_DUNE_GEOMETRY


/* Define to 1 if you have module dune-mmesh available */
#cmakedefine01 HAVE_DUNE_MMESH


/* Define to 1 if you have module dune-spgrid available */
#cmakedefine01 HAVE_DUNE_SPGRID


/* Define to 1 if you have module dune-subgrid available */
#cmakedefine01 HAVE_DUNE_SUBGRID


/* Define to 1 if you have module opm-grid available */
#cmakedefine01 HAVE_OPM_GRID


/* Define to 1 if you have module opm-common available */
#cmakedefine01 HAVE_OPM_COMMON


/* Define to 1 if you have module dune-functions available */
#cmakedefine01 HAVE_DUNE_FUNCTIONS


/* Define to 1 if you have module dune-foamgrid available */
#cmakedefine01 HAVE_DUNE_FOAMGRID


/* Define to 1 if you have module dune-alugrid available */
#cmakedefine01 HAVE_DUNE_ALUGRID


/* Define to 1 if you have module dune-istl available */
#cmakedefine01 HAVE_DUNE_ISTL


/* Define to 1 if you have module dune-localfunctions available */
#cmakedefine01 HAVE_DUNE_LOCALFUNCTIONS


/* Define to 1 if you have module dune-grid available */
#cmakedefine01 HAVE_DUNE_GRID


/* Define to 1 if you have module dumux available */
#cmakedefine01 HAVE_DUMUX


/* begin private */
/* Define to the version of dune-common */
#define DUNE_COMMON_VERSION "${DUNE_COMMON_VERSION}"

/* Define to the major version of dune-common */
#define DUNE_COMMON_VERSION_MAJOR ${DUNE_COMMON_VERSION_MAJOR}

/* Define to the minor version of dune-common */
#define DUNE_COMMON_VERSION_MINOR ${DUNE_COMMON_VERSION_MINOR}

/* Define to the revision of dune-common */
#define DUNE_COMMON_VERSION_REVISION ${DUNE_COMMON_VERSION_REVISION}

/* Standard debug streams with a level below will collapse to doing nothing */
#define DUNE_MINIMAL_DEBUG_LEVEL ${DUNE_MINIMAL_DEBUG_LEVEL}

/* does the standard library provide experimental::make_array() ? */
#cmakedefine DUNE_HAVE_CXX_EXPERIMENTAL_MAKE_ARRAY 1

/* does the standard library provide experimental::is_detected ? */
#cmakedefine DUNE_HAVE_CXX_EXPERIMENTAL_IS_DETECTED 1

/* does the language support lambdas in unevaluated contexts ? */
#cmakedefine DUNE_HAVE_CXX_UNEVALUATED_CONTEXT_LAMBDA 1

/* does the standard library provide identity ? */
#cmakedefine DUNE_HAVE_CXX_STD_IDENTITY 1

/* Define if you have a BLAS library. */
#cmakedefine HAVE_BLAS 1

/* Define if you have LAPACK library. */
#cmakedefine HAVE_LAPACK 1

/* Define if you have the MPI library.  */
#cmakedefine HAVE_MPI ENABLE_MPI

/* Deactivate cxx bindings for MPI */
#if defined(HAVE_MPI) && HAVE_MPI
#define MPICH_SKIP_MPICXX 1
#define OMPI_SKIP_MPICXX 1
#define MPI_NO_CPPBIND 1
#define MPIPP_H
#define _MPICC_H
#endif

/* Define if you have the GNU GMP library. The value should be ENABLE_GMP
   to facilitate activating and deactivating GMP using compile flags. */
#cmakedefine HAVE_GMP ENABLE_GMP

/* Define if you have the GCC Quad-Precision library. The value should be ENABLE_QUADMATH
   to facilitate activating and deactivating QuadMath using compile flags. */
#cmakedefine HAVE_QUADMATH ENABLE_QUADMATH

/* Define if you have the Vc library. The value should be ENABLE_VC
   to facilitate activating and deactivating Vc using compile flags. */
#cmakedefine HAVE_VC ENABLE_VC

/* Define to 1 if you have the Threading Building Blocks (TBB) library */
#cmakedefine HAVE_TBB 1




/* old feature support macros which were tested until 2.8, kept around for one more release */
#define HAS_ATTRIBUTE_DEPRECATED 0
#define HAS_ATTRIBUTE_DEPRECATED_MSG 0
#define HAS_ATTRIBUTE_UNUSED 0

/* Define to ENABLE_UMFPACK if the UMFPack library is available */
#cmakedefine HAVE_UMFPACK ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse library is available */
#cmakedefine HAVE_SUITESPARSE ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's AMD library is available */
#cmakedefine HAVE_SUITESPARSE_AMD ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's BTF library is available */
#cmakedefine HAVE_SUITESPARSE_BTF ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's CAMD library is available */
#cmakedefine HAVE_SUITESPARSE_CAMD ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's CCOLAMD library is available */
#cmakedefine HAVE_SUITESPARSE_CCOLAMD ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's CHOLMOD library is available */
#cmakedefine HAVE_SUITESPARSE_CHOLMOD ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's COLAMD library is available */
#cmakedefine HAVE_SUITESPARSE_COLAMD ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's CXSPARSE library is available */
#cmakedefine HAVE_SUITESPARSE_CXSPARSE ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's KLU library is available */
#cmakedefine HAVE_SUITESPARSE_KLU ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's LDL library is available */
#cmakedefine HAVE_SUITESPARSE_LDL ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's RBIO library is available */
#cmakedefine HAVE_SUITESPARSE_RBIO ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's SPQR library is available
   and if it's version is at least 4.3 */
#cmakedefine HAVE_SUITESPARSE_SPQR ENABLE_SUITESPARSE

/* Define to ENABLE_SUITESPARSE if the SuiteSparse's UMFPACK library is available */
#cmakedefine HAVE_SUITESPARSE_UMFPACK ENABLE_SUITESPARSE

/* Define to 1 if METIS is available */
#cmakedefine HAVE_METIS 1

/* Define to 1 if the Scotch replacement for METIS is used. */
#cmakedefine HAVE_SCOTCH_METIS 1

/* Define to 1 if you have the ParMETIS library. */
#cmakedefine HAVE_PARMETIS 1

/* Define to 1 if the PTScotch replacement for ParMETIS is used. */
#cmakedefine HAVE_PTSCOTCH_PARMETIS 1

/* Define to 1 if PT-Scotch is available */
#cmakedefine HAVE_PTSCOTCH 1

/* Used to call lapack functions */
#cmakedefine LAPACK_NEEDS_UNDERLINE





/* Define to the version of dune-geometry */
#define DUNE_GEOMETRY_VERSION "${DUNE_GEOMETRY_VERSION}"

/* Define to the major version of dune-geometry */
#define DUNE_GEOMETRY_VERSION_MAJOR ${DUNE_GEOMETRY_VERSION_MAJOR}

/* Define to the minor version of dune-geometry */
#define DUNE_GEOMETRY_VERSION_MINOR ${DUNE_GEOMETRY_VERSION_MINOR}

/* Define to the revision of dune-geometry */
#define DUNE_GEOMETRY_VERSION_REVISION ${DUNE_GEOMETRY_VERSION_REVISION}






/* Define to ENABLE_SUPERLU if the SuperLU library is available */
#cmakedefine HAVE_SUPERLU ENABLE_SUPERLU

/* Define to the integer type that SuperLU was compiled for
   See e.g. what int_t is defined to in slu_sdefs.h */
#cmakedefine SUPERLU_INT_TYPE @SUPERLU_INT_TYPE@

/* Define to ENABLE_ARPACKPP if the ARPACK++ library is available */
#cmakedefine HAVE_ARPACKPP ENABLE_ARPACKPP

/* Define to the version of dune-istl */
#define DUNE_ISTL_VERSION "${DUNE_ISTL_VERSION}"

/* Define to the major version of dune-istl */
#define DUNE_ISTL_VERSION_MAJOR ${DUNE_ISTL_VERSION_MAJOR}

/* Define to the minor version of dune-istl */
#define DUNE_ISTL_VERSION_MINOR ${DUNE_ISTL_VERSION_MINOR}

/* Define to the revision of dune-istl */
#define DUNE_ISTL_VERSION_REVISION ${DUNE_ISTL_VERSION_REVISION}

/* Enable/Disable the backwards compatibility of the category enum/method in dune-istl solvers, preconditioner, etc. */
#cmakedefine DUNE_ISTL_SUPPORT_OLD_CATEGORY_INTERFACE @DUNE_ISTL_SUPPORT_OLD_CATEGORY_INTERFACE@





/* Define to the version of dune-localfunctions */
#define DUNE_LOCALFUNCTIONS_VERSION "${DUNE_LOCALFUNCTIONS_VERSION}"

/* Define to the major version of dune-localfunctions */
#define DUNE_LOCALFUNCTIONS_VERSION_MAJOR ${DUNE_LOCALFUNCTIONS_VERSION_MAJOR}

/* Define to the minor version of dune-localfunctions */
#define DUNE_LOCALFUNCTIONS_VERSION_MINOR ${DUNE_LOCALFUNCTIONS_VERSION_MINOR}

/* Define to the revision of dune-localfunctions */
#define DUNE_LOCALFUNCTIONS_VERSION_REVISION ${DUNE_LOCALFUNCTIONS_VERSION_REVISION}





/* Define to the version of dune-grid */
#define DUNE_GRID_VERSION "${DUNE_GRID_VERSION}"

/* Define to the major version of dune-grid */
#define DUNE_GRID_VERSION_MAJOR ${DUNE_GRID_VERSION_MAJOR}

/* Define to the minor version of dune-grid */
#define DUNE_GRID_VERSION_MINOR ${DUNE_GRID_VERSION_MINOR}

/* Define to the revision of dune-grid */
#define DUNE_GRID_VERSION_REVISION ${DUNE_GRID_VERSION_REVISION}

/* Alberta version found by configure, either 0x200 for 2.0 or 0x300 for 3.0 */
#cmakedefine DUNE_ALBERTA_VERSION @DUNE_ALBERTA_VERSION@

/* This is only true if alberta-library was found by configure _and_ if the
   application uses the ALBERTA_CPPFLAGS */
#cmakedefine HAVE_ALBERTA ENABLE_ALBERTA

/* Define to 1 if you have mkstemp function */
#cmakedefine01 HAVE_MKSTEMP








/* Define to the version of dumux */
#define DUMUX_VERSION "${DUMUX_VERSION}"

/* Define to the major version of dumux */
#define DUMUX_VERSION_MAJOR ${DUMUX_VERSION_MAJOR}

/* Define to the minor version of dumux */
#define DUMUX_VERSION_MINOR ${DUMUX_VERSION_MINOR}

/* Define to the revision of dumux */
#define DUMUX_VERSION_REVISION ${DUMUX_VERSION_REVISION}

/* Define the path to dumux */
#define DUMUX_SOURCE_DIR "${CMAKE_SOURCE_DIR}"

/* Define the major version of opm-grid */
#define OPM_GRID_VERSION_MAJOR ${OPM_GRID_VERSION_MAJOR}

/* Define the minor version of opm-grid */
#define OPM_GRID_VERSION_MINOR ${OPM_GRID_VERSION_MINOR}

/* Define to 1 if gnuplot was found */
#cmakedefine DUMUX_HAVE_GNUPLOT 1

/* Define path to gnuplot executable */
#cmakedefine GNUPLOT_EXECUTABLE "@GNUPLOT_EXECUTABLE@"

/* Define to 1 if gstat was found */
#cmakedefine DUMUX_HAVE_GSTAT 1

/* Define path to gstat executable */
#cmakedefine GSTAT_EXECUTABLE "@GSTAT_EXECUTABLE@"

/* Define to 1 if gmsh was found */
#cmakedefine DUMUX_HAVE_GMSH 1

/* Define path to gmsh executable */
#cmakedefine GMSH_EXECUTABLE "@GMSH_EXECUTABLE@"

/* Defines whether pvpython has been found */
#cmakedefine DUMUX_HAVE_PVPYTHON 1

/* Define the path to pvpython */
#define PVPYTHON_EXECUTABLE "${PVPYTHON_EXECUTABLE}"

/* Define to 1 if quadmath was found */
#cmakedefine DUMUX_HAVE_QUAD 1

/* Set if Kokkos was found */
#cmakedefine DUMUX_HAVE_KOKKOS ENABLE_KOKKOS

/* Set if OpenMP was found */
#cmakedefine DUMUX_HAVE_OPENMP ENABLE_OPENMP

/* Set the DUMUX_MULTITHREADING_BACKEND */
#ifndef DUMUX_MULTITHREADING_BACKEND
#define DUMUX_MULTITHREADING_BACKEND ${DUMUX_MULTITHREADING_BACKEND}
#endif

/* Set DUMUX_HAVE_CPP_PARALLEL_ALGORITHMS if available */
#cmakedefine DUMUX_HAVE_CPP_PARALLEL_ALGORITHMS 1



/* begin Fluidics-network
   put the definitions for config.h specific to
   your project here. Everything above will be
   overwritten
*/

/* begin private */
/* Name of package */
#define PACKAGE "@DUNE_MOD_NAME@"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "@DUNE_MAINTAINER@"

/* Define to the full name of this package. */
#define PACKAGE_NAME "@DUNE_MOD_NAME@"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "@DUNE_MOD_NAME@ @DUNE_MOD_VERSION@"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "@DUNE_MOD_NAME@"

/* Define to the home page for this package. */
#define PACKAGE_URL "@DUNE_MOD_URL@"

/* Define to the version of this package. */
#define PACKAGE_VERSION "@DUNE_MOD_VERSION@"

/* end private */

/* Define to the version of Fluidics-network */
#define FLUIDICS_NETWORK_VERSION "@FLUIDICS_NETWORK_VERSION@"

/* Define to the major version of Fluidics-network */
#define FLUIDICS_NETWORK_VERSION_MAJOR @FLUIDICS_NETWORK_VERSION_MAJOR@

/* Define to the minor version of Fluidics-network */
#define FLUIDICS_NETWORK_VERSION_MINOR @FLUIDICS_NETWORK_VERSION_MINOR@

/* Define to the revision of Fluidics-network */
#define FLUIDICS_NETWORK_VERSION_REVISION @FLUIDICS_NETWORK_VERSION_REVISION@

/* end Fluidics-network
   Everything below here will be overwritten
*/ 

/* Grid type magic for DGF parser */
@GRID_CONFIG_H_BOTTOM@

