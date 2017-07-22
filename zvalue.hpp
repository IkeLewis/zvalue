#ifndef ZVALUE_H_
#define ZVALUE_H_

// For size_t
#include <sys/types.h>
#include <vector>

namespace zvalue_ns {

std::vector<size_t> zvalue_inverse(const std::vector<size_t>& zvals);
std::vector<size_t> zvalue(const std::vector<size_t>& ints);

}

#endif /* ZVALUE_H_ */
