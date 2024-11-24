.PHONY: build cppinstall test cpptest clean lint cpplint cppformat dependencies

RELEASE_TYPE = Release
CPP_SRC = src/cppsrc

# Build C++ Project
build: cppinstall
	mkdir -p build
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=$(RELEASE_TYPE)/generators/conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=$(RELEASE_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-G Ninja
	cd build && cmake --build .

# Install Conan
cppinstall:
	pip install --upgrade pip
	pipx install --force conan
	@if [ ! -f ~/.conan2/profiles/default ]; then \
		conan profile detect; \
	else \
		echo "Conan default profile already exists, skipping profile detection."; \
	fi
	pipx install --force ninja
	conan install . --build=missing

# Run all tests
test: cpptest

cpptest: build
	@cd build && ./intern_tests

clean:
	@rm -rf build

# Run all linting
lint: cpplint

cpplint: build
	run-clang-tidy -p build
	find src -name '*.cpp' -o -name '*.hpp' | xargs clang-format --dry-run --Werror

# Run all formatting
format: cppformat

# Format C++ code
cppformat:
	find src -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
	run-clang-tidy -fix -j $(shell nproc) -p build



format: cppformat

cppformat: build
	find $(CPP_SRC) -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
	run-clang-tidy -fix -j $(shell nproc) -p build

dependencies:
	# Ensure required tools are installed
	pip install --upgrade pip
	pipx install conan
	conan profile detect
	bash < .github/scripts/conan-profile.sh
	pipx install ninja
