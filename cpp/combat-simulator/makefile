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
SRC1 = Client.cpp
SRC2 = Menu.cpp
SRC3 = Barbarian.cpp
SRC4 = BlueMen.cpp
SRC5 = Combat.cpp
SRC6 = Creature.cpp
SRC7 = Die.cpp
SRC8 = Goblin.cpp
SRC9 =
SRC10 = ReptilePeople.cpp
SRC11 = 
SRC12 = TheShadow.cpp
SRC13 = Tournament.cpp
SRCS = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7} ${SRC8} ${SRC9} ${SRC10} ${SRC11} ${SRC12} ${SRC13} ${SRC14}

# HEADERS
HEADER1 = Client.hpp
HEADER2 = Menu.hpp
HEADER3 = Barbarian.hpp
HEADER4 = BlueMen.hpp
HEADER5 = Combat.hpp
HEADER6 = Creature.hpp
HEADER7 = Die.hpp
HEADER8 = Goblin.hpp
HEADER9 = QueueList.hpp
HEADER10 = ReptilePeople.hpp
HEADER11 = StackList.hpp
HEADER12 = TheShadow.hpp
HEADER13 = Tournament.hpp
HEADERS = ${HEADER2} ${HEADER3} ${HEADER4} ${HEADER5} ${HEADER6} ${HEADER7} ${HEADER8} ${HEADER9} ${HEADER10} ${HEADER11}  ${HEADER12} ${HEADER13} ${HEADER14}

# EXECUTABLES
PROG1 = tournament
PROG2 =
PROG3 =
PROGS = ${PROG1} ${PROG2} ${PROG3}

# DOCUMENTS
DOC1 = cs162_assignment4_hillyers.pdf
DOC2 =
DOC3 =
DOC4 = readme.txt
DOC5 = main.menu
DOCS = ${DOC1} ${DOC2} ${DOC3} ${DOC4} ${DOC5}

# COMPRESSED FILE
ZIP = cs162_assignment4_hillyers.zip

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
	zip ${ZIP} ${SRCS} ${HEADERS} ${DOCS} makefile

# make clean
clean:
	rm -f ${PROGS} *.o *~
