
/*
 * Author
 *   David Blom, TU Delft. All rights reserved.
 */

#pragma once

#include "TubeFlowLinearizedSolidSolver.H"
#include "SDCFsiSolverInterface.H"

namespace tubeflow
{
    class SDCTubeFlowBDFLinearizedSolidSolver : public TubeFlowLinearizedSolidSolver, public sdc::SDCFsiSolverInterface
    {
        public:
            SDCTubeFlowBDFLinearizedSolidSolver(
                int N,
                scalar nu,
                scalar rho,
                scalar h,
                scalar L,
                scalar dt,
                scalar G,
                scalar E0,
                scalar r0,
                scalar T,
                int timeOrder
                );

            virtual ~SDCTubeFlowBDFLinearizedSolidSolver();

            virtual void evaluateFunction(
                const int k,
                const fsi::vector & q,
                const scalar t,
                fsi::vector & f
                ) override;

            virtual void finalizeTimeStep() override;

            virtual int getDOF() override;

            virtual void getSolution(
                fsi::vector & solution,
                fsi::vector & f
                ) override;

            virtual void setSolution(
                const fsi::vector & solution,
                const fsi::vector & f
                ) override;

            virtual scalar getEndTime() override;

            virtual scalar getTimeStep() override;

            virtual void nextTimeStep() override;

            virtual void initTimeStep() override;

            virtual void setNumberOfImplicitStages( int k ) override;

            virtual void implicitSolve(
                bool corrector,
                const int k,
                const int kold,
                const scalar t,
                const scalar dt,
                const fsi::vector & qold,
                const fsi::vector & rhs,
                fsi::vector & f,
                fsi::vector & result
                ) override;

            virtual void prepareImplicitSolve(
                bool corrector,
                const int k,
                const int kold,
                const scalar t,
                const scalar dt,
                const fsi::vector & qold,
                const fsi::vector & rhs
                ) override;

            virtual void finalizeImplicitSolve( int k ) override;

            virtual void getVariablesInfo(
                std::deque<int> & dof,
                std::deque<bool> & enabled,
                std::deque<std::string> & names
                ) override;

        private:
            int k;

            std::deque<fsi::vector> uStages;
            std::deque<fsi::vector> rStages;
            std::deque<fsi::vector> unStages;
            std::deque<fsi::vector> rnStages;
    };
}
