QUAD_CLASS_HOME?=$(PWD)/..

SKETCH_BOOK=./firmware

.PHONY: setup
setup:
	(cd $(SKETCH_BOOK)/hardware/; git clone git@github.com:NVSL/QuadClass-Atmega128RFA-Arduino-Addon.git)

.PHONY:
setup-clean:
	rm -rf $(SKETCH_BOOK)/hardware/QuadClass*

