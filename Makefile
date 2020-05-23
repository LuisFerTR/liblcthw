CC=gcc
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=$(OPTLIBS)

SRC_DIR=./src
BUILD_DIR=./build
TESTS_DIR=./tests

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SOURCES=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c, %.out,$(TEST_SOURCES))

TARGET=$(BUILD_DIR)/liblcthw.a

all: target tests

target: build $(TARGET) 

$(TARGET): CFLAGS += -fPIC
$(TARGET): $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(TESTS_DIR)/%.out: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $< $(TARGET) -o $@ $(LIBS)

.PHONY: tests
tests: LDLIBS += $(TARGET)
tests: $(TESTS) 
	sh ./tests/runtests.sh

build:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TESTS_DIR)

clean:
	rm -rf $(BUILD_DIR) || true
	rm $(OBJECTS) || true
	rm $(TESTS) || true