#ifndef unrolled_h_
#define unrolled_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <iostream>
const int num_elements_per_node = 6;

// -----------------------------------------------------------------
// NODE CLASS
template <class T> class Node {
public:
  Node() : next_(NULL), prev_(NULL) {}
  Node(const T& e): num_elements(0), elements(new T[6]), prev_(NULL), next_(NULL) {}
  
  //REPRESENTATION
  int num_elements;
  T* elements;
  Node<T>* next_;
  Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class dslist;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T> class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL) {
    ptr_=p;
    offsets=0; 
  }
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->elements[offsets];  }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    if (offsets > ptr_ -> num_elements-1) {
      ptr_ = ptr_->next_;
      offsets=0;
    } else {
      offsets++;
    }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    if (offsets >= ptr_ -> num_elements-1) {
      ptr_ = ptr_->next_;
      offsets=0;
    } else {
      offsets++;
    }
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if (offsets > 0) {
      ptr_ = ptr_->prev_;
    } else {
      offsets--;
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if (offsets > 0) {
      ptr_ = ptr_->prev_;
    } else {
      offsets--;
    }
    return temp;
  }
  // the dslist class needs access to the private ptr_ member variable
  //friend class unrolled<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const { return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const { return ptr_ != r.ptr_; }

//private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  int offsets;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T> class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const unrolled<T>& old) { copy_list(old); }
  UnrolledLL& operator= (unrolled<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->elements[0];  }
  T& front() { return head_->elements[0]; }
  const T& back() const { return tail_->elements[tail_->num_elements-1]; }
  T& back() { return tail_->elements[tail_->num_elements-1]; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();
  void print(std::ostream& s);

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(tail_->next_); }

