CC = gcc

TEST_FLAGS =

H_FILES = e_lock.h

INSTALL_DIR = /usr/local/

.PHONY: install uninstall

test: $(H_FILES) tests.c
	gcc tests.c $(TEST_FLAGS) -o $@

install:
	mkdir -p $(INSTALL_DIR)/include
	sudo mv $(H_FILES) $(INSTALL_DIR)/include

uninstall:
	cd $(INSTALL_DIR/include && sudo rm -f $(H_FILES)
