FROM ubuntu:16.04
LABEL Author oskar.oestby@gmail.com

RUN apt-get update -qq && apt-get upgrade -qqy

RUN apt-get install -qy build-essential \
    gcc \
    git \
    cmake \
    make

WORKDIR /heis_lab
RUN cwd || ls -alt