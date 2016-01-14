#include "xpath.hpp"

#include <cctype>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>

#include "pugixml.hpp"

using namespace std;

using namespace pugi;

StringVal xpath_query(FunctionContext* ctx, const StringVal& in, const StringVal& query, const StringVal& delim) {
 
 
  // make sure params are not null
  if (in.is_null || query.is_null) return StringVal::null();

  xml_document xml_document;

  ostringstream outputstream("");

  xml_parse_result hr = xml_document.load_buffer(in.ptr, in.len);

  xpath_node_set node_set = xml_document.select_nodes(reinterpret_cast<const char*>(query.ptr));
 
  for (xpath_node_set::const_iterator iter = node_set.begin(); iter != node_set.end(); ++iter) {
	xpath_node node = *iter;

	node.node().print(outputstream, "", pugi::format_raw);
	
	switch(node.node().type()) {
		case node_pcdata:
			if(iter + 1 != node_set.end()) outputstream << reinterpret_cast<const char*>(delim.ptr);
			break;
		default:
			break;
	}

  }

  string out = outputstream.str();

  StringVal result(ctx, out.size());
  memcpy(result.ptr, out.c_str(), out.size());

  return result;
}
