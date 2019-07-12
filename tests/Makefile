EXEC := run_tests
MAIN := test_lib
TESTS := test_core test_extras
FIXTURES := ../src/Arduino


CC := g++


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES))

.PHONY: all check clean distclean


all: $(EXEC)

$(EXEC): $(MAIN).cc $(OBJS)
	$(CC) -o $@ $^

%.o: %.cc
	$(CC) -o $@ -c $<

check: all
	valgrind ./$(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
