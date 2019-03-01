# Heisprosjekt

Repo for heisprosjekt 2019
## Dependencies
To build install dependencies:
```bash
sudo apt install cmake make build-essential git
```
and run the `build.sh` script.

## Build
To build the project run the build script
```bash
./build.sh
```

## Unit tests
For unit tests we use the Unity test project. Tests are built with the project and should be in the build folder.

## CI

This project is set up to be built on a Jenkins build server. There the Docker image will be used to build the code in a sterile environment. 
After successful builds the server will run all unit tests and report back to the repository with the build status.
