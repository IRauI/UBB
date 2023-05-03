#include "Validator.h"
#include <assert.h>
#include <sstream>

void ActivityValidator::validate(const Activity& a) {
	vector<string> msgs;
	if (a.getDuration() <= 0) msgs.push_back("Durata negativa!!!");
	if (a.getType().size() == 0) msgs.push_back("Tip vid!!!");
	if (a.getTitle().size() == 0) msgs.push_back("Titlu vid!!!");
	if (a.getDescription().size() == 0) msgs.push_back("Descriere vida!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << "\n";
	}
	return out;
}

void testValidator() {
	ActivityValidator v;
	Activity a{ "","","",-1 };
	try {
		v.validate(a);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("tip") >= 0);
		assert(mesaj.find("titlu") >= 0);
		assert(mesaj.find("durata") >= 0);
		assert(mesaj.find("descriere") >= 0);
	}

}