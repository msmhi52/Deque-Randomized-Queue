#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>
#include <random>
#include <algorithm>
#include <utility>

using namespace std;

template <typename Object>
class RandomizedQueue{
public:

	RandomizedQueue(): queue(NULL), queue_size(1), num_elements(0){
		queue = new Object [queue_size]; //with size 10, dynamically allocate memory.
	}

	bool isEmpty(){
		if(num_elements == 0) return true;
		else return false;
	}

	int size(){
		return num_elements;
	}

	void enqueue(Object item){
		if(num_elements == queue_size) resize(queue_size*2); //if queue is full, resize twice.
		queue[num_elements] = item;
		num_elements++;
	}

	Object dequeue(){
		if(num_elements) throw "cannot dequeue a empty queue!!";

		//generates random number.
		random_device rnd_dev;
		mt19937 generator(rnd_dev());
		uniform_int_distribution<size_t> distr(0, num_elements-1);
		size_t rand_num = distr(generator);		
		
		Object item = queue[rand_num];
		queue[rand_num]->~Object(); //delete element of queue
		if(rand_num != num_elements - 1) copy(queue + rand_num+1, queue + num_elements-1, queue + rand_num);

		if(num_elements > 0 && num_elements == queue_size/4) resize(queue_size/2);
		
		return item;
	}

	Object sample(){
		random_device rnd_dev;
		mt19937 generator(rnd_dev());
		uniform_int_distribution<size_t> distr(0, num_elements-1);
		
		size_t rand_num = distr(generator);

		return queue[rand_num];
	}

	Object& operator[](const size_t m_position) const{
		if(m_position > queue_size) throw out_of_range("Out of range error. Please put valid input.");
		return queue[m_position];
	}

	class iterator_t: public iterator<forward_iterator_tag, Object, ptrdiff_t, Object*, Object&> {
		size_t current;
		RandomizedQueue<Object> *randquu;

	public:
		iterator_t(size_t m, RandomizedQueue<Object> &rq): current(m), randquu(&rq){};

		iterator_t& operator++(){
			if(current >= randquu->num_elements) throw out_of_range("out of bounds iterator increment!");
			current += 1;
			return *this;
		}

		iterator_t operator++(int){
			if(current >= randquu->num_elements) throw out_of_range("out of bounds iterator increment!");
			iterator_t temp = *this;
			++(*this);
			return temp;
		}

		Object operator*() const{
			if(current >= randquu->num_elements) throw invalid_argument("Invalid iterator dereference!");
			return randquu->queue[current];
		}

		bool operator == (const iterator_t &rhs) const{
			return current == rhs.current;
		}

		bool operator != (const iterator_t &rhs) const{
			return current != rhs.current;
		}
	};

	iterator_t begin(){
		if(num_elements == 0) throw invalid_argument("Invalid iterator argument!");
		random_device rnd_dev;
		mt19937 generator(rnd_dev());
		for(size_t i = 0; i < num_elements; i++){
			uniform_int_distribution<size_t> distr(0, i);
			size_t r = distr(generator);
			swap(queue[r], queue[i]);
		}
		return iterator_t(0, *this);
	}

	iterator_t end(){
		if(num_elements == 0) throw invalid_argument("Invalid iterator argument!");
		return iterator_t(num_elements, *this);
	}

private:
	void resize(const size_t m_newsize){ 
		if(m_newsize < queue_size) throw "new size must be larger than original!!";
		Object* new_quu = new Object[m_newsize]; //newly dynamically allocate memory, with larger size.
		copy(queue, queue + queue_size, new_quu);

		delete[] queue;
		queue = new_quu;
		queue_size = m_newsize;
	};

	Object *queue;
	size_t queue_size;
	size_t num_elements;

};

