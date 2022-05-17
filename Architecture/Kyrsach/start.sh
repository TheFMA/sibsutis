#!/bin/bash
./Basic\ Translator/bin/main.exe program.vb data.sa
./Assembler\ Translator/bin/main.exe data.sa data.o
cp data.o Computer\ Simulator/bin/
cd Computer\ Simulator/bin
./main.exe
