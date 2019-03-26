FROM ubuntu:16.04
LABEL Author oskar.oestby@gmail.com

RUN apt-get update -qq && apt-get upgrade -qqy \
&& apt-get install -qy \
gcc \
git \
clang \
curl \
zip \
make \
autoconf \
flex \
bison \
libtool && rm -rf /var/lib/apt/lists/*

RUN curl -JLO https://github.com/Linux-Comedi/comedilib/archive/master.zip && \
unzip comedilib-master.zip && \
cd /comedilib-master && \
echo "Starting Comedi configuration" &&\
./autogen.sh && \
./configure --with-udev-hotplug=/lib --sysconfdir=/etc && \
make && make install && \
cd .. && \
echo "Removing Comedi build remnants" && \
rm -rf comedilib-master comedilib-master.zip && \
echo "Build completed!"
WORKDIR /heis_lab