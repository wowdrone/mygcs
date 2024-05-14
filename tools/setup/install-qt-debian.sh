#!/usr/bin/env bash

# Set default variables
QT_VERSION="${QT_VERSION:-6.6.3}"
QT_PATH="${QT_PATH:-/opt/Qt}"
QT_HOST="${QT_HOST:-linux}"
QT_TARGET="${QT_TARGET:-desktop}"
QT_MODULES="${QT_MODULES:-qtcharts qtlocation qtpositioning qtspeech qt5compat qtmultimedia qtserialport qtimageformats qtshadertools qtconnectivity qtquick3d qtsensors}"

# Exit immediately if a command exits with a non-zero status
set -e

apt-get update
apt-get install python3 python3-pip -y
pip3 install aqtinstall
aqt install-qt ${QT_HOST} ${QT_TARGET} ${QT_VERSION} -O ${QT_PATH} -m ${QT_MODULES}
echo "Remember to export the following to your PATH: ${QT_PATH}/${QT_VERSION}/*/bin"
echo "export PATH=$(readlink -e ${QT_PATH}/${QT_VERSION}/*/bin/):PATH"
