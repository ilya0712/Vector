#include <iostream>


template<typename T>
class Vector
{
private:
	T* arr;
	size_t size;
	size_t capacity;
public:
	Vector() { arr = nullptr; size = 0; capacity = 0; }
	Vector(const int& value) { reserve(2 * value); }

	size_t getSize() const { return size; }
	size_t getCapacity() const { return capacity; }

	void reserve(const int& value);
	void resize(const int& value, const T& object = T());
	void push_back(const int& value);
	void pop_back();
	void print() const;

};



template<typename T>
void Vector<T>::reserve(const int& value)
{
	if (value <= capacity)
		return;
	T* newArray = nullptr;
	try
	{
		newArray = reinterpret_cast<T*>(new int8_t[value * sizeof(T)]);
		for (unsigned int i = 0; i < size; ++i)
		{
			new (newArray + i) T(arr[i]);
		}
	}
	catch (...)
	{
		std::cout << "Exception because of reserve...\n";
		for (unsigned int i = 0; i < size; i++)
			(newArray + i)->~T();
		delete[] reinterpret_cast<int8_t*>(newArray);
		throw;
	}

	for (unsigned int i = 0; i < size; i++)
	{
		(arr + i)->~T();
	}

	delete[] reinterpret_cast<int8_t*>(arr);
	arr = newArray;
	capacity = value;
}


template<typename T>
void Vector<T>::resize(const int& value, const T& object)
{
	if (value == size)
		return;

	try
	{
		if (value > capacity)
		{
			reserve(value);
			for (unsigned int i = size; i < value; i++)
				new (arr + i) T(object);
		}
	}
	catch (...)
	{
		std::cout << "Exception because of resize...\n";
		for (unsigned int i = 0; i < size; i++)
			(arr + i)->~T();
		delete[] reinterpret_cast<int8_t*>(arr);
		throw;
	}

	if (value < size)
	{
		for (unsigned int i = value; i < size; i++)
		{
			(arr + i)->~T();
			delete[] reinterpret_cast<int8_t*>(arr + i);
		}
	}
	size = value;
}


template<typename T>
void Vector<T>::push_back(const int& value)
{
	if (!capacity && !size)
		reserve(1);
	if (size == capacity)
		reserve(2 * size);
	new (arr + size) T(value);
	++size;
}


template<typename T>
void Vector<T>::pop_back()
{
	--size;
	(arr + size)->~T();
}


template<typename T>
void Vector<T>::print() const
{
	for (unsigned int i = 0; i < size; i++)
		std::cout << arr[i] << " ";
	std::cout << '\n';
}


int main()
{
	
	try
	{
		Vector<int> vector(10);
		for (unsigned int i = 0; i < 10; i++)
			vector.push_back(i);
		vector.print();

		vector.pop_back();

		vector.print(); 
		std::cout << vector.getCapacity() << '\n';
		std::cout << vector.getSize() << '\n';
	}
	catch (...)
	{
		std::cout << "Caught exception in main\n";
	}

	return 0;
}