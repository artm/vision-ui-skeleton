# artm's dev setup boilerplate

The goal of this is to automate my development practices so starting new
projects is an easy streamlined process.

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

## cucumber

Cucumber is used for behavior driven design. It is combined with ruby
naturally and with C++ / Qt unnaturally. In Qt-less C++ projects (no
GUI) cucumber calls out to c++ via ruby's popen or something like that.

## guard

guard is used for continuous testing and poor man's continuous
integration.

