CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS=main.o controller.o display.o textdisplay.o graphicsdisplay.o window.o board.o player.o link.o cell.o download.o linkboost.o firewall.o scan.o polarize.o buff.o remove.o enrage.o
EXEC=RAIInet
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
.PHONYL: clean
clean:
	rm ${OBJECTS} ${EXEC}
