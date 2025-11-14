#ifndef __SEAR_XML_PARSER_H_
#define __SEAR_XML_PARSER_H_

#include <nlohmann/json.hpp>
#include <rapidxml.hpp>
#include <string>

#include "logger.hpp"
#include "security_request.hpp"

namespace SEAR {
// XMLParser Parses an XML String and forms a JSON String
class XMLParser {
 private:
  void XMLToJSON( std::string xml_string, nlohmann::json& output_json, SecurityRequest& request);

 public:
  nlohmann::json buildJSONString(SecurityRequest& request);
};
}  // namespace SEAR

#endif