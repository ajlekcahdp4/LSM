#!/usr/bin/gnuplot
set terminal postscript eps enhanced color solid
set output "1.res.ps"
set style line 1 lc rgb "blue" lw 4
set style line 2 lc rgb "red" lw 4 ps 2
set grid xtics ytics
set title "graph"
set xlabel "ics(X)"
set ylabel "ygrik(Y)"
set xrange [0.9 * 1.000000 : 1.1 * 4.000000]
set yrange [0.9 * 1.200000 : 1.1 * 16.300000]
plot 5.060000 * x -5.050000 linestyle 1, "data/1.res" with points linestyle 2
