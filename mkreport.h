// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_MKREPORT_H
#define MEASUREMENT_KIT_MKREPORT_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/// mkreport_open_request_t is a request for the open-report API.
typedef struct mkreport_open_request mkreport_open_request_t;

/// mkreport_open_response_t is a response from the open-report API.
typedef struct mkreport_open_response mkreport_open_response_t;

/// mkreport_open_request_new_nonnull creates a new open-report request. It
/// always returns a valid pointer. It aborts if allocation fails.
mkreport_open_request_t *mkreport_open_request_new_nonnull(void);

/// mkreport_open_request_set_probe_asn sets the probe ASN for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_probe_asn(
    mkreport_open_request_t *request,
    const char *probe_asn);

/// mkreport_open_request_set_probe_cc sets the probe CC for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_probe_cc(
    mkreport_open_request_t *request,
    const char *probe_cc);

/// mkreport_open_request_set_software_name sets the software name for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_software_name(
    mkreport_open_request_t *request,
    const char *software_name);

/// mkreport_open_request_set_software_version sets the software name for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_software_version(
    mkreport_open_request_t *request,
    const char *software_version);

/// mkreport_open_request_set_test_name sets the software name for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_test_name(
    mkreport_open_request_t *request,
    const char *test_name);

/// mkreport_open_request_set_test_version sets the software name for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_test_version(
    mkreport_open_request_t *request,
    const char *test_version);

/// mkreport_open_request_set_test_start_time sets the software name for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_test_start_time(
    mkreport_open_request_t *request,
    const char *test_start_time);

/// mkreport_open_request_set_base_url sets the base URL for
/// the @p request. It aborts if passed any null pointer.
void mkreport_open_request_set_base_url(
    mkreport_open_request_t *request,
    const char *base_url);

/// mkreport_open_request_set_ca_bundle_path sets the CA bundle
/// path. Required on mobile. Aborts if passed null arguments.
void mkreport_open_request_set_ca_bundle_path(
    mkreport_open_request_t *request,
    const char *ca_bundle_path);

/// mkreport_open_request_set_timeout sets the timeout. After that time has
/// expired, the request will fail. It aborts if passed null arguments.
void mkreport_open_request_set_timeout(
    mkreport_open_request_t *request,
    int64_t timeout);

/// mkreport_open_request_perform_nonnull performs @p request. It will
/// always return a valid pointer. It aborts if any malloc fails.
mkreport_open_response_t *mkreport_open_request_perform_nonnull(
    const mkreport_open_request_t *request);

/// mkreport_open_request_delete destroys @p request. Note that
/// @p request MAY be a null pointer.
void mkreport_open_request_delete(
    mkreport_open_request_t *request);

/// mkreport_open_response_good returns true if we received a response
/// from the API and such response indicated success, false otherwise. It
/// calls abort if @p response is a null pointer.
int64_t mkreport_open_response_good(
    const mkreport_open_response_t *response);

/// mkreport_open_response_get_report_id returns the report ID. It always
/// returns a valid string owned by @p response. It aborts if passed
/// null arguments.
const char *mkreport_open_response_get_report_id(
    const mkreport_open_response_t *response);

/// mkreport_open_response_get_binary_logs returns the (possibly
/// non UTF-8) logs in @p data and @p count. The byte array returned in @p
/// data is owned by @p response and becomes invalid after @p response
/// is deleted. It aborts if passed any null pointer argument.
void mkreport_open_response_get_binary_logs(
    const mkreport_open_response_t *response,
    const uint8_t **data, size_t *count);

/// mkreport_open_response_delete destroys @p response. Note that
/// @p response MAY be a null pointer.
void mkreport_open_response_delete(
    mkreport_open_response_t *response);

/// mkreport_update_request_t is a request for the update-report API.
typedef struct mkreport_update_request mkreport_update_request_t;

