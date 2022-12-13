#include "Doctor.H"

#include <iostream>

Void Doctor::Diagnose(const Sym8 *note) {
    std::cout << note << '\n';
}

Void Doctor::Diagnose(DiagnosisSeverity severity, CompilerModule origin,
                      Nat64 description, Nat64 prescription,
                      const Sym8 *note) {
    std::cout << note << '\n';
}
