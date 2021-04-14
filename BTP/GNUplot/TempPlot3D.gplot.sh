#how to run 
#gnuplot TempPlot3D.gplot.sh

set term postscript eps enhanced color
set output "Temp3D8x8.eps"
set xlabel "Processor X Direction"
set ylabel "Processor Y Direction"
#set zlabel "Instant Temperature"
set dgrid3d 8,8
#set hidden3d
set pm3d
splot "Data.txt"  u 1:2:3 with lines title "Network Saving"
