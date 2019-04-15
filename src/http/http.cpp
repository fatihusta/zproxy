#include "http.h"
using namespace http;

const std::unordered_map<std::string, HTTP_HEADER_NAME>
    http_info::headers_names = {
        {"", HTTP_HEADER_NAME::NONE},
        {"Accept", HTTP_HEADER_NAME::ACCEPT},
        {"Accept-Charset", HTTP_HEADER_NAME::ACCEPT_CHARSET},
        {"Accept-Encoding", HTTP_HEADER_NAME::ACCEPT_ENCODING},
        {"Accept-Language", HTTP_HEADER_NAME::ACCEPT_LANGUAGE},
        {"Accept-Ranges", HTTP_HEADER_NAME::ACCEPT_RANGES},
        {"Access-Control-Allow-Credentials",
         HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_CREDENTIALS},
        {"Access-Control-Allow-Headers",
         HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_HEADERS},
        {"Access-Control-Allow-Methods",
         HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_METHODS},
        {"Access-Control-Allow-Origin",
         HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_ORIGIN},
        {"Access-Control-Expose-Headers",
         HTTP_HEADER_NAME::ACCESS_CONTROL_EXPOSE_HEADERS},
        {"Access-Control-Max-Age", HTTP_HEADER_NAME::ACCESS_CONTROL_MAX_AGE},
        {"Access-Control-Request-Headers",
         HTTP_HEADER_NAME::ACCESS_CONTROL_REQUEST_HEADERS},
        {"Access-Control-Request-Method",
         HTTP_HEADER_NAME::ACCESS_CONTROL_REQUEST_METHOD},
        {"Age", HTTP_HEADER_NAME::AGE},
        {"Allow", HTTP_HEADER_NAME::ALLOW},
        {"Authorization", HTTP_HEADER_NAME::AUTHORIZATION},
        {"Cache-Control", HTTP_HEADER_NAME::CACHE_CONTROL},
        {"Connection", HTTP_HEADER_NAME::CONNECTION},
        {"Content-Disposition", HTTP_HEADER_NAME::CONTENT_DISPOSITION},
        {"Content-Encoding", HTTP_HEADER_NAME::CONTENT_ENCODING},
        {"Content-Language", HTTP_HEADER_NAME::CONTENT_LANGUAGE},
        {"Content-Length", HTTP_HEADER_NAME::CONTENT_LENGTH},
        {"Content-Location", HTTP_HEADER_NAME::CONTENT_LOCATION},
        {"Content-Range", HTTP_HEADER_NAME::CONTENT_RANGE},
        {"Content-Security-Policy", HTTP_HEADER_NAME::CONTENT_SECURITY_POLICY},
        {"Content-Security-Policy-Report-Only",
         HTTP_HEADER_NAME::CONTENT_SECURITY_POLICY_REPORT_ONLY},
        {"Content-Type", HTTP_HEADER_NAME::CONTENT_TYPE},
        {"Cookie", HTTP_HEADER_NAME::COOKIE},
        {"Cookie2", HTTP_HEADER_NAME::COOKIE2},
        {"DNT", HTTP_HEADER_NAME::DNT},
        {"Date", HTTP_HEADER_NAME::DATE},
        {"Destination", HTTP_HEADER_NAME::DESTINATION},
        {"ETag", HTTP_HEADER_NAME::ETAG},
        {"Expect", HTTP_HEADER_NAME::EXPECT},
        {"Expect-CT", HTTP_HEADER_NAME::EXPECT_CT},
        {"Expires", HTTP_HEADER_NAME::EXPIRES},
        {"Forwarded", HTTP_HEADER_NAME::FORWARDED},
        {"From", HTTP_HEADER_NAME::FROM},
        {"Host", HTTP_HEADER_NAME::HOST},
        {"If-Match", HTTP_HEADER_NAME::IF_MATCH},
        {"If-Modified-Since", HTTP_HEADER_NAME::IF_MODIFIED_SINCE},
        {"If-None-Match", HTTP_HEADER_NAME::IF_NONE_MATCH},
        {"If-Range", HTTP_HEADER_NAME::IF_RANGE},
        {"If-Unmodified-Since", HTTP_HEADER_NAME::IF_UNMODIFIED_SINCE},
        {"Keep-Alive", HTTP_HEADER_NAME::KEEP_ALIVE},
        {"Large-Allocation", HTTP_HEADER_NAME::LARGE_ALLOCATION},
        {"Last-Modified", HTTP_HEADER_NAME::LAST_MODIFIED},
        {"Location", HTTP_HEADER_NAME::LOCATION},
        {"Origin", HTTP_HEADER_NAME::ORIGIN},
        {"Pragma", HTTP_HEADER_NAME::PRAGMA},
        {"Proxy-Authenticate", HTTP_HEADER_NAME::PROXY_AUTHENTICATE},
        {"Proxy-Authorization", HTTP_HEADER_NAME::PROXY_AUTHORIZATION},
        {"Public-Key-Pins", HTTP_HEADER_NAME::PUBLIC_KEY_PINS},
        {"Public-Key-Pins-Report-Only",
         HTTP_HEADER_NAME::PUBLIC_KEY_PINS_REPORT_ONLY},
        {"Range", HTTP_HEADER_NAME::RANGE},
        {"Referer", HTTP_HEADER_NAME::REFERER},
        {"Referrer-Policy", HTTP_HEADER_NAME::REFERRER_POLICY},
        {"Retry-After", HTTP_HEADER_NAME::RETRY_AFTER},
        {"Server", HTTP_HEADER_NAME::SERVER},
        {"Set-Cookie", HTTP_HEADER_NAME::SET_COOKIE},
        {"Set-Cookie2", HTTP_HEADER_NAME::SET_COOKIE2},
        {"SourceMap", HTTP_HEADER_NAME::SOURCEMAP},
        {"Strict-Transport-Security",
         HTTP_HEADER_NAME::STRICT_TRANSPORT_SECURITY},
        {"TE", HTTP_HEADER_NAME::TE},
        {"Timing-Allow-Origin", HTTP_HEADER_NAME::TIMING_ALLOW_ORIGIN},
        {"Tk", HTTP_HEADER_NAME::TK},
        {"Trailer", HTTP_HEADER_NAME::TRAILER},
        {"Transfer-Encoding", HTTP_HEADER_NAME::TRANSFER_ENCODING},
        {"Upgrade", HTTP_HEADER_NAME::UPGRADE},
        {"Upgrade-Insecure-Requests",
         HTTP_HEADER_NAME::UPGRADE_INSECURE_REQUESTS},
        {"User-Agent", HTTP_HEADER_NAME::USER_AGENT},
        {"Vary", HTTP_HEADER_NAME::VARY},
        {"Via", HTTP_HEADER_NAME::VIA},
        {"WWW-Authenticate", HTTP_HEADER_NAME::WWW_AUTHENTICATE},
        {"Warning", HTTP_HEADER_NAME::WARNING},
        {"X-Content-Type-Options", HTTP_HEADER_NAME::X_CONTENT_TYPE_OPTIONS},
        {"X-DNS-Prefetch-Control", HTTP_HEADER_NAME::X_DNS_PREFETCH_CONTROL},
        {"X-Forwarded-For", HTTP_HEADER_NAME::X_FORWARDED_FOR},
        {"X-Forwarded-Host", HTTP_HEADER_NAME::X_FORWARDED_HOST},
        {"X-Forwarded-Proto", HTTP_HEADER_NAME::X_FORWARDED_PROTO},
        {"X-Frame-Options", HTTP_HEADER_NAME::X_FRAME_OPTIONS},
        {"X-XSS-Protection", HTTP_HEADER_NAME::X_XSS_PROTECTION}};
