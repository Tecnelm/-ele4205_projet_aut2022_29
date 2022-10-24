# ELE4205_Project 
 
[TOC]

This project has been realize in an educational context. 

The objectiv of this project is to realize and application composed by :
- Server : located on and SBC ([OdroidC2](https://www.hardkernel.com/shop/odroid-c2/))
- Client : located on the host computer


## Setup environnement 

To set up the environement execute the folowing command:
> git clone git@bitbucket.org:rgourdeau/ele4205_projet_aut2022_29.git 

Download poky odroid toolchain and install it.

You can also generate your toolchain with the build tool *Yocto* (folowing instruction in LAB[1])

:information_source: In case of non default path of pokytoolchain set **POKY_INSTALL_DIR** in your environement variable. 

> export POKY_INSTALL_DIR="path/to/poky/odroid"
     
structure of poky_install_dir :

    .
    ├── environment-setup-aarch64-poky-linux
    ├── site-config-aarch64-poky-linux
    ├── sysroots
    │   ├── aarch64-poky-linux
    │   │   ├── bin
    │   │   ├── boot
    │   │   ├── dev
    │   │   ├── etc
    │   │   ├── home
    │   │   ├── lib
    │   │   ├── media
    │   │   ├── mnt
    │   │   ├── proc
    │   │   ├── run
    │   │   ├── sbin
    │   │   ├── sys
    │   │   ├── tmp
    │   │   ├── usr
    │   │   └── var
    │   └── x86_64-pokysdk-linux
    │       ├── environment-setup.d
    │       ├── etc
    │       ├── lib
    │       ├── sbin
    │       ├── usr
    │       └── var
    └── version-aarch64-poky-linux


### Dependencies
- Opencv *2.4* on Client 
- Opencv *3.1* on Server 
- Poky-odroid-toolchain 
- cmake *MINIMUM VERSION 3.12*
- build-essential 

### Build
    
    bash
    cd ele4205_projet_aut2022_29
    cmake . -B build
    cmake --build build/
    
Executable will be located in `build/client/***` for the client.

Executable will be located in `build/server/ele4205_project` 