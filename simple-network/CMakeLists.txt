# Set C++ flags to include debugging information
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Executables for simple_network
dumux_add_test(NAME simple_network
               SOURCES main.cc
               LABELS simp)

# Add a symlink for each input file
add_input_file_links()
dune_symlink_to_source_files(FILES "htubeinitialsolutioncc.txt")
dune_symlink_to_source_files(FILES "nodeinitialsolutioncc.txt")

