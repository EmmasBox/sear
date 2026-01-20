#ifndef __META_API_EXPORTER_H_
#define __META_API_EXPORTER_H_

#include <nlohmann/json.hpp>
#include <string>

#include "sear_result.h"
#include "security_request.hpp"

namespace SEAR {
class MetaAPIExporter {
 public:
  void api_meta_export(SecurityRequest &request, bool profile_exists_check);
};
}  // namespace SEAR

#endif /* __META_API_EXPORTER_H_ */
