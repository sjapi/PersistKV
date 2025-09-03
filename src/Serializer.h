#ifndef __SERIALIZER_HPP__
#define __SERIALIZER_HPP__

#include <string>

template <typename T>
class PersistKVSerializer {
public:
	static std::string serialize(const T& obj) {
		static_assert(sizeof(T) == 0, "Serializer not implemented for this type");
		return {};
	}

	static T deserialize(const std::string& data) {
		static_assert(sizeof(T) == 0, "Serializer not implemented for this type");
		return T{};
	}
private:
	PersistKVSerializer();
};

template <>
class PersistKVSerializer<int> {
public:
	static std::string serialize(const int& obj) {
		return std::to_string(obj);
	}

	static int deserialize(const std::string& data) {
		return std::stoi(data);
	}
private:
	PersistKVSerializer();
};

template <>
class PersistKVSerializer<double> {
public:
	static std::string serialize(const double& obj) {
		return std::to_string(obj);
	}

	static double deserialize(const std::string& data) {
		return std::stod(data);
	}
private:
	PersistKVSerializer();
};

template <>
class PersistKVSerializer<std::string> {
public:
	static std::string serialize(const std::string& obj) {
		return obj;
	}

	static std::string deserialize(const std::string& data) {
		return data;
	}
private:
	PersistKVSerializer();
};

template <>
class PersistKVSerializer<bool> {
public:
	static std::string serialize(const bool& obj) {
		return obj ? "1" : "0";
	}

	static bool deserialize(const std::string& data) {
		return data == "1";
	}
private:
	PersistKVSerializer();
};

#endif
