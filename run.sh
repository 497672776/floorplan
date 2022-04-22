#!/bin/bash

cd build
rm -rf *
cmake ..
make
echo "**************************************************************************************"
#echo "The startpoint is: $1"
./solution ../resource/testcase/n100.hardblocks ../resource/testcase/n100.pl ../resource/testcase/n100.nets ../resource/output/n100_03.floorplan 0.3
echo "**************************************************************************************"
cd ..
