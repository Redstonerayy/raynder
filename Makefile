.PHONY: build

build:
	mkdir -p build
	CXX=clang++ CC=clang cmake -B ./build -S . -G Ninja
	ninja -C ./build

run: build
	./build/raynder

clean:
	rm -rf ./build