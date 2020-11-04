## Switched RLC Circuit

### Netlist
![Circuit for netlist][./switched_circuit_netlist.png]

### Offline C++ simulation
1. Compile simulation,
```bash
g++ -std=c++14 -Wall -Wextra -g -MP -MMD -c switched_circuit.cpp -o switched_circuit.o && g++ -o switched_circuit switched_circuit.o
```

2. Run simulaton,
```C++
./switched_circuit > sim_data.csv
```

3. Plot the simulation data, for instance, using Gnuplot,
```
plot "sim_data.csv" using 1:3 with linespoints title 'Voltage across R', "sim_data.csv" using 1:4 with linespoints title 'Current through switch', "sim_data.csv" using 1:5 with linespoints title 'Switch state'
```
![Simulation plot][./switched_circuit.png]
