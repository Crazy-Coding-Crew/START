INCDIR    = include
SRCDIR    = src
OBJDIR    = obj
LIBDIR    = lib
BINDIR    = bin
ODBDIR    = odb
SCHEMADIR = $(ODBDIR)/schema

LIBFILE   = $(LIBDIR)/libDB.so
DATABASE  = pgsql

C++       = clang++
CXXFLAGS  = -std=c++11 -I$(INCDIR)/ -I$(ODBDIR)/ -fPIC
LDFLAGS   = -fPIC -shared
ODB       = odb
ODBFLAGS  = --hxx-suffix .h --ixx-suffix .icc --std c++11 --generate-schema --generate-query -I$(INCDIR)/

HLIST       = $(wildcard $(INCDIR)/*.h)
CXXLIST     = $(wildcard $(SRCDIR)/*.cxx)
ODB_HLIST   = $(subst $(INCDIR),$(ODBDIR),$(HLIST:.h=-odb.h))
ODB_CXXLIST = $(ODB_HLIST:.h=.cxx)
OBJLIST     = $(addprefix $(OBJDIR)/,$(notdir  $(ODB_CXXLIST:.cxx=.o) $(CXXLIST:.cxx=.o))) 

EXECUTABLES = bin/updateDB

.PHONY: all
all: $(LIBFILE) $(EXECUTABLES)

.SECONDARY:

$(LIBFILE): $(OBJLIST)
	@mkdir -p $(LIBDIR)
	@$(C++) $(LDFLAGS) -o $@ $^ 

$(OBJDIR)/%-odb.o: $(ODBDIR)/%-odb.cxx
	@mkdir -p $(OBJDIR)
	@$(C++) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx
	@mkdir -p $(OBJDIR)
	@$(C++) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%-odb.o: $(ODBDIR)/%-odb.cxx
	@mkdir -p $(OBJDIR)
	@$(C++) $(CXXFLAGS) -c $< -o $@

$(ODBDIR)/%-odb.cxx: $(HLIST)
	@mkdir -p $(ODBDIR)
	@mkdir -p $(SCHEMADIR)
	@$(ODB) -d $(DATABASE) $(ODBFLAGS) -o $(ODBDIR) $^
	@mv $(ODBDIR)/*.sql $(SCHEMADIR)

bin/updateDB: $(OBJLIST)
	@mkdir -p $(BINDIR)
	@$(C++) $(CXXFLAGS) -lboost_program_options -lodb-pgsql -lodb $^ -o $@

.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBDIR)
	@rm -rf $(BINDIR)
	@rm -rf $(ODBDIR)
	@rm -rf $(SCHEMADIR)

