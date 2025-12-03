
#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

#include <nlohmann/json.hpp>

#include "irrsim00.hpp"
#include "security_reqeust.hpp"

namespace SEAR {

void Racmap::buildRACMAPRequest(
    racmap_extract_underbar_arg_area_t *arg_area, int function_code) {
  // Make sure buffer is clear.
  std::memset(arg_area, 0, sizeof(racmap_extract_underbar_arg_area_t));

  racmap_extract_args_t *args                 = &arg_area->args;
  racmap_extract_arg_pointers_t *arg_pointers = &arg_area->arg_pointers;

  /***************************************************************************/
  /* Set Extract Arguments */
  /***************************************************************************/
  args->ALET_SAF_rc           = ALET;
  args->ALET_RACF_rc          = ALET;
  args->ALET_RACF_rsn         = ALET;
  args->ACEE                  = ACEE;
  args->function_code         = function_code;

  /***************************************************************************/
  /* Set Extract Argument Pointers */
  /*                                                                         */
  /* Enable transition from 64-bit XPLINK to 31-bit OSLINK. */
  /***************************************************************************/
  arg_pointers->p_work_area =
      reinterpret_cast<char *__ptr32>(&args->RACF_work_area);
  arg_pointers->p_ALET_SAF_rc   = &(args->ALET_SAF_rc);
  arg_pointers->p_SAF_rc        = &(args->SAF_rc);
  arg_pointers->p_ALET_RACF_rc  = &(args->ALET_RACF_rc);
  arg_pointers->p_RACF_rc       = &(args->RACF_rc);
  arg_pointers->p_ALET_RACF_rsn = &(args->ALET_RACF_rsn);
  arg_pointers->p_RACF_rsn      = &(args->RACF_rsn);

  arg_pointers->p_function_code = &(args->function_code);

  arg_pointers->p_userid_length = &(args->useridLength)
  arg_pointers->p_userid        = &(args->userid)

  arg_pointers->p_certificate_length = &(args->useridLength)
  arg_pointers->p_certificate        = &(args->userid)

  arg_pointers->p_application_userid_length = &(args->application_userid_length)
  arg_pointers->p_application_userid        = &(args->application_userid)

  arg_pointers->p_distinguished_name_length = &(args->distinguished_name_length)
  arg_pointers->p_distinguished_name        = &(args->distinguished_name)

  arg_pointers->p_registry_name_length      = &(args->registry_name_length)
  arg_pointers->p_registry_name             = &(args->registry_name)
}

void Racmap::extract(SecurityRequest &request) {
    nlohmann::json profile;
    profile["profile"] = nlohmann::json::object();

    auto unique_ptr = make_unique31<racmap_extract_underbar_arg_area_t>();
    racmap_extract_underbar_arg_area_t *p_arg_area = unique_ptr.get();
    Racmap::buildRACMAPRequest(p_arg_area);

    // Call R_usermap
    Logger::getInstance().debug("Calling IRRSIM00 ...");
    rc = callRmap(reinterpret_cast<char *__ptr32>(&p_arg_area->arg_pointers,USER_TO_EMAIL_FUNCTION_CODE));
    Logger::getInstance().debug("Done");

    request.setIntermediateResultJSON(profile);
}
} // namespace SEAR