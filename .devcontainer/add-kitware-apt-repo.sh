#!/usr/bin/env bash
#
set -e

echo "Installing CMake..."
apt-get -y purge --auto-remove cmake

wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - >/usr/share/keyrings/kitware-archive-keyring.gpg

echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' >/etc/apt/sources.list.d/kitware.list

apt-get update &&
  export DEBIAN_FRONTEND=noninteractive &&
  apt-get -y install --no-install-recommends \
    cmake
