#include "waf.h"

bool Waf::checkRequestWaf(HttpStream &stream)
{
	std::string httpVersion = stream.request.getHttpVersion();
	std::string httpMethod(stream.request.method,
			       stream.request.method_len);

	modsecurity::intervention::reset(&stream.modsec_transaction->m_it);
	stream.modsec_transaction->processConnection(
		stream.client_connection.getPeerAddress().data(),
		stream.client_connection.getPeerPort(),
		stream.client_connection.getLocalAddress().data(),
		stream.client_connection.getLocalPort());

	stream.modsec_transaction->processURI(stream.request.path.data(),
					      httpMethod.data(),
					      httpVersion.data());

	for (int i = 0; i < static_cast<int>(stream.request.num_headers); i++) {
		auto name = reinterpret_cast<unsigned char *>(
			const_cast<char *>(stream.request.headers[i].name));
		auto value = reinterpret_cast<unsigned char *>(
			const_cast<char *>(stream.request.headers[i].value));
		stream.modsec_transaction->addRequestHeader(
			name, stream.request.headers[i].name_len, value,
			stream.request.headers[i].value_len);
	}
	stream.modsec_transaction->processRequestHeaders();

	if (stream.request.message_length == 0 &&
	    stream.request.content_length != 0) {
		if (MAX_DATA_SIZE - stream.client_connection.buffer_size < 0) {
			streamLogMessage(
				&stream,
				"the request body is not checked because it could overload the connection buffer");
		} else {
			stream.client_connection.read();
			stream.request.message_length =
				stream.request.content_length;
		}
	}

	if (stream.request.message_length > 0) {
		stream.modsec_transaction->appendRequestBody(
			(unsigned char *)stream.request.message,
			stream.request.message_length);
	}
	stream.modsec_transaction->processRequestBody();

	// Checking interaction
	if (stream.modsec_transaction->m_it.disruptive) {
		if (stream.modsec_transaction->m_it.log != nullptr) {
			streamLogWaf(&stream, "%s",
				     stream.modsec_transaction->m_it.log);
		} else
			streamLogWaf(
				&stream,
				"WAF in request disrupted the HTTP transaction");

		// redirect returns disruptive=1

		// process is going to be cut. Executing the logging phase
		if (!stream.modsec_transaction->processLogging())
			zcu_log_print(LOG_ERR,
				      "(%lx) WAF, error processing the log",
				      pthread_self());

		return true;
	}

	return false;
}

bool Waf::checkResponseWaf(HttpStream &stream)
{
	std::string httpVersion = stream.response.getHttpVersion();

	modsecurity::intervention::reset(&stream.modsec_transaction->m_it);
	for (int i = 0; i < static_cast<int>(stream.response.num_headers);
	     i++) {
		if (stream.response.headers[i].header_off)
			continue;
		auto name = reinterpret_cast<unsigned char *>(
			const_cast<char *>(stream.response.headers[i].name));
		auto value = reinterpret_cast<unsigned char *>(
			const_cast<char *>(stream.response.headers[i].value));
		stream.modsec_transaction->addResponseHeader(
			name, stream.response.headers[i].name_len, value,
			stream.response.headers[i].value_len);
	}

	stream.modsec_transaction->processResponseHeaders(
		stream.response.http_status_code, httpVersion);

	if (stream.response.message_length == 0 &&
	    stream.response.content_length != 0) {
		if (MAX_DATA_SIZE - stream.backend_connection.buffer_size < 0) {
			streamLogMessage(
				&stream,
				"the response body is not checked because it could overload the connection buffer");
		} else {
			stream.backend_connection.read();
			stream.response.message_length =
				stream.response.content_length;
		}
	}

	if (stream.response.message_length > 0) {
		stream.modsec_transaction->appendResponseBody(
			reinterpret_cast<unsigned char *>(
				stream.response.message),
			stream.response.message_length);
	}

	stream.modsec_transaction->processResponseBody();

	stream.modsec_transaction->processLogging();
	// Checking interaction
	if (stream.modsec_transaction->m_it.disruptive) {
		if (stream.modsec_transaction->m_it.log != nullptr) {
			streamLogWaf(&stream, "%s",
				     stream.modsec_transaction->m_it.log);
		} else
			streamLogWaf(
				&stream,
				"WAF in response disrupted the HTTP transaction");
		stream.modsec_transaction
			->processLogging(); // TODO:: is it necessary??

		return true;
	}
	return false;
}

// todo: parse only the directives of a listener
std::shared_ptr<Rules> Waf::reloadRules()
{
	int err = 0;
	regex_t WafRules;
	char lin[ZCU_DEF_BUFFER_SIZE];
	regmatch_t matches[5];
	Config config;
	config.init(global::StartOptions::getCurrent());
	auto rules = std::make_shared<Rules>();
	zcu_log_print(LOG_NOTICE, "file to update %s",
		      global::StartOptions::getCurrent().conf_file_name.data());

	if (regcomp(&WafRules, "^[ \t]*WafRules[ \t]+\"(.+)\"[ \t]*$",
		    REG_ICASE | REG_NEWLINE | REG_EXTENDED))
		return nullptr;

	// compile regexp
	while (config.conf_fgets(lin, ZCU_DEF_BUFFER_SIZE) && !err) {
		if (!regexec(&WafRules, lin, 4, matches, 0)) {
			lin[matches[1].rm_eo] = '\0';
			auto file = std::string(lin + matches[1].rm_so,
						lin + matches[1].rm_eo - lin +
							matches[1].rm_so);
			err = rules->loadFromUri(file.data());
			if (err == -1) {
				zcu_log_print(
					LOG_ERR,
					"Error loading waf ruleset file %s: %s",
					file.data(),
					rules->getParserError().data());
				return nullptr;
			}
		}
	}
	// enable for debug purpose only
	// dumpRules(*rules);
	zcu_log_print(LOG_INFO, "The WAF rulesets waf reloaded properly");
	return rules;
}

void Waf::dumpRules(modsecurity::Rules &rules)
{
	zcu_log_print(LOG_DEBUG, "Rules: ");
	for (int i = 0; i <= modsecurity::Phases::NUMBER_OF_PHASES; i++) {
		auto rule = rules.getRulesForPhase(i);
		if (rule) {
			for (auto &x : *rule) {
				zcu_log_print(LOG_DEBUG,
					      "\tRule Id: %d From %s at %d ",
					      x->m_ruleId, x->m_fileName.data(),
					      x->m_lineNumber);
			}
		}
	}
}
