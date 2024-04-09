cmake_minimum_required(VERSION 3.28)

project(AK LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(AK)
configure_file(AK/Debug.h.in AK/Debug.h @ONLY)
target_include_directories(AK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(AK PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(AK PUBLIC -Wno-user-defined-literals)
target_compile_features(AK PUBLIC cxx_std_23)
target_sources(AK PUBLIC
  FILE_SET
    CXX_MODULES
  FILES
    AK/AK.cppm
    AK/IterationDecision.cppm
    AK/StdLibExtraDetails.cppm
    AK/StdLibExtras.cppm
    AK/Concepts.cppm
    AK/BitCast.cppm
    AK/Types.cppm
    AK/FloatingPoint.cppm
    AK/DefaultDelete.cppm
    AK/TypeCasts.cppm
    AK/SinglyLinkedListSizePolicy.cppm
    AK/Forward.cppm
    AK/Iterator.cppm
    AK/HashFunctions.cppm
    AK/StringHash.cppm
    AK/SipHash.cppm
    AK/ByteReader.cppm
    AK/Atomic.cppm
    AK/Singleton.cppm
    AK/Traits.cppm
    AK/TypedTransfer.cppm
    AK/NumericLimits.cppm
    AK/Checked.cppm
    AK/Kmalloc.cppm
    AK/Optional.cppm
    AK/Array.cppm
    AK/Span.cppm
    AK/Random.cppm
    AK/BuiltinWrappers.cppm
    AK/BigIntBase.cppm
    AK/Endian.cppm
    AK/Find.cppm
    AK/AllOf.cppm
    AK/AnyOf.cppm
    AK/StringUtils.cppm
    AK/StringView.cppm
    AK/CharacterTypes.cppm
    AK/TypeList.cppm
    AK/Variant.cppm
    AK/Error.cppm
    AK/CheckedFormatString.cppm
    AK/Format.cppm
    AK/Result.cppm
    AK/GenericLexer.cppm
    AK/IntegralMath.cppm
    AK/ReverseIterator.cppm
    AK/Vector.cppm
  FILE_SET
    HEADERS
  FILES
    AK/Assertions.h
    AK/Diagnostics.h
    AK/EnumBits.h
    AK/FormatMacros.h
    AK/Noncopyable.h
    AK/Platform.h
    AK/PublicMacros.h
    AK/Try.h
  FILES
    AK/SipHash.cpp
    AK/Kmalloc.cpp
    AK/Assertions.cpp
    AK/Random.cpp
    AK/Error.cpp
    AK/Format.cpp
    AK/GenericLexer.cpp
)

add_executable(Test test/test.cpp)
add_test(NAME Test COMMAND Test)
target_link_libraries(Test PUBLIC AK)