private:
  // private helper functions
  void copy_list(unrolled<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T> UnrolledLL<T>& unrolled<T>::operator=(unrolled<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T> void UnrolledLL<T>::push_front(const T& v) {
  if (!tail_) { // special case: initially empty list
    Node<T>* newp = new Node<T>(v);
    newp->elements[0]=v;
    head_ = tail_ = newp;
    ++(newp->num_elements);
  } else {
    if (head_->num_elements >= num_elements_per_node) { // checking to see if you are out of bounds
      Node<T>* newp = new Node<T>(v);
      newp->elements[0]=v;
      newp->next_ = head_;
      head_->prev_ = newp;
      head_ = newp;
      head_->elements[0]=v;
      ++(head_->num_elements);
    } else { // just add to the array
      for (int i=head_->num_elements; i>0; i--) {
        head_->elements[i]=head_->elements[i-1];
      }
      head_->elements[0]=v;
      head_->num_elements++;
    }
  }
  ++size_;
}

template <class T> void UnrolledLL<T>::pop_front() {
  if (size_!=0) {
    if ((head_->num_elements)==1) {
      Node<T>* newp=head_;
      head_=head_->next_;
      delete newp;
      newp=NULL;
    } else {
      for (int i=0; i<(head_->num_elements)-1; i++) {
        head_->elements[i]=head_->elements[i+1];
      }
      --(head_->num_elements);
    }
  }
  size_--;
}

template <class T> void UnrolledLL<T>::push_back(const T& v) {
  if (tail_==NULL) { // special case: initially empty list
    Node<T>* newp = new Node<T>(v);
    newp->elements[0]=v;
    head_ = tail_ = newp;
    ++(newp->num_elements);
  } else {
    if (tail_->num_elements >= num_elements_per_node) { // checking to see if you are out of bounds
      Node<T>* newp = new Node<T>(v);
      newp->elements[0]=v;
      newp->prev_ = tail_;
      tail_->next_ = newp;
      tail_ = newp; 
      ++(newp->num_elements);
    } else { // just add to the array
      tail_->elements[tail_->num_elements]=v;
      tail_->num_elements++;
    }
  }
  ++size_;
}

template <class T> void UnrolledLL<T>::pop_back() {
  if (size_!=0) {
    if ((tail_->num_elements)==1) {
      tail_=tail_->prev_;
      delete tail_->next_;
      tail_->next_=NULL;
    } else if ((head_->num_elements)==1) {
      delete head_;
      head_=NULL;
      tail_=NULL;
    } else {
      tail_->elements[(tail_->num_elements)-1]=0;
      --(tail_->num_elements);
    } 
  }
  size_--;
}

// do these lists look the same (length & contents)?
template <class T> bool operator== (unrolled<T>& left, unrolled<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T> bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right) { return !(left==right); }

template <class T> typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  if (itr.ptr_ == head_ && head_ == tail_) { // One node left in the list.
    if (head_->num_elements==1) {
      delete head_;
      head_=NULL;
      tail_=NULL;
      itr.ptr_=NULL;
    } else {
      for (int i=itr.offsets; i<(head_->num_elements)-1; ++i) {
        head_->elements[i]=head_->elements[i+1];
      }
      head_->elements[(head_->num_elements)-1]=0;
      --(head_->num_elements);
    }
  } else if (itr.ptr_ == head_) { // Removing the head in a list with at least two nodes
    if (head_->num_elements==1) {
      Node<T>* temp=head_;
      head_=head_->next_;
      temp->next_=NULL;
      delete temp;
      temp=NULL;
      itr.ptr_=head_;
      itr.offsets=0;
    } else {
      for (int i=itr.offsets; i<(head_->num_elements)-1; ++i) {
        head_->elements[i]=head_->elements[i+1];
      }
      head_->elements[(head_->num_elements)-1]=0;
      --(head_->num_elements);
    }
  } else if (itr.ptr_ == tail_) { // Removing the tail in a list with at least two nodes
    if (tail_->num_elements==1) {
      tail_=tail_->prev_;
      delete tail_->next_;
      tail_->next_=NULL;
      itr.ptr_=NULL;
    } else {
      for (int i=itr.offsets; i<(tail_->num_elements)-1; ++i) {
        tail_->elements[i]=tail_->elements[i+1];
      }
      tail_->elements[(tail_->num_elements)-1]=0;
      --(tail_->num_elements);
    }
  } else { // Normal remove
    if (itr.ptr_->num_elements==1) {
      itr.ptr_->prev_->next_=itr.ptr_->next_;
      itr.ptr_->next_->prev_=itr.ptr_->prev_;
      delete itr.ptr_;
      itr.ptr_=itr.ptr_->next_;
    } else {
      for (int i=itr.offsets; i<(itr.ptr_->num_elements)-1; ++i) {
        itr.ptr_->elements[i]=itr.ptr_->elements[i+1];
      }
      itr.ptr_->elements[(itr.ptr_->num_elements)-1]=0;
      --(itr.ptr_->num_elements);
      if (itr.offsets==(head_->num_elements)-1) {
        itr.ptr_=itr.ptr_->next_;
      }
    }
  }
  itr++;
  iterator result(itr);
  return result;
}

template <class T> typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  ++size_;
  if (itr.ptr_->num_elements < num_elements_per_node) {
    if (itr.offsets==0) {
      for (int i=(itr.ptr_->num_elements); i>0; i--) {
        itr.ptr_->elements[i]=itr.ptr_->elements[i-1];
      }
    } else {
      for (int i=(itr.ptr_->num_elements); i>=itr.offsets; i--) {
        itr.ptr_->elements[i]=itr.ptr_->elements[i-1];
      }
    }
    itr.offsets++;
    itr.ptr_->elements[itr.offsets]=v;
    ++(itr.ptr_->num_elements);
  } else {
    int x = itr.ptr_->num_elements;
    Node<T>* newp = new Node<T>();
    newp->next_=itr.ptr_->next_;
    newp->prev_=itr.ptr_;
    itr.ptr_->next_=newp;
    int count=0;
    for (int i=itr.offsets; i<x; i++) {
      newp->elements[count]=itr.ptr_->elements[i];
      count++;
      --(itr.ptr_->num_elements);
    }
    itr.ptr_->elements[itr.ptr_->num_elements]=v;
  }
  return itr.ptr_;
}

template <class T> void UnrolledLL<T>::copy_list(UnrolledLL<T>& old) { 
  size_ = old.size_;
  if (size_ == 0) { // handle the special case of an empty list.
    head_ = tail_ = 0;
    return;
  }
  for (UnrolledLL<T>::iterator old_p = old.begin(); old_p != old.end(); old_p++) { 
    this->push_back(*old_p);
  }
}

template <class T> void UnrolledLL<T>::destroy_list() {
  Node<T> *current = head_;
  Node<T> *next;
  while (current != NULL) {
    next = current->next_;
    delete current;
    current = next;
  }
  size_=0;
  head_=NULL;
  tail_=NULL;
}

template <class T> void UnrolledLL<T>::print(std::ostream& s) {
  s << "UnrolledLL, size: " << this->size() << std::endl;
  Node<T>* t = head_;
  while (t) {
    Node<T>* n = t->next_;
    s << " node:[" << t->num_elements << "] ";
    for (int i=0; i<t->num_elements; ++i) {
      s << t->elements[i] << " ";
    }
    s << std::endl;
    t = n;
  }
}

#endif