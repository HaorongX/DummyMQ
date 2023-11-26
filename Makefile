SUBDIRS = $(shell ls -d */)

all:
	for dir in $(SUBDIRS) ; do \
		cd $$dir && $(MAKE) -e HDIR=$(CURDIR); \
		cd ..; \
	done