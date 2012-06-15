
VERSION   = 0.2.0
CXX 	 ?= g++
CXXFLAGS ?= -g -Wall
CXXFLAGS += -Iinclude/sanity -std=c++0x
prefix   ?= /usr/local

sanity_hdr 	= include/sanity/check.h \
			  include/sanity/compose.h \
			  include/sanity/defines.h \
			  include/sanity/exceptions.h \
			  include/sanity/trace.h

sanity_src  = src/check.cpp \
			  src/exceptions.cpp \
			  src/trace.cpp	

dist_files 	= $(sanity_hdr) \
			  $(sanity_srcs) \
		      Makefile \
			  README.txt \
			  COPYING.txt
				 				 
ifeq ($(MSYSTEM), MINGW32)
  EXEEXT=exe
  LIBEXT=dll
else
  EXEEXT=
  LIBEXT=so
endif

.PHONY: all clean install dist
.SUFFIXES: .o .cpp

all: bin/sanity.$(LIBEXT)
	
clean: 
	rm -f src/*.o src/*.d bin/sanity.$(LIBEXT) lib/libsanity.a

install: bin/sanity.$(LIBEXT)
	cp --parents $(sanity_hdr) $(prefix)
	cp --parents lib/libsanity.a $(prefix)
	cp --parents bin/sanity.$(LIBEXT) $(prefix)

uninstall:
	rm -r $(prefix)/include/sanity
	
dist:
	mkdir sanity-$(VERSION)
	cp --parents $(dist_files) sanity-$(VERSION)
	tar -czf sanity-$(VERSION).tar.gz sanity-$(VERSION)
	rm -r sanity-$(VERSION)
	
bin/sanity.$(LIBEXT): $(patsubst %.cpp, %.o, $(sanity_src))
	mkdir -p bin
	mkdir -p lib
	$(CXX) -shared -fPIC $(LDFLAGS) -Wl,--out-implib=$(patsubst bin/%.$(LIBEXT),lib/lib%.a, $@) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MD -c $< -o $(patsubst %.cpp, %.o, $<)

ifneq "$(MAKECMDGOALS)" "clean"
deps = $(patsubst %.cpp, %.d, $(sanity_src))
-include $(deps)
endif
