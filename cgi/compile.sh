#!/bin/sh
cmake .
make
cp ./SweInterfaceCgi ./bin/SweInterface.cgi
mv SweInterfaceCgi /Applications/MAMP/cgi-bin/SweInterface.cgi