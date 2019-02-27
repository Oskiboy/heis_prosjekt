FROM ubuntu:16.04

RUN apt-get update && apt-get upgrade
RUN apt-get install npm