ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    doxygen \
    g++-12 \
    gpg \
    graphviz \
    python3-pip \
    wget

COPY ./add-kitware-apt-repo.sh ./add-llvm-apt-repo.sh /tmp/

RUN chmod +x /tmp/add-kitware-apt-repo.sh /tmp/add-llvm-apt-repo.sh \
    && /tmp/add-kitware-apt-repo.sh \
    && /tmp/add-llvm-apt-repo.sh \
    && rm -f /tmp/add-kitware-apt-repo.sh /tmp/add-llvm-apt-repo.sh

RUN pip --no-cache-dir install cmakelang