const std::unordered_map<HTTP_HEADER_NAME, const std::string>
    http_info::headers_names_strings = {
        {HTTP_HEADER_NAME::NONE, ""},
        {HTTP_HEADER_NAME::ACCEPT, "Accept"},
        {HTTP_HEADER_NAME::ACCEPT_CHARSET, "Accept-Charset"},
        {HTTP_HEADER_NAME::ACCEPT_ENCODING, "Accept-Encoding"},
        {HTTP_HEADER_NAME::ACCEPT_LANGUAGE, "Accept-Language"},
        {HTTP_HEADER_NAME::ACCEPT_RANGES, "Accept-Ranges"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_CREDENTIALS,
         "Access-Control-Allow-Credentials"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_HEADERS,
         "Access-Control-Allow-Headers"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_METHODS,
         "Access-Control-Allow-Methods"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_ALLOW_ORIGIN,
         "Access-Control-Allow-Origin"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_EXPOSE_HEADERS,
         "Access-Control-Expose-Headers"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_MAX_AGE, "Access-Control-Max-Age"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_REQUEST_HEADERS,
         "Access-Control-Request-Headers"},
        {HTTP_HEADER_NAME::ACCESS_CONTROL_REQUEST_METHOD,
         "Access-Control-Request-Method"},
        {HTTP_HEADER_NAME::AGE, "Age"},
        {HTTP_HEADER_NAME::ALLOW, "Allow"},
        {HTTP_HEADER_NAME::AUTHORIZATION, "Authorization"},
        {HTTP_HEADER_NAME::CACHE_CONTROL, "Cache-Control"},
        {HTTP_HEADER_NAME::CONNECTION, "Connection"},
        {HTTP_HEADER_NAME::CONTENT_DISPOSITION, "Content-Disposition"},
        {HTTP_HEADER_NAME::CONTENT_ENCODING, "Content-Encoding"},
        {HTTP_HEADER_NAME::CONTENT_LANGUAGE, "Content-Language"},
        {HTTP_HEADER_NAME::CONTENT_LENGTH, "Content-Length"},
        {HTTP_HEADER_NAME::CONTENT_LOCATION, "Content-Location"},
        {HTTP_HEADER_NAME::CONTENT_RANGE, "Content-Range"},
        {HTTP_HEADER_NAME::CONTENT_SECURITY_POLICY, "Content-Security-Policy"},
        {HTTP_HEADER_NAME::CONTENT_SECURITY_POLICY_REPORT_ONLY,
         "Content-Security-Policy-Report-Only"},
        {HTTP_HEADER_NAME::CONTENT_TYPE, "Content-Type"},
        {HTTP_HEADER_NAME::COOKIE, "Cookie"},
        {HTTP_HEADER_NAME::COOKIE2, "Cookie2"},
        {HTTP_HEADER_NAME::DNT, "DNT"},
        {HTTP_HEADER_NAME::DATE, "Date"},
        {HTTP_HEADER_NAME::DESTINATION, "Destination"},
        {HTTP_HEADER_NAME::ETAG, "ETag"},
        {HTTP_HEADER_NAME::EXPECT, "Expect"},
        {HTTP_HEADER_NAME::EXPECT_CT, "Expect-CT"},
        {HTTP_HEADER_NAME::EXPIRES, "Expires"},
        {HTTP_HEADER_NAME::FORWARDED, "Forwarded"},
        {HTTP_HEADER_NAME::FROM, "From"},
        {HTTP_HEADER_NAME::HOST, "Host"},
        {HTTP_HEADER_NAME::IF_MATCH, "If-Match"},
        {HTTP_HEADER_NAME::IF_MODIFIED_SINCE, "If-Modified-Since"},
        {HTTP_HEADER_NAME::IF_NONE_MATCH, "If-None-Match"},
        {HTTP_HEADER_NAME::IF_RANGE, "If-Range"},
        {HTTP_HEADER_NAME::IF_UNMODIFIED_SINCE, "If-Unmodified-Since"},
        {HTTP_HEADER_NAME::KEEP_ALIVE, "Keep-Alive"},
        {HTTP_HEADER_NAME::LARGE_ALLOCATION, "Large-Allocation"},
        {HTTP_HEADER_NAME::LAST_MODIFIED, "Last-Modified"},
        {HTTP_HEADER_NAME::LOCATION, "Location"},
        {HTTP_HEADER_NAME::ORIGIN, "Origin"},
        {HTTP_HEADER_NAME::PRAGMA, "Pragma"},
        {HTTP_HEADER_NAME::PROXY_AUTHENTICATE, "Proxy-Authenticate"},
        {HTTP_HEADER_NAME::PROXY_AUTHORIZATION, "Proxy-Authorization"},
        {HTTP_HEADER_NAME::PUBLIC_KEY_PINS, "Public-Key-Pins"},
        {HTTP_HEADER_NAME::PUBLIC_KEY_PINS_REPORT_ONLY,
         "Public-Key-Pins-Report-Only"},
        {HTTP_HEADER_NAME::RANGE, "Range"},
        {HTTP_HEADER_NAME::REFERER, "Referer"},
        {HTTP_HEADER_NAME::REFERRER_POLICY, "Referrer-Policy"},
        {HTTP_HEADER_NAME::RETRY_AFTER, "Retry-After"},
        {HTTP_HEADER_NAME::SERVER, "Server"},
        {HTTP_HEADER_NAME::SET_COOKIE, "Set-Cookie"},
        {HTTP_HEADER_NAME::SET_COOKIE2, "Set-Cookie2"},
        {HTTP_HEADER_NAME::SOURCEMAP, "SourceMap"},
        {HTTP_HEADER_NAME::STRICT_TRANSPORT_SECURITY,
         "Strict-Transport-Security"},
        {HTTP_HEADER_NAME::TE, "TE"},
        {HTTP_HEADER_NAME::TIMING_ALLOW_ORIGIN, "Timing-Allow-Origin"},
        {HTTP_HEADER_NAME::TK, "Tk"},
        {HTTP_HEADER_NAME::TRAILER, "Trailer"},
        {HTTP_HEADER_NAME::TRANSFER_ENCODING, "Transfer-Encoding"},
        {HTTP_HEADER_NAME::UPGRADE, "Upgrade"},
        {HTTP_HEADER_NAME::UPGRADE_INSECURE_REQUESTS,
         "Upgrade-Insecure-Requests"},
        {HTTP_HEADER_NAME::USER_AGENT, "User-Agent"},
        {HTTP_HEADER_NAME::VARY, "Vary"},
        {HTTP_HEADER_NAME::VIA, "Via"},
        {HTTP_HEADER_NAME::WWW_AUTHENTICATE, "WWW-Authenticate"},
        {HTTP_HEADER_NAME::WARNING, "Warning"},
        {HTTP_HEADER_NAME::X_CONTENT_TYPE_OPTIONS, "X-Content-Type-Options"},
        {HTTP_HEADER_NAME::X_DNS_PREFETCH_CONTROL, "X-DNS-Prefetch-Control"},
        {HTTP_HEADER_NAME::X_FORWARDED_FOR, "X-Forwarded-For"},
        {HTTP_HEADER_NAME::X_FORWARDED_HOST, "X-Forwarded-Host"},
        {HTTP_HEADER_NAME::X_FORWARDED_PROTO, "X-Forwarded-Proto"},
        {HTTP_HEADER_NAME::X_FRAME_OPTIONS, "X-Frame-Options"},
        {HTTP_HEADER_NAME::X_XSS_PROTECTION, "X-XSS-Protection"},
        {HTTP_HEADER_NAME::X_SSL_SUBJECT, "X-SSL-Subject"},
        {HTTP_HEADER_NAME::X_SSL_CIPHER, "X-SSL-Cipher"},
        {HTTP_HEADER_NAME::X_SSL_ISSUER, "X-SSL-Issuer"},
        {HTTP_HEADER_NAME::X_SSL_SERIAL, "X-SSL-Serial"},
        {HTTP_HEADER_NAME::X_SSL_NOTBEFORE, "X-SSL-notBefore"},
        {HTTP_HEADER_NAME::X_SSL_NOTAFTER, "X-SSL-notAfter"},
        {HTTP_HEADER_NAME::X_SSL_CERTIFICATE, "X-SSL-Certificate"}};

