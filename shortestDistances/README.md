# Computing Shortest Distances

#### **Model and Code Design by:** Benjamin Carman
#### **With Help and Supervision from:** Dr. Vardges Melkonian
#### *Designed and implemented as a part of tutorial studies in Operations Research*

## Description

### Overview
This directory contains C++ code to compute the shortest distances between every pair of counties in a state. It does this by taking as an argument an adjacency matrix for the state like the one found in [shortestDistances.cc](/shortestDistances/shortestDistances.cc) where the entry is 1 if the corresponding pair of counties are adjacent and 0 if not. The code then uses Dijkstra's shortest path algorithm to compute the shortest distance between any pair of nodes where that distance is defined by the number of counties that must be passed through to reach the other county. It outputs these distances to stdout as a matrix and can be used to define the 'distances' parameter in the AMPL model.

## Usage

### Prerequisites
* A C++11 or newer compiler
* An adjacency matrix input file in the following example form:

                County1     County2     ...     CountyN
      County1      0           1        ...        0
      County2      1           0        ...        0
          .        .           .        ...        .
          .        .           .        ...        .
          .        .           .        ...        .
      CountyN      0           0        ...        1

### Compiling and running shortestDistances
Simply compile the code in shortestDistances.cc and run it using the adjacency matrix input file as a command line argument as in the following:

    g++ shortestDistances.cc
    ./a.out adjacencyMatrixOhio.txt
