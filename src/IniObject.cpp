#include "IniObject.h"

std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& IniObject::Data() {
	return _dataMap;
}
std::unordered_map<std::string, std::string>& IniObject::SectionData(const std::string& section) {
	if (auto ite = _dataMap.find(section); ite != _dataMap.end()) {
		return ite->second;
	}
	static std::unordered_map<std::string, std::string> _emptyData;
	return _emptyData;
}

bool IniObject::HasSection(const std::string& section) const {
	return _dataMap.find(section) != _dataMap.end();
}

bool IniObject::HasKey(const std::string& section, const std::string& key) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		return iteSection->second.find(key) != iteSection->second.end();
	}
	return false;
}

const std::string& IniObject::GetString(const std::string& section, const std::string& key, const std::string& defaultValue) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		if (auto ite = iteSection->second.find(key); ite != iteSection->second.end()) {
			return ite->second;
		}
	}
	return defaultValue;
}
double IniObject::GetDouble(const std::string& section, const std::string& key, double defaultValue) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		if (auto ite = iteSection->second.find(key); ite != iteSection->second.end()) {
			std::size_t pos;
			double ret = std::stod(ite->second, &pos);
			if (pos > 0) {
				return ret;
			}
		}
	}
	return defaultValue;
}
float IniObject::GetFloat(const std::string& section, const std::string& key, float defaultValue) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		if (auto ite = iteSection->second.find(key); ite != iteSection->second.end()) {
			try {
				std::size_t pos;
				float ret = std::stof(ite->second, &pos);
				if (pos > 0) {
					return ret;
				}
			} catch (...) {
				return defaultValue;
			}
		}
	}
	return defaultValue;
}
int IniObject::GetInt(const std::string& section, const std::string& key, int defaultValue) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		if (auto ite = iteSection->second.find(key); ite != iteSection->second.end()) {
			try {
				std::size_t pos;
				int ret = std::stoi(ite->second, &pos);
				if (pos > 0) {
					return ret;
				}
			} catch (...) {
				return defaultValue;
			}
		}
	}
	return defaultValue;
}
long long IniObject::GetInt64(const std::string& section, const std::string& key, long long defaultValue) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		if (auto ite = iteSection->second.find(key); ite != iteSection->second.end()) {
			try {
				std::size_t pos;
				long long ret = std::stoll(ite->second, &pos);
				if (pos > 0) {
					return ret;
				}
			} catch (...) {
				return defaultValue;
			}
		}
	}
	return defaultValue;
}
bool IniObject::GetBool(const std::string& section, const std::string& key, bool defaultValue) const {
	if (auto iteSection = _dataMap.find(section); iteSection != _dataMap.end()) {
		if (auto ite = iteSection->second.find(key); ite != iteSection->second.end()) {
			const auto& value = ite->second;
			for (std::size_t i = 0; i < value.size(); ++i) {
				char ch = value[i];
				if (ch == ' ' || ch == '\t') {
					continue;
				}
				// true
				if (ch == 'T' || ch == 't') {
					if (i + 3 >= value.size()) {
						break;
					}
					if (ch = value[i + 1]; ch != 'U' && ch != 'u') {
						break;
					}
					if (ch = value[i + 2]; ch != 'R' && ch != 'r') {
						break;
					}
					if (ch = value[i + 3]; ch != 'E' && ch != 'e') {
						break;
					}
					return true;
				}
				// false
				if (ch == 'F' || ch == 'f') {
					if (i + 4 >= value.size()) {
						break;
					}
					if (ch = value[i + 1]; ch != 'A' && ch != 'a') {
						break;
					}
					if (ch = value[i + 2]; ch != 'L' && ch != 'l') {
						break;
					}
					if (ch = value[i + 3]; ch != 'S' && ch != 's') {
						break;
					}
					if (ch = value[i + 4]; ch != 'E' && ch != 'e') {
						break;
					}
					return false;
				}
				break;
			}
		}
	}
	return defaultValue;
}

void IniObject::Set(const std::string& section, const std::string& key, const std::string& value) {
	_dataMap[section][key] = value;
}
void IniObject::Set(const std::string& section, const std::string& key, double value) {
	_dataMap[section][key] = std::to_string(value);
}
void IniObject::Set(const std::string& section, const std::string& key, float value) {
	_dataMap[section][key] = std::to_string(value);
}
void IniObject::Set(const std::string& section, const std::string& key, int value) {
	_dataMap[section][key] = std::to_string(value);
}
void IniObject::Set(const std::string& section, const std::string& key, long long value) {
	_dataMap[section][key] = std::to_string(value);
}
void IniObject::Set(const std::string& section, const std::string& key, bool value) {
	_dataMap[section][key] = value ? "true" : "false";
}