const std::unordered_map<REQUEST_METHOD, const std::string>
    http_info::http_verb_strings{
        {REQUEST_METHOD::ACL, "ACL"},
        {REQUEST_METHOD::BASELINE_CONTROL, "BASELINE-CONTROL"},
        {REQUEST_METHOD::BCOPY, "BCOPY"},
        {REQUEST_METHOD::BDELETE, "BDELETE"},
        {REQUEST_METHOD::BIND, "BIND"},
        {REQUEST_METHOD::BMOVE, "BMOVE"},
        {REQUEST_METHOD::BPROPFIND, "BPROPFIND"},
        {REQUEST_METHOD::BPROPPATCH, "BPROPPATCH"},
        {REQUEST_METHOD::CHECKIN, "CHECKIN"},
        {REQUEST_METHOD::CHECKOUT, "CHECKOUT"},
        {REQUEST_METHOD::CONNECT, "CONNECT"},
        {REQUEST_METHOD::COPY, "COPY"},
        {REQUEST_METHOD::DELETE, "DELETE"},
        {REQUEST_METHOD::GET, "GET"},
        {REQUEST_METHOD::HEAD, "HEAD"},
        {REQUEST_METHOD::LABEL, "LABEL"},
        {REQUEST_METHOD::LINK, "LINK"},
        {REQUEST_METHOD::LOCK, "LOCK"},
        {REQUEST_METHOD::MERGE, "MERGE"},
        {REQUEST_METHOD::MKACTIVITY, "MKACTIVITY"},
        {REQUEST_METHOD::MKCALENDAR, "MKCALENDAR"},
        {REQUEST_METHOD::MKCOL, "MKCOL"},
        {REQUEST_METHOD::MKREDIRECTREF, "MKREDIRECTREF"},
        {REQUEST_METHOD::MKWORKSPACE, "MKWORKSPACE"},
        {REQUEST_METHOD::MOVE, "MOVE"},
        {REQUEST_METHOD::NOTIFY, "NOTIFY"},
        {REQUEST_METHOD::OPTIONS, "OPTIONS"},
        {REQUEST_METHOD::ORDERPATCH, "ORDERPATCH"},
        {REQUEST_METHOD::PATCH, "PATCH"},
        {REQUEST_METHOD::POLL, "POLL"},
        {REQUEST_METHOD::POST, "POST"},
        {REQUEST_METHOD::PRI, "PRI"},
        {REQUEST_METHOD::PROPFIND, "PROPFIND"},
        {REQUEST_METHOD::PROPPATCH, "PROPPATCH"},
        {REQUEST_METHOD::PUT, "PUT"},
        {REQUEST_METHOD::REBIND, "REBIND"},
        {REQUEST_METHOD::REPORT, "REPORT"},
        {REQUEST_METHOD::RPC_IN_DATA, "RPC_IN_DATA"},
        {REQUEST_METHOD::RPC_OUT_DATA, "RPC_OUT_DATA"},
        {REQUEST_METHOD::SEARCH, "SEARCH"},
        {REQUEST_METHOD::SUBSCRIBE, "SUBSCRIBE"},
        {REQUEST_METHOD::TRACE, "TRACE"},
        {REQUEST_METHOD::UNBIND, "UNBIND"},
        {REQUEST_METHOD::UNCHECKOUT, "UNCHECKOUT"},
        {REQUEST_METHOD::UNLINK, "UNLINK"},
        {REQUEST_METHOD::UNLOCK, "UNLOCK"},
        {REQUEST_METHOD::UNSUBSCRIBE, "UNSUBSCRIBE"},
        {REQUEST_METHOD::UPDATE, "UPDATE"},
        {REQUEST_METHOD::UPDATEREDIRECTREF, "UPDATEREDIRECTREF"},
        {REQUEST_METHOD::VERSION_CONTROL, "VERSION-CONTROL"},
        {REQUEST_METHOD::X_MS_ENUMATTS, "X_MS_ENUMATTS"}};

