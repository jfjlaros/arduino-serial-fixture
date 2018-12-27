EXEC := run_tests
MAIN := test_lib
TESTS := test_core test_extras
FIXTURES := ../src/Arduino


CC := g++


OBJS := $(addsuffix .o, $(TESTS) $(FIXTURES))

.PHONY: clean distclean


all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $(MAIN).cc $^

%.o: %.cc
	$(CC) -o $@ -c $<

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC)
