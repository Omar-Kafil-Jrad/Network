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
 *
 * \brief The node sub problem
 */
#ifndef DUMUX_NODE_SUBPROBLEM_HH
#define DUMUX_NODE_SUBPROBLEM_HH

#include <dune/common/indices.hh>

#include <dumux/porousmediumflow/problem.hh>
#include <dumux/common/properties.hh>
#include <dumux/common/boundarytypes.hh>
#include <dumux/common/numeqvector.hh>
#include <dumux/common/parameters.hh>

namespace Dumux {

/*!
 * \brief The node sub problem
 */
template<class TypeTag, std::size_t tag>
class NodeSubProblem : public PorousMediumFlowProblem<TypeTag>
{
    using ParentType = PorousMediumFlowProblem<TypeTag>;
    using GridView = typename GetPropType<TypeTag, Properties::GridGeometry>::GridView;
    using Scalar = GetPropType<TypeTag, Properties::Scalar>;

    // Grid dimension
    static constexpr int dim = GridView::dimension;
    static constexpr int dimWorld = GridView::dimensionworld;
    static constexpr auto domainIdx = Dune::index_constant<tag>{};
    using Element = typename GridView::template Codim<0>::Entity;
    using GlobalPosition = typename Element::Geometry::GlobalCoordinate;

    // Dumux specific types
    using Indices = typename GetPropType<TypeTag, Properties::ModelTraits>::Indices;
    using PrimaryVariables = GetPropType<TypeTag, Properties::PrimaryVariables>;
    using BoundaryTypes = Dumux::BoundaryTypes<GetPropType<TypeTag, Properties::ModelTraits>::numEq()>;
    using GridGeometry = GetPropType<TypeTag, Properties::GridGeometry>;
    using FVElementGeometry = typename GetPropType<TypeTag, Properties::GridGeometry>::LocalView;
    using NumEqVector = Dumux::NumEqVector<PrimaryVariables>;
    using FluidSystem = GetPropType<TypeTag, Properties::FluidSystem>;

    using VolumeVariables = GetPropType<TypeTag, Properties::VolumeVariables>;
    using SubControlVolume = typename FVElementGeometry::SubControlVolume;
    using SubControlVolumeFace = typename FVElementGeometry::SubControlVolumeFace;
    using GridVariables = GetPropType<TypeTag, Properties::GridVariables>;
    using ElementFluxVariablesCache = typename GridVariables::GridFluxVariablesCache::LocalView;
    
    enum {
        pressureH2OIdx = Indices::pressureIdx,
        saturationDNAPLIdx = Indices::saturationIdx,
        contiDNAPLEqIdx = Indices::conti0EqIdx + FluidSystem::comp1Idx,
        waterPhaseIdx = FluidSystem::phase0Idx,
        dnaplPhaseIdx = FluidSystem::phase1Idx
    };

    using CouplingManager = GetPropType<TypeTag, Properties::CouplingManager>;

public:
    NodeSubProblem(std::shared_ptr<const GridGeometry> gridGeometry,
                   std::shared_ptr<CouplingManager> couplingManager,
                   const std::string& paramGroup = "")
    : ParentType(gridGeometry, paramGroup),
      couplingManager_(couplingManager)
    {
        //2pinfiltration
        initialValues_ = readFileToContainer<std::vector<PrimaryVariables>>("nodeinitialsolutioncc.txt");
        //test1p2p
        problemName_  =  getParam<std::string>("Vtk.OutputName") + "_" + getParamFromGroup<std::string>(paramGroup, "Problem.Name");
    }

    /*!
     * \brief The problem name.
     */
    const std::string& name() const
    {
        return problemName_;
    }

    /*!
     * \brief Specifies which kind of boundary condition should be
     *        used for which equation on a given boundary control volume.
     *
     * \param element The element
     * \param scvf The boundary sub control volume face
     */
    BoundaryTypes boundaryTypes(const Element &element, const SubControlVolumeFace &scvf) const
    {
        BoundaryTypes values;

        // set Neumann BCs to all boundaries first
        values.setAllNeumann();

        // set the coupling boundary condition at the interface
        if (couplingManager_->isCoupled(domainIdx, scvf))
            values.setAllCouplingNeumann();

        return values;
    }

    /*!
     * \brief Evaluate the boundary conditions for a Dirichlet control volume.
     *
     * \param element The element for which the Dirichlet boundary condition is set
     * \param scvf The boundary subcontrolvolumeface
     *
     * For this method, the \a values parameter stores primary variables.
     */
    // We need to fix values for the two primary variables: the water pressure
    // and the DNAPL saturation.
    PrimaryVariables dirichletAtPos(const GlobalPosition &globalPos) const
    {
        PrimaryVariables values;
        // The waterphase pressure is given by P_(input) on our Dirichlet boundary:
        values[pressureH2OIdx] = P_;
        // The saturation of the DNAPL Trichlorethene is zero on our Dirichlet boundary:
        values[saturationDNAPLIdx] = 0.0;

        return values;
    }

