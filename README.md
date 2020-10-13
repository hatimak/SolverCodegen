<img src="./ortis_logo_300dpi.png" width="300"/>

# ORTiS LB-LMC Solver C++ Code Generation Tools for Power Electronic System Real-Time Simulation

Copyright (C) 2019-2020 Matthew Milton and Others

C++ code generation tools for CPU or FPGA simulation solvers of nonlinear electrical and power electronic systems

These tools are part of the Open Real-Time Simulation (ORTiS) framework.

Utilizing these tools and FPGA High-Level Synthesis (HLS) tools, real-time simulation solvers of sizable power electronic systems executing on FPGA devices with 35 nanosecond simulation time steps are feasible.

Solvers generated by the tools utilize the Latency Based Linear Multi-step Compound (LB-LMC) simulation method to solve system models.

The tools include the LB-LMC C++ Solver Code Generation C++ Library along with a Command Line Interface (CLI) tool to allow creation of simulation solvers via either C++ programming or command shell environments.

## Requirements

These tools require C++14 or higher complaint compiler suite to build, such as GCC.

Besides the C++ standard library, the tools depend on the following third-party libaries to compile:

  * Eigen 3 -- Linear Algebra Template Library
http://eigen.tuxfamily.org/

Solvers generated by the tools are C++03 complaint and do not have any dependencies.

High Level Synthesis (HLS) of C++ solvers for FPGA execution is supported using Xilinx Vivado HLx suite for Xilinx FPGA devices.

## License

Solver C++ Code Generation Tools are licensed under the GNU General Public License (GPL) v3.0 (https://www.gnu.org/licenses/).

## Literature 
  
The solver code generation tools were first presented in:

* M. Milton and A. Benigni, "Software and Synthesis Development Libraries for Power Electronic System Real-Time Simulation," *2019 IEEE Electric Ship Technologies Symposium (ESTS)*, Arlington VA, 2019, pp. 368-376, Aug. 2019.
doi: 10.1109/ESTS.2019.8847940
url: https://ieeexplore.ieee.org/document/8847940

The code generation tools have been applied in the following recent work:

* M. Vygoder, M. Milton, J. Gudex, R. Cuzner, and A. Benigni, ``A Hardware-in-the-Loop Platform for DC Protection,'' IEEE Journal of Emerging and Selected Topics in Power Electronics, Aug. 2020, Early Access.
doi:  10.1109/JESTPE.2020.3017769
url: https://ieeexplore.ieee.org/document/9171341

* M. Vygoder, J. Gudex, R. Cuzner, M. Milton, and A. Benigni, ``Real Time Simulation of Transient Overvoltage and Common-Mode during Line-to-Ground Fault in DC Ungrounded Systems,'' IECON 2019 -- 45th Annual Conference of the IEEE Industrial Electronics Society, Lisbon, Portugal, 2019, pp. 6451-6456.
doi: 10.1109/IECON.2019.8927034
url: https://ieeexplore.ieee.org/document/8927034

* M. Milton, M. Vygoder, J. Gudex, R. Cuzner, and A. Benigni, ``Power Electronic System Real-Time Simulation on National Instruments FPGA Platforms,'' 2019 IEEE Electric Ship Technologies Symposium (ESTS), Arlington VA, 2019, pp. 32-38.
doi:  10.1109/ESTS.2019.8847934
url: https://ieeexplore.ieee.org/document/8847934
  
The LB-LMC simulation solver algorithm applied in generated solvers was first proposed in:  

 * A. Benigni and A. Monti, "A Parallel Approach to Real-Time Simulation of Power Electronics Systems," in *IEEE Transactions on Power Electronics*, vol. 30, no. 9, pp. 5192-5206, Sept. 2015.
doi: 10.1109/TPEL.2014.2361868
url: https://ieeexplore.ieee.org/document/6918539

FPGA execution of the LB-LMC solver algorithm is demonstrated in the following papers: 

* M. Milton, A. Benigni, and A. Monti, "Real-Time Multi-FPGA Simulation of Energy Conversion Systems," in IEEE Trans. Energy Conversion, vol. 34, no.4, pp. 2198-2208, Dec. 2019.
doi:  10.1109/TEC.2019.2938811
url: https://ieeexplore.ieee.org/document/8822485

* M. Difronzo, M. Milton, M. Davidson and A. Benigni, "Hardware-in-the-loop testing of high switching frequency power electronics converters," *2017 IEEE Electric Ship Technologies Symposium (ESTS)*, Arlington, VA, 2017, pp. 299-304.
doi: 10.1109/ESTS.2017.8069297
url: https://ieeexplore.ieee.org/document/8069297

 * M. Milton, A. Benigni and J. Bakos, "System-Level, FPGA-Based, Real-Time Simulation of Ship Power Systems," in *IEEE Transactions on Energy Conversion*, vol. 32, no. 2, pp. 737-747, June 2017.
doi: 10.1109/TEC.2017.2692525
url: https://ieeexplore.ieee.org/document/7894204
 
 * Milton, M. A.(2016). *A Comparison Of FPGA Implementation Of Latency-Based Solvers For Power Electronic System Real-Time Simulation*. (Master's thesis). Retrieved from https://scholarcommons.sc.edu/etd/3903

## Acknowledgements
* Matthew Milton - solver codegen tools creator and lead developer
* Andrea Benigni - original creator of the LB-LMC method
* Michele Difronzo - component model developer and software tester
* Dhiman Chowdhury - component model developer
* Mark Vygoder - component model developer and software tester



