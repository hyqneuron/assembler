//===- llvm/Support/ErrorHandling.h - Callbacks for errors ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an API used to indicate error conditions.
// Callbacks can be registered for these errors through this API.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_ERRORHANDLING_H
#define LLVM_SUPPORT_ERRORHANDLING_H

#include "llvm/Support/Compiler.h"
#include "yasmx/Config/export.h"
#include <string>

namespace llvm {
  class Twine;

  /// An error handler callback.
  typedef void (*llvm_error_handler_t)(const std::string& reason);

  /// Installs a new error handler: this function will be called whenever a
  /// serious error is encountered by LLVM.
  /// If you are using llvm_start_multithreaded, you should register the handler
  /// before doing that.
  ///
  /// If no error handler is installed the default is to print the error message
  /// to stderr, and call exit(1).
  /// If an error handler is installed then it is the handler's responsibility
  /// to log the message, it will no longer be printed to stderr.
  /// If the error handler returns, then exit(1) will be called.
  YASM_LIB_EXPORT
  void llvm_install_error_handler(llvm_error_handler_t handler);

  /// Restores default error handling behaviour.
  /// This must not be called between llvm_start_multithreaded() and
  /// llvm_stop_multithreaded().
  YASM_LIB_EXPORT
  void llvm_remove_error_handler(void);

  /// Reports a serious error, calling any installed error handler.
  /// If no error handler is installed the default is to print the message to
  /// standard error, followed by a newline.
  /// After the error handler is called this function will call exit(1), it 
  /// does not return.
  YASM_LIB_EXPORT
  void llvm_report_error(const char *reason) NORETURN;
  YASM_LIB_EXPORT
  void llvm_report_error(const std::string &reason) NORETURN;
  YASM_LIB_EXPORT
  void llvm_report_error(const Twine &reason) NORETURN;

  /// This function calls abort(), and prints the optional message to stderr.
  /// Use the llvm_unreachable macro (that adds location info), instead of
  /// calling this function directly.
  YASM_LIB_EXPORT
  void llvm_unreachable_internal(const char *msg=0, const char *file=0,
                                 unsigned line=0) NORETURN;
}

/// Prints the message and location info to stderr in !NDEBUG builds.
/// In NDEBUG mode it only prints "UNREACHABLE executed".
/// Use this instead of assert(0), so that the compiler knows this path
/// is not reachable even for NDEBUG builds.
#ifndef NDEBUG
#define llvm_unreachable(msg) llvm_unreachable_internal(msg, __FILE__, __LINE__)
#else
#define llvm_unreachable(msg) llvm_unreachable_internal()
#endif

#endif
