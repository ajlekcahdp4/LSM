#! /usr/bin/gnuplot
set terminal png size 1200, 900
set output "1.res.png"
set grid xtics ytics
set style line 1 lc rgb "blue" lw 4
set style line 2 lc rgb "red" lw 4 ps 2
set title "graph"
set xlabel "x"
set ylabel "y"
set xrange [-1.1 * 1.000000 : 1.1 * 4.000000]
set yrange [-1.1 * 1.000000 : 1.1 * 4.000000]
plot 1.000000 * x +0.000000 linestyle 1, "sources/gnuplot/1.dat" with points linestyle 2