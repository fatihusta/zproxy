#include "httpsessionmanager.h"
#include <regex>

using namespace sessions;

std::mutex HttpSessionManager::lock_mtx;

HttpSessionManager::HttpSessionManager() : session_type(SESS_NONE) {}

HttpSessionManager::~HttpSessionManager() {
  for (auto &session : sessions_set) {
    delete session.second;
  }
}

SessionInfo *HttpSessionManager::addSession(HttpStream &stream,
                                            Backend &backend_to_assign) {
  if (this->session_type == sessions::SESS_NONE)
    return nullptr;
  // TODO::Implement

  std::string key("");
  switch (this->session_type) {
    case SESS_NONE:
      return nullptr;
    case SESS_IP: {
      key = stream.client_connection.getPeerAddress();
      break;
    }
    case SESS_COOKIE: {
      if(!stream.request.getHeaderValue(http::HTTP_HEADER_NAME::COOKIE, key)){
        return nullptr;
      }
      break;
    }
    case SESS_URL: {
      std::string url = stream.request.getUrl();
      key = stream.request.getQueryParameter(url, sess_id);
      break;
    }
    case SESS_PARM: {
      std::string url = stream.request.getUrl();
      key = stream.request.getUrlParameter(url);
      break;
    }
    case SESS_HEADER: {
      if(!stream.request.getHeaderValue(sess_id, key))
        key = "";
      break;
    }
    case SESS_BASIC:
      //TODO: IMPLEMENTAR IGUAL QUE POUND (NO HACER FALTA AUTHENTICATION)
      if(!stream.request.getHeaderValue(http::HTTP_HEADER_NAME::AUTHORIZATION, key)) {
          key = "";
      } else {
        std::stringstream string_to_iterate(key);
        std::istream_iterator<std::string> begin(string_to_iterate);
        std::istream_iterator<std::string> end;
        std::vector<std::string> header_value_parts(begin, end);
        //TODO: Decode base64
        if (header_value_parts[0] != "Basic") {
          key = "";
        } else {
          key = header_value_parts[1]; //Currently it stores username:password
        }
      }
      break;
  }
  // check if we have a new key to insert,
  if (!key.empty()) {
    auto new_session = new SessionInfo();
    new_session->assigned_backend = &backend_to_assign;
    std::lock_guard<std::mutex> locker(lock_mtx);
    sessions_set.emplace(std::make_pair(key, new_session));
    return new_session;
  }
  return nullptr;
}

void HttpSessionManager::deleteSession(HttpStream &stream) {
  std::lock_guard<std::mutex> locker(lock_mtx);
  auto ip_address = stream.client_connection.getPeerAddress();
  SessionInfo *session = nullptr;
  if ((session = sessions_set[ip_address]) != nullptr) {
    // we have a stored session
    delete session;
    if (sessions_set.erase(ip_address) < 1) {
      Debug::logmsg(LOG_DEBUG, "No session to delete for %s",
                    ip_address.c_str());
    }
  }
}

