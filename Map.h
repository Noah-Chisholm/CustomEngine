#pragma once
#include <vector>
#include <functional> // for std::hash

template<typename Key, typename Value>
class Map {
	struct Entry {
		Key key;
		Value value;
	};

public:
	Map(size_t initialBucketCount = 16)
		: Buckets(initialBucketCount) {
	}

	// Insert or update a key-value pair
	void Set(const Key& key, const Value& value) {
		size_t index = GetBucketIndex(key);
		for (auto& entry : Buckets[index]) {
			if (entry.key == key) {
				entry.value = value;
				return;
			}
		}
		Buckets[index].push_back({ key, value });
	}

	// Retrieve a pointer to the value (nullptr if not found)
	Value* Get(const Key& key) {
		size_t index = GetBucketIndex(key);
		for (auto& entry : Buckets[index]) {
			if (entry.key == key) {
				return &entry.value;
			}
		}
		return nullptr;
	}

	const Value* Get(const Key& key) const {
		size_t index = GetBucketIndex(key);
		for (const auto& entry : Buckets[index]) {
			if (entry.key == key) {
				return &entry.value;
			}
		}
		return nullptr;
	}

	const bool Find(const Key& key) const {
		size_t index = GetBucketIndex(key);
		for (const auto& entry : Buckets[index]) {
			if (entry.key == key) {
				return true;
			}
		}
		return false;
	}

	// Remove a key-value pair
	void Remove(const Key& key) {
		size_t index = GetBucketIndex(key);
		auto& bucket = Buckets[index];
		for (auto it = bucket.begin(); it != bucket.end(); ++it) {
			if (it->key == key) {
				bucket.erase(it);
				return;
			}
		}
	}

	// Clear all entries
	void Clear() {
		for (auto& bucket : Buckets) {
			bucket.clear();
		}
	}

	// Get the number of entries
	size_t Size() const {
		size_t size = 0;
		for (const auto& bucket : Buckets) {
			size += bucket.size();
		}
		return size;
	}

	// Check if the map is empty
	bool IsEmpty() const {
		return Size() == 0;
	}

	// Override [] operator for easy access
	Value& operator[](const Key& key) {
		size_t index = GetBucketIndex(key);
		for (auto& entry : Buckets[index]) {
			if (entry.key == key) {
				return entry.value;
			}
		}
		Buckets[index].push_back({ key, Value() });
		return Buckets[index].back().value;
	}



private:
	std::vector<std::vector<Entry>> Buckets;

	size_t GetBucketIndex(const Key& key) const {
		std::hash<Key> hasher;
		return hasher(key) % Buckets.size();
	}
};