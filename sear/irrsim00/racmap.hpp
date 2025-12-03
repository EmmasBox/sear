#ifndef __RACMAP_H_
#define __RACMAP_H_

#include <string>
#include "irrsim00.hpp"
#include "security_request.hpp"

namespace SEAR {
class Racmap {
    public:
    static void extract(SecurityRequest &request);
    private:
    void buildRACMAPRequest(
    racmap_extract_underbar_arg_area_t *arg_area, int function_code);
};
}  // namespace SEAR

#endif