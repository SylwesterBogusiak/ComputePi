# ComputePi

# Calculate π

Pi value calculations with use different formulas.

The goal of this repository is to present a few algorithms that allow you to calculate π with a high level of precision.

In order to do this we use C language with math library and in some cases MPFR library is used. The MPFR library is open source project, and is dedicated when You use floating point numbers with lots of decimal places. Obviously the greater precision of number you use, the longer the calculation will take.

# Logic behind the calculation

Each of the presented algorithms are in single c file. Each of it has unique name.
To compile source code best to use GCC.

To run the app from terminal You need to add few parameters. For example number of iterations or precision as number of decimal places used to calculate the final value.

When increase the the number of iterations, the more loops the calculation is run. When precision is higher processor compute same iteration much longer.

# Algorithms used

Archimedes - CPIARCH - Compute Pi Archimedes algorithm.
Madhava-Gregory-Leibniz - CPILL1 - COMPUTE PI LONG LEIBNIZ V1 
Madhava-Gregory-Leibniz - CPILL2 - COMPUTE PI LONG LEIBNIZ V2
Machin - MLPI - MACHIN-LIKE PI
Euler's - CPISE - COMPUTE PI STANDARD EULER'S
Euler's - CPILE - COMPUTE PI LONG EULER'S
Madhava - CPILM - Compute Pi Long Madhava.

and for other Pi value related with Golden Ratio and Golden Phi number
FDSPHIPI algorithm - Four div by squared Phi - JAIN PI
FTSPHIPI algorithm - Four Times Squared phi - JAIN PI
FTSPHIPI2 algorithm - Four Times Squared phi - JAIN PI

extra
BRESPI - BRESENHAM AND PI CIRCLES IN COLOURS OF R G B - for testing the Pi values with drawing circles

# To do

Ramanujan-Sato
Chudnovsky
Bailey-Borwein-Plouffe
Gauss-Legendre

