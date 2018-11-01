#include "mkreport.h"

#include <iostream>

#define MKCURL_INLINE_IMPL
#include "mkcurl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "json.hpp"

static std::string collector_baseurl() {
  return "https://collector-sandbox.ooni.io";
}

static std::string open_report() {
  mkreport_open_request_uptr r{
      mkreport_open_request_new_nonnull()};
  mkreport_open_request_set_probe_asn(r.get(), "AS30722");
  mkreport_open_request_set_probe_cc(r.get(), "IT");
  mkreport_open_request_set_software_name(r.get(), "mkreport");
  mkreport_open_request_set_software_version(r.get(), "0.0.1");
  mkreport_open_request_set_test_name(r.get(), "dummy");
  mkreport_open_request_set_test_version(r.get(), "0.0.1");
  mkreport_open_request_set_test_start_time(r.get(), "2018-11-01 15:33:17");
  mkreport_open_request_set_base_url(r.get(), collector_baseurl().c_str());
  mkreport_open_request_set_ca_bundle_path(r.get(), "ca-bundle.pem");
  mkreport_open_request_set_timeout(r.get(), 14);
  mkreport_open_response_uptr re{
      mkreport_open_request_perform_nonnull(r.get())};
  {
    std::string logs = mkreport_open_response_moveout_logs(re);
    REQUIRE(logs.size() > 0);
    std::clog << "=== BEGIN OPEN LOGS ===" << std::endl;
    std::clog << logs;
    std::clog << "=== END OPEN LOGS ===" << std::endl;
  }
  REQUIRE(mkreport_open_response_good(re.get()));
  std::string report_id;
  {
    report_id = mkreport_open_response_get_report_id(re.get());
    REQUIRE(report_id.size() > 0);
    std::clog << report_id << std::endl;
  }
  return report_id;
}

TEST_CASE("We can open a report") {
  (void)open_report();
}

static std::string dummy_report(std::string report_id) {
  nlohmann::json doc;
  doc["annotations"] = nlohmann::json::object();
  doc["data_format_version"] = "0.2.0";
  doc["id"] = "bdd20d7a-bba5-40dd-a111-9863d7908572";
  doc["input"] = nullptr;
  doc["input_hashes"] = nlohmann::json::array();
  doc["measurement_start_time"] = "2018-11-01 15:33:20";
  doc["options"] = nlohmann::json::array();
  doc["probe_asn"] = "AS0";
  doc["probe_cc"] = "ZZ";
  doc["probe_city"] = nullptr;
  doc["probe_ip"] = "127.0.0.1";
  doc["report_id"] = report_id;
  doc["software_name"] = "mkreport";
  doc["software_version"] = "0.0.1";
  doc["test_helpers"] = nlohmann::json::array();
  doc["test_keys"] = nlohmann::json::object();
  doc["test_keys"]["client_resolver"] = "91.80.37.104";
  doc["test_name"] = "dummy";
  doc["test_runtime"] = 5.0565230846405;
  doc["test_start_time"] = "2018-11-01 15:33:17";
  doc["test_version"] = "0.0.1";
  return doc.dump();
}

static void update_report(std::string report_id) {
  mkreport_update_request_uptr r{mkreport_update_request_new_nonnull()};
  mkreport_update_request_set_report_id(r.get(), report_id.c_str());
  mkreport_update_request_set_content(r.get(), dummy_report(report_id).c_str());
  mkreport_update_request_set_base_url(r.get(), collector_baseurl().c_str());
  mkreport_update_request_set_ca_bundle_path(r.get(), "ca-bundle.pem");
  mkreport_update_request_set_timeout(r.get(), 14);
  mkreport_update_response_uptr re{
      mkreport_update_request_perform_nonnull(r.get())};
  {
    std::string logs = mkreport_update_response_moveout_logs(re);
    REQUIRE(logs.size() > 0);
    std::clog << "=== BEGIN LOGIN LOGS ===" << std::endl;
    std::clog << logs;
    std::clog << "=== END LOGIN LOGS ===" << std::endl;
  }
  REQUIRE(mkreport_update_response_good(re.get()));
}

TEST_CASE("We can update a report") {
  update_report(open_report());
}

TEST_CASE("We can close a report") {
  std::string report_id = open_report();
  update_report(report_id);
  mkreport_close_request_uptr r{mkreport_close_request_new_nonnull()};
  mkreport_close_request_set_report_id(r.get(), report_id.c_str());
  mkreport_close_request_set_base_url(r.get(), collector_baseurl().c_str());
  mkreport_close_request_set_ca_bundle_path(r.get(), "ca-bundle.pem");
  mkreport_close_request_set_timeout(r.get(), 14);
  mkreport_close_response_uptr re{
      mkreport_close_request_perform_nonnull(r.get())};
  {
    std::string logs = mkreport_close_response_moveout_logs(re);
    REQUIRE(logs.size() > 0);
    std::clog << "=== BEGIN LOGIN LOGS ===" << std::endl;
    std::clog << logs;
    std::clog << "=== END LOGIN LOGS ===" << std::endl;
  }
  REQUIRE(mkreport_close_response_good(re.get()));
}
