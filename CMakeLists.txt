# CMakeList.txt: проект CMake для CalcCPP; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CalcCPP2 "CalcCPP.cpp" "Token_stream.h" "Token_stream.cpp" "Token.h" "functions.h" "functions.cpp" "std_lib_facilities.h" "Roman.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CalcCPP2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
