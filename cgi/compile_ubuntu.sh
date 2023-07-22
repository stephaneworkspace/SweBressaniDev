#!/bin/sh
cmake .
make
cp ./SweInterfaceCgi ./bin/SweInterface.cgi
mv SweInterfaceCgi /usr/lib/cgi-bin/SweInterface.cgi
