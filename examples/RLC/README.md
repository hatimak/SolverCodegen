## RLC Circuit

### Offline C++ simulation
1. Compile simulation,
```bash
g++ -std=c++14 -Wall -Wextra -g -MP -MMD -c RLC_Circuit.cpp -o RLC_Circuit.o && g++ -o RLC_Circuit RLC_Circuit.o
```

2. Run simulaton,
```C++
./RLC_Circuit > sim_data.csv
```

3. Plot the simulation data, for instance, using Gnuplot,
```
plot "sim_data.csv" using 1:4 with linespoints title 'Inductor current'
```
![Inductor Current][./inductor_current.png]
