#ifndef __SEAR_SECURITY_ADMIN_H_
#define __SEAR_SECURITY_ADMIN_H_

#include <cstdint>
#include <nlohmann/json.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>
#include <valijson/adapters/nlohmann_json_adapter.hpp>

#include "extractor.hpp"
#include "keyring_modifier.hpp"
#include "logger.hpp"
#include "sear_result.h"
#include "sear_schema.hpp"
#include "security_request.hpp"

namespace SEAR {

class SecurityAdmin {
 private:
  SecurityRequest request_;
  void doExtract(Extractor &extractor);
  void doAddAlterDelete();
  void doAddAlterDeleteKeyring(KeyringModifier &modifier);
  void doAddCertificate(KeyringModifier &modifier);
  void doDeleteCertificate(KeyringModifier &modifier);
  void doRemoveCertificate(KeyringModifier &modifier);
  bool jsonValidator(nlohmann::json request_json, nlohmann::json input_schema);

 public:
  SecurityAdmin(sear_result_t *p_result, bool debug);
  void makeRequest(const char *p_request_json_string, int length);
};
}  // namespace SEAR

#endif
