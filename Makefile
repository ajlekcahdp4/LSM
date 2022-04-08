CC = gcc
SRC_PATH = sources/
DEBUG = -g

all: MAIN_T LSM_T SLE_T
	./bash_scripts/mkdir.sh data
	$(CC) $(DEBUG) temps/main.o temps/lsm.o temps/SLE.o -lm -o run
	rm -rf temps
MAIN_T:
	./bash_scripts/mkdir.sh temps
	$(CC) -c $(DEBUG) $(SRC_PATH)main.c -o temps/main.o
LSM_T:
	$(CC) -c $(DEBUG) $(SRC_PATH)lsm/lsm.c -o temps/lsm.o
SLE_T:
	$(CC) -c $(DEBUG) $(SRC_PATH)SLE/SLE.c -o temps/SLE.o
clean:
	rm -rf *.o *.out temps run
clean_data:
	rm -rf *.res *.dat data/*
