FROM ubuntu:16.04
LABEL Author oskar.oestby@gmail.com

RUN apt-get update -qq && apt-get upgrade -qy

RUN apt-get install -y build-essential \
    gcc \
    git \
    cmake \
    make 
