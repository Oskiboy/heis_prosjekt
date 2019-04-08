FROM ubuntu:16.04
LABEL Author oskar.oestby@gmail.com

RUN apt-get update -qq && apt-get upgrade -qqy \
&& apt-get install -qy \
build-essential \
gcc \
git \
cmake \
clang \
make \
autoconf \
flex \
bison \
libtool && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/Linux-Comedi/comedilib.git && \
cd /comedilib && \
echo "Starting Comedi configuration" &&\
./autogen.sh && \
./configure --with-udev-hotplug=/lib --sysconfdir=/etc && \
make && make install && \
cd .. && \
echo "Removing Comedi build remnants" && \
rm -rf comedilib && \
echo "Build completed!"
WORKDIR /heis_lab