#include <iostream>
#include <string>
#include <map>
#include <vector>

enum class SetType {
	Inf = -1,
	Fin
};
template <typename T>
struct Content {
	std::vector<T> vec;
	T* finarr = nullptr;
};
template <typename T>
class Set {
private:
	Content<T> content;
	SetType type;
	void linkItem(T value) {
		if (!std::count(content.vec.begin(), content.vec.end(), value)) {
			content.vec.push_back(value);
		}
	}
	void addElement(T value) {
		if (Capacity >= MaxCapacity) return;
		for (int i = 0; i < Capacity; i++)
			if (content.finarr[i] == value)
				return;
		content.finarr[Capacity] = value;
		Capacity++;
	}
	bool inf() {
		return type == SetType::Inf;
	}
public:
	const std::string Name;
	const int MaxCapacity;
	int Capacity = 0;
	Set(int capacity, std::string name):MaxCapacity(capacity), Name(name) {
		if (capacity < 0) {
			type = SetType::Inf;
			content.vec = std::vector<T>();
		}
		else if (capacity >= 0) {
			type = SetType::Fin;
			content.finarr = new T[capacity];
		}
	}
	bool operator==(const Set<T>& rv) {
		if (this->Capacity != rv.Capacity) return false;
		if (this->Values() != rv.Values()) return false;
		return true;
	}
	std::vector<T> Values() {
		if (inf()) {
			return content.vec;
		}
		else {
			std::vector<T> values;
			for (int i = 0; i < Capacity; i++)
				values.push_back(content.finarr[i]);
			return values;
		}
	}
	void Add(T value) {
		if (inf()) {
			linkItem(value);
		}
		else {
			addElement(value);
		}
	}
	void Add(std::vector<T> values) {
		for (T x : values)
			Add(x);
	}
	Set<T> Sum(Set<T> set) {
		Set<T> result = *this;
		result.Name = this->Name + "¡ú" + set.Name;
		result->Add(set.Values());
		return result;
	}
	Set<T> Intersection(Set<T> set) {
		Set<T> result((int)set.type, this->Name+"¡û"+set.Name);
		for (T x : set.Values())
			for (T x2 : this->Values())
				if (x == x2) result.Add(x);
		return result;
	}
	Set<T> Difference(Set<T> set) {
		Set<T> result((int)set.type, this->Name + "-" + set.Name);
		for (T x : this->Values()) {
			int c = 0;
			for (T x2 : set.Values()) {
				if (x == x2) c++;
			}
			if (c == 0) result.Add(x);
		}
		return result;
	}
	Set<T> Complementary(Set<T> U) {
		Set<T> result((int)U.type, this->Name+"c");
		for (T x : U.Values()) {
			int c = 0;
			for (T x2 : this->Values()) {
				if (x == x2) c++;
			}
			if (c == 0) result.Add(x);
		}
		return result;
	}
	void PPrint() {
		std::vector<T> values;
		if (inf())
			for (int i = 0; i < content.vec.size(); i++)
				values.push_back(content.vec[i]);
		else 
			for (int i = 0; i < Capacity; i++) 
				values.push_back(content.finarr[i]);
		std::cout << Name << " = { ";
		int i = 0;
		for (; i < values.size() - 1; i++)
			std::cout << values[i] << ", ";
		std::cout << values[i] << " }" << std::endl;
	}
};