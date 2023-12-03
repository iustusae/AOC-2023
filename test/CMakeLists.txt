# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(tttTests LANGUAGES CXX)

# ---- Tests ----

add_executable(ttt_test source/ttt_test.cpp)
target_link_libraries(ttt_test PRIVATE ttt_lib)
target_compile_features(ttt_test PRIVATE cxx_std_20)

add_test(NAME ttt_test COMMAND ttt_test)

# ---- End-of-file commands ----

add_folders(Test)
