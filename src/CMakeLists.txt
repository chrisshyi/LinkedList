add_executable(main main.cpp format.cc)
target_include_directories(main PUBLIC ../include)
target_include_directories(main PUBLIC ../fmt)
target_compile_features(main PUBLIC cxx_std_17)