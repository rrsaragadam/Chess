CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD -Werror=vla
EXEC = chess
OBJECTS = game.o move.o main.o display.o player.o human.o computer.o board.o square.o piece.o king.o queen.o bishop.o rook.o knight.o pawn.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

