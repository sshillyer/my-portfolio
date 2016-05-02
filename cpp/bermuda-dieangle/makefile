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
SRC1 = GameClient.cpp
SRC2 = Menu.cpp
SRC3 = Player.cpp
SRC4 = Space.cpp
SRC5 = Cave.cpp
SRC6 = Ocean.cpp
SRC7 = Reef.cpp
SRC8 = Ship.cpp
SRC9 = Trench.cpp
SRC10 = Item.cpp
SRC11 = DivingBelt.cpp
SRC12 = Map.cpp
SRC13 = Direction.cpp
SRC14 = Flare.cpp
SRC15 = Flippers.cpp
SRC16 = BigTreasure.cpp
SRC17 = OxygenTank.cpp
SRC18 = RescueBeacon.cpp
SRC19 = UserInterface.cpp
SRCS = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7} ${SRC8} ${SRC9} ${SRC10} ${SRC11} ${SRC12} ${SRC13} ${SRC14} ${SRC15} ${SRC16} ${SRC17} ${SRC18} ${SRC19}

# HEADERS
HEADER1 = GameClient.hpp
HEADER2 = Menu.hpp
HEADER3 = Player.hpp
HEADER4 = Space.hpp
HEADER5 = Cave.hpp
HEADER6 = Ocean.hpp
HEADER7 = Reef.hpp
HEADER8 = Ship.hpp
HEADER9 = Trench.hpp
HEADER10 = Item.hpp
HEADER11 = DivingBelt.hpp
HEADER12 = Map.hpp
HEADER13 = Direction.hpp
HEADER14 = Flare.hpp
HEADER15 = Flippers.hpp
HEADER16 = BigTreasure.hpp
HEADER17 = OxygenTank.hpp
HEADER18 = RescueBeacon.hpp
HEADER19 = UserInterface.hpp
HEADERS = ${HEADER1} ${HEADER2} ${HEADER3} ${HEADER4} ${HEADER5} ${HEADER6} ${HEADER7} ${HEADER8} ${HEADER9} ${HEADER10} ${HEADER11}  ${HEADER12} ${HEADER13} ${HEADER14} ${HEADER15} ${HEADER16} ${HEADER17} ${HEADER18} ${HEADER19}

# EXECUTABLES
PROG1 = dive
PROG2 =
PROG3 =
PROGS = ${PROG1} ${PROG2} ${PROG3}

# DOCUMENTS
DOC1 = cs162_lab9_hillyers.pdf
DOC2 =
DOC3 =
DOC4 = readme.txt
DOC5 = main.menu
DOCS = ${DOC1} ${DOC2} ${DOC3} ${DOC4} ${DOC5}

# COMPRESSED FILE
ZIP = cs162_lab9_hillyers.zip

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
