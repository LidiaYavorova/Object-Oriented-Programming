#pragma once
#include <iostream>

template <typename T>
class Vector {
public:
	Vector() {
		data = new T[1];
		size = 0;
		capacity = 1;
		reserve(8);

	}
	Vector(const Vector& other) {
		copyFrom(other);
	}
	Vector(Vector&& other) noexcept {
		moveFrom(std::move(other));
	}
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}

	Vector& operator=(Vector&& other) noexcept {
		if (this != &other) {
			free();
			moveFrom(std::move(other));
		}
		return *this;
	}

	~Vector() {
		free();
	}

	void reserve(size_t newCapacity) {
		if (newCapacity <= capacity) {
			return;
		}
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < size; i++) {
			newData[i] = std::move(data[i]);
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	void resize(size_t newSize) {
		if (newSize <= size) {
			return;
		}
		T* newData = new T[newSize];
		for (size_t i = 0; i < size; i++) {
			newData[i] = std::move(data[i]);
		}
		delete[] data;
		data = newData;
		capacity = newSize;
		size = newSize;
	}

	void push_back(const T& value) {

		if (size >= capacity) {
			reserve(capacity * 2);
		}
		data[size++] = value;
	}

	void push_back(T&& value) {
		if (size >= capacity) {
			reserve(capacity * 2);
		}
		data[size++] = std::move(value);
	}

	T* getData() {
		return data;
	}
	const T* getData() const {
		return data;
	}

	using iterator = T*;
	using const_iterator = const T*;
	iterator begin() { return data; }
	iterator end() { return data + size; }
	const_iterator begin() const { return data; }
	const_iterator end() const { return data + size; }

	size_t getSize() const {
		return size;
	}

	const T& operator[](int i) const {
		return data[i];
	}
	T& operator[](int i) {
		return data[i];
	}

private:
	T* data;
	size_t capacity;
	size_t size;

	void free() {
		delete[] data;
		data = nullptr;
		capacity = 0;
		size = 0;
	}

	void copyFrom(const Vector& other) {
		data = new T[other.capacity];
		for (size_t i = 0; i < other.size; i++) {
			data[i] = other.data[i];
		}
		capacity = other.capacity;
		size = other.size;
	}

	void moveFrom(Vector&& other) {
		data = other.data;
		other.data = nullptr;
		capacity = other.capacity;
		other.capacity = 0;
		size = other.size;
		other.size = 0;
	}
};