    /*!
     * \brief Evaluates the boundary conditions for a Neumann boundary segment.
     *
     * This is the method for the case where the Neumann condition is
     * potentially solution dependent.
     *
     * \param element The finite element
     * \param fvGeometry The finite-volume geometry
     * \param elemVolVars All volume variables for the element
     * \param elemFluxVarsCache Flux variables caches for all faces in stencil
     * \param scvf The sub control volume face
     *
     * Negative values mean influx.
     * E.g. for the mass balance that would the mass flux in \f$ [ kg / (m^2 \cdot s)] \f$.
     */
    template<class ElementVolumeVariables, class ElementFluxVarsCache>
    NumEqVector neumann(const Element& element,
                        const FVElementGeometry& fvGeometry,
                        const ElementVolumeVariables& elemVolVars,
                        const ElementFluxVarsCache& elemFluxVarsCache,
                        const SubControlVolumeFace& scvf) const
    {
        NumEqVector values(0.0);
        const auto bcTypes = boundaryTypes(element, scvf);
        if (bcTypes.hasCouplingNeumann())
            values[contiDNAPLEqIdx] = couplingManager_->advectiveFluxCoupling(domainIdx, element, fvGeometry, elemVolVars, scvf, dnaplPhaseIdx);

        return values;
    }


    /*!
     * \brief Evaluate the source term for all phases within a given
     *        sub-control-volume.
     *
     * \param element The element for which the source term is set
     * \param fvGeomentry The fvGeometry
     * \param elemVolVars The element volume variables
     * \param scv The subcontrolvolume
     */
    template<class ElementVolumeVariables>
    NumEqVector source(const Element &element,
                       const FVElementGeometry& fvGeometry,
                       const ElementVolumeVariables& elemVolVars,
                       const SubControlVolume &scv) const
    { return NumEqVector(0.0); }

    /*!
     * \brief Evaluate the initial value for a control volume.
     *
     * \param element The element
     *
     * For this method, the \a priVars parameter stores primary
     * variables.
     */
    PrimaryVariables initial(const Element& element) const
    {
        // The input data is written for a uniform grid with discretization length delta.
        // Accordingly, we need to find the index of our cells, depending on the x and y coordinates,
        // that corresponds to the indices of the input data set.
        const auto delta = 0.01;
        const unsigned int cellsX = (this->gridGeometry().bBoxMax()[0] - this->gridGeometry().bBoxMin()[0])/delta;
        const auto globalPos = element.geometry().center();

         // Shift the coordinates to start from zero
        const unsigned int shiftedX = std::trunc((globalPos[0] - this->gridGeometry().bBoxMin()[0]) / delta);
        const unsigned int shiftedY = std::trunc((globalPos[1] - this->gridGeometry().bBoxMin()[1]) / delta);

        // Calculate the data index for the 1D initial solution array
        const unsigned int dataIdx = shiftedY * cellsX + shiftedX;

         // Debug prints
        
        if (dataIdx >= initialValues_.size()) 
        {
        std::cerr << "dataIdx out of bounds: " << dataIdx << std::endl;
        // Handle the error appropriately
        throw std::out_of_range("dataIdx out of bounds");
        }

        return initialValues_[dataIdx];
    }


    //! Set the coupling manager
    void setCouplingManager(std::shared_ptr<CouplingManager> cm)
    { couplingManager_ = cm; }

    //! Get the coupling manager
    const CouplingManager& couplingManager() const
    { return *couplingManager_; }

private:
    bool onLeftBoundary_(const GlobalPosition &globalPos) const
    { return globalPos[0] < this->gridGeometry().bBoxMin()[0] + eps_; }

    bool onRightBoundary_(const GlobalPosition &globalPos) const
    { return globalPos[0] > this->gridGeometry().bBoxMax()[0] - eps_; }

    bool onLowerBoundary_(const GlobalPosition &globalPos) const
    { return globalPos[1] < this->gridGeometry().bBoxMin()[1] + eps_; }

    bool onUpperBoundary_(const GlobalPosition &globalPos) const
    { return globalPos[1] > this->gridGeometry().bBoxMax()[1] - eps_; }

    std::shared_ptr<CouplingManager> couplingManager_;
    Scalar P_;
    static constexpr Scalar eps_ = 1e-7;
    std::string problemName_;
    std::vector<PrimaryVariables> initialValues_;

};

} //end namespace Dumux

#endif
