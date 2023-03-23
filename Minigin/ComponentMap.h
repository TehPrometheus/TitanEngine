#pragma once
#include <atomic>
#include <unordered_map>

template <typename  ComponentType>
class ComponentMap
{
	class BaseComponent;
public:
	typedef typename std::unordered_map<int, ComponentType>::iterator iterator;
	typedef typename std::unordered_map<int, ComponentType>::const_iterator const_iterator;
	typedef typename std::unordered_map<int, ComponentType>::value_type value_type;

	const_iterator begin() const { return m_Map.begin(); };
	const_iterator end() const { return m_Map.end(); };
	iterator begin() { return m_Map.begin(); };
	iterator end() { return m_Map.end(); };

	template <typename Key>
	iterator find() { return m_Map.find(GetTypeId<Key>()); }

	template <typename Key>
	const_iterator find() const { return m_Map.find(GetTypeId<Key>()); }

	template <typename Key, typename ValueType>
	void add(ValueType value) { m_Map[GetTypeId<Key>()] = value; }

	template <typename Key>
	bool erase(bool freeMemory);

private:
	template <typename Key>
	static int GetTypeId();

	static std::atomic_int LastTypeId;
	std::unordered_map<int, ComponentType> m_Map;
};

template<typename ValueType>
std::atomic_int ComponentMap<ValueType>::LastTypeId(0);

template<typename ComponentType>
template<typename Key>
bool ComponentMap<ComponentType>::erase(bool freeMemory)
{
	auto it{ m_Map.find(GetTypeId<Key>()) };

	if (it != m_Map.end())
	{
		if(freeMemory)
			delete it->second;
		m_Map.erase(it);
		return true;
	}

	return false;
}

template<typename ValueType>
template<typename Key>
int ComponentMap<ValueType>::GetTypeId()
{
	static const int id = LastTypeId++;
	return id;
}
