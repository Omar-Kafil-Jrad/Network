// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*****************************************************************************
 *   See the file COPYING for full copying permissions.                      *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *****************************************************************************/
/*!
 * \file
 * \brief The coupled exercise properties file or the interface case.
 */
#ifndef DUMUX_SIMPLE_NETWORK_PROPERTIES_HH
#define DUMUX_SIMPLE_NETWORK_PROPERTIES_HH


#include <dune/grid/yaspgrid.hh>
#include <dumux/multidomain/staggeredtraits.hh>
#include <dumux/multidomain/boundary/darcydarcy/couplingmanager.hh>

#include <dumux/material/components/trichloroethene.hh>
#include <dumux/material/components/simpleh2o.hh>
#include <dumux/material/fluidsystems/1pliquid.hh>
#include <dumux/material/fluidsystems/2pimmiscible.hh>

#include <dumux/common/properties.hh>
#include <dumux/discretization/cctpfa.hh>
#include <dumux/porousmediumflow/2p/model.hh>


#include "spatialparams.hh"
#include "nodesubproblem.hh"
#include "htubesubproblem.hh"

namespace Dumux::Properties {

// Create new type tags
namespace TTag {

struct PorousMediumFlowTwoP { using InheritsFrom = std::tuple<TwoP, CCTpfaModel>; };
// differentiate between the two subproblems
struct NodeSub { using InheritsFrom = std::tuple<PorousMediumFlowTwoP>; };
struct HTubeSub { using InheritsFrom = std::tuple<PorousMediumFlowTwoP>; };

} // end namespace TTag

// the coupling manager
template<class TypeTag>
struct CouplingManager<TypeTag, TTag::PorousMediumFlowTwoP>
{ 
    using type = DarcyDarcyBoundaryCouplingManager<MultiDomainTraits<Properties::TTag::HTubeSub, Properties::TTag::NodeSub>>; 
};

// Set the grid type

template<class TypeTag>
struct Grid<TypeTag, TTag::PorousMediumFlowTwoP>
{
    static constexpr auto dim = 2;
    using Scalar = GetPropType<TypeTag, Properties::Scalar>;
    using TensorGrid = Dune::YaspGrid<2, Dune::TensorProductCoordinates<Scalar, dim> >;
    using type = TensorGrid;
};

// set the spatial params
template<class TypeTag>
struct SpatialParams<TypeTag, TTag::PorousMediumFlowTwoP>
{
    using type = TwoPSpatialParams<GetPropType<TypeTag, Properties::GridGeometry>,
                                       GetPropType<TypeTag, Properties::Scalar>>;
};

// Set the problem property
// differentiate between the two subproblems
template<class TypeTag>
struct Problem<TypeTag, TTag::HTubeSub> { using type = HTubeSubProblem<TypeTag, 0>; };
template<class TypeTag>
struct Problem<TypeTag, TTag::NodeSub> { using type = NodeSubProblem<TypeTag, 1>; };



// Set the Fluidsystem
template<class TypeTag>
struct FluidSystem<TypeTag, TTag::PorousMediumFlowTwoP>
{
  using Scalar = GetPropType<TypeTag, Properties::Scalar>;
  using WettingPhase = FluidSystems::OnePLiquid<Scalar, Components::SimpleH2O<Scalar> >;
  using NonwettingPhase = FluidSystems::OnePLiquid<Scalar, Components::Trichloroethene<Scalar> >;

  using type = FluidSystems::TwoPImmiscible<Scalar, WettingPhase, NonwettingPhase>;
};

// Set the Formulation
// The two-phase model implements different primary variable formulations.
// Here we choose the pressure of the first phase and the saturation of the second phase.
// The order of phases is specified by the fluid system.
// With our choice of FluidSystem this means that the first phase is water and the second
// phase is DNAPL. We choose the `p0s1` formulation, which means a $`p_w - S_n`$ formulation,
// as the first phase (i.e. water) is the wetting phase in this example.
template<class TypeTag>
struct Formulation<TypeTag, TTag::PorousMediumFlowTwoP>
{ static constexpr auto value = TwoPFormulation::p0s1; };

} //end namespace Dumux::Properties

#endif
