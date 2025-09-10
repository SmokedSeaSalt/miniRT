#!/bin/bash

# Exit on any error
set -e

#install cmocka
# Save the current directory
ORIG_DIR=$(pwd)

# Define installation directory
INSTALL_DIR="$HOME/local_libs"

# Create directory if it doesn't exist
mkdir -p "$INSTALL_DIR"
cd "$INSTALL_DIR"

#clone cmocka
if [ ! -d "cmocka" ]; then
    git clone https://git.cryptomilk.org/projects/cmocka.git
fi
cd cmocka

# Create and enter build directory
mkdir -p build
cd build

# Configure CMake for local installation
cmake -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" ..

#actually compile
make install
echo "CMocka installed in $INSTALL_DIR"

# Return to the original directory
cd "$ORIG_DIR"

#setup precommit hook
git config core.hooksPath tests/hooks