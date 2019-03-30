//
// Created by abdess on 10/4/18.
//
#pragma once

#include <string>
#include "../../src/debug/Debug.h"
#include "../../src/json/JsonData.h"
#include "../../src/json/JsonDataValueTypes.h"
#include "../../src/json/json.h"
#include "../../src/json/jsonparser.h"
#include "gtest/gtest.h"
#include "../../src/util/common.h"

using namespace json;

TEST(JSON_TEST, JSON_TEST1) {
  JsonObject root;
  root.emplace("description",make_unique<JsonDataValue>("get services of farm"));
  auto services = make_unique<JsonObject>();

  auto backends = make_unique<JsonArray>();
  auto backends1= make_unique<JsonObject>();
  auto backends2= make_unique<JsonObject>();


  backends1->emplace("alias",make_unique<JsonDataValue>("http-server-1"));
  backends1->emplace("id",make_unique<JsonDataValue>(0));
  backends1->emplace("ip",make_unique<JsonDataValue>("192.168.100.254"));
  backends1->emplace("port",make_unique<JsonDataValue>(80));
  backends1->emplace("status",make_unique<JsonDataValue>("up"));
  backends1->emplace("timeout",make_unique<JsonDataValue>(20));
  backends1->emplace("weight",make_unique<JsonDataValue>());

  backends2->emplace("alias",make_unique<JsonDataValue>("http-server-2"));
  backends2->emplace("id",make_unique<JsonDataValue>(0));
  backends2->emplace("ip",make_unique<JsonDataValue>("192.168.100.253"));
  backends2->emplace("port",make_unique<JsonDataValue>(80));
  backends2->emplace("status",make_unique<JsonDataValue>("up"));
  backends2->emplace("timeout",make_unique<JsonDataValue>(20));
  backends2->emplace("weight",make_unique<JsonDataValue>());

  backends->emplace_back(std::move(backends1));
  backends->emplace_back(std::move(backends2));
  services->emplace("backends",std::move(backends));

  services->emplace("cookiedomain",make_unique<JsonDataValue>("zevenet.cpm"));
  services->emplace("cookieinsert",make_unique<JsonDataValue>("true"));
  services->emplace("cookiename",make_unique<JsonDataValue>("peasocookie"));
  services->emplace("cookiepath",make_unique<JsonDataValue>("/patfh"));
  services->emplace("cookiettl",make_unique<JsonDataValue>(20));
  services->emplace("farmguardian",make_unique<JsonDataValue>("check_tcp-cut_conns"));
  services->emplace("httpsb",make_unique<JsonDataValue>(false));
  services->emplace("id",make_unique<JsonDataValue>("serv"));
  services->emplace("leastresp",make_unique<JsonDataValue>(false));
  services->emplace("persistence",make_unique<JsonDataValue>("COOKIE"));
  services->emplace("redirect",make_unique<JsonDataValue>(""));
  services->emplace("redirect_code",make_unique<JsonDataValue>(""));
  services->emplace("redirecttype",make_unique<JsonDataValue>(""));
  services->emplace("sessionid",make_unique<JsonDataValue>("JSESSIONID"));
  services->emplace("sts_status",make_unique<JsonDataValue>("false"));
  services->emplace("sts_timeout",make_unique<JsonDataValue>(0));
  services->emplace("ttl",make_unique<JsonDataValue>(18));
  services->emplace("vhost",make_unique<JsonDataValue>());

  root.emplace("services",std::move(services));
  std::string json_str = root.stringify();

  // TODO::fixme  root.freeJson();
  ASSERT_TRUE(true);
}

TEST(JSON_TEST, PARSER_TEST) {
  std::string json_string =
      "{\n"
      "    \"address\": \"0.0.0.0\",\n"
      "    \"port\": 8899,\n"
      "    \"services\": [\n"
      "        {\n"
      "            \"backends\": [\n"
      "                {\n"
      "                    \"address\": \"192.168.101.253\",\n"
      "                    \"connect-time\": 0,\n"
      "                    \"connections\": 0,\n"
      "                    \"id\": 1,\n"
      "                    \"name\": \"bck_1\",\n"
      "                    \"pending-connections\": 0,\n"
      "                    \"port\": 80,\n"
      "                    \"response-time\": 0,\n"
      "                    \"status\": \"active\",\n"
      "                    \"weight\": 5\n"
      "                },\n"
      "                {\n"
      "                    \"address\": \"192.168.101.254\",\n"
      "                    \"connect-time\": 0,\n"
      "                    \"connections\": 0,\n"
      "                    \"id\": 2,\n"
      "                    \"name\": \"bck_2\",\n"
      "                    \"pending-connections\": 0,\n"
      "                    \"port\": 80,\n"
      "                    \"response-time\": 0,\n"
      "                    \"status\": \"active\",\n"
      "                    \"weight\": 6\n"
      "                }\n"
      "            ],\n"
      "            \"id\": 1,\n"
      "            \"name\": \"srv1\",\n"
      "            \"sessions\": [\n"
      "                {\n"
      "                    \"backend-id\": 2,\n"
      "                    \"id\": \"127.0.0.1\",\n"
      "                    \"last-seen\": 1539952046\n"
      "                }\n"
      "            ],\n"
      "            \"status\": \"active\"\n"
      "        },\n"
      "        {\n"
      "            \"backends\": [\n"
      "                {\n"
      "                    \"address\": \"192.168.101.253\",\n"
      "                    \"connect-time\": 0,\n"
      "                    \"connections\": 0,\n"
      "                    \"id\": 1,\n"
      "                    \"name\": \"bck_1\",\n"
      "                    \"pending-connections\": 0,\n"
      "                    \"port\": 80,\n"
      "                    \"response-time\": 0,\n"
      "                    \"status\": \"active\",\n"
      "                    \"weight\": 5\n"
      "                },\n"
      "                {\n"
      "                    \"address\": \"192.168.101.254\",\n"
      "                    \"connect-time\": 0,\n"
      "                    \"connections\": 0,\n"
      "                    \"id\": 2,\n"
      "                    \"name\": \"bck_2\",\n"
      "                    \"pending-connections\": 0,\n"
      "                    \"port\": 80,\n"
      "                    \"response-time\": 0,\n"
      "                    \"status\": \"active\",\n"
      "                    \"weight\": 6\n"
      "                }\n"
      "            ],\n"
      "            \"id\": 2,\n"
      "            \"name\": \"srv2\",\n"
      "            \"sessions\": [],\n"
      "            \"status\": \"active\"\n"
      "        }\n"
      "    ]\n"
      "}";
  auto new_json = JsonParser::parse(json_string);
  auto str = new_json->stringify();
  json_string.erase(
      std::remove_if(json_string.begin(), json_string.end(), isspace),
      json_string.end());
  str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
  ASSERT_TRUE(json_string.length() == str.length());
}