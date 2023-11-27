BIN_DIR    ?= build
BUILD_TYPE ?= Debug
BUILD_DIR  ?= $(BIN_DIR)/$(BUILD_TYPE)


all: build test gcov_report
.PHONY: all

configure:
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
.PHONY: configure

debug:   BUILD_TYPE = debug
release: BUILD_TYPE = release
build release debug s21_matrix_oop.a: configure	
	cmake --build $(BUILD_DIR)
.PHONY: build release debug

test:
	cmake --build $(BUILD_DIR) --target check
.PHONY: test

memcheck:
	cmake --build $(BUILD_DIR) --target memcheck
.PHONY: memcheck

gcov_report: configure
	cmake --build $(BUILD_DIR) --target coverage
.PHONY: gcov_report

clean:
	rm -rf $(BUILD_DIR)
fclean:
	rm -rf $(BIN_DIR)
.PHONY: clean fclean
