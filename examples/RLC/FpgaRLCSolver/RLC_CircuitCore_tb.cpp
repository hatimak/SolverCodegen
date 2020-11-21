
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "RLC_CircuitCore.hpp"
#include "DataLogger.hpp"

int simulateSystem();

int main() {
    return simulateSystem();
}

    //definition for the simulation function that uses the solver

int simulateSystem() {
#ifdef VHLS_FP

    std::cout << "Using Xilinx fixed point for real.\n"
              << "Word size: " << FP_WORD_SIZE << "\n"
              << "Integral size: " << FP_INT_SIZE << "\n"
              << "Fractional size: " << FP_FRAC_SIZE << "\n"
              << std::endl;

#else

    std::cout << "Using double precision floating point for real.\n" << std::endl;

#endif

    // simulation parameters -----------------------------------------------------------------------

    const static double DT = 50.0e-9;  //simulation time step length (s)
    const static double TFINAL = 0.15; //simulation final time (s)

    const static long NUM_STEPS = long(TFINAL/DT);
    const static long NUM_SYSTEM_SOLUTIONS = 2;
    const static long NUM_INTERNAL_SOLUTIONS = 1;
    const static long NUM_ANALOG_OUTPUTS = 0;
    const static long NUM_INPUTS = 0;
    const static long NUM_TIME_STEP = 1;
    const static long NUM_QUANTITIES = NUM_TIME_STEP + NUM_SYSTEM_SOLUTIONS + NUM_INTERNAL_SOLUTIONS + NUM_INPUTS + NUM_ANALOG_OUTPUTS;

    double time = 0.0;

    real x_out[2];
    real l_current_ind;

    const static std::string LOG_FILENAME = "RLC_CircuitCore_Results.csv";
    const static long NROWS = NUM_STEPS + 1;
    const static long NCOLUMNS = NUM_QUANTITIES;

    std::vector<std::string> LOG_HEADERS;
    LOG_HEADERS.push_back("Time (s)");

    LOG_HEADERS.push_back("x1");
    LOG_HEADERS.push_back("x2");

    LOG_HEADERS.push_back("Inductor current (A)");

    DataLogger<double> logger;

    try {
        logger.initializeByRowColumn(NROWS, NCOLUMNS);
    } catch(...) {
        std::cout << "Logger failed to initialize memory for samples.\n";

        return -1;
    }

    logger.fillCurrentRow(0.0); // Initialize first row to all zeros for time = 0

    std::cout << "Performing simulation... ";

    while(time < TFINAL) {
        time += DT;

        RLC_Circuit_solverCore(x_out, &l_current_ind);

        logger << time << x_out[0] << x_out[1] << l_current_ind;
    }
    std::cout << "done.\n";

    logger.dumpToTextFile(LOG_FILENAME,LOG_HEADERS);

    return 0;
}
