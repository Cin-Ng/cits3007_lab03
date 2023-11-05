
# info gcc
#
#'-fstack-clash-protection'
#     Generate code to prevent stack clash style attacks.  When this
#     ...
#
#     NOTE: In Ubuntu 19.10 and later versions,
#     '-fstack-clash-protection' is enabled by default for C, C++, ObjC,
#     ObjC++, unless '-fno-stack-clash-protection' is found.

CC = gcc

CFLAGS = -pedantic -Wall -Wextra -g -O0

BINARIES = makepath labmakepath

all: $(BINARIES)

# each binary is built from an .o file
$(foreach binary,$(BINARIES),$(eval $(binary): $(binary).o))

# each .o file is a target
$(foreach binary,$(BINARIES),$(eval $(binary).o:))

all: $(BINARIES)

clean:
	-rm $(BINARIES) *.o