/// mkreport_update_response_t is a response to the update-report API.
typedef struct mkreport_update_response mkreport_update_response_t;

/// mkreport_update_request_new_nonnull creates a new update-report request. It
/// will always return a valid pointer and will abort if out of memory.
mkreport_update_request_t *mkreport_update_request_new_nonnull(void);

/// mkreport_update_request_set_report_id sets the report ID for
/// the @p request. It will abort if passed null pointers.
void mkreport_update_request_set_report_id(
    mkreport_update_request_t *request,
    const char *report_id);

/// mkreport_update_request_set_content sets the content for
/// the @p request. It will abort if passed null pointers.
void mkreport_update_request_set_content(
    mkreport_update_request_t *request,
    const char *content);

/// mkreport_update_request_set_base_url sets the base URL for
/// the @p request. It will abort if passed null pointers.
void mkreport_update_request_set_base_url(
    mkreport_update_request_t *request,
    const char *base_url);

/// mkreport_update_request_set_ca_bundle_path sets the CA bundle
/// path. Required on mobile. Aborts if passed null arguments.
void mkreport_update_request_set_ca_bundle_path(
    mkreport_update_request_t *request,
    const char *ca_bundle_path);

/// mkreport_update_request_set_timeout sets the timeout. After that time has
/// expired, the request will fail. It aborts if passed null arguments.
void mkreport_update_request_set_timeout(
    mkreport_update_request_t *request,
    int64_t timeout);

/// mkreport_update_request_perform_nonnull performs @p request. It will
/// always return a valid pointer. It aborts if passed a null @p request.
mkreport_update_response_t *mkreport_update_request_perform_nonnull(
    const mkreport_update_request_t *request);

/// mkreport_update_request_delete destroys @p request. Note that @p
/// request MAY be a null pointer.
void mkreport_update_request_delete(mkreport_update_request_t *request);

/// mkreport_update_response_good returns true if we received a response
/// from the API and that response is successful, false otherwise. It
/// calls abort if passed a null pointer argument.
int64_t mkreport_update_response_good(
    const mkreport_update_response_t *response);

/// mkreport_update_response_get_binary_logs returns the (possibly
/// non UTF-8) logs in @p data and @p count. The byte array returned in @p
/// data is owned by @p response and becomes invalid after @p response
/// is deleted. It aborts if passed any null pointer argument.
void mkreport_update_response_get_binary_logs(
    const mkreport_update_response_t *response,
    const uint8_t **data, size_t *count);

/// mkreport_update_response_delete destroys @p response. Note that
/// @p response MAY be a null pointer.
void mkreport_update_response_delete(
    mkreport_update_response_t *response);

/// mkreport_close_request_t is a request for the close-report API.
typedef struct mkreport_close_request mkreport_close_request_t;

/// mkreport_close_response_t is a response from the close-report API.
typedef struct mkreport_close_response mkreport_close_response_t;

/// mkreport_close_request_new_nonnull creates a new close-report request. The
/// returned pointer is always valid. This function calls abort if allocating
/// new memory fails.
mkreport_close_request_t *mkreport_close_request_new_nonnull(void);

/// mkreport_close_request_set_report_id sets the report ID for
/// the @p request. It aborts if passed any null pointer.
void mkreport_close_request_set_report_id(
    mkreport_close_request_t *request,
    const char *report_id);

/// mkreport_close_request_set_base_url sets the base URL for
/// the @p request. It aborts if passed any null pointer.
void mkreport_close_request_set_base_url(
    mkreport_close_request_t *request,
    const char *base_url);

/// mkreport_close_request_set_ca_bundle_path sets the CA bundle
/// path. Required on mobile. Aborts if passed null arguments.
void mkreport_close_request_set_ca_bundle_path(
    mkreport_close_request_t *request,
    const char *ca_bundle_path);

