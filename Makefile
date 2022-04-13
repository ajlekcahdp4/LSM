CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC_PATH = sources/
DEBUG = -g

all: MAIN_T LSM_T SLE_T GNUPLOT_T
	$(CC) $(CFLAGS) $(DEBUG) temps/main.o temps/lsm.o temps/SLE.o temps/gnuplot.o -lm -o run
	rm -rf temps
MAIN_T:
	chmod +x $(SRC_PATH)scripts/mkdir.sh
	./$(SRC_PATH)scripts/mkdir.sh temps
	$(CC) -c $(CFLAGS) $(DEBUG) $(SRC_PATH)main.c -o temps/main.o
LSM_T:
	$(CC) -c $(CFLAGS) $(DEBUG) $(SRC_PATH)lsm/lsm.c -o temps/lsm.o
SLE_T:
	$(CC) -c $(CFLAGS) $(DEBUG) $(SRC_PATH)SLE/SLE.c -o temps/SLE.o
GNUPLOT_T:
	$(CC) -c $(CFLAGS) $(DEBUG) $(SRC_PATH)gnuplot/gnuplot.c -o temps/gnuplot.o
clean:
	rm -rf *.o *.out temps run vgcore.*
clean_data:
	rm -rf *.dat *.res /*.ps *.sh /*.png
