#! /usr/bin/gnuplot
set terminal postscript eps enhanced color solid
set output "result.ps"

set xlabel "X" 
set ylabel "Y"
set grid
set yrange [-1.1:1.1]
set xrange[-pi:pi]
set title "Gnuplot for habr" font "Helvetica Bold, 20"
plot sin(x) title "sinux"  lc rgb "red", cos(x)  title "cosinus" lc rgb "green"