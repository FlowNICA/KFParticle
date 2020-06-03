# KFParticle Package

## General information

The KF Partice package has been developed for the complete reconstruction of short-lived particles with their momentum, energy, mass, lifetime, decaylength, rapidity, etc.
This package is based on the Kalman filter method.

The KF Simple package is simplified version of the KF Partice package based on its mathematical apparatus.
At the current moment it is developed to reconstruct only one decay channel: $`\Lambda`$ $`\rightarrow`$ $`\pi^-`$ $`p^+`$.
In future KFPS can be developed for another decay channels.

## Pre-requirements

### Root

ROOT6 is needed for installation:

https://root.cern.ch/building-root

### Vc library

The KF Particle is SIMD'ized (vectorized) package. Vc library is needed for installation

https://github.com/VcDevel/Vc

    git clone https://github.com/VcDevel/Vc
    mkdir build install
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install -DBUILD_TESTING=OFF ..
    make -j
    make install
    
## Installation

    git clone git@git.cbm.gsi.de:pwg-c2f/analysis/KFParticle.git      //TODO after merge lubynets-simple into master!
    source /PATH_TO_ROOT6/bin/thisroot.sh
    export Vc_DIR=/VC_INSTALL_DIR/lib/cmake/Vc
    mkdir build install
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ../
    make -j
    make install