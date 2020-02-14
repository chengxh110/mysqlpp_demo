
include_directories(
  include
  /usr/include/mysql++/
  /usr/include/mysql
)
link_directories (/usr/lib)

ADD_EXECUTABLE(test1 demo1.cpp)
ADD_EXECUTABLE(test2 demo2.cpp)
ADD_EXECUTABLE(test3 demo3.cpp)
ADD_EXECUTABLE(test4 demo4.cpp)
ADD_EXECUTABLE(test5 demo5.cpp)

target_link_libraries (test1 mysqlpp mysqlclient)
target_link_libraries (test2 mysqlpp mysqlclient)
target_link_libraries (test3 mysqlpp mysqlclient)
target_link_libraries (test4 mysqlpp mysqlclient)
target_link_libraries (test5 mysqlpp mysqlclient)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)