TARGETS = auxv-dumper

all: $(TARGETS)

.PHONY: clean

clean:
	rm -f $(TARGETS)

auxv-dumper: auxv-dumper.cpp
	clang++ -o $@ $^ -g -Wall -Wextra -std=c++20