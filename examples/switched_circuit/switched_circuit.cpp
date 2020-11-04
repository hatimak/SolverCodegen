#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

#include "switched_circuit.hpp"

#define DIV 10
#define SW_TIME 5500

int main() {
    const static double DT = 50.0e-9;
    const static double TFINAL = 0.0015;

    const static long NUM_STEPS = long(TFINAL/DT);

    double time = 0.0;
    double x_sys[2];
    double x_int;
    bool sw_state = false;

    long cntr = 0, sw_cntr = 0;

//    std::cout << "Switched Circuit Testbench using SolverCodegen\n";
//    std::cout << "Time step, x[0], x[1], switch current, switch state\n";

    while(time < TFINAL) {
        time += DT;
        cntr += 1;
        sw_cntr += 1;

        if (SW_TIME == sw_cntr) {
            sw_cntr = 0;
            sw_state = !sw_state;
        }

        switched_circuit_solver<0, double>(x_sys, &x_int, sw_state);

        if (DIV == cntr) {
            cntr = 0;
            std::cout << time << ", "
                      << x_sys[0] << ", "
                      << x_sys[1] << ", "
                      << x_int << ", "
                      << sw_state
                      << "\n";
        }
    }

    return 0;
}
