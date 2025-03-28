CC = gcc

# TEST
TEST_FLAGS = -g

# LIB

LIB_NAME = elock

# INSTALL

H_FILES = elock.h
INSTALL_DIR = /usr/local

# -----------------------------------------------------------------------------

.PHONY: install uninstall clean

all:

test: $(H_FILES) tests.c
	gcc tests.c $(TEST_FLAGS) -o $@

install:
	sudo mkdir -p $(INSTALL_DIR)/include/$(LIB_NAME)
	sudo cp $(H_FILES) $(INSTALL_DIR)/include/$(LIB_NAME)

uninstall:
	sudo rm -rf $(INSTALL_DIR)/include/$(LIB_NAME)

clean:
	rm -f test
