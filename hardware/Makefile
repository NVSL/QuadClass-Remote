TESTS=controller_board.test
DESIGN=controller_board
EAGLINT_HOME=../../Eagle-Lint/
RESOURCES_ROOT=../../QuadClass-Resources/
LBRS=$(wildcard ../../QuadClass-Quadcopter-Solution/lbr/*.lbr) $(wildcard lbr/*.lbr) $(wildcard $(RESOURCES_ROOT)/Eagle/lbr/*.lbr)
CHECKS=--check AtmegaChecker IMUChecker 
VERSION=v4-rev5-rc1
include ../../QuadClass-Quadcopter-Solution/Make.rules

STRIPPED=remote+pwr+ftdi+gim+lcd+IMU+tp.sch remote+pwr+ftdi+gim+lcd+IMU.sch remote+pwr+ftdi+gim+lcd.sch remote+pwr+ftdi+gim.sch remote+pwr+ftdi.sch remote+pwr.sch remote.sch

.PHONY: stripped
stripped:
	@echo You need to run strip_down.scr first, for this to work
	$(MAKE) $(subst .sch,.digikey-bom.csv,$(STRIPPED))
