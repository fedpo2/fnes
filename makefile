##
# FNES
#
# @file
# @version 0.1

COMPILE: src/main.cpp
	g++ src/main.cpp -o bin/FNES -lraylib


run: src/main.cpp
	g++ src/main.cpp -o bin/fnes -lraylib
	./bin/fnes messi.nes

# end
