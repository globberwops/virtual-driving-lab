#!/usr/bin/env bash
#
set -e

LLVM_VERSION=${1:-"none"}

if [ "${LLVM_VERSION}" = "none" ]; then
  echo "No LLVM version specified, skipping LLVM reinstallation"
  exit 0
fi

echo "Installing LLVM..."

wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key 2>/dev/null | gpg --dearmor - >/usr/share/keyrings/llvm-snapshot-keyring.gpg

echo 'deb [signed-by=/usr/share/keyrings/llvm-snapshot-keyring.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy main' >/etc/apt/sources.list.d/llvm.list

apt-get update &&
  export DEBIAN_FRONTEND=noninteractive &&
  apt-get -y install --no-install-recommends \
    clang-${LLVM_VERSION} \
    clang-format-${LLVM_VERSION} \
    clang-tidy-${LLVM_VERSION} \
    clangd-${LLVM_VERSION}
