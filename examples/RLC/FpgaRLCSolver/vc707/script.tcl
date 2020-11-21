############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project FpgaRLCSolver
add_files FpgaRLCSolver/RLC_Circuit.hpp
add_files FpgaRLCSolver/RLC_CircuitCore.cpp
add_files FpgaRLCSolver/RLC_CircuitCore.hpp
open_solution "vc707"
set_part {xc7vx485tffg1761-2} -tool vivado
create_clock -period 50ns -name default
#source "./FpgaRLCSolver/vc707/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
