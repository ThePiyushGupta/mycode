input="${wsf}/input.txt"
output="${wsf}/output.txt"
flags= -Wall -Wextra -g -std=c++17 -O2 -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
# flags = -W
flags2= -std=c++2a

ifeq ($(str),ha)
  flags=$(flags2)
endif

all: ${name}.out
	$ timeout 5 ./${name}.out <${input} >${output}  

${name}.out :${name}.cpp

	$ g++ ${flags} -o ${name}.out $^