/// mkreport_close_request_set_timeout sets the timeout. After that time has
/// expired, the request will fail. It aborts if passed null arguments.
void mkreport_close_request_set_timeout(
    mkreport_close_request_t *request,
    int64_t timeout);

/// mkreport_close_request_perform_nonnull performs @p request. It
/// always returns a valid pointer. It aborts if allocation fails.
mkreport_close_response_t *
mkreport_close_request_perform_nonnull(
    const mkreport_close_request_t *request);

/// mkreport_close_request_delete destroys @p request. Note that
/// @p request MAY be a null pointer.
void mkreport_close_request_delete(
    mkreport_close_request_t *request);

/// mkreport_close_response_good returns true if we received a response
/// from the API and such response indicated success, false otherwise. It
/// calls abort if @p response is a null pointer.
int64_t mkreport_close_response_good(
    const mkreport_close_response_t *response);

/// mkreport_close_response_get_binary_logs returns the (possibly
/// non UTF-8) logs in @p data and @p count. The byte array returned in @p
/// data is owned by @p response and becomes invalid after @p response
/// is deleted. It aborts if passed any null pointer argument.
void mkreport_close_response_get_binary_logs(
    const mkreport_close_response_t *response,
    const uint8_t **data, size_t *count);

/// mkreport_close_response_delete destroys @p response. Note that
/// @p response MAY be a null pointer.
void mkreport_close_response_delete(
    mkreport_close_response_t *response);

#ifdef __cplusplus
}  // extern "C"

#include <memory>
#include <string>

/// mkreport_open_request_deleter is a deleter for
/// mkreport_open_request_t.
struct mkreport_open_request_deleter {
  void operator()(mkreport_open_request_t *s) {
    mkreport_open_request_delete(s);
  }
};

/// mkreport_open_request_uptr is a unique pointer to a
/// mkreport_open_request_t instance.
using mkreport_open_request_uptr = std::unique_ptr<
    mkreport_open_request_t, mkreport_open_request_deleter>;

/// mkreport_open_response_deleter is a deleter for
/// mkreport_open_response_t.
struct mkreport_open_response_deleter {
  void operator()(mkreport_open_response_t *s) {
    mkreport_open_response_delete(s);
  }
};

/// mkreport_open_response_uptr is a unique pointer to a
/// mkreport_open_response_t instance.
using mkreport_open_response_uptr = std::unique_ptr<
    mkreport_open_response_t, mkreport_open_response_deleter>;

/// mkreport_update_request_deleter is a deleter for
/// mkreport_update_request_t.
struct mkreport_update_request_deleter {
  void operator()(mkreport_update_request_t *s) {
    mkreport_update_request_delete(s);
  }
};

/// mkreport_update_request_uptr is a unique pointer to a
/// mkreport_update_request_t instance.
using mkreport_update_request_uptr = std::unique_ptr<
    mkreport_update_request_t, mkreport_update_request_deleter>;

/// mkreport_update_response_deleter is a deleter for
/// mkreport_update_response_t.
struct mkreport_update_response_deleter {
  void operator()(mkreport_update_response_t *s) {
    mkreport_update_response_delete(s);
  }
};

/// mkreport_update_response_uptr is a unique pointer to a
/// mkreport_update_response_t instance.
using mkreport_update_response_uptr = std::unique_ptr<
    mkreport_update_response_t, mkreport_update_response_deleter>;

/// mkreport_close_request_deleter is a deleter for
/// mkreport_close_request_t.
struct mkreport_close_request_deleter {
  void operator()(mkreport_close_request_t *s) {
    mkreport_close_request_delete(s);
  }
};

/// mkreport_close_request_uptr is a unique pointer to a
/// mkreport_close_request_t instance.
using mkreport_close_request_uptr = std::unique_ptr<
    mkreport_close_request_t, mkreport_close_request_deleter>;

/// mkreport_close_response_deleter is a deleter for
/// mkreport_close_response_t.
struct mkreport_close_response_deleter {
  void operator()(mkreport_close_response_t *s) {
    mkreport_close_response_delete(s);
  }
};

