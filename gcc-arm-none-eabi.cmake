set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          arm)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)

find_program(ARM_GCC arm-none-eabi-gcc)
if(NOT ARM_GCC)
  message(FATAL_ERROR "arm-none-eabi-gcc not in PATH")
endif()

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PREFIX                arm-none-eabi-)

set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

find_program(ARM_GCC ${CMAKE_C_COMPILER})
if(NOT ARM_GCC)
  message(FATAL_ERROR "${CMAKE_C_COMPILER} not in PATH")
endif()

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -fdata-sections -ffunction-sections")

set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--print-memory-usage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--verbose")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")

set(CMAKE_C_LINKER_FLAGS   "${CMAKE_C_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS}")

#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group")
#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")
