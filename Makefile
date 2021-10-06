MAKE_DIR = $(PWD)
CONFIG = $(shell mkdir build/; cd build; cmake ..; make -j)

STATE_DIR = /home/tim/Documents/dev/projet\ transverse/src/shared/state

.PHONY : all
all: clean configure build 
default_target = all

.PHONY : clean
clean : 
	@$(MAKE) -C src/shared/state -f state.mk clean
	-rm -r build

#créaction du répertoire build et compilation du cmake
.PHONY : configure
configure :
	$(CONFIG)

.PHONY : build
build : 
	@$(MAKE) -C src/shared/state -f state.mk build
