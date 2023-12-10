

add_executable(TestVebTreeWithHashMapInsertAndDelete TestVebTreeWithHashMapInsertAndDelete.cpp)
target_link_libraries(TestVebTreeWithHashMapInsertAndDelete PUBLIC HashedVEBTree GTest::GTest)

target_include_directories(TestVebTreeWithHashMapInsertAndDelete PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/HashedVEBTreeMap"
        )

add_executable(TestVebTreeWithHashMapSuccessorAndPredecessor TestVebTreeWithHashMapSuccessorAndPredecessor.cpp)
target_link_libraries(TestVebTreeWithHashMapSuccessorAndPredecessor
        PUBLIC HashedVEBTree GTest::GTest)

add_executable(TestVebTreeUtils TestVEBTreeUtils.cpp)
target_link_libraries(TestVebTreeUtils
        PUBLIC  HashedVEBTree GTest::GTest)
target_include_directories(TestVebTreeWithHashMapInsertAndDelete PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/HashedVEBTreeMap"
        )