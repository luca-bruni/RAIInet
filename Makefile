CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS=main.o controller.o display.o textdisplay.o
EXEC=RAIInet
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
.PHONYL: clean
clean:
	rm ${OBJECTS} ${EXEC}
