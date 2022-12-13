#ifndef KC_DOCTOR_H
#define KC_DOCTOR_H

#include "Compiler.H"
#include "Location.H"

#include <stdexcept>

enum class DiagnosisSeverity {
    VERBOSE,
    MILD,
    MODERATE,
    SEVERE,
};

struct Diagnosis {
    DiagnosisSeverity Severity;
    CompilerModule Origin;
    Nat64 Description;
    Nat64 Prescription;
    const Sym8 *Note;

public:
    using OutOfRange = std::out_of_range;
    using InvalidArgument = std::invalid_argument;
};

class Doctor {
public:
    static
    Void Diagnose(const Sym8 *note);

    static
    Void Diagnose(DiagnosisSeverity severity, CompilerModule origin,
                  Nat64 description, Nat64 prescription,
                  const Sym8 *note);

};

#endif // KC_DOCTOR_H
