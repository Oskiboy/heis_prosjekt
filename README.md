# Heisprosjekt

Repo for heisprosjekt 2019

## Docker

This project is configured so it can be built with Docker. To build you need to have Docker installed, then run:

```bash
docker build .
```

from the top directory of the project.

## Dependencies

To build install dependencies:

```bash
sudo apt install gcc \
clang \
curl \
zip \
make \
autoconf \
flex \
bison \
libtool
```

For this to compile you also need the [Comedilib library](https://github.com/Linux-Comedi/comedilib).
Download, and follow the instructions in the INSTALL file.

## Build

To build the project run the build script

```bash
make
```

To build unit tests run:

```bash
make tests
```

To build the documentation run:

```bash
make docs
```

## Unit tests

For unit tests we use the Unity test project.
To build follow the guide above.

## CI

This project is set up to be built on a Jenkins build server. There the Docker image will be used to build the code in a sterile environment.
