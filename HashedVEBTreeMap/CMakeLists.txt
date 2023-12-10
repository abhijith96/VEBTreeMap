
add_library(HashedVEBTree VEBTreeWithHashMap.cpp VEBTreeUtil.cpp IPAddress.cpp VEBTreeValueObject.cpp)
target_include_directories(HashedVEBTree
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )