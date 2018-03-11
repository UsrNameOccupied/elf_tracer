g++ -g -finstrument-functions -c test.cpp ../tracer.cpp
ar rcs libtest_.a test.o tracer.o
g++ -g -o main main.cpp -ltest_ -L`pwd` -ldl -rdynamic
