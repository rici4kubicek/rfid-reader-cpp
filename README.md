# RFID reader in Cpp

## Linux image for NanoPi Neo Core
Can be downloaded from http://download.friendlyarm.com/nanopineocore.

You must burn this image to uSD card. You can use some program, e.g. Etcher or Win32 Disk Imager
* default username: pi
* default password: pi

## Install WiringNP 
Log into your nano board via SSH, open a terminal and install the WiringNP library by running the following commands:
```
git clone https://github.com/friendlyarm/WiringNP
cd WiringNP/
chmod 755 build
./build
```
## How to build this repo
* install qmake on NanoPi Neo Core: ``` sudo apt-get install qt5-default ``` (take some time)
* install build essentials: ``` sudo apt-get install build-essential ``` 
* go to root directory of this repository
* run ``` qmake RFIDreader.pro ```, this create Makefile in root directory of this repo
* run ``` make ```

After processing the command, we are able to run the RFID reader at the root of the repository: ``` sudo ./RFIDreader ``` 
