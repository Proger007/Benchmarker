FROM ubuntu:24.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    lsb-release \
    gcc-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    build-essential \
    python3 \
    ninja-build \
    cmake \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*