/// mkreport_close_response_uptr is a unique pointer to a
/// mkreport_close_response_t instance.
using mkreport_close_response_uptr = std::unique_ptr<
    mkreport_close_response_t, mkreport_close_response_deleter>;

/// mkreport_open_response_moveout_logs moves the logs out of
/// @p response. It aborts if passed a null pointer.
std::string mkreport_open_response_moveout_logs(
    mkreport_open_response_uptr &response);

/// mkreport_update_response_moveout_logs moves the logs out of
/// @p response. It aborts if passed a null pointer.
std::string mkreport_update_response_moveout_logs(
    mkreport_update_response_uptr &response);

/// mkreport_close_response_moveout_logs moves the logs out of
/// @p response. It aborts if passed a null pointer.
std::string mkreport_close_response_moveout_logs(
    mkreport_close_response_uptr &response);

// The implementation can be included inline by defining this preprocessor
// symbol. If you only care about API, you can stop reading here.
#ifdef MKREPORT_INLINE_IMPL

#include <vector>

#include "json.hpp"
#include "mkcurl.h"

struct mkreport_open_request {
  std::string probe_asn;
  std::string probe_cc;
  std::string software_name;
  std::string software_version;
  std::string test_name;
  std::string test_version;
  std::string test_start_time;
  std::string base_url;
  std::string ca_bundle_path;
  int64_t timeout = 30;
};

struct mkreport_open_response {
  int64_t good = false;
  std::string report_id;
  std::string logs;
};

mkreport_open_request_t *mkreport_open_request_new_nonnull() {
  return new mkreport_open_request_t;
}

void mkreport_open_request_set_probe_asn(
    mkreport_open_request_t *request,
    const char *probe_asn) {
  if (request == nullptr || probe_asn == nullptr) {
    abort();
  }
  request->probe_asn = probe_asn;
}

void mkreport_open_request_set_probe_cc(
    mkreport_open_request_t *request,
    const char *probe_cc) {
  if (request == nullptr || probe_cc == nullptr) {
    abort();
  }
  request->probe_cc = probe_cc;
}

void mkreport_open_request_set_software_name(
    mkreport_open_request_t *request,
    const char *software_name) {
  if (request == nullptr || software_name == nullptr) {
    abort();
  }
  request->software_name = software_name;
}

void mkreport_open_request_set_software_version(
    mkreport_open_request_t *request,
    const char *software_version) {
  if (request == nullptr || software_version == nullptr) {
    abort();
  }
  request->software_version = software_version;
}

void mkreport_open_request_set_test_name(
    mkreport_open_request_t *request,
    const char *test_name) {
  if (request == nullptr || test_name == nullptr) {
    abort();
  }
  request->test_name = test_name;
}

void mkreport_open_request_set_test_version(
    mkreport_open_request_t *request,
    const char *test_version) {
  if (request == nullptr || test_version == nullptr) {
    abort();
  }
  request->test_version = test_version;
}

void mkreport_open_request_set_test_start_time(
    mkreport_open_request_t *request,
    const char *test_start_time) {
  if (request == nullptr || test_start_time == nullptr) {
    abort();
  }
  request->test_start_time = test_start_time;
}

void mkreport_open_request_set_base_url(
    mkreport_open_request_t *request, const char *base_url) {
  if (request == nullptr || base_url == nullptr) {
    abort();
  }
  request->base_url = base_url;
}

void mkreport_open_request_set_ca_bundle_path(
    mkreport_open_request_t *request,
    const char *ca_bundle_path) {
  if (request == nullptr || ca_bundle_path == nullptr) {
    abort();
  }
  request->ca_bundle_path = ca_bundle_path;
}

void mkreport_open_request_set_timeout(
    mkreport_open_request_t *request,
    int64_t timeout) {
  if (request == nullptr) {
    abort();
  }
  request->timeout = timeout;
}

