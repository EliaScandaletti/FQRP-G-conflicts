
CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -Wextra -Werror -g

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
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $? $(LOADLIBES) $(LDLIBS) -o $@


$(OBJECTS): obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $? -o $@
