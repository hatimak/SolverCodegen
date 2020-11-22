# ==============================================================
# File generated on Sun Nov 22 01:23:53 CET 2020
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
# SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
# IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# ==============================================================
add_files -tb ../RLC_CircuitCore_tb.cpp -cflags { -Wno-unknown-pragmas}
add_files -tb ../DataLogger.hpp -cflags { -Wno-unknown-pragmas}
add_files FpgaRLCSolver/RLC_CircuitCore.hpp
add_files FpgaRLCSolver/RLC_CircuitCore.cpp
add_files FpgaRLCSolver/RLC_Circuit.hpp
set_part xc7vx485tffg1761-2
create_clock -name default -period 50ns
