#include "zvalue.hpp"
#include "significant.hpp"

namespace zvalue_ns {

std::vector<size_t> zvalue_inverse(const std::vector<size_t>& zval) {
  // Return the inverse of zval (a vector of integers).

  // The number of dimensions
  size_t d = zval.size();

  std::vector<size_t> invz(d, 0);

  // The number of bits in the z-value
  size_t z_num_bits = d * num_bits;

  for (size_t j = 0; j < d; ++j) {
    for (size_t i = j, k = 0; i < z_num_bits && k < num_bits; i += d, ++k) {
      setLSB(k, invz[j], LSB(i, zval));
    }
  }

  return invz;
}

std::vector<size_t> zvalue(const std::vector<size_t>& invz) {
  // Return the zvalue of invz (a vector of integers).

  std::vector<size_t> zval(invz.size(), 0);

  for (size_t i = 0, k = 0; i < sizeof(size_t) * 8; ++i) {
    for (size_t j = 0; j < zval.size(); ++j, ++k) {
      // bit(k, zval) = bit(i, invz[j]), where k=i*d + j.
      // assert(k==i*zval.size() + j);
      setLSB(k, zval, LSB(i, invz[j]));
    }
  }

  return zval;
}
}
