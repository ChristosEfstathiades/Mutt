add_library(mutt_lib App.cpp Tokenizer.cpp Generation.cpp Parser.cpp)
target_include_directories(mutt_lib PUBLIC ../include)