#Makefile

all: prepare dependency build_binary run_tests

build_binary:
	cmake --build build/ -j

dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png

prepare:
	rm -rf build
	mkdir build
	mkdir build/boost_root

run_tests:
	./build/test/test_unit
	./build/test/test_unit2
