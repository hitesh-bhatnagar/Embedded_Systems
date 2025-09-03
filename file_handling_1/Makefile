CC = gcc
CFLAGS = -Wall
OBJ = main.o sensor.o logger.o

all: embedded_app

embedded_app: $(OBJ)
	$(CC) -o $@ $(OBJ)

main.o: main.c sensor.h logger.h
	$(CC) $(CFLAGS) -c main.c

sensor.o: sensor.c sensor.h
	$(CC) $(CFLAGS) -c sensor.c

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f *.o embedded_app  sensor_log.txt
