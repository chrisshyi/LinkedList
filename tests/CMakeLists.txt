add_executable(tests tests.cpp)
target_include_directories(tests PUBLIC ../include)
target_compile_features(tests PUBLIC cxx_std_17)