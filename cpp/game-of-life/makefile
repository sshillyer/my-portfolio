#########################################################
# File: Makefile
# Author: Shawn Hillyer
#########################################################

CXX = g++

# -std=c++0x specifies to use a certain language version.
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

####################
### USER SECTION ###
####################

# SRCS
SRC1 = GameOfLife.cpp
SRC2 = Grid.cpp
SRC3 = Pattern.cpp
SRC4 = Point.cpp
SRC5 = GameClient.cpp
SRCS = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5}

# HEADERS
HEADER1 = Cell.hpp
HEADER2 = GameOfLife.hpp
HEADER3 = Grid.hpp
HEADER4 = Pattern.hpp
HEADER5 = Point.hpp
HEADERS = ${HEADER1} ${HEADER2} ${HEADER3} ${HEADER4} ${HEADER5}

# EXECUTABLES
PROG1 = GameClient
PROG2 =
PROG3 =
PROGS = ${PROG1} ${PROG2} ${PROG3}

# DOCUMENTS
DOC1 = shawn_hillyer_assignment1.pdf
DOCS = ${DOC1}

# COMPRESSED FILE
ZIP = cs162_assignment1_hillyers.zip

#####################
### BUILD SECTION ###
#####################

# make default
default:
	${CXX} ${SRCS} ${HEADERS} -o ${PROG1}

# make all
all:
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o ${PROG1}

# make zip
zip:
	zip ${ZIP} ${SRCS} ${HEADERS} ${DOC} makefile

# make clean
clean:
	rm -f ${PROGS} *.o *~
