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
 * \brief A test problem for the coupled Stokes/Darcy problem (1p)
 */

#include <config.h>

#include <iostream>
#include <fstream>

#include <dune/common/parallel/mpihelper.hh>
#include <dune/common/timer.hh>


#include <dumux/common/initialize.hh>
#include <dumux/common/properties.hh>
#include <dumux/common/parameters.hh>
#include <dumux/common/dumuxmessage.hh>

#include <dumux/common/partial.hh>

#include <dumux/linear/istlsolvers.hh>
#include <dumux/linear/linearalgebratraits.hh>
#include <dumux/linear/linearsolvertraits.hh>

#include <dumux/io/grid/gridmanager_yasp.hh>

#include <dumux/assembly/fvassembler.hh>
#include <dumux/assembly/diffmethod.hh>
#include <dumux/discretization/method.hh>
#include <dumux/io/vtkoutputmodule.hh>



#include <dumux/multidomain/traits.hh>
#include <dumux/multidomain/fvgridgeometry.hh>
#include <dumux/multidomain/fvassembler.hh>
#include <dumux/multidomain/newtonsolver.hh>

#include "properties.hh"

int main(int argc, char** argv)
{
    using namespace Dumux;

    // maybe initialize MPI and/or multithreading backend
    Dumux::initialize(argc, argv);
    const auto& mpiHelper = Dune::MPIHelper::instance();

    // print dumux start message
    if (mpiHelper.rank() == 0)
        DumuxMessage::print(/*firstCall=*/true);


    // parse command line arguments and input file
    Parameters::init(argc, argv);

    // Define the sub problem type tags
    using TypeTag = Properties::TTag::PorousMediumFlowTwoP;
    using HTubeTypeTag = Properties::TTag::HTubeSub;
    using NodeTypeTag = Properties::TTag::NodeSub;

    // create two individual grids (from the given grid file or the input file)
    // for both sub-domains
    using HTubeGridManager = Dumux::GridManager<GetPropType<HTubeTypeTag, Properties::Grid>>;
    HTubeGridManager hTubeGridManager;
    hTubeGridManager.init("HTube"); // pass parameter group

    using NodeGridManager = Dumux::GridManager<GetPropType<NodeTypeTag, Properties::Grid>>;
    NodeGridManager nodeGridManager;
    nodeGridManager.init("Node"); // pass parameter group

    

    // we compute on the leaf grid view
    const auto& hTubeGridView = hTubeGridManager.grid().leafGridView();
    const auto& nodeGridView = nodeGridManager.grid().leafGridView();
     

    // create the finite volume grid geometry
    using HTubeFVGridGeometry = GetPropType<HTubeTypeTag, Properties::GridGeometry>;
    auto hTubeFvGridGeometry = std::make_shared<HTubeFVGridGeometry>(hTubeGridView);
    using NodeFVGridGeometry = GetPropType<NodeTypeTag, Properties::GridGeometry>;
    auto nodeFvGridGeometry = std::make_shared<NodeFVGridGeometry>(nodeGridView);
    

    // the mixed dimension type traits
    using Traits = MultiDomainTraits<HTubeTypeTag, NodeTypeTag>;
    constexpr auto domain0Idx = Traits::template SubDomain<0>::Index();
    constexpr auto domain1Idx = Traits::template SubDomain<1>::Index();


    // the coupling manager
    using CouplingManager = GetPropType<TypeTag, Properties::CouplingManager>;
    auto couplingManager = std::make_shared<CouplingManager>();

    // the problem (initial and boundary conditions)
    using HTubeProblem = GetPropType<HTubeTypeTag, Properties::Problem>;
    auto hTubeProblem = std::make_shared<HTubeProblem>(hTubeFvGridGeometry, couplingManager, "HTube");
    using NodeProblem = GetPropType<NodeTypeTag, Properties::Problem>;
    auto nodeProblem = std::make_shared<NodeProblem>(nodeFvGridGeometry, couplingManager, "Node");
    

    // the solution vector
    Traits::SolutionVector sol;
    sol[domain0Idx].resize(hTubeFvGridGeometry->numDofs());
    sol[domain1Idx].resize(nodeFvGridGeometry->numDofs());
    hTubeProblem->applyInitialSolution(sol[domain0Idx]);
    nodeProblem->applyInitialSolution(sol[domain1Idx]);
    auto oldSol = sol;

    // compute the coupling map
    couplingManager->init(hTubeProblem, nodeProblem, sol);

    // the grid variables
    using HTubeGridVariables = GetPropType<HTubeTypeTag, Properties::GridVariables>;
    auto hTubeGridVariables = std::make_shared<HTubeGridVariables>(hTubeProblem, hTubeFvGridGeometry);
    using NodeGridVariables = GetPropType<NodeTypeTag, Properties::GridVariables>;
    auto nodeGridVariables = std::make_shared<NodeGridVariables>(nodeProblem, nodeFvGridGeometry);
    hTubeGridVariables->init(sol[domain0Idx]);
    nodeGridVariables->init(sol[domain1Idx]);

    // get some time loop parameters
    using Scalar = Traits::Scalar;
    const auto tEnd = getParam<Scalar>("TimeLoop.TEnd");
    const auto maxDt = getParam<Scalar>("TimeLoop.MaxTimeStepSize");
    auto dt = getParam<Scalar>("TimeLoop.DtInitial");

    // initialize the vtk output module
    using SolutionVector0 = std::decay_t<decltype(sol[domain0Idx])>;
    VtkOutputModule<HTubeGridVariables, SolutionVector0> vtkWriter0(*hTubeGridVariables, sol[domain0Idx], hTubeProblem->name());
    GetPropType<HTubeTypeTag, Properties::IOFields>::initOutputModule(vtkWriter0);
    vtkWriter0.write(0.0);

    using SolutionVector1 = std::decay_t<decltype(sol[domain1Idx])>;
    VtkOutputModule<NodeGridVariables, SolutionVector1> vtkWriter1(*nodeGridVariables, sol[domain1Idx], nodeProblem->name());
    GetPropType<NodeTypeTag, Properties::IOFields>::initOutputModule(vtkWriter1);
    vtkWriter1.write(0.0);

    // instantiate time loop
    auto timeLoop = std::make_shared<TimeLoop<Scalar>>(0.0, dt, tEnd);
    timeLoop->setMaxTimeStepSize(maxDt);

    // the assembler with time loop for instationary problem
    using Assembler = MultiDomainFVAssembler<Traits, CouplingManager, DiffMethod::numeric>;
    auto assembler = std::make_shared<Assembler>(std::make_tuple(hTubeProblem, nodeProblem),
                                                 std::make_tuple(hTubeFvGridGeometry, nodeFvGridGeometry),
                                                 std::make_tuple(hTubeGridVariables, nodeGridVariables),
                                                 couplingManager, timeLoop, oldSol);

    // the linear solver
    using LinearSolver = ILUBiCGSTABIstlSolver<SeqLinearSolverTraits, LinearAlgebraTraitsFromAssembler<Assembler>>;
    auto linearSolver = std::make_shared<LinearSolver>();

    // the non-linear solver
    using NewtonSolver = MultiDomainNewtonSolver<Assembler, LinearSolver, CouplingManager>;
    NewtonSolver nonLinearSolver(assembler, linearSolver, couplingManager);

    // time loop
    timeLoop->start();
    while (!timeLoop->finished())
    {
        // solve the non-linear system with time step control
        nonLinearSolver.solve(sol, *timeLoop);

        // make the new solution the old solution
        oldSol = sol;
        hTubeGridVariables->advanceTimeStep();
        nodeGridVariables->advanceTimeStep();

        // advance the time loop to the next step
        timeLoop->advanceTimeStep();

        // write vtk output
        vtkWriter0.write(timeLoop->time());
        vtkWriter1.write(timeLoop->time());

        // report statistics of this time step
        timeLoop->reportTimeStep();

        // set new dt as suggested by newton controller
        timeLoop->setTimeStepSize(nonLinearSolver.suggestTimeStepSize(timeLoop->timeStepSize()));
    }

    timeLoop->finalize(mpiHelper.getCommunication());

    ////////////////////////////////////////////////////////////
    // finalize, print dumux message to say goodbye
    ////////////////////////////////////////////////////////////

    // print dumux end message
    if (mpiHelper.rank() == 0)
    {
        Parameters::print();
        DumuxMessage::print(/*firstCall=*/false);
    }

    return 0;
}
