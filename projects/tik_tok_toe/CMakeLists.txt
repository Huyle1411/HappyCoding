cmake_minimum_required(VERSION 3.5)

project(tik_tok_toe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set( project_sources
#   main.cpp
#   Board.cpp
#)
set(SOURCE
   main.cpp
   controller/gameplay.cpp
   ui/userinterface.cpp
   ui/board.cpp
)
set(HEADERS
    common/singleton.h
    common/myTypeDef.h
    controller/gameplay.h
    ui/userinterface.h
    ui/board.h
)

add_executable(${PROJECT_NAME}
  ${SOURCE}
  ${HEADERS}
)
#add_executable(tik_tok_toe main.cpp