SessionInfo *HttpSessionManager::getSession(HttpStream &stream,
                                            bool update_if_exist) {
  std::string session_key("");
  SessionInfo *session = nullptr;
  switch (session_type) {
  case sessions::SESS_NONE:
    return nullptr;
  case sessions::SESS_IP: {
    session_key = stream.client_connection.getPeerAddress();
    // TODO::This must change !! no try catch !!!
    // sessions_set[ip_address];
    if (sessions_set.count(session_key) > 0) {
      session = this->sessions_set[session_key];
    }
    break;
  }
  case sessions::SESS_COOKIE: {
    std::string session_key;
    if(!stream.request.getHeaderValue(http::HTTP_HEADER_NAME::COOKIE, session_key)){
      session_key = "";
    } else {
      if (sessions_set.count(session_key) > 0) {
        session = this->sessions_set[session_key];
      }
    }
    break;
  }
  case sessions::SESS_URL: {
    std::string url = stream.request.getUrl();
    session_key = stream.request.getQueryParameter(url, sess_id);
    if (!session_key.empty() && sessions_set.count(session_key) > 0) {
      session = this->sessions_set[session_key];
    }
    break;
  }
  case sessions::SESS_PARM: {
      std::string url = stream.request.getUrl();
      session_key = stream.request.getUrlParameter(url);
      if (!session_key.empty() && sessions_set.count(session_key) > 0) {
          session = this->sessions_set[session_key];
      }
      break;
  }
  case sessions::SESS_HEADER: {
    std::string session_key;
    if (!stream.request.getHeaderValue(sess_id, session_key)) {
      session_key = "";
    } else {
      if (sessions_set.count(session_key) > 0)
        session = this->sessions_set[session_key];
    }
    break;
  }
    case sessions::SESS_BASIC: {
        if(!stream.request.getHeaderValue(http::HTTP_HEADER_NAME::AUTHORIZATION, session_key)) {
            session_key = "";
        } else {
          std::stringstream string_to_iterate(session_key);
          std::istream_iterator<std::string> begin(string_to_iterate);
          std::istream_iterator<std::string> end;
          std::vector<std::string> header_value_parts(begin, end);
          //TODO: Decode base64
          if (header_value_parts[0] != "Basic") {
            session_key = "";
          } else {
            session_key = header_value_parts[1]; //Currently it stores username:password
            if (sessions_set.count(session_key) > 0) {
              session = this->sessions_set[session_key];
            }
          }
        }
      }
  //TODO:
  default: { // For SESS_BASIC, SESS_HEADER and SESS_COOKIE
    break;
  }
  }
  if (session != nullptr) {
    // we have a stored session, check if it has not expired.
    if (!session->hasExpired(this->ttl)) {
      if (update_if_exist)
        session->update();
      return session;
    } else {
      // TODO::free session info ?? maybe  not and avoid reallocation of new
      // SessionInfo struct
      if (!update_if_exist) {
        sessions_set.erase(session_key);
        delete session;
      }
    }
  }

  return nullptr;
}

json::JsonArray *HttpSessionManager::getSessionsJson() {
  auto data = new json::JsonArray();
  for (auto &session : sessions_set) {
    auto json_data = new json::JsonObject();
    json_data->emplace(JSON_KEYS::ID, new json::JsonDataValue(session.first));
    json_data->emplace(
        JSON_KEYS::BACKEND_ID,
        new json::JsonDataValue(session.second->assigned_backend->backend_id));

    json_data->emplace(JSON_KEYS::LAST_SEEN_TS,
                       new json::JsonDataValue(session.second->getTimeStamp()));
    data->push_back(json_data);
  }
  return data;
}

bool HttpSessionManager::addSession(JsonObject *json_object, std::vector<Backend *> backend_set) {
    if (json_object == nullptr)
      return false;
    auto new_session = new SessionInfo();
    if (json_object->at(JSON_KEYS::BACKEND_ID)->isValue() && json_object->at(JSON_KEYS::ID)->isValue()) {
      int session_json_backend_id = static_cast<JsonDataValue*>(json_object->at(JSON_KEYS::BACKEND_ID))->number_value;
      for(auto backend : backend_set){
        if(backend->backend_id != session_json_backend_id) continue;
        new_session->assigned_backend = backend;
      }
      if (new_session->assigned_backend == nullptr)
        return false;
      std::lock_guard<std::mutex> locker(lock_mtx);
      std::string key = static_cast<JsonDataValue*>(json_object->at(JSON_KEYS::ID))->string_value;
      sessions_set.emplace(std::make_pair(key, new_session));
      return true;
    } else {
      return false;
    }
}

bool HttpSessionManager::deleteSession(JsonObject &json_object, std::vector<Backend *> backend_set) {
  if (json_object.count(JSON_KEYS::BACKEND_ID) > 0 && json_object.at(JSON_KEYS::BACKEND_ID)->isValue()) {
    Backend *bck = nullptr;
    int session_json_backend_id = static_cast<JsonDataValue*>(json_object.at(JSON_KEYS::BACKEND_ID))->number_value;
    for (auto backend : backend_set) {
        if(backend->backend_id != session_json_backend_id) continue;
        bck = backend;
    }

    if (bck == nullptr) return false;
    auto itr = sessions_set.begin();
    while (itr != sessions_set.end()) {
        if (itr->second->assigned_backend == bck) {
          sessions_set.erase(itr++);
        } else {
           ++itr;
        }
    }
    return true;
  } else  {
    if (json_object.count(JSON_KEYS::ID) > 0 && json_object.at(JSON_KEYS::ID)->isValue()) {
      std::string key = static_cast<JsonDataValue*>(json_object.at(JSON_KEYS::ID))->string_value;
      for(auto session : sessions_set) {
        if (session.first != key) continue;
        sessions_set.erase(key);
        return true;
      }
    }
    return false;
  }
}
