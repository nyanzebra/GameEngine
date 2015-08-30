#pragma once

namespace cppe {
namespace memory {

constexpr unsigned long long int operator"" _byte(unsigned long long int size) { return size; }
constexpr unsigned long long int operator"" _kilobyte(unsigned long long int size) { return size * 1024_byte; }
constexpr unsigned long long int operator"" _megabyte(unsigned long long int size) { return size * 1024_kilobyte; }
constexpr unsigned long long int operator"" _gigabyte(unsigned long long int size) { return size * 1024_megabyte; }
constexpr unsigned long long int operator"" _terabyte(unsigned long long int size) { return size * 1024_gigabyte; }
constexpr unsigned long long int operator"" _petabyte(unsigned long long int size) { return size * 1024_terabyte; }

}//namespace memory
}//namespace cppe
