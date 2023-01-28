ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

LABEL org.opencontainers.image.source=https://github.com/globberwops/virtual-driving-lab
LABEL org.opencontainers.image.description="Dev Container"

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    doxygen \
    g++-12 \
    gpg \
    graphviz \
    python3-pip \
    wget

RUN pip --no-cache-dir install cmakelang

ARG REINSTALL_CMAKE_VERSION="none"
COPY ./reinstall-cmake.sh /tmp/
RUN if [ "${REINSTALL_CMAKE_VERSION}" != "none" ]; then \
    chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

ARG REINSTALL_NINJA_VERSION="none"
COPY ./reinstall-ninja.sh /tmp/
RUN if [ "${REINSTALL_NINJA_VERSION}" != "none" ]; then \
    chmod +x /tmp/reinstall-ninja.sh && /tmp/reinstall-ninja.sh ${REINSTALL_NINJA_VERSION}; \
    fi \
    && rm -f /tmp/reinstall-ninja.sh

ARG REINSTALL_LLVM_VERSION="none"
COPY ./reinstall-llvm.sh /tmp/
RUN if [ "${REINSTALL_LLVM_VERSION}" != "none" ]; then \
    chmod +x /tmp/reinstall-llvm.sh && /tmp/reinstall-llvm.sh ${REINSTALL_LLVM_VERSION}; \
    fi \
    && rm -f /tmp/reinstall-llvm.sh
