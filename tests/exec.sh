g++ -g -finstrument-functions -c test.cpp ../tracer.cpp main.cpp
g++ -g -o main main.o  test.o tracer.o -ldl -rdynamic
