#ifndef _DOCTOR_HPP
#define _DOCTOR_HPP

#include "definitions.hpp"

namespace KC {

struct Location {
        const Sym *path;
        Nat64 index;
        struct Point {
                Nat64 row;
                Nat64 column;
        } start;
        Point end;
};

struct Diagnosis {
        Location location;
        const enum class Severity {
                MILD,
                MODERATE,
                SEVERE,
        } severity;
        const enum class Disease {
#include "diseases.defs"
        } disease;
        const Sym *note;
};

constexpr const Diagnosis TEMP_DIAGNOSIS = {
    .location =
        {
            .path = "/foo/bar/baz",
            .index = 0,
            .start =
                {
                    .row = 0,
                    .column = 0,
                },
            .end =
                {
                    .row = 0,
                    .column = 0,
                },
        },
    .severity = Diagnosis::Severity::SEVERE,
    .disease = Diagnosis::Disease::UNKNOWN_TOKEN,
};

} // namespace KC

#endif // _DOCTOR_HPP
