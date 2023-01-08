#ifndef PATHLIB_ANNOTATIONS_HPP
#define PATHLIB_ANNOTATIONS_HPP

namespace pathlib {

/// Wrap the __has_cpp_attribute so it evaluates to a false-y value on compilers
/// that do not define it.
///
/// See:
/// https://isocpp.org/std/standing-documents/sd-6-sg10-feature-test-recommendations#testing-for-the-presence-of-an-attribute-__has_cpp_attribute
#if defined(__has_cpp_attribute)
// NOLINTNEXTLINE: Not possible with a constexpr function
#define HAS_CPP_ATTRIBUTE(attrname) __has_cpp_attribute(attrname)
#else
#define HAS_CPP_ATTRIBUTE(attrname) 0
#endif

#if HAS_CPP_ATTRIBUTE(nodiscard)
#define PATHLIB_NODISCARD [[nodiscard]]
#else
#define PATHLIB_NODISCARD
#endif

#if HAS_CPP_ATTRIBUTE(noreturn)
#define PATHLIB_NORETURN [[noreturn]]
#else
#define PATHLIB_NORETURN
#endif

} // namespace pathlib

#endif // PATHLIB_ANNOTATIONS_HPP
