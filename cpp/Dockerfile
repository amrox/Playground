ARG CMAKE_VERSION_MAJOR=3
ARG CMAKE_VERSION_MINOR=16
ARG CMAKE_VERSION_PATCH=2

FROM ubuntu:latest as builder
LABEL Name=playground-c Version=0.0.1
RUN apt-get -y update \
    && apt-get install -y \
        build-essential \
        clang \
        curl \
        git \
        openssl

ARG CMAKE_VERSION_MAJOR
ARG CMAKE_VERSION_MINOR
ARG CMAKE_VERSION_PATCH
ENV CMAKE_VERSION=$CMAKE_VERSION_MAJOR.$CMAKE_VERSION_MINOR.$CMAKE_VERSION_PATCH
ENV CMAKE_VERSION_SHORT=$CMAKE_VERSION_MAJOR.$CMAKE_VERSION_MINOR

WORKDIR /build/cmake
RUN curl -O https://cmake.org/files/v${CMAKE_VERSION_SHORT}/cmake-${CMAKE_VERSION}-Linux-x86_64.sh && \
    yes | sh cmake-${CMAKE_VERSION}-Linux-x86_64.sh && \
    mkdir -p /opt/cmake && \
    cp -R cmake-${CMAKE_VERSION}-Linux-x86_64/* /opt/cmake/

###

FROM builder
COPY . /work/src
WORKDIR /work/build
RUN /opt/cmake/bin/cmake ../src/ && make
CMD /opt/cmake/bin/ctest
