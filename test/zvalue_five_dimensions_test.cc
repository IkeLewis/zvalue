#include "../zvalue.hpp"
#include "gtest/gtest.h"

using namespace zvalue_ns;

TEST (ZvalueTest, Dimensions5) {

  size_t num = 200;
  size_t min = -1 - num;
  size_t max = -1;
  min = 0;
  max = num;
  size_t count = 0;
  for (size_t i = min; i < max; ++i) {
    for (size_t j = min; j < max; ++j) {
      std::vector<size_t> a = {i,i,j,j,j};
      std::vector<size_t> za = zvalue(a);
      std::vector<size_t> zia = zvalue_inverse(a);

      EXPECT_EQ(zvalue_inverse(za), a);
      EXPECT_EQ(zvalue(zia), a);

      count++;
    }
  }
  EXPECT_EQ(count, (size_t)40000);

}
