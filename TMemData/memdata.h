#pragma once
#include <initializer_list>
#include <iostream>
#include <cstdlib>      // дл€ рандома
#include <ctime>
#include <string>       // дл€ std::getline
#include <sstream>      // дл€ std::istringstream

#define MEM_STEP 15             // шаг: сколько выдел€етс€ €чеек пам€ти минимум при добавлении эл-тов

template <typename vector_type>
class Vector;

template <typename vector_type>
class MemData {
    vector_type* _data;        // хранилище данных
    size_t _size;              // размер заполненной части хранилища
    size_t _capacity;          // вместимость хранилища

public: 
    // конструкторы
    MemData(size_t size = 0);                       // по размеру + по умолчанию
    MemData(std::initializer_list<vector_type>);    // по списку инициализации
    MemData(const vector_type*, size_t);            // инициализации
    MemData(const MemData&);                        // копировани€
    MemData(MemData&&) noexcept;                    // с move-семантикой
    // деструктор
    ~MemData();

    // публичные методы проверок
    inline bool is_empty() const noexcept;         // на пустоту

    // геттеры
    inline size_t get_size() const noexcept;                            // размера
    inline size_t get_capacity() const noexcept;                        // вместимости
    inline const vector_type* const get_data_const() const noexcept;    // хранилища (возвр указ-ль по которому Ќ≈Ћ№«я мен€ть)
    inline vector_type* const get_data_changeable() noexcept;           // хранилища (возвр указ-ль по которому ћќ∆Ќќ мен€ть)

    // сеттеры пам€ти и размера заполненной части
    void set_memory(size_t) noexcept;                                   // установка пам€ти без сохранени€ данных
    void reset_memory(size_t size, size_t start_index = 0);             // перевыделение пам€ти с сохранением данных
    void clear_memory() noexcept;                                       // очистка пам€ти
    inline void set_size(size_t size);                                  // установка размера заполненной части

    // операторы
    MemData& operator=(const MemData&) noexcept;                        // присваивани€
    MemData& operator=(MemData&&) noexcept;                             // присваивани€ с move-семантикой
    bool operator==(const MemData&) const noexcept;                     // сравнени€

    // друзь€шки:
    // -функции
    template <typename vector_type> // <----иначе не компилируетс€
    friend void quick_sort(MemData<vector_type>& md);                   // сортировки
    template <typename vector_type>
    friend void shuffle(MemData<vector_type>&);                         // перемешивани€

    // -классы
    friend class Vector<vector_type>;

private:
    // служебные методы
    inline bool is_full() const noexcept;                               // проверка на переполнение
};

// реализаци€ инлайновых методов в хедере, но вне класса
template <typename vector_type>
inline bool MemData<vector_type>::is_empty() const noexcept {
    return (_size == 0);
}
template <typename vector_type>
inline size_t MemData<vector_type>::get_size() const noexcept {
    return _size;
}
template <typename vector_type>
inline size_t MemData<vector_type>::get_capacity() const noexcept {
    return _capacity;
}
template <typename vector_type>
inline const vector_type* const MemData<vector_type>::get_data_const() const noexcept {
    return _data;
}
template <typename vector_type>
inline vector_type* const MemData<vector_type>::get_data_changeable() noexcept {
    return _data;
}
template <typename vector_type>
inline void MemData<vector_type>::set_size(size_t size) {
    if (size > _capacity) {
        throw std::invalid_argument("ERROR: Size is bigger than capacity!");
    }
    else {
        _size = size;
    }
}
template <typename vector_type>
inline bool MemData<vector_type>::is_full() const noexcept {
    return (_size >= _capacity);
}

// функции вне класса
int calculate_capacity(size_t);     // какую вместимость выставить при заданном кол-ве эл-тов
template <typename vector_type>
void quick_sort_recursive(vector_type* data, int left, int right); 
template <typename vector_type>
int partition(vector_type* data, int left, int right);