const std::unordered_map<std::string, REQUEST_METHOD> http_info::http_verbs = {
    {"ACL", REQUEST_METHOD::ACL},
    {"BASELINE-CONTROL", REQUEST_METHOD::BASELINE_CONTROL},
    {"BCOPY", REQUEST_METHOD::BCOPY},
    {"BDELETE", REQUEST_METHOD::BDELETE},
    {"BIND", REQUEST_METHOD::BIND},
    {"BMOVE", REQUEST_METHOD::BMOVE},
    {"BPROPFIND", REQUEST_METHOD::BPROPFIND},
    {"BPROPPATCH", REQUEST_METHOD::BPROPPATCH},
    {"CHECKIN", REQUEST_METHOD::CHECKIN},
    {"CHECKOUT", REQUEST_METHOD::CHECKOUT},
    {"CONNECT", REQUEST_METHOD::CONNECT},
    {"COPY", REQUEST_METHOD::COPY},
    {"DELETE", REQUEST_METHOD::DELETE},
    {"GET", REQUEST_METHOD::GET},
    {"HEAD", REQUEST_METHOD::HEAD},
    {"LABEL", REQUEST_METHOD::LABEL},
    {"LINK", REQUEST_METHOD::LINK},
    {"LOCK", REQUEST_METHOD::LOCK},
    {"MERGE", REQUEST_METHOD::MERGE},
    {"MKACTIVITY", REQUEST_METHOD::MKACTIVITY},
    {"MKCALENDAR", REQUEST_METHOD::MKCALENDAR},
    {"MKCOL", REQUEST_METHOD::MKCOL},
    {"MKREDIRECTREF", REQUEST_METHOD::MKREDIRECTREF},
    {"MKWORKSPACE", REQUEST_METHOD::MKWORKSPACE},
    {"MOVE", REQUEST_METHOD::MOVE},
    {"NOTIFY", REQUEST_METHOD::NOTIFY},
    {"OPTIONS", REQUEST_METHOD::OPTIONS},
    {"ORDERPATCH", REQUEST_METHOD::ORDERPATCH},
    {"PATCH", REQUEST_METHOD::PATCH},
    {"POLL", REQUEST_METHOD::POLL},
    {"POST", REQUEST_METHOD::POST},
    {"PRI", REQUEST_METHOD::PRI},
    {"PROPFIND", REQUEST_METHOD::PROPFIND},
    {"PROPPATCH", REQUEST_METHOD::PROPPATCH},
    {"PUT", REQUEST_METHOD::PUT},
    {"REBIND", REQUEST_METHOD::REBIND},
    {"REPORT", REQUEST_METHOD::REPORT},
    {"RPC_IN_DATA", REQUEST_METHOD::RPC_IN_DATA},
    {"RPC_OUT_DATA", REQUEST_METHOD::RPC_OUT_DATA},
    {"SEARCH", REQUEST_METHOD::SEARCH},
    {"SUBSCRIBE", REQUEST_METHOD::SUBSCRIBE},
    {"TRACE", REQUEST_METHOD::TRACE},
    {"UNBIND", REQUEST_METHOD::UNBIND},
    {"UNCHECKOUT", REQUEST_METHOD::UNCHECKOUT},
    {"UNLINK", REQUEST_METHOD::UNLINK},
    {"UNLOCK", REQUEST_METHOD::UNLOCK},
    {"UNSUBSCRIBE", REQUEST_METHOD::UNSUBSCRIBE},
    {"UPDATE", REQUEST_METHOD::UPDATE},
    {"UPDATEREDIRECTREF", REQUEST_METHOD::UPDATEREDIRECTREF},
    {"VERSION-CONTROL", REQUEST_METHOD::VERSION_CONTROL},
    {"X_MS_ENUMATTS", REQUEST_METHOD::X_MS_ENUMATTS}};

