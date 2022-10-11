
Pulse.o : Pulse.h Pulse.C
	  g++ -fPIC -c Pulse.C `root-config --libs` -I`root-config --incdir`

Event.o : Event.h Event.C
	  g++ -fPIC -c Event.C `root-config --libs` -I`root-config --incdir`

libsumet.so : Event.C Pulse.C
	      g++ -shared -o libsumet.so Stat.o Pulse.o Event.o  
