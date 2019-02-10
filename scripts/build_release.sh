#! /bin/bash
#
# Build release version of the application.
#

# Check if qmake is in PATH
QMAKE_VER="$(qmake -v)"
if [[ -z "${QMAKE_VER}" ]]; then
  echo
  echo "ERROR: qmake is not found in PATH."
  echo "Find Qt installation and update your PATH like:"
  echo 'PATH=/home/user/Qt/5.10.0/gcc_64/bin:$PATH'
  echo 'and run this script again.'
  exit
else
  echo
  echo "${QMAKE_VER}"
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${SCRIPT_DIR}/..

# Create out dir if none
if [ ! -d out ]; then mkdir out; fi
cd out

echo
echo "Building..."
if [ -d BuildDir ]; then rm -rdf BuildDir; fi
mkdir BuildDir
cd BuildDir
qmake -config release ../../Adeptus.pro
make
