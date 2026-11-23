CXX = g++
CXXFLAGS = -g -std=c++17
CLANG_FORMAT ?= clang-format
GCOV ?= gcov
GCOVR ?= gcovr
GTEST_LIBS ?= -lgtest_main -lgtest -pthread

STYLE_FILES := $(wildcard Include/*.h Sample/*.cpp Tests/*.cpp)
TEST_BINARY := Binary/MathLibTest
COVERAGE_DIR := coverage
COVERAGE_BINARY := $(COVERAGE_DIR)/MathLibTest
COVERAGE_REPORT_DIR := $(COVERAGE_DIR)/html
COVERAGE_HTML := $(COVERAGE_REPORT_DIR)/index.html

.PHONY: all clean coverage deb package-test release-package rpm sample style-check test

all:

deb:
	sh packaging/package.sh deb

rpm:
	sh packaging/package.sh rpm

release-package: deb rpm

package-test:
	sh Tests/PackageTest.sh

sample: Binary/Sample

Binary/Sample: $(wildcard Include/*.h) Sample/sample.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) Sample/sample.cpp -IInclude -o $@

$(TEST_BINARY): Tests/MathLibTest.cpp $(wildcard Include/*.h)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -IInclude Tests/MathLibTest.cpp $(GTEST_LIBS) -o $@

clean:
	rm -rf dist
	rm -f Binary/Sample $(TEST_BINARY) $(COVERAGE_BINARY) \
		$(COVERAGE_BINARY).gcda $(COVERAGE_BINARY).gcno
	rm -rf $(COVERAGE_REPORT_DIR)

style-check:
	@command -v $(CLANG_FORMAT) >/dev/null 2>&1 || { echo "Error: $(CLANG_FORMAT) is required for style-check" >&2; exit 127; }
	$(CLANG_FORMAT) --dry-run --Werror $(STYLE_FILES)

test: $(TEST_BINARY)
	./$(TEST_BINARY)

coverage:
	@command -v $(GCOVR) >/dev/null 2>&1 || { echo "Error: $(GCOVR) is required for HTML coverage reports" >&2; exit 127; }
	@command -v $(GCOV) >/dev/null 2>&1 || { echo "Error: $(GCOV) is required for coverage" >&2; exit 127; }
	rm -rf $(COVERAGE_REPORT_DIR)
	mkdir -p $(COVERAGE_DIR) $(COVERAGE_REPORT_DIR)
	rm -f $(COVERAGE_BINARY).gcda
	$(CXX) $(CXXFLAGS) --coverage -IInclude Tests/MathLibTest.cpp $(GTEST_LIBS) -o $(COVERAGE_BINARY)
	./$(COVERAGE_BINARY)
	$(GCOVR) --root . --filter 'Include/.*' --gcov-executable $(GCOV) \
		--html-details $(COVERAGE_HTML) --print-summary
