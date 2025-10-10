#include "xml_parser.hpp"

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "../conversion.hpp"
#include "logger.hpp"
#include "sear_error.hpp"
#include <rapidxml.hpp>

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

namespace SEAR {
// Public Methods of XMLParser
nlohmann::json XMLParser::buildJSONString(SecurityRequest& request) {
  std::string xml_buffer;

  const char* p_raw_result = request.getRawResultPointer();
  int raw_result_length    = request.getRawResultLength();

  auto xml_ebcdic_result_unique_ptr =

      std::make_unique<char[]>(raw_result_length + 1);
  std::memset(xml_ebcdic_result_unique_ptr.get(), 0, raw_result_length + 1);

  // Build a JSON string from the XML result string, SMO return and Reason
  // Codes
  Logger::getInstance().debug("Raw EBCDIC encoded result XML:");
  Logger::getInstance().hexDump(p_raw_result, raw_result_length);

  std::memcpy(xml_ebcdic_result_unique_ptr.get(), p_raw_result,
              raw_result_length);

  std::string ebcdic_string = std::string(xml_ebcdic_result_unique_ptr.get());

  xml_buffer = toUTF8(ebcdic_string, "IBM-1047");

  Logger::getInstance().debug("Decoded result XML:", xml_buffer);

  nlohmann::json result_json;

  XMLParser::XMLToJSON(xml_buffer, result_json, request);

  return result_json;
}

void XMLParser::XMLToJSON(const std::string& xml_string, nlohmann::json& output_json, SecurityRequest& request) {
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<> * root_node;

  nlohmann::json new_json;

  std::vector<char> xml_copy {xml_string.begin(),xml_string.end()};
  xml_copy.push_back('\0');
  doc.parse<0>(xml_copy.data()); 

  // Find our root node
	root_node = doc.first_node("securityresult");

	for (rapidxml::xml_node<> * result_node = root_node->first_node(); result_node; result_node = result_node->next_sibling())
	{
    rapidxml::xml_node<> * command_node = result_node->first_node("command");
    rapidxml::xml_node<> * error_node = result_node->first_node("error");

    const std::string &node_name = result_node->name();
    
    if (node_name.compare("error") == 0) {
      request.setSEARReturnCode(8);
      throw SEARError("Unable to parse XML returned by IRRSMO00");
    } else {
      if (command_node) {
        output_json["command"]["safreturncode"] = command_node->first_node("safreturncode")->value();
        output_json["command"]["returncode"] = command_node->first_node("returncode")->value();
        output_json["command"]["reasoncode"] = command_node->first_node("reasoncode")->value();
        output_json["command"]["image"] = command_node->first_node("image")->value();
        Logger::getInstance().debug("command: ",command_node->first_node("image")->value());
        Logger::getInstance().debug("racf reason code: ", command_node->first_node("reasoncode")->value());

        Logger::getInstance().debug("node: ",result_node->name());

        break;
      } else if (error_node) {
        rapidxml::xml_node<> * errormessage_node = error_node->first_node("errormessage");
        rapidxml::xml_node<> * erroroffset_node = error_node->first_node("erroroffset");
        rapidxml::xml_node<> * textinerror_node = error_node->first_node("textinerror");
        if (errormessage_node && erroroffset_node && textinerror_node) {
          request.setSEARReturnCode(4);
          std::string errormessage_str = "Error message produced by IRRSMO00: ";
          errormessage_str.append(errormessage_node->value());
          errormessage_str.append(" at offset ");
          errormessage_str.append(erroroffset_node->value());
          errormessage_str.append(" (");
          errormessage_str.append(textinerror_node->value());
          errormessage_str.append(")");
          throw SEARError(errormessage_str);
        } else if (errormessage_node) {
          request.setSEARReturnCode(4);
          std::string errormessage_str = "Error message produced by IRRSMO00: ";
          errormessage_str.append(errormessage_node->value());
          throw SEARError(errormessage_str);
        } else {
          request.setSEARReturnCode(8);
          throw SEARError("Unable to find error message returned by IRRSMO00");
        }
        break;
      }
    }
	}
    // Convert profile JSON to C string.
  std::string result_json_string = output_json.dump();
  Logger::getInstance().debug("new JSON:", result_json_string);
  return;
}
}