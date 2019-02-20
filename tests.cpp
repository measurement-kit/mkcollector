#include "mkmock.hpp"

MKMOCK_DEFINE_HOOK(open_response_error, int64_t);
MKMOCK_DEFINE_HOOK(open_response_status_code, int64_t);
MKMOCK_DEFINE_HOOK(open_response_body, std::string);
MKMOCK_DEFINE_HOOK(update_response_error, int64_t);
MKMOCK_DEFINE_HOOK(update_response_status_code, int64_t);
MKMOCK_DEFINE_HOOK(close_response_error, int64_t);
MKMOCK_DEFINE_HOOK(close_response_status_code, int64_t);

#define MKCURL_INLINE_IMPL
#include "mkcurl.hpp"

#define MKCOLLECTOR_MOCK
#define MKCOLLECTOR_INLINE_IMPL
#include "mkcollector.hpp"

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// clang-format off
const uint8_t binary_input[] = {
  0x57, 0xe5, 0x79, 0xfb, 0xa6, 0xbb, 0x0d, 0xbc, 0xce, 0xbd, 0xa7, 0xa0,
  0xba, 0xa4, 0x78, 0x78, 0x12, 0x59, 0xee, 0x68, 0x39, 0xa4, 0x07, 0x98,
  0xc5, 0x3e, 0xbc, 0x55, 0xcb, 0xfe, 0x34, 0x3c, 0x7e, 0x1b, 0x5a, 0xb3,
  0x22, 0x9d, 0xc1, 0x2d, 0x6e, 0xca, 0x5b, 0xf1, 0x10, 0x25, 0x47, 0x1e,
  0x44, 0xe2, 0x2d, 0x60, 0x08, 0xea, 0xb0, 0x0a, 0xcc, 0x05, 0x48, 0xa0,
  0xf5, 0x78, 0x38, 0xf0, 0xdb, 0x3f, 0x9d, 0x9f, 0x25, 0x6f, 0x89, 0x00,
  0x96, 0x93, 0xaf, 0x43, 0xac, 0x4d, 0xc9, 0xac, 0x13, 0xdb, 0x22, 0xbe,
  0x7a, 0x7d, 0xd9, 0x24, 0xa2, 0x52, 0x69, 0xd8, 0x89, 0xc1, 0xd1, 0x57,
  0xaa, 0x04, 0x2b, 0xa2, 0xd8, 0xb1, 0x19, 0xf6, 0xd5, 0x11, 0x39, 0xbb,
  0x80, 0xcf, 0x86, 0xf9, 0x5f, 0x9d, 0x8c, 0xab, 0xf5, 0xc5, 0x74, 0x24,
  0x3a, 0xa2, 0xd4, 0x40, 0x4e, 0xd7, 0x10, 0x1f
};
// clang-format on

TEST_CASE("We deal with open errors") {
  SECTION("On failure to serialize the request body") {
    mk::collector::OpenRequest request;
    request.probe_cc = std::string{(const char *)binary_input,
                                   sizeof(binary_input)};
    mk::collector::Settings settings;
    auto response = mk::collector::open(request, settings);
    REQUIRE(!response.good);
  }

  SECTION("On network error") {
    MKMOCK_WITH_ENABLED_HOOK(open_response_error, CURL_LAST, {
      mk::collector::OpenRequest request;
      mk::collector::Settings settings;
      auto response = mk::collector::open(request, settings);
      REQUIRE(!response.good);
    });
  }

  SECTION("On HTTP error") {
    MKMOCK_WITH_ENABLED_HOOK(open_response_error, 0, {
      MKMOCK_WITH_ENABLED_HOOK(open_response_status_code, 500, {
        mk::collector::OpenRequest request;
        mk::collector::Settings settings;
        auto response = mk::collector::open(request, settings);
        REQUIRE(!response.good);
      });
    });
  }

  SECTION("On invalid JSON body") {
    MKMOCK_WITH_ENABLED_HOOK(open_response_error, 0, {
      MKMOCK_WITH_ENABLED_HOOK(open_response_status_code, 200, {
        MKMOCK_WITH_ENABLED_HOOK(open_response_body, "{", {
          mk::collector::OpenRequest request;
          mk::collector::Settings settings;
          auto response = mk::collector::open(request, settings);
          REQUIRE(!response.good);
        });
      });
    });
  }
}

