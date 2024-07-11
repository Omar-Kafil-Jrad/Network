// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
//
// SPDX-FileCopyrightInfo: Copyright © DuMux Project contributors, see AUTHORS.md in root folder
// SPDX-License-Identifier: GPL-3.0-or-later
//

#ifndef DUMUX_SIMPLE_NETWORK_SPATIAL_PARAMS_HH
#define DUMUX_SIMPLE_NETWORK_SPATIAL_PARAMS_HH

#include <dumux/porousmediumflow/fvspatialparamsmp.hh>

// We include all laws which are needed to define the interaction between the solid matrix and the fluids, e.g. laws for capillary pressure saturation relationships.
#include <dumux/material/fluidmatrixinteractions/2p/vangenuchten.hh>

// ### The spatial parameters class
// In the TwoPSpatialParams class we define all functions needed to describe the porous matrix, e.g. porosity and permeability. We inherit from the `FVPorousMediumFlowSpatialParamsMP` class, which is the base class for multiphase porous medium flow applications.

namespace Dumux {

template<class GridGeometry, class Scalar>
class TwoPSpatialParams
: public FVPorousMediumFlowSpatialParamsMP<GridGeometry, Scalar, TwoPSpatialParams<GridGeometry, Scalar>>
{
    //we introduce using declarations that are derived from the property system which we need in this class
    using GridView = typename GridGeometry::GridView;
    using Element = typename GridView::template Codim<0>::Entity;
    using FVElementGeometry = typename GridGeometry::LocalView;
    using SubControlVolume = typename FVElementGeometry::SubControlVolume;
    using ThisType = TwoPSpatialParams<GridGeometry, Scalar>;
    using ParentType = FVPorousMediumFlowSpatialParamsMP<GridGeometry, Scalar, ThisType>;

    static constexpr int dimWorld = GridView::dimensionworld;
    using GlobalPosition = typename Element::Geometry::GlobalCoordinate;

    using PcKrSwCurve = FluidMatrix::VanGenuchtenDefault<Scalar>;

public:
    using PermeabilityType = Scalar;
    
    //Here, we get parameters for the porosity and permeability from the input file. Additionally, we set the parameters for the Van-Genuchten relationship.
    
    TwoPSpatialParams(std::shared_ptr<const GridGeometry> gridGeometry)
    : ParentType(gridGeometry)
    , pcKrSwCurve("SpatialParams") // read params from input file
    {
        // Here, we get the permeabilities from the params.input file.
        // In case that no parameter is set, the default parameters (9.05e-12 and 4.6e-10) are used
        
        K_ = getParam<Scalar>("SpatialParams.Permeability", 4.6e-10);
        porosity_ = getParam<Scalar>("SpatialParams.Porosity");
    }
     

    // We define the (intrinsic) permeability $`[m^2]`$. In this test, we use element-wise distributed permeabilities.
    template<class ElementSolution>
    PermeabilityType permeability(const Element& element,
                                  const SubControlVolume& scv,
                                  const ElementSolution& elemSol) const
    {
        return K_;
    }

    // We set the porosity $`[-]`$ depending on the position
    Scalar porosityAtPos(const GlobalPosition& globalPos) const
    {
        return porosity_;
    }

    // We set the parameter object for the Van Genuchten material law.
    template<class ElementSolution>
    auto fluidMatrixInteraction(const Element& element,
                                const SubControlVolume& scv,
                                const ElementSolution& elemSol) const
    {
        return makeFluidMatrixInteraction(pcKrSwCurve);
    }


     // Here we can define which phase is to be considered as the wetting phase. We choose the first phase
     // in the fluid system, which is water in our case (see definition of `FluidSystem` property).
    template<class FluidSystem>
    int wettingPhaseAtPos(const GlobalPosition& globalPos) const
    {  return FluidSystem::phase0Idx; }

private:
    
    Scalar K_;
    Scalar porosity_;

    const PcKrSwCurve pcKrSwCurve;

    static constexpr Scalar eps_ = 1.5e-7;
};

} // end namespace Dumux

#endif
