FROM ubuntu:16.04
LABEL Author oskar.oestby@gmail.com

RUN apt-get update -qq && apt-get upgrade -qqy

RUN apt-get update && apt-get install -qy build-essential \
    gcc \
    clang \
    git \
    cmake \
    make \
    autoconf \
    swig \
    python \
    flex \
    byacc \
    bison \
    libtool

RUN git clone https://github.com/Linux-Comedi/comedilib.git
WORKDIR /comedilib
RUN ./autogen.sh
RUN ./configure --with-udev-hotplug=/lib --sysconfdir=/etc
RUN make && make install
WORKDIR /
RUN rm -rf comedilib
WORKDIR /heis_lab