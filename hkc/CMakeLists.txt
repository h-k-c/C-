PROJECT(emmmm)

FILE(GLOB emmmm_SRCS
    devil.hpp
    devil.cpp
    main.cpp
    Task.h
    Task.cpp
    Sort.h
    Sort.cpp
    Node.h
    Robot.h
    createTree.cpp
    Robot.cpp
    InfoCons.h
    InfoCons.cpp
    class.h
    readyadvence.h
    readyadvence.cpp
    Graph.h
    dealwithtask.cpp
    planwithtask.cpp
    planwithcons_not_info.cpp
    action.cpp
    Nature.h
    Nature.cpp
    Tasknum.h
    Tasknum.cpp
)
SOURCE_GROUP("" FILES ${emmmm_SRCS})

ADD_EXECUTABLE(emmmm ${emmmm_SRCS})

ADD_DEPENDENCIES(emmmm frame utility)
TARGET_LINK_LIBRARIES(emmmm frame utility ${Boost_LIBRARIES})
