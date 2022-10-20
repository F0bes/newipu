EE_BIN = csc.elf
EE_OBJS = csc.o
EE_INCS += -I../../include
EE_LDFLAGS = -L../..
EE_LIBS = -lkernel -lnewipu -ldma -lgraph -ldraw
EE_CXXFLAGS = -O3

EE_DVP = dvp-as

EE_CFLAGS = -I$(shell pwd) -Werror -DGIT_VERSION="\"$(GIT_VERSION)\""

all: $(EE_BIN)

clean:
	rm -f $(EE_OBJS) $(EE_BIN)

run: $(EE_BIN)
	ps2client execee host:$(EE_BIN)

wsl: $(EE_BIN)
	$(PCSX2) --elf="$(shell wslpath -w $(shell pwd))/$(EE_BIN)"

emu: $(EE_BIN)
	$(PCSX2) --elf="$(shell pwd)/$(EE_BIN)"

reset:
	ps2client reset
	ps2client netdump

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
