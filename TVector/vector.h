#pragma once
#include <iostream>
#include <cstdlib>
#include "memdata.h"

template<typename vector_type>
class Vector {
    MemData<vector_type> _mem;	// õðàíèëèùå äàííûõ + ðàçìåð  + âìåñòèìîñòü
    size_t _front;				// èíäåêñ ïåðâîãî ýëåìåíòà
    size_t _back;				// èíäåêñ ïîñëåäíåãî ýëåìåíòà

public:
	// êîíñòðóêòîðû
    Vector(size_t size = 0);					// êîíñòðóêòîð ïî ðàçìåðó + ïî óìîë÷àíèþ
    Vector(std::initializer_list<vector_type>); // êîíñòðóêòîð ïî ñïèñêó èíèöèàëèçàöèè
    Vector(vector_type*, size_t);               // êîíñòðóêòîð èíèöèàëèçàöèè
    Vector(const Vector<vector_type>&);         // êîíñòðóêòîð êîïèðîâàíèÿ
    Vector(Vector<vector_type>&&) noexcept;     // êîíñòðóêòîð ñ move-ñåìàíòèêîé
	// äåñòðóêòîð
    ~Vector() = default; //íàïèøåòñÿ êîìïèëÿòîðîì

	// ïóáëè÷íûå ìåòîäû ïðîâåðîê
	inline bool is_empty() const noexcept {			// íà ïóñòîòó
		return _mem.is_empty();
	}
	inline bool is_full() const noexcept {			// íà ïåðåïîëíåíèå
		return _mem.is_full();
	}

	// ãåòòåðû
	inline size_t get_size() const noexcept {		// ðàçìåðà
		return _mem._size;
	}
	inline size_t get_capacity() const noexcept {	// âìåñòèìîñòè
		return _mem._capacity;
	}
	inline vector_type get_front() const {			// ïåðâîãî ýëåìåíòà (âîçâð. êîïèþ)
		if (_mem._size != 0) {
			return (_mem._data)[_front];
		}
		else {
			throw std::logic_error("ERROR: Vector is empty! Can't get front");
		}
	}
	inline vector_type get_back() const {			// ïîñëåäíåãî ýëåìåíòà (âîçâð. êîïèþ)
		if (_mem._size != 0) {
			return (_mem._data)[_back];
		}
		else {
			throw std::logic_error("ERROR: Vector is empty! Can't get back");
		}
	}
	inline MemData<vector_type> get_mem_copy() const noexcept {            // êîïèè ìåìäàòû (äëÿ òåñòîâ)
		return _mem;
	}
	inline const MemData<vector_type>& get_mem_original() const noexcept { // îðèãèíàëà ìåìäàòû (äëÿ òåñòîâ íà move)
		return _mem;
	}

	// ñåòòåðû
	inline vector_type& front_ref() {				// ïåðâîãî ýëåìåíòà (âîçâð. ññûëêó)
		if (_mem._size != 0) {
			return (_mem._data)[_front];
		}
		else {
			throw std::logic_error("ERROR: Vector is empty! Can't set front");
		}
	}
	inline vector_type& back_ref() {				// ïîñëåäíåãî ýëåìåíòà (âîçâð. ññûëêó)
		if (_mem._size != 0) {
			return (_mem._data)[_back];
		}
		else {
			throw std::logic_error("ERROR: Vector is empty! Can't set back");
		}
	}

	// ïóáëè÷íûå ìåòîäû âñòàâîê
    void push_front(vector_type) noexcept;					// 1 ýëåìåíòà â íà÷àëî
    void push_front_many(vector_type*, size_t) noexcept;	// íåñêîëüêèõ â íà÷àëî
    void push_back(vector_type) noexcept;					// 1 ýëåìåíòà â êîíåö
    void push_back_many(vector_type*, size_t) noexcept;		// íåñêîëüêèõ â êîíåö
    void insert(vector_type, size_t);						// 1 ýëåìåíòà ïî ïîçèöèè
    void insert_many(vector_type*, size_t, size_t);			// íåñêîëüêèõ ïî ïîçèöèè

	// óäàëåíèé
    void pop_front();                               // 1 ýëåìåíòà èç íà÷àëà
    void pop_front_many(size_t);					// íåñêîëüêèõ èç íà÷àëà
    void pop_back();                                // 1 ýëåìåíòà èç êîíöà
    void pop_back_many(size_t);						// íåñêîëüêèõ èç êîíöà
    void erase(size_t);                             // 1 ýëåìåíòà ïî ïîçèöèè
    void erase_many(size_t, size_t);				// íåñêîëüêèõ ïî ïîçèöèè

	// ïåðåãðóçêè îïåðàòîðîâ
    Vector<vector_type>& operator=(const Vector<vector_type>&) noexcept;      // ïðèñâàèâàíèÿ
    Vector<vector_type>& operator=(Vector<vector_type>&&) noexcept;           // ïðèñâàèâàíèÿ ñ move-ñåìàíòèêîé
	vector_type operator[](size_t) const noexcept;       // îáðàùåíèÿ ïî èíäåêñó (íå èçì., âîçâð. êîïèþ)
    vector_type& operator[](size_t) noexcept;            // îáðàùåíèÿ ïî èíäåêñó (èçì., âîçâð. ññûëêó)

	// äðóæåñòâåííûå ôóíêöèè
	// ïåðåãðóçêè ââîäà-âûâîäà
	template <typename vector_type>
	friend std::ostream& operator<< (std::ostream&, const Vector<vector_type>&);	// âûâîäà
	template <typename vector_type>
	friend std::istream& operator>> (std::istream&, Vector<vector_type>&);			// ââîäà
	// ñîðòèðîâêè è ïåðåìåøèâàíèÿ
	template <typename vector_type>
    friend void quick_sort(Vector<vector_type>&);		// ñîðòèðîâêè (Õîàðà)
	template <typename vector_type>
	friend void shuffle(Vector<vector_type>&);	// ïåðåìåøèâàíèÿ (Ôèøåð-Éåòñà)

private:
	// ñëóæåáíûé ìåòîä ïîëó÷åíèÿ (ãåòòåð) ôèçè÷åñêîãî èíäåêñà ïî îòíîñèòåëüíîìó
	inline size_t get_mem_index(size_t i) const {
		return ((i + _front) % _mem._capacity);
	}
};
