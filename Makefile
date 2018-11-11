input="/home/piyush/Desktop/competitveCoding/input.txt"
output="/home/piyush/Desktop/competitveCoding/output.txt"
flags=-Warray-bounds -std=c++17 -g

all:${name}
	$ ./${name} <${input} >${output} 


${name}:${name}.cpp
	$ g++ ${flags} -o $@ $^



