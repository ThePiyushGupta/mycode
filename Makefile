input="${wsf}/input.txt"
output="${wsf}/output.txt"
flags= -Wall -Wextra -g -std=c++17 -O2 -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
# flags = -W
flags2=-g -O2 -std=c++17 

ifeq ($(str),ha)
  flags=$(flags2)
endif

all:${name}
	$ time ./a.out <${input} >${output}  

${name}:${name}.cpp

	$ g++ ${flags} $^





