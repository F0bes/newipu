EE_LIB= libnewipu.a
EE_OBJS = src/newipu.o
EE_INCS += -I./include


GIT_VERSION := "$(shell git describe --abbrev=6 --always --tags --dirty)"
EE_CXXFLAGS = -Wall -O3 -DGIT_VERSION="\"$(GIT_VERSION)\""

all: $(EE_LIB)
	make -C samples/csc all

clean:
	rm -f $(EE_OBJS) $(EE_LIB)
	make -C samples/csc clean

emu: $(EE_LIB)
	make -C samples/csc clean emu

run: $(EE_LIB)
	make -C samples/csc clean run

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.eeglobal
