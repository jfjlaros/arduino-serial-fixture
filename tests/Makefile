EXEC := run_tests
MAIN := test_lib
FIXTURES := ../src/Arduino


CC := g++
CC_ARGS := -Wno-pmf-conversions


OBJS := $(addsuffix .o, $(FIXTURES))

.PHONY: clean distclean


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $(MAIN).cc $(notdir $^)

%.o: %.cc
	$(CC) $(CC_ARGS) -c $<

clean:
	rm -f $(notdir $(OBJS))

distclean: clean
	rm -f $(EXEC)