mkreport_open_response_t *mkreport_open_request_perform_nonnull(
    const mkreport_open_request_t *request) {
  if (request == nullptr) {
    abort();
  }
  mkreport_open_response_uptr response{
      new mkreport_open_response_t};  // new cannot fail
  mkcurl_request_uptr curl_request{mkcurl_request_new_nonnull()};
  mkcurl_request_set_ca_bundle_path_v2(
      curl_request.get(), request->ca_bundle_path.c_str());
  mkcurl_request_set_timeout_v2(curl_request.get(), request->timeout);
  mkcurl_request_set_method_post_v2(curl_request.get());
  mkcurl_request_add_header_v2(
      curl_request.get(), "Content-Type: application/json");
  {
    std::string url = request->base_url;
    url += "/report";
    mkcurl_request_set_url_v2(curl_request.get(), url.c_str());
  }
  {
    std::string body;
    nlohmann::json doc;
    doc["data_format_version"] = "0.2.0";
    doc["format"] = "json";
    doc["input_hashes"] = nlohmann::json::array();
    doc["probe_asn"] = request->probe_asn;
    doc["probe_cc"] = request->probe_cc;
    doc["software_name"] = request->software_name;
    doc["software_version"] = request->software_version;
    doc["test_name"] = request->test_name;
    doc["test_start_time"] = request->test_start_time,
    doc["test_version"] = request->test_version;
    try {
      body = doc.dump();
    } catch (const std::exception &exc) {
      response->logs += exc.what();
      response->logs += "\n";
      return response.release();
    }
    response->logs += "Request body: ";
    response->logs += body;
    response->logs += "\n";
    mkcurl_request_movein_body_v2(curl_request, std::move(body));
  }
  mkcurl_response_uptr curl_response{
      mkcurl_request_perform_nonnull(curl_request.get())};
  response->logs += mkcurl_response_moveout_logs_v2(curl_response);
  if (mkcurl_response_get_error_v2(curl_response.get()) != 0) {
    return response.release();
  }
  if (mkcurl_response_get_status_code_v2(curl_response.get()) != 200) {
    return response.release();
  }
  {
    std::string body = mkcurl_response_moveout_body_v2(curl_response);
    response->logs += "Response body: ";
    response->logs += body;
    response->logs += "\n";
    nlohmann::json doc;
    try {
      doc = nlohmann::json::parse(body);
      response->report_id = doc.at("report_id").get<std::string>();
    } catch (const std::exception &exc) {
      response->logs += exc.what();
      response->logs += "\n";
      return response.release();
    }
  }
  response->good = true;
  return response.release();
}

void mkreport_open_request_delete(
    mkreport_open_request_t *request) {
  delete request;
}

int64_t mkreport_open_response_good(
    const mkreport_open_response_t *response) {
  if (response == nullptr) {
    abort();
  }
  return response->good;
}

const char *mkreport_open_response_get_report_id(
    const mkreport_open_response_t *response) {
  if (response == nullptr) {
    abort();
  }
  return response->report_id.c_str();
}

void mkreport_open_response_get_binary_logs(
    const mkreport_open_response_t *response,
    const uint8_t **data, size_t *count) {
  if (response == nullptr || data == nullptr || count == nullptr) {
    abort();
  }
  *data = (const uint8_t *)response->logs.c_str();
  *count = response->logs.size();
}

void mkreport_open_response_delete(
    mkreport_open_response_t *response) {
  delete response;
}

struct mkreport_update_request {
  std::string report_id;
  std::string content;
  std::string base_url;
  std::string ca_bundle_path;
  int64_t timeout = 30;
};

struct mkreport_update_response {
  int64_t good = false;
  std::string logs;
};

mkreport_update_request_t *mkreport_update_request_new_nonnull() {
  return new mkreport_update_request_t;
}

