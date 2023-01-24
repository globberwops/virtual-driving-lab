#!/usr/bin/env bash
#
set -e

echo "Installing LLVM..."
apt-get -y purge --auto-remove clang-14

wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key 2>/dev/null | gpg --dearmor - >/usr/share/keyrings/llvm-snapshot-keyring.gpg

echo 'deb [signed-by=/usr/share/keyrings/llvm-snapshot-keyring.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy main' >/etc/apt/sources.list.d/llvm.list

apt-get update &&
  export DEBIAN_FRONTEND=noninteractive &&
  apt-get -y install --no-install-recommends \
    clang-16 \
    clang-format-16 \
    clang-tidy-16 \
    clangd-16
