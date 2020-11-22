#ifndef RLC_CIRCUITCORE_HPP
#define RLC_CIRCUITCORE_HPP

// TODO: This define should be done via compile flags
#define VHLS_FP

#ifdef VHLS_FP

    #include <ap_fixed.h> // include Xilinx Vivado HLS's ap_fixed definitions

    #define FP_WORD_SIZE 64 // Word size of fixed point real type in bits
    #define FP_INT_SIZE 24  // Integral size of fixed point real type in bits
    #define FP_FRAC_SIZE (FP_WORD_SIZE-FP_INT_SIZE) // Fractional size of fixed point real type in bits

    typedef ap_fixed<FP_WORD_SIZE, FP_INT_SIZE, AP_RND> real;

#else

    typedef double real;

#endif

    void RLC_Circuit_solverCore(
        real x_out[2],
        real *l_current_ind
    );

#endif
