#ifndef __META_API_EXPORTER_H_
#define __META_API_EXPORTER_H_

#include <nlohmann/json.hpp>
#include <string>

#include "sear_result.h"
#include "security_request.hpp"

namespace SEAR {
class MetaAPIValidator {
 public:
  void export_valid_traits(SecurityRequest &request);
};
}  // namespace SEAR

#endif /* __META_API_EXPORTER_H_ */
