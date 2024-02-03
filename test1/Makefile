# Automatically find all source files in the current directory
SOURCES:=$(wildcard *.c)

# Extract the first source file (assumes at least one source file exists)
FIRST_SOURCE:=$(firstword $(SOURCES))
# Extract the name of the program from the first source file
progname:=$(basename $(FIRST_SOURCE))

# Specify the compiler and compiler flags for C
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -g3

# Generate intermediate files
PREPROCS:=$(patsubst %.c,%.i,$(SOURCES))
ASSEMBLES:=$(patsubst %.c,%.s,$(SOURCES))
OBJS:=$(patsubst %.c,%.o,$(SOURCES))

# Find test input files
TEST_INPUTS:=$(wildcard test*.input)
# Generate test names based on input files
TESTS:=$(patsubst %.input,%,$(TEST_INPUTS))
# Corresponding expected output files
TEST_EXPECTED:=$(patsubst %.input,%.expected,$(TEST_INPUTS))

# Main target for building the program and running tests
all: $(progname) qa

# Target for building and running tests
qa: $(TESTS)

# Rule for building the executable from object files
$(progname): $(OBJS) | .gitignore
	$(CC) $(CFLAGS) $^ -o $@

# Rule for running tests
test%: $(progname)
	@if [ -f $@.input ]; then \
		./$< < $@.input > $@.output || echo "Negative $@..."; \
		if [ -f $@.expected ]; then \
			diff $@.output $@.expected && echo PASSED || echo FAILED; \
		else \
			echo "No expected output for $@, printing actual output:"; \
			cat $@.output; \
		fi; \
	else \
		echo "Test $@ skipped, input file missing"; \
	fi

# Rule for generating preprocessed source files
%.i: %.c
	$(CC) $(CFLAGS) -E $< -o $@

# Rule for generating assembly files
%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@

# Rule for generating object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create .gitignore file
.gitignore:
	echo $(progname) > .gitignore

# Clean up intermediate and generated files
clean:
	rm -rf *.i *.s *.o *.output .gitignore $(progname)

# Declare the generated files as precious (won't be deleted)
.PRECIOUS: $(PREPROCS) $(ASSEMBLES)
# Declare the generated files as secondary (won't trigger recompilation)
.SECONDARY: $(PREPROCS) $(ASSEMBLES)

