#include "RLC_Circuit.hpp"
#include "RLC_CircuitCore.hpp"


void RLC_Circuit_solverCore(real x_out[2], real *l_current_ind) {
    #pragma HLS ARRAY_PARTITION variable=x_out dim=1
    #pragma HLS INLINE RECURSIVE

    #pragma HLS latency min=0 max=0

    solver_region: {
        #pragma HLS protocol

        RLC_Circuit_solver<0, real>(x_out, l_current_ind);
    }
}
