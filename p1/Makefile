all: mydash-project

mydash-project:
	cd mydash-src; make

dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config > doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"

clean:   
	touch mydash
	rm -i mydash

test: mydash
	valgrind --leak-check=full  --suppressions=valgrind.supp ./mydash

