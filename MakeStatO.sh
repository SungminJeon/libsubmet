#!bin/bash



g++ -fPIC -c Stat.C

g++ -shared -o Stat.so Stat.o

rm Stat.o

