project(emoji)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/android-emoji)

set(emoji_SRCS
    ${REPO_PATH}/EmojiFactory.cpp
)

add_definitions(-Wall -Werror)
add_library(emoji ${emoji_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(emoji PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(emoji
    cutils
    utils
    log
    dl pthread
)
target_include_directories(emoji
    PRIVATE
    ${LIBUTILS_INCLUDES}
    PUBLIC
    ${REPO_PATH}
)

install(TARGETS emoji DESTINATION ${ANDROID_LIB_DIR})
