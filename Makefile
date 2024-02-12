PKGS := ncurses

EXEC := example

OBJS := $(addprefix src/,main.o)

CFLAGS := -I./include `pkg-config --cflags $(PKGS)`
LDFLAGS := `pkg-config --libs $(PKGS)`

$(EXEC): $(OBJS) -lcurses
	cc $(LDFLAGS) -o $@ $^

-include $(OBJS:.o=.d)
 
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o
	gcc -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	@rm $(EXEC)
	@find -type f -name *.d -o -name *.o -exec rm {} \;
