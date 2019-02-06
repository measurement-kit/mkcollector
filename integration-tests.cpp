#include "mkcollector.hpp"

#include <iostream>

#define MKCURL_INLINE_IMPL
#include "mkcurl.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "json.hpp"

static std::string collector_baseurl() {
  return "https://collector-sandbox.ooni.io";
}

static std::string open_report() {
  mk::collector::OpenRequest r;
  r.probe_asn = "AS30722";
  r.probe_cc = "IT";
  r.software_name = "mkcollector";
  r.software_version = "0.0.1";
  r.test_name = "dummy";
  r.test_version = "0.0.1";
  r.test_start_time = "2018-11-01 15:33:17";
  r.base_url = collector_baseurl();
  r.ca_bundle_path = "ca-bundle.pem";
  r.timeout = 14;
  mk::collector::OpenResponse re = mk::collector::open(r);
  {
    REQUIRE(re.logs.size() > 0);
    std::clog << "=== BEGIN OPEN LOGS ===" << std::endl;
    for (auto &s : re.logs) {
      std::clog << s << std::endl;
    }
    std::clog << "=== END OPEN LOGS ===" << std::endl;
  }
  REQUIRE(re.good);
  REQUIRE(re.report_id.size() > 0);
  return re.report_id;
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
  doc["software_name"] = "mkcollector";
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
  mk::collector::UpdateRequest r;
  r.report_id = report_id;
  r.content = dummy_report(report_id);
  r.base_url = collector_baseurl();
  r.ca_bundle_path = "ca-bundle.pem";
  r.timeout = 14;
  mk::collector::UpdateResponse re = mk::collector::update(r);
  {
    REQUIRE(re.logs.size() > 0);
    std::clog << "=== BEGIN UPDATE LOGS ===" << std::endl;
    for (auto &s : re.logs) {
      std::clog << s << std::endl;
    }
    std::clog << "=== END UPDATE LOGS ===" << std::endl;
  }
  REQUIRE(re.good);
}

TEST_CASE("We can open, update, and close a report") {
  std::string report_id = open_report();
  update_report(report_id);
  mk::collector::CloseRequest r;
  r.report_id = report_id;
  r.base_url = collector_baseurl();
  r.ca_bundle_path = "ca-bundle.pem";
  r.timeout = 14;
  mk::collector::CloseResponse re = mk::collector::close(r);
  {
    REQUIRE(re.logs.size() > 0);
    std::clog << "=== BEGIN CLOSE LOGS ===" << std::endl;
    for (auto &s : re.logs) {
      std::clog << s << std::endl;
    }
    std::clog << "=== END CLOSE LOGS ===" << std::endl;
  }
  REQUIRE(re.good);
}
