.PHONY: build cppinstall test cpptest clean lint cpplint cppformat format gdb benchmark prof

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    RELEASE_TYPE = Debug
else
    RELEASE_TYPE = Release
endif

build: cppinstall
	mkdir -p build
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=../build/conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=$(RELEASE_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-G Ninja
	cd build && cmake --build .

cppinstall:
	pip install --upgrade pip
	pipx install --force conan
	conan profile detect --force
	pipx install --force ninja
	conan install . --build=missing --output-folder=build -s build_type=$(RELEASE_TYPE)

clean:
	@rm -rf build

test: cpptest

cpptest: build
	@cd build && ctest --output-on-failure

lint: cpplint

cpplint: build
	find src -type f \( -name '*.cpp' -o -name '*.hpp' \) | xargs run-clang-tidy -p build --
	find src -type f \( -name '*.cpp' -o -name '*.hpp' \) | xargs clang-format --dry-run --Werror

format: cppformat

cppformat:
	find src -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i
	run-clang-tidy -fix -j $(shell nproc 2>/dev/null || sysctl -n hw.ncpu) -p build

gdb:
	$(MAKE) build DEBUG=1
	cd build/bin && gdb poker_solver_benchmarking

benchmark: build 
	@echo "Running Poker Solver Benchmark..."
	@cp input.txt build/bin/input.txt || echo "Warning: input.txt not found!"
	@cd build/bin && ./poker_solver_benchmarking

prof: 
	@echo "Building Poker Solver with Profiling..."
	mkdir -p build
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=../build/conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DPROFILING=ON \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-G Ninja
	cd build && cmake --build .
	@echo "Running Poker Solver Benchmark with Profiling..."
	@cd build/bin && ./poker_solver_benchmarking
	@echo "Generating profiling report..."
	@cd build/bin && gprof poker_solver gmon.out > profile_report.txt
	@echo "Profiling complete. See build/bin/profile_report.txt"

perf:
	@echo "Building Poker Solver with Profiling..."
	mkdir -p build
	cd build && cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=../build/conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DPROFILING=ON \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-G Ninja
	cd build && cmake --build .
	@echo "Running Poker Solver Benchmark with Profiling using perf..."
	@cd build/bin && perf record --call-graph=dwarf -o perf.data ./poker_solver_benchmarking
	@echo "Generating perf report..."
	@cd build/bin &&  perf report --stdio --sort=overhead --percent-limit 5 > profile_report.txt
	@echo "Profiling complete. See build/bin/profile_report.txt"

