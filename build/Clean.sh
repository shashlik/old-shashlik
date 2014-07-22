#!/bin/sh

# As a simple way to lessen the risk of invoking this in the wrong place:
# Don't invoke rm -r unless the previous rm's work.
rm -r CMakeFiles CMakeCache.txt && rm *.cmake Makefile && rm -r src