TEST_CASE("We deal with update errors") {
  SECTION("On failure to serialize the request body") {
    mk::collector::UpdateRequest request;
    request.content = "{";  // make content parsing fail
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  SECTION("When the data_format_version field is missing") {
    mk::collector::UpdateRequest request;
    request.content = "{}";
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  SECTION("When the data_format_version field is not a string") {
    mk::collector::UpdateRequest request;
    request.content = R"({"data_format_version": []})";
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  SECTION("When the data_format_version field is inconsistent") {
    mk::collector::UpdateRequest request;
    request.content = R"({"data_format_version": "0.1.0"})";
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  SECTION("When the report_id field is missing") {
    mk::collector::UpdateRequest request;
    request.content = R"({"data_format_version": "0.2.0"})";
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  SECTION("When the report_id field is not a string") {
    mk::collector::UpdateRequest request;
    request.content = R"({"data_format_version": "0.2.0", "report_id": []})";
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  std::string report_id = "20180208T095233Z_AS15169_O986SVua4krXdAnMx3aGC83INNJAo1GTZII2OwBQx2H4Qx0LKA";

  SECTION("When the report_id field is inconsistent") {
    mk::collector::UpdateRequest request;
    request.report_id = report_id;
    request.content = R"({"data_format_version": "0.2.0", "report_id": "xx"})";
    mk::collector::Settings settings;
    auto response = mk::collector::update(request, settings);
    REQUIRE(!response.good);
  }

  std::string minimal_good_content = R"({
    "data_format_version": "0.2.0",
    "report_id": "20180208T095233Z_AS15169_O986SVua4krXdAnMx3aGC83INNJAo1GTZII2OwBQx2H4Qx0LKA"
  })";

  SECTION("On network error") {
    MKMOCK_WITH_ENABLED_HOOK(update_response_error, CURL_LAST, {
      mk::collector::UpdateRequest request;
      request.content = minimal_good_content;
      request.report_id = report_id;
      mk::collector::Settings settings;
      auto response = mk::collector::update(request, settings);
      REQUIRE(!response.good);
    });
  }

  SECTION("On HTTP error") {
    MKMOCK_WITH_ENABLED_HOOK(update_response_error, 0, {
      MKMOCK_WITH_ENABLED_HOOK(update_response_status_code, 500, {
        mk::collector::UpdateRequest request;
        request.content = minimal_good_content;
        request.report_id = report_id;
        mk::collector::Settings settings;
        auto response = mk::collector::update(request, settings);
        REQUIRE(!response.good);
      });
    });
  }
}

TEST_CASE("We deal with close errors") {
  SECTION("On network error") {
    MKMOCK_WITH_ENABLED_HOOK(close_response_error, CURL_LAST, {
      mk::collector::CloseRequest request;
      mk::collector::Settings settings;
      auto response = mk::collector::close(request, settings);
      REQUIRE(!response.good);
    });
  }

  SECTION("On HTTP error") {
    MKMOCK_WITH_ENABLED_HOOK(close_response_error, 0, {
      MKMOCK_WITH_ENABLED_HOOK(close_response_status_code, 500, {
        mk::collector::CloseRequest request;
        mk::collector::Settings settings;
        auto response = mk::collector::close(request, settings);
        REQUIRE(!response.good);
      });
    });
  }
}

TEST_CASE("open_request_from_measurement works as expected") {
  SECTION("with good input") {
    auto str = R"({
      "probe_asn": "AS0",
      "probe_cc": "ZZ",
      "software_name": "mkcollector",
      "software_version": "0.0.1",
      "test_name": "dummy",
      "test_start_time": "2018-11-01 15:33:17",
      "test_version": "0.0.1"
    })";
    auto re = mk::collector::open_request_from_measurement(str);
    REQUIRE(re.good);
    REQUIRE(re.value.probe_asn == "AS0");
    REQUIRE(re.value.probe_cc == "ZZ");
    REQUIRE(re.value.software_name == "mkcollector");
    REQUIRE(re.value.software_version == "0.0.1");
    REQUIRE(re.value.test_name == "dummy");
    REQUIRE(re.value.test_start_time == "2018-11-01 15:33:17");
    REQUIRE(re.value.test_version == "0.0.1");
  }

  SECTION("with bad input") {
    auto re = mk::collector::open_request_from_measurement("{}");
    REQUIRE(!re.good);
  }
}
