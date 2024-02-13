# PKGS to be included using pkg-config (optional)
#PKGS :=
PKGS := ncurses


# Executables
EXEC := example
TEST := "test_$(EXEC)"


# Object files
OBJS := $(addprefix src/,saske.o)
EXEC_OBJS := $(addprefix src/,main.o)
TEST_OBJS := $(addprefix test/,main.o test.o)


# Configs
CFLAGS := -Iinclude
LDFLAGS :=

ifneq ($(PKGS),)
	CFLAGS += $(shell pkg-config --cflags $(PKGS))
	LDFLAGS += $(shell pkg-config --libs $(PKGS))
endif

# Targets
all: $(EXEC) $(TEST)

$(EXEC): $(EXEC_OBJS) $(OBJS)
	cc -o $@ $^ $(LDFLAGS)

$(TEST): $(TEST_OBJS) $(OBJS)
	cc -o $@ $^ $(LDFLAGS)

-include $(OBJS:.o=.d)
-include $(EXEC_OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)
 
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o
	gcc -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	@rm $(EXEC) $(TEST)
	@find -type f -name *.d -o -name *.o -exec rm {} \;
