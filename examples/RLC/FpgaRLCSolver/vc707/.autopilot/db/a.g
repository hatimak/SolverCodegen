#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /local-home/svg-hka/fzj/jugit/SolverCodegen/examples/RLC/FpgaRLCSolver/vc707/.autopilot/db/a.g.bc ${1+"$@"}
