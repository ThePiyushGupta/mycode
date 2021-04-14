set title "Network Savings"
set term postscript eps enhanced color
set output "idk.eps"

# A method suggested by Hans-Bernhard Broeker
# <broeker@physik.rwth-aachen.de>: display a separate parametric
# surface for each fence.
set zrange [20:90]
unset label
unset arrow
set xrange [2:20]; set yrange [0:3000]
# set arrow from 5,-5,-1.2 to 5,5,-1.2 lt -1
# set label 1 "increasing v" at 6,0,-1
# set arrow from 5,6,-1 to 5,5,-1 lt -1
# set label 2 "u=0" at 5,6.5,-1
# set arrow from 5,6,sinc(5,5) to 5,5,sinc(5,5) lt -1
# set label 3 "u=1" at 5,6.5,sinc(5,5)
# set parametric
set hidden3d offset 0	# front/back coloring makes no sense for fenceplot #
# set isosamples 2,33

splot "output2.txt"  u 1:2:3 with lines title "Network Saving"

