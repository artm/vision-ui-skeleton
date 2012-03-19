# artm's dev setup boilerplate

The goal of this is to automate my development practices so starting new
projects is an easy streamlined process.

# directory structure

- source root
  - main: main executable(s) will be built there
    - gui code that won't be tested goes here as well
  - cmake: cmake extensions, macros and scripts
  - ruby: ruby helpers and private libraries that aren't gems yet
  - lib: project specific libraries:
    - every project will have a static project library linked into main
      executable and tests
    - some dependencies may be placed under lib as git submodules
      - cxxtest
  - test: cxxtest based unit tests
  - vendor: bundler installs gems into vendor/bundle

# cmake

I use cmake as a basis for C/C++ build system. The boilerplate comes
with CMakeLists.txt in several directories setup in a particular way.

# C/C++

## Qt

Qt is used for GUIs.

Optional (?)

## OpenCV

Optional

## ffmpeg

Optional

# ruby

Ruby is used for high level automation tasks. setting up the right ruby
version is left out for now. on the mac platform I use rbenv to setup
ruby version.

## bundler

bundler is used for gem management.

## guard

guard is used for continuous testing and poor man's continuous
integration.

