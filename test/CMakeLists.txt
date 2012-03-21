INCLUDE_DIRECTORIES(${PROJECT_LIB_DIR}/cxxtest)

LIST_FILES(test.headers TEST_HEADERS "test_*.h")

FOREACH(header ${TEST_HEADERS})
  MESSAGE("-- Test header: ${header}")
  STRING(REGEX REPLACE "\\.h$" ".cpp" source ${header})
  STRING(REGEX REPLACE "\\.h$" "" exe ${header})
  CXXTEST_ADD_TEST(${exe} ${source} ${CMAKE_CURRENT_SOURCE_DIR}/${header})
  SET_TARGET_PROPERTIES(${exe} PROPERTIES COMPILE_FLAGS "-Winvalid-pch -include ${PROJECT_PCH}")
  TARGET_LINK_LIBRARIES(${exe} ${PROJECT_LIB})
ENDFOREACH(header)
