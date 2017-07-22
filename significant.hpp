#ifndef SIGNIFICANT_H_
#define SIGNIFICANT_H_

#include <vector>
#include <limits.h>
#include <stdint.h>

const static size_t one = 1;
const static size_t zero = 0;
const static size_t max_val = ~zero;
const static size_t num_bits = sizeof(size_t) * 8;

// ASSUMPTIONS:
//
// The vector <ints> is assumed to store bits in least significant
// order.

inline bool LSB(const u_char& index, const size_t& num) {
  // Return the <index> th least significant bit of <num>, where 0 <=
  // index < num_bits.

  return (num & (one << index)) >> index;
}

inline bool LSB(const size_t& index, const std::vector<size_t>& ints) {
  // Returns the <index> th least significant bit of <ints>, where 0
  // <= index < num_bits * ints.size().

  // To return the <red_index> th least significant bit of <ints> we
  size_t red_index = index % (num_bits * ints.size());

  // return the (index % num_bits) th least significant bit of the
  // (index/num_bits) th least significant int.
  return LSB(red_index % num_bits, ints[red_index / num_bits]);
}

inline bool MSB(const size_t& index, const size_t& num) {
  // Returns the <index> th most significant bit of <num>, where
  // 0 <= index < num_bits.

  size_t shift_amt = num_bits - 1 - index % num_bits;
  return (num & (one << shift_amt)) >> shift_amt;
}

inline bool MSB(const size_t& index, const std::vector<size_t>& ints) {
  // Returns the <index> th most significant bit of <ints>, where 0 <=
  // index < num_bits * ints.size().

  // The <red_index> th most significant bit of <ints> will be
  // returned
  size_t red_index = index % (num_bits * ints.size());
  // that bit is the (red_index % num_bits) th most significant bit of
  // the the <arr_index> th most significant int.
  size_t arr_index = red_index / num_bits;

  // The <arr_index> th most significant int will be at the index
  // (arr_size - 1 - arr_index), since ints are stored from least
  // significant to most significant.
  return MSB(red_index % num_bits, ints[ints.size() - 1 - arr_index]);
}

inline void setLSB(const size_t& index, size_t& num, const bool& val) {
  // Sets the <index> th least significant bit of <num> to <val>,
  // where 0 <= index < num_bits.

  // Create a mask consisting of all zeros except for the nth least
  // sig. bit.
  size_t _0_1_0_ = (one << index % num_bits);
  // Create a mask consisting of all zeros or all ones w/ the same
  // logical value as val.
  size_t val2 = max_val * ((size_t)val);

  num = (((val2 & _0_1_0_) | num) | ((~val2 & ~_0_1_0_) & num));

  // Analysis:
  //
  // Case: val == 1
  // num = (val2 & _0_1_0_) | num)   = (000..100...0) | num, so that
  // the <index> th bit is set to 1.
  //
  // Case: val == 0
  // num = (~ val2 & ~_0_1_0_ & num) = (111..011...1) & num, so that
  // the <index> th bit is set to 0.
  //
  // In either case, the <index> th bit is set correctly.
}

inline void setLSB(const size_t& index, std::vector<size_t>& ints,
                    const bool& val) {
  // Sets the <index> th least significant bit of <ints> to <val>, where
  // 0 <= index < num_bits * ints.size().

  // The <red_index> th least significant bit of <ints> will be set
  size_t red_index = index % (num_bits * ints.size());
  // by setting the (index % num_bits) th least significant bit of the
  //(index/num_bits) th least significant int.
  setLSB(red_index % num_bits, ints[red_index / num_bits], val);
}

inline void setMSB(const size_t& index, size_t& num, const bool& val) {
  // Sets the <index> th most significant bit of <num> to <val>, where
  // 0 <= index < num_bits.

  // Create a mask consisting of all zeros except for the nth most
  // significant bit.
  size_t _0_1_0_ = (one << ((num_bits - 1) - index % num_bits));

  // Create a mask consisting of all zeros or all ones w/ the same
  // logical value as val.
  size_t val2 = max_val * val;

  num = (((val2 & _0_1_0_) | num) | ((~val2 & ~_0_1_0_) & num));
}

inline void setMSB(const size_t& index, std::vector<size_t>& ints, const bool& val) {
  // Sets the <index> th most significant bit of <ints> to <val>,
  // where 0 <= index < num_bits * ints.size().

  // Set the <red_index> th most significant bit of <ints> by
  size_t red_index = index % (num_bits * ints.size());
  // setting the (red_index % num_bits) th most significant bit of the
  // the <arr_index> th most significant int.
  size_t arr_index = red_index / num_bits;

  // The <arr_index> th most significant int will be at the index
  // (arr_size - 1 - arr_index), since ints are stored from least
  // significant to most significant.

  setMSB(red_index % num_bits, ints[ints.size() - 1 - arr_index], val);
}

#endif /* SIGNIFICANT_H_ */
