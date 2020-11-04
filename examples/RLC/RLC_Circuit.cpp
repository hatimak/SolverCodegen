#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

#include "RLC_Circuit.hpp"

#define DIV 100

int main() {
    const static double DT = 50.0e-9;
    const static double TFINAL = 0.15;

    const static long NUM_STEPS = long(TFINAL/DT);

    double time = 0.0;
    double x_sys[2];
    double x_int;

    long cntr = 0;

//    std::cout << "RLC Testbench using SolverCodegen\n";
//    std::cout << "Time step, x[0], x[1], inductor current\n";

    while(time < TFINAL) {
        time += DT;
        cntr += 1;

        RLC_Circuit_solver<0, double>(x_sys, &x_int);

        if (DIV == cntr) {
            cntr = 0;
            std::cout << time << ", "
                      << x_sys[0] << ", "
                      << x_sys[1] << ", "
                      << x_int
                      << "\n";
        }
    }

    return 0;
}