void mkreport_update_request_set_report_id(
    mkreport_update_request_t *request,
    const char *report_id) {
  if (request == nullptr || report_id == nullptr) {
    abort();
  }
  request->report_id = report_id;
}

void mkreport_update_request_set_content(
    mkreport_update_request_t *request,
    const char *content) {
  if (request == nullptr || content == nullptr) {
    abort();
  }
  request->content = content;
}

void mkreport_update_request_set_base_url(
    mkreport_update_request_t *request, const char *base_url) {
  if (request == nullptr || base_url == nullptr) {
    abort();
  }
  request->base_url = base_url;
}

void mkreport_update_request_set_ca_bundle_path(
    mkreport_update_request_t *request,
    const char *ca_bundle_path) {
  if (request == nullptr || ca_bundle_path == nullptr) {
    abort();
  }
  request->ca_bundle_path = ca_bundle_path;
}

void mkreport_update_request_set_timeout(
    mkreport_update_request_t *request,
    int64_t timeout) {
  if (request == nullptr) {
    abort();
  }
  request->timeout = timeout;
}

mkreport_update_response_t *mkreport_update_request_perform_nonnull(
    const mkreport_update_request_t *request) {
  if (request == nullptr) {
    abort();
  }
  mkreport_update_response_uptr response{
    new mkreport_update_response_t};  // new cannot fail
  mkcurl_request_uptr curl_request{mkcurl_request_new_nonnull()};
  mkcurl_request_set_ca_bundle_path_v2(
      curl_request.get(), request->ca_bundle_path.c_str());
  mkcurl_request_set_timeout_v2(curl_request.get(), request->timeout);
  mkcurl_request_set_method_post_v2(curl_request.get());
  mkcurl_request_add_header_v2(
      curl_request.get(), "Content-Type: application/json");
  {
    std::string url = request->base_url;
    url += "/report/";
    url += request->report_id;
    mkcurl_request_set_url_v2(curl_request.get(), url.c_str());
  }
  {
    std::string body;
    nlohmann::json doc;
    doc["format"] = "json";
    try {
      doc["content"] = nlohmann::json::parse(request->content);
      body = doc.dump();
    } catch (const std::exception &exc) {
      response->logs += exc.what();
      response->logs += "\n";
      return response.release();
    }
    response->logs += "Request body: ";
    response->logs += body;
    response->logs += "\n";
    mkcurl_request_movein_body_v2(curl_request, std::move(body));
  }
  mkcurl_response_uptr curl_response{
      mkcurl_request_perform_nonnull(curl_request.get())};
  response->logs += mkcurl_response_moveout_logs_v2(curl_response);
  if (mkcurl_response_get_error_v2(curl_response.get()) != 0) {
    return response.release();
  }
  if (mkcurl_response_get_status_code_v2(curl_response.get()) != 200) {
    return response.release();
  }
  {
    std::string body = mkcurl_response_moveout_body_v2(curl_response);
    response->logs += "Response body: ";
    response->logs += body;
    response->logs += "\n";
  }
  response->good = true;
  return response.release();
}

void mkreport_update_request_delete(mkreport_update_request_t *request) {
  delete request;
}

int64_t mkreport_update_response_good(
    const mkreport_update_response_t *response) {
  if (response == nullptr) {
    abort();
  }
  return response->good;
}

void mkreport_update_response_get_binary_logs(
    const mkreport_update_response_t *response,
    const uint8_t **data, size_t *count) {
  if (response == nullptr || data == nullptr || count == nullptr) {
    abort();
  }
  *data = (const uint8_t *)response->logs.c_str();
  *count = response->logs.size();
}

void mkreport_update_response_delete(
    mkreport_update_response_t *response) {
  delete response;
}

struct mkreport_close_request {
  std::string report_id;
  std::string base_url;
  std::string ca_bundle_path;
  int64_t timeout = 30;
};

