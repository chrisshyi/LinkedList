FLAGS = -std=c++17 -stdlib=libc++ -glldb
main: main.cpp linked_list.h
	clang++ $(FLAGS) -o main $< format.cc
clean:
	rm main