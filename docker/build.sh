#!/bin/bash -ex

# The next two lines are commented out to ease the burden on the
# debian mirrors.
#
# apt-get update
# apt-get -y upgrade
apt-get -y install cmake git

git clone https://github.com/IkeLewis/zvalue

cd zvalue

cmake -DCMAKE_BUILD_TYPE="Debug" -G "Unix Makefiles"
make
# make install
make test