const std::unordered_map<validation::REQUEST_RESULT, const std::string>
    validation::request_result_reason = {
        {REQUEST_RESULT::OK, "valid request"},
        {REQUEST_RESULT::METHOD_NOT_ALLOWED, "Method not allowed"},
        {REQUEST_RESULT::BAD_REQUEST, "Bad request"},
        {REQUEST_RESULT::BAD_URL, "Bad URL"},
        {REQUEST_RESULT::URL_CONTAIN_NULL, "URL contains null"},
        {REQUEST_RESULT::REQUEST_TOO_LARGE, "Request too large"},
        {REQUEST_RESULT::SERVICE_NOT_FOUND, "no service"},
        {REQUEST_RESULT::BACKEND_NOT_FOUND, "no backend"},
        {REQUEST_RESULT::BACKEND_TIMEOUT, "Backend response timeout"},
};

const std::unordered_map<UPGRADE_PROTOCOLS, const std::string>
      http_info::upgrade_protocols_strings = {
        {UPGRADE_PROTOCOLS::WEBSOCKET, "websocket"},
        {UPGRADE_PROTOCOLS::H2C, "h2c"},
        {UPGRADE_PROTOCOLS::TLS, "tls"},
};

const std::unordered_map<std::string, UPGRADE_PROTOCOLS>
      http_info::upgrade_protocols = {
        {"websocket", UPGRADE_PROTOCOLS::WEBSOCKET},
        {"h2c", UPGRADE_PROTOCOLS::H2C},
        {"tls", UPGRADE_PROTOCOLS::TLS},
};

