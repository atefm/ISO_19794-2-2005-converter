# ISO_19794-2-2005-converter
A simple tool to convert ISO 19794-2 fingerprint minutiae template to the following text format:

width

height

n

x_0,y_0,theta_0

x_1,y_1,theta_1

.

.

.

x_n,y_n,theta_n

## Prequirement:
g++

cmake 3.5 minimum

## How to compile:
mkdir build

cd build

cmake ..

make

## Usage
./ISO_19794_2_2005_converter <fmd.ist> <fmd.txt>

where <fmd.ist> is the source file where fingerprint minutia data is in ISO/IEC 19794-2 2005 format

      <fmd.txt> is the output file where to fingerprint minutia data is written in text format
