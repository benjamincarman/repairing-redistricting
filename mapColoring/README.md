# Map Coloring

#### **Model and Code Design by:** Benjamin Carman
#### **With Help and Supervision from:** Dr. Vardges Melkonian
#### *Designed and implemented as a part of tutorial studies in Operations Research*

## Description

### Overview
The code in this directory serves to automatically generate colored maps for a state given a set of districts and the counties chosen to be in them. It does this by first assigning colors to each district based on its party leanings. A reddish hue corresponds to a Republican-leaning district and a blueish hue corresponds to a Democrat-leaning district. It then takes a county's location and recursively colors all pixels within that county's bordered region in the image the color of its corresponding district using the OpenCV3 library.

## Usage

### Prerequisites
* CMake and an updated C++ compiler
* OpenCV3 for C++ installed

### Compiling and running mapColoring
Compiling and running this application could depend on your systems and its requirements. Ensure you have a C++ compiler, CMake, and OpenCV3 installed on your computer. Then run the following:

    cmake .
    make
    ./mapColoring <image> <county-locations> <district-choices> <blues> <reds> <leansDemocrat>

where:
* \<image\> is the state's map with each county colored white\
* \<county-locations\> is a list of each county with a pixel coordinate pair located inside that county
* \<district-choices\> is the output parameter 'c' of the AMPL model saying whether or not a county is in a given district
* \<blues\> is a list of RBG values of various blue hues
* \<reds\> is a list of RBG values of various red hues
* \<leansDemocrat\> is the output parameter 'leansDemocrat' of the AMPL model saying whether or not a given district has more Democrat voters

Doing the above will then display and save a colored state map based on the choice of districts.
