CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -lstdc++
TFLAGS=-Wall -Werror -Wextra -g -lstdc++ -lgtest -Wuninitialized
GCOV=--coverage
FLAG_COV = -lcheck -lgcov -fprofile-arcs --coverage



all: clean test install


.PHONY: test
test: calc_test credit_test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open report/index.html


.PHONY: clean
clean:
	rm -rf *.o *.dSYM *.a *.gcda *.gcno *.info
	rm -rf calc_test
	rm -rf credit_test
	rm -rf report
	rm -rf doxygen/html 
	rm -rf SMART_CALC.tar


.PHONY: install
install: 
	mkdir build
	cmake view -B build
	cmake --build Build
	make copy
	make run
	
.PHONY: copy
copy:
	cp -rf build/SMART_CALC.app $(HOME)/Desktop/SMART_CALC.app

.PHONY: run
run:
	open $(HOME)/Desktop/SMART_CALC.app

.PHONY: uninstall
uninstall: clean
	rm -rf build/SMART_CALC.app
	rm -rf build/CMakeFiles
	rm -rf build/Makefile
	rm -rf build/SMART_CALC_autogen
	rm -rf build/CMakeCache.txt
	rm -rf build/cmake_install.cmake
	rm -rf $(HOME)/Desktop/SMART_CALC.app
	rm -rf build

.PHONY: dvi
dvi:
	cd doxygen && chmod +x doxygen && ./doxygen Doxyfile && open html/index.html
	
.PHONY: dist
dist: 
	tar --totals -cvf SMART_CALC.tar build/SMART_CALC.app/Contents/MacOS/SMART_CALC


calc_test:
	$(CC) $(TFLAGS) $(GCOV) model/smart_calc.cc model/string_validation.cc model/tests/calc_model_tests.cc -o calc_test && ./calc_test
	
credit_test:
	$(CC) $(TFLAGS) $(GCOV) model/credit_calc.cc model/tests/credit_calc_tests.cc -o credit_test && ./credit_test	