struct mkreport_close_response {
  int64_t good = false;
  std::string logs;
};

mkreport_close_request_t *mkreport_close_request_new_nonnull() {
  return new mkreport_close_request_t;
}

void mkreport_close_request_set_report_id(
    mkreport_close_request_t *request,
    const char *report_id) {
  if (request == nullptr || report_id == nullptr) {
    abort();
  }
  request->report_id = report_id;
}

void mkreport_close_request_set_base_url(
    mkreport_close_request_t *request,
    const char *base_url) {
  if (request == nullptr || base_url == nullptr) {
    abort();
  }
  request->base_url = base_url;
}

void mkreport_close_request_set_ca_bundle_path(
    mkreport_close_request_t *request,
    const char *ca_bundle_path) {
  if (request == nullptr || ca_bundle_path == nullptr) {
    abort();
  }
  request->ca_bundle_path = ca_bundle_path;
}

void mkreport_close_request_set_timeout(
    mkreport_close_request_t *request,
    int64_t timeout) {
  if (request == nullptr) {
    abort();
  }
  request->timeout = timeout;
}

mkreport_close_response_t *mkreport_close_request_perform_nonnull(
    const mkreport_close_request_t *request) {
  if (request == nullptr) {
    abort();
  }
  mkreport_close_response_uptr response{
      new mkreport_close_response_t};  // new cannot fail
  mkcurl_request_uptr curl_request{mkcurl_request_new_nonnull()};
  mkcurl_request_set_method_post_v2(curl_request.get());
  mkcurl_request_set_ca_bundle_path_v2(
      curl_request.get(), request->ca_bundle_path.c_str());
  mkcurl_request_set_timeout_v2(curl_request.get(), request->timeout);
  {
    std::string url = request->base_url;
    url += "/report/";
    url += request->report_id;
    url += "/close";
    mkcurl_request_set_url_v2(curl_request.get(), url.c_str());
  }
  mkcurl_response_uptr curl_response{
      mkcurl_request_perform_nonnull(curl_request.get())};
  response->logs += mkcurl_response_moveout_logs_v2(curl_response);
  if (mkcurl_response_get_error_v2(curl_response.get()) != 0) {
    return response.release();
  }
  if (mkcurl_response_get_status_code_v2(curl_response.get()) != 200) {
    return response.release();
  }
  {
    std::string body = mkcurl_response_moveout_body_v2(curl_response);
    response->logs += "Response body: ";
    response->logs += body;
    response->logs += "\n";
  }
  response->good = true;
  return response.release();
}

void mkreport_close_request_delete(
    mkreport_close_request_t *request) {
  delete request;
}

int64_t mkreport_close_response_good(
    const mkreport_close_response_t *response) {
  if (response == nullptr) {
    abort();
  }
  return response->good;
}

void mkreport_close_response_get_binary_logs(
    const mkreport_close_response_t *response,
    const uint8_t **data, size_t *count) {
  if (response == nullptr || data == nullptr || count == nullptr) {
    abort();
  }
  *data = (const uint8_t *)response->logs.c_str();
  *count = response->logs.size();
}

void mkreport_close_response_delete(
    mkreport_close_response_t *response) {
  delete response;
}

std::string mkreport_open_response_moveout_logs(
    mkreport_open_response_uptr &response) {
  if (response == nullptr) {
    abort();
  }
  return std::move(response->logs);
}

std::string mkreport_update_response_moveout_logs(
    mkreport_update_response_uptr &response) {
  if (response == nullptr) {
    abort();
  }
  return std::move(response->logs);
}

std::string mkreport_close_response_moveout_logs(
    mkreport_close_response_uptr &response) {
  if (response == nullptr) {
    abort();
  }
  return std::move(response->logs);
}

#endif  // MKREPORT_INLINE_IMPL
#endif  // __cplusplus
#endif  // MEASUREMENT_KIT_MKREPORT_H
