PROJECT(hkc-test)

FILE(GLOB hkc-test_SRCS
    devil.hpp
    devil.cpp
    main.cpp
    Task.h
    Task.cpp
    Node.h
    Sort.h
    Sort.cpp
    Robot.h
    Robot.cpp
    InfoCons.h
    InfoCons.cpp
    class.h
    createTree.cpp
    dealwithtask.cpp
    readyadvence.h
    readyadvence.cpp
)
SOURCE_GROUP("" FILES ${hkc-test_SRCS})

ADD_EXECUTABLE(hkc-test ${hkc-test_SRCS})

ADD_DEPENDENCIES(hkc-test frame utility)
TARGET_LINK_LIBRARIES(hkc-test frame utility ${Boost_LIBRARIES})
