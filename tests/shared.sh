#!/bin/sh
g++ -fPIC -g -finstrument-functions -c test.cpp ../tracer.cpp
g++ -c main.cpp
g++ -shared -o libtest.so test.o tracer.o
g++ -g -o main main.o  -ltest -L`pwd` -ldl