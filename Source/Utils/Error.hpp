#pragma once
#ifndef UTILS_ERROR_HPP
#define UTILS_ERROR_HPP

#include "../Core.hpp"

struct Error {
  enum struct Severity {
    Minor,
    Major,
    Critical,
  };

  Error::Severity severity;
  const Char8 *message;

  Error();
  constexpr Error(Error::Severity severity, const Char8 *message)
    : severity(severity), message(message){}
  Void Destroy();
};

struct ErrorBuffer {
  UInt64 space;
  UInt64 size;
  Error *buffer;

  ErrorBuffer(UInt64 space = 2);
  Void Destroy();
  Void Put(Error error);
  Void Flush();
};

#endif  // UTILS_ERROR_HPP
