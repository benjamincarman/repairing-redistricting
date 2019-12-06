# Repairing Redistricting

#### **Model and Code Design by:** Benjamin Carman
#### **With Help and Supervision from:** Dr. Vardges Melkonian
#### *Designed and implemented as a part of tutorial studies in Operations Research*

## Description

### Overview

This repository contains a model written in AMPL to automate and optimize the process of Congressional redistricting. The corresponding model complete with data for the state of Ohio and solving commands can be found in this directory and are ready to be run using the solver Gurobi on the the NEOS servers found at https://neos-server.org/neos/solvers/lp:Gurobi/AMPL.html.

A full description of the model used to generate these districts can be found in the [report](repairingRedistricting.pdf).

The output of running this model for maximum distances 4, 5, and 6 with a leeway of 1 from the ideal proportion of districts leaning toward one party are the other can be found in [testsOhio](/testsOhio).

The code for coloring Ohio district maps using the model's output for district choices can be found in [mapColoring](/mapColoring).

The code for generating shortest distance data between counties in a state given adjacency information as required by the model can be found in [shortestDistances](/shortestDistances).
