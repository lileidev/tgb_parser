clear

rm -f lexer.cpp lexer.h
rm -f parser.cpp parser.h location.hh
rm main

bison parser.y

flex lexer.l

# g++ main.cpp node.cpp codegen.cpp tokens.c parser.c -o parser -g -fsanitize=address -fno-omit-frame-pointer -I.. -I/usr/include/llvm-14 -I/usr/include/llvm-c-14/ `llvm-config --libs core native --cxxflags --ldflags`
g++ main.cpp parser.cpp lexer.cpp driver.cpp -L /usr/lib/x86_64-linux-gnu/ -lyaml-cpp -o main -g -fsanitize=address -fno-omit-frame-pointer

./main
