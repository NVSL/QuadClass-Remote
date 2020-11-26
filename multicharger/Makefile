QUAD_CLASS_HOME?=../..
TESTS=multicharger-redux.test
DESIGN=multicharger-redux
EAGLINT_HOME=$(QUAD_CLASS_HOME)/QuadClass-QuadCMS/
RESOURCES_ROOT=$(QUAD_CLASS_HOME)/QuadClass-Resources/
LBRS=$(wildcard $(QUAD_CLASS_HOME)/QuadClass-Quadcopter-Solution/hardware/lbr/*.lbr) $(wildcard ../hardware/lbr/*.lbr) $(wildcard $(RESOURCES_ROOT)/Eagle/lbr/*.lbr)
CHECKS=--check EagleLint.BoardStyle.BoardLint EagleLint.SchematicStyle.SchematicLint
VERSION=v1-rev1-rc3
BOM_QTY=20

ASSEMBLY=yes

include $(RESOURCES_ROOT)/make/PCB.make
