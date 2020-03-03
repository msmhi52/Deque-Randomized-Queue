#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>

using namespace std;

template <typename Object>
class node_t{
public:
        node_t(Object m_element): element(m_element), next(nullptr), prev(nullptr){};

        Object element;
        node_t* next;
        node_t* prev;
};

template <typename Object>
class Deque{
public:
	Deque():num_element(0), first(nullptr), last(nullptr){};

	bool isEmpty(){
		if(num_element == 0) return true;
		else return false;
	};

	size_t size(){
		return num_element;
	};	

	void addFirst(Object item){
		if(item == NULL) throw "Do not input NULL!!";

		if(!first)	first = last = new node_t<Object>(item);
		else{
			node_t<Object>* new_node = new node_t<Object>(item);
			first->prev = new_node;
			new_node->next = first;
			first = new_node;
		}
		num_element++;
	}
	
	void addLast(Object item){
		if(item == NULL) throw "Do not input NULL!!";

		if(!last)	first = last = new node_t<Object>(item);
		else{
			node_t<Object>* new_node = new node_t<Object>(item);
			last->next = new_node;
			new_node->prev = last;
			last = new_node;
		}
		num_element++;
	};
	
	Object removeFirst(){
		if(!first) throw "Deque is empty!!";

		Object item = first->element; //copy the element of the first to item
		first = first->next;
		delete first->prev; // explicitly delete old first in c++.
		first->prev = nullptr;
		num_element--;
		return item;
	};
	
	Object removeLast(){
		if(!last) throw "Deque is empty!!";

		Object item = last->element;
		last = last->prev;
		delete last->next;
		last->next = nullptr;
		num_element--;
		return item;
	};

	class iterator_t:public iterator<forward_iterator_tag, node_t<Object>, ptrdiff_t, node_t<Object>*, node_t<Object>& >{
		node_t<Object>* current;
	
	public:
		iterator_t(node_t<Object>* some_node): current(some_node){};
		
		iterator_t& operator++(){
			if(current == nullptr) throw "out of bounds iterator increment!";

			current = current->next;
			return *this;
		}
		iterator_t operator++(int){
			if(current == nullptr) throw "out of bounds iterator increment!";

			iterator_t tmp = *this;
			current = current->next;
			return tmp;
		}
		Object operator*() const{
			if(current == nullptr) throw "Invalid iterator dereference!";
			return current->element;
		}
		Object operator->() const{
			if(current == nullptr) throw "Invalid iterator dereference!";
			return current->element;
		}
		bool operator == (const iterator_t &rhs) const{
			return current == rhs.current;
		}
		bool operator != (const iterator_t &rhs) const{
			return current != rhs.current;
		}

	};
	iterator_t begin() {
		if(!first) throw "no deque has been made!!";
		return iterator_t(first);
	}
	iterator_t end() {
		if(!last) throw "no deque has been made!!";//can end be made if there is no deque?
		return iterator_t(last->next);
	}
private:
    size_t num_element;
    node_t<Object>* first;
    node_t<Object>* last;

};

int main(){
	try{
		Deque<double> dq;

		cout << dq.size() << "\n";
		dq.addFirst(1.1);
		dq.addLast(2.2);
		dq.addFirst(3.3);
		cout << dq.size() << "\n";
		dq.removeLast();
		dq.addLast(4.4);
		for(Deque<double>::iterator_t itr = dq.begin(); itr != dq.end(); ++itr){
			cout << *itr << " ";
		}
		dq.removeFirst();
		for(Deque<double>::iterator_t itr = dq.begin(); itr != dq.end(); itr++){
			cout << *itr << " ";
		}
	}
	catch(out_of_range& oor) {cout << "Out of Range error: " << oor.what() << "\n";}

	return 0;
}
