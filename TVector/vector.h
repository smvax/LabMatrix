#pragma once
#include <iostream>
#include <cstdlib>
#include "memdata.h"

template<typename vector_type>
class Vector {
    MemData<vector_type> _mem;	// хранилище данных + размер  + вместимость
    size_t _front;				// индекс первого элемента
    size_t _back;				// индекс последнего элемента

public:
	// конструкторы
    Vector(size_t size = 0);						// конструктор по размеру + по умолчанию
    Vector(std::initializer_list<vector_type>);		// конструктор по списку инициализации
    Vector(const vector_type*, size_t);				// конструктор инициализации
    Vector(const Vector<vector_type>&);				// конструктор копировани€
    Vector(Vector<vector_type>&&) noexcept;			// конструктор с move-семантикой
	// деструктор
    ~Vector() = default; //напишетс€ компил€тором

	// публичные методы проверок
	inline bool is_empty() const noexcept;			// на пустоту
	inline bool is_full() const noexcept;			// на переполнение

	// геттеры
	inline size_t get_size() const noexcept;			// размера
	inline size_t get_capacity() const noexcept;		// вместимости
	inline vector_type get_front() const;				// первого элемента (возвр. копию)
	inline vector_type get_front_idx() const;			// первого элемента (возвр. индекс) ƒЋя GTESTS
	inline vector_type get_back() const;				// последнего элемента (возвр. копию)
	inline vector_type get_back_idx() const;			// последнего элемента (возвр. индес) ƒЋя GTESTS
	inline MemData<vector_type> get_mem_copy() const noexcept;            // копии мемдаты (дл€ тестов)
	inline const MemData<vector_type>& get_mem_original() const noexcept; // оригинала мемдаты (дл€ тестов на move)

	// сеттеры
	inline vector_type& front_ref();						// первого элемента (возвр. ссылку)
	inline vector_type& back_ref();							// последнего элемента (возвр. ссылку)

	// публичные методы вставок
    void push_front(vector_type) noexcept;					// 1 элемента в начало
    void push_front_many(vector_type*, size_t) noexcept;	// нескольких в начало
    void push_back(vector_type) noexcept;					// 1 элемента в конец
    void push_back_many(vector_type*, size_t) noexcept;		// нескольких в конец
    void insert(vector_type, size_t);						// 1 элемента по позиции
    void insert_many(vector_type*, size_t, size_t);			// нескольких по позиции

	// удалений
    void pop_front();                               // 1 элемента из начала
    void pop_front_many(size_t);					// нескольких из начала
    void pop_back();                                // 1 элемента из конца
    void pop_back_many(size_t);						// нескольких из конца
    void erase(size_t);                             // 1 элемента по позиции
    void erase_many(size_t, size_t);				// нескольких по позиции
	void shrink_to_fit();							// неиспользуемой пам€ти

	// перегрузки операторов
    Vector<vector_type>& operator=(const Vector<vector_type>&) noexcept;      // присваивани€
    Vector<vector_type>& operator=(Vector<vector_type>&&) noexcept;           // присваивани€ с move-семантикой
	vector_type operator[](size_t) const noexcept;			// обращени€ по индексу (не изм., возвр. копию)
    vector_type& operator[](size_t) noexcept;				// обращени€ по индексу (изм., возвр. ссылку)

	// дружественные функции
	// перегрузки ввода-вывода
	template <typename vector_type>
	friend std::ostream& operator<< (std::ostream&, const Vector<vector_type>&);	// вывода
	template <typename vector_type>
	friend std::istream& operator>> (std::istream&, Vector<vector_type>&);			// ввода
	// сортировки и перемешивани€
	template <typename vector_type>
    friend void quick_sort(Vector<vector_type>&);		// сортировки (’оара)
	template <typename vector_type>
	friend void shuffle(Vector<vector_type>&);			// перемешивани€ (‘ишер-…етса)

private:
	// служебный метод получени€ (геттер) физического индекса по относительному
	inline size_t get_mem_index(size_t i) const;
};

// реализаци€ инлайновых методов в хедере, но вне класса
template<typename vector_type>
inline bool Vector<vector_type>::is_empty() const noexcept {
	return _mem.is_empty();
}
template<typename vector_type>
inline bool Vector<vector_type>::is_full() const noexcept {
	return _mem.is_full();
}
template<typename vector_type>
inline size_t  Vector<vector_type>::get_size() const noexcept {
	return _mem._size;
}
template<typename vector_type>
inline size_t  Vector<vector_type>::get_capacity() const noexcept {
	return _mem._capacity;
}
template<typename vector_type>
inline vector_type  Vector<vector_type>::get_front() const {
	if (_mem._size != 0) {
		return (_mem._data)[_front];
	}
	else {
		throw std::logic_error("ERROR: Vector is empty! Can't get front");
	}
}
template<typename vector_type>
inline vector_type  Vector<vector_type>::get_front_idx() const {
	if (_mem._size != 0) {
		return _front;
	}
	else {
		throw std::logic_error("ERROR: Vector is empty! Can't get front");
	}
}
template<typename vector_type>
inline vector_type Vector<vector_type>::get_back() const {
	if (_mem._size != 0) {
		return (_mem._data)[_back];
	}
	else {
		throw std::logic_error("ERROR: Vector is empty! Can't get back");
	}
}
template<typename vector_type>
inline vector_type Vector<vector_type>::get_back_idx() const {
	if (_mem._size != 0) {
		return _back;
	}
	else {
		throw std::logic_error("ERROR: Vector is empty! Can't get back");
	}
}
template<typename vector_type>
inline MemData<vector_type> Vector<vector_type>::get_mem_copy() const noexcept {
	return _mem;
}
template<typename vector_type>
inline const MemData<vector_type>& Vector<vector_type>::get_mem_original() const noexcept {
	return _mem;
}
template<typename vector_type>
inline vector_type& Vector<vector_type>::front_ref() {
	if (_mem._size != 0) {
		return (_mem._data)[_front];
	}
	else {
		throw std::logic_error("ERROR: Vector is empty! Can't set front");
	}
}
template<typename vector_type>
inline vector_type& Vector<vector_type>::back_ref() {
	if (_mem._size != 0) {
		return (_mem._data)[_back];
	}
	else {
		throw std::logic_error("ERROR: Vector is empty! Can't set back");
	}
}
template<typename vector_type>
inline size_t Vector<vector_type>::get_mem_index(size_t i) const {
	return ((i + _front) % _mem._capacity);
}