
#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

#include <nlohmann/json.hpp>

#include "irrsim00.hpp"
#include "security_reqeust.hpp"

namespace SEAR {

void Racmap::extract(SecurityRequest &request) {

}
} // namespace SEAR