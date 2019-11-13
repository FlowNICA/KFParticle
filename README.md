# KFParticle Simple Finder (KFPS)

## General information

KFSimple package is a simplified version of the KFParticle package. At the current moment it is developed to reconstruct only one decay channel: $`\Lambda`$ `\rightarrow` `\pi^-` `p^+`$.
KFP Simple is based on KFParticle Finder, it uses mathematical apparatus implemented in KFPF.
The basic idea and reconstruction algorithm also reproduce the "Usual" KFParticle Finder, but KFP Simple is free of overloading of too complicated procedure as in KFParticle Finder.
Also the advantage of KFPS is that reconstruction procedure is clear and under full control of user, almost in the "hand mode". It gives a possibility of detailed analysis of V0 reconstruction, in particular of decay parameters distributions in order to optomize selection criterias (cuts).

In future KFPS can be developed for another decay channels.

## Pre-requirements

### Root

ROOT6 is needed for installation:

https://root.cern.ch/building-root

### Vc library

KFParticle Finder is SIMD'ized (vectorized) package. Vc library is needed for installation

https://github.com/VcDevel/Vc

    export Vc_DIR=PATH_TO_YOUR_VC_DIR
    git clone https://github.com/VcDevel/Vc
    cd "$Vc_DIR"
    mkdir build install
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install -DBUILD_TESTING=OFF ..
    make -j
    make install
    
### KFParticle Finder

"Usual" KFParticle Finder is used in Simple package.

https://git.cbm.gsi.de/pwg-c2f/analysis/KFParticle

    git clone
    mkdir build install
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ../
    make -j
    make install                              TODO Fix this part
    
## Installation

### Interface

KFParticle Simple Interface provides universal objects for input information, output candidates and selection cuts.

                                              TODO Write the instruction after formation
                                              
### KFPSimple

                                              TODO Write the instruction after formation

## Run KFPSimple

You can run KFPSimple with macro ...TODO with input file situated in input directory.

    