const std::unordered_map<std::string, CONNECTION_VALUES>
      http_info::connection_values = {
        {"Upgrade", CONNECTION_VALUES::UPGRADE},
        {"close", CONNECTION_VALUES::CLOSE},
        {"Keep-Alive", CONNECTION_VALUES::KEEP_ALIVE},
};

const std::unordered_map<http::TRANSFER_ENCODING_TYPE, const std::string>
    http_info::compression_types_strings = {
  {http::TRANSFER_ENCODING_TYPE::GZIP, "gzip"},
  {http::TRANSFER_ENCODING_TYPE::COMPRESS, "compress"},
  {http::TRANSFER_ENCODING_TYPE::DEFLATE, "deflate"},
  {http::TRANSFER_ENCODING_TYPE::BR, "br"},
  {http::TRANSFER_ENCODING_TYPE::IDENTITY, "identity"},
};

const std::unordered_map<std::string, http::TRANSFER_ENCODING_TYPE>
    http_info::compression_types = {
  {"gzip", http::TRANSFER_ENCODING_TYPE::GZIP},
  {"compress", http::TRANSFER_ENCODING_TYPE::COMPRESS},
  {"deflate", http::TRANSFER_ENCODING_TYPE::DEFLATE},
  {"br", http::TRANSFER_ENCODING_TYPE::BR},
  {"identity", http::TRANSFER_ENCODING_TYPE::IDENTITY},
};
