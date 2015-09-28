INCDIR    = include
SRCDIR    = src
OBJDIR    = obj
LIBDIR    = lib
ODBDIR    = odb
SCHEMADIR = $(ODBDIR)/schema

LIBFILE   = $(LIBDIR)/libDB.so
DATABASE  = pgsql

C++       = clang++-3.5
CXXFLAGS  = -std=c++11 -I$(INCDIR)/ -fPIC
LDFLAGS   = -fPIC -shared
ODB       = odb
ODBFLAGS  = --hxx-suffix .h --ixx-suffix .icc --std c++11 --generate-schema --generate-query -I$(INCDIR)/

HLIST       = $(wildcard $(INCDIR)/*.h)
CXXLIST     = $(wildcard $(SRCDIR)/*.cxx)
ODB_HLIST   = $(subst $(INCDIR),$(ODBDIR),$(HLIST:.h=-odb.h))
ODB_CXXLIST = $(ODB_HLIST:.h=.cxx)
OBJLIST     = $(addprefix $(OBJDIR)/,$(notdir $(CXXLIST:.cxx=.o) $(ODB_CXXLIST:.cxx=.o))) #$(addprefix $(OBJDIR)/,$(patsubst %.cxx,%.o,$(notdir $(CXXLIST))) $(patsubst %.cxx,%.o,$(notdir $(ODB_CXXLIST))))

.SECONDARY:

$(LIBFILE): $(OBJLIST)
	@mkdir -p $(LIBDIR)
	@$(C++) $(LDFLAGS) -o $@ $^ 

$(OBJDIR)/%-odb.o: $(ODBDIR)/%-odb.cxx ODB_FILES
	@mkdir -p $(OBJDIR)
	@$(C++) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx
	@mkdir -p $(OBJDIR)
	@$(C++) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

$(OBJDIR)/%-odb.o: $(ODBDIR)/%-odb.cxx
	@mkdir -p $(OBJDIR)
	@$(C++) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

$(ODBDIR)/%-odb.cxx: $(HLIST)
	@mkdir -p $(ODBDIR)
	@mkdir -p $(SCHEMADIR)
	@$(ODB) -d $(DATABASE) $(ODBFLAGS) -o $(ODBDIR) $^
	@mv $(ODBDIR)/*.sql $(SCHEMADIR)


.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBDIR)
	@rm -rf $(ODBDIR)
	@rm -rf $(SCHEMADIR)

