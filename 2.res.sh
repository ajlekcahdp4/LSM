#! /usr/bin/gnuplot
set terminal png size 1200, 1000
set output "2.res.png"
set font "Times, 20"
set style line 1 lc rgb "blue" lw 4
set style line 2 lc rgb "red" lw 4 ps 3
set style line 3 lc rgb "black" lw 2
set grid xtics ytics
set xzeroaxis linestyle 3
set yzeroaxis linestyle 3
set xlabel "x" font "Times, 20"
set ylabel "y" font "Times, 20"
set xrange [0.700000 : 4.300000]
set yrange [-2.461260 : 59.725860]
plot exp (0.999702 * x) linestyle 1, "2.dat" with points linestyle 2 notitle
