
CXXFLAGS = -Iinclude -Wall -Wextra -Werror -g
LDFLAGS = -Iinclude

SRCDIR = src
SOURCES = $(shell find $(SRCDIR)/ -type f -name *.cpp)

OBJDIR = obj
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

BINDIR = bin

all: $(BINDIR)/main

clean:
	@-rm -r $(OBJDIR)/
	@-rm -r $(BINDIR)/

$(BINDIR)/main: $(OBJECTS)
	@echo $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $? $(LOADLIBES) $(LDLIBS) -o $@


$(OBJECTS): obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $? -o $@
