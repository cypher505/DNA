SUBDIRS := Testing

all: $(SUBDIRS) 

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

clean:
	$(MAKE) -C $(SUBDIRS) clean

