//
// Created by abdess on 4/25/18.
//

#ifndef S_ZHTTP_SERVICE_H
#define S_ZHTTP_SERVICE_H

#include <vector>
#include "../config/pound_struct.h"
#include "../connection/connection.h"
#include "../config/BackendConfig.h"
#include "../http/HttpRequest.h"

class Service {

  std::vector<Backend *> backend_set;
 public:

  bool disabled;
  bool ignore_case;

 public:
  ServiceConfig &service_config;
  Backend *getBackend(Connection &connection);
  Service(ServiceConfig &service_config_);

  void addBackend(BackendConfig *backend_config, std::string address, int port, int backend_id);
  void addBackend(BackendConfig *backend_config, int backend_id);
  bool doMatch(HttpRequest &request);
};

#endif //S_ZHTTP_SERVICE_H