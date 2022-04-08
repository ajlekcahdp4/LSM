#! /usr/bin/gnuplot
set terminal postscript eps enhanced color solid
set output "result.ps"

set xlabel "X" 
set ylabel "Y"
set grid
set yrange [-1.1:1.1]
set xrange[-pi:pi]
set title "Gnuplot for habr" font "Helvetica Bold, 20"
plot exp(3*x + 2) title "sinux"  lc rgb "red"