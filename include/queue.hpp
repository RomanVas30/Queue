#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

template <typename T>
struct ForwardList {
    Node<T> *first;
    Node<T> *last;
    auto insert(ForwardList*& , T) -> void;
    auto amount_of_elements (ForwardList *) -> int;
    auto ForwardList_del(ForwardList*&) -> void;

};

template <typename T>
class Queue {
    public:
    Queue();
    Queue(initializer_list<T> );
    Queue(const Queue& );
    auto swap(Queue& ) -> void;
    auto operator=(const Queue& ) -> void;
    auto empty() -> bool;
    auto size() -> T;
    auto push(T) -> void;
    auto pop() -> void;
    auto front() -> T&;
    auto back() -> T&;
    bool operator==(const Queue& );
    ~Queue();
    template <typename T2>
    friend std::ostream& operator<< (std::ostream&, Queue<T2>&);
    template <typename T3>
    friend std::istream& operator>> (std::istream&, Queue<T3>&);

    private:
    ForwardList<T>* list;
};

template <typename T>
auto ForwardList<T>::insert(ForwardList*& list, T val) -> void{
    Node<T>* curr = new Node<T>{val, nullptr};
    if (list->first == nullptr){
        list->first = curr;
        list->last = curr;
    }
    else {
        list->last->next = curr;
        list->last = curr;
    }
}

template <typename T>
auto ForwardList<T>::ForwardList_del(ForwardList*& list) -> void{
  if (list->first==nullptr) return;
    Node<T> *curr= list->first;
    if (curr->next==nullptr) {
        delete list->first;
        list->first=nullptr;
        list->last= nullptr;
        return;
    }
    curr=list->first->next;
    delete list->first;
    list->first= curr;
    return;
}

template <typename T>
auto ForwardList<T>::amount_of_elements(ForwardList* list) -> int{
    if (list->first == nullptr) return 0;
    Node<T>* curr = list->first;
    int count = 0;
    while (curr != nullptr){
        ++count;
        curr = curr->next;
    }
    return count;
}

template <typename T>
Queue<T>::Queue(){
    ForwardList<T>* curr = new ForwardList<T>{nullptr,nullptr};
    list = curr;
};

template <typename T>
Queue<T>::Queue(initializer_list<T> list_curr){
    ForwardList<T>* curr = new ForwardList<T>{nullptr,nullptr};
    list = curr;
    for (auto x:list_curr) {
        list->insert(list,x);
    }
};

template <typename T>
Queue<T>::Queue(const Queue& Q){
    this->list = Q.list;
};

template <typename T>
auto Queue<T>::swap(Queue& Q) -> void{
    ForwardList<T>* curr = this->list;
    this->list = Q.list;
    Q.list = curr;
};

template <typename T>
auto Queue<T>::operator=(const Queue& Q) -> void{
    this->list = Q.list;
    return;
};

template <typename T>
auto Queue<T>::empty() -> bool{
    if (list->first == nullptr)
    return true;
    else return false;
};

template <typename T>
auto Queue<T>::size() -> T{
    int size_ = list->amount_of_elements(list);
    return size_;
};

template <typename T>
auto Queue<T>::push(T val) -> void{
    list->insert(list, val);
}

template <typename T>
auto Queue<T>::pop() -> void{
    if(empty()) return;
    Node<T>* curr = list->first;
    list->first = list->first->next;
    delete curr;
};

template <typename T>
auto Queue<T>::front() -> T&{
    if (list->first==nullptr) {
        Node<T> * curr= new Node<T> {0,nullptr};
        list->first= curr;
        list->last=curr;
    }
    return *&list->first->data;
};

template <typename T>
auto Queue<T>::back() -> T&{
    if (list->first==nullptr) {
        Node<T> * curr= new Node<T> {0,nullptr};
        list->first= curr;
        list->last=curr;
    }
    
    else return *&list->last->data;
};

template <typename T>
bool Queue<T>::operator==(const Queue& Q){
    Node<T>* curr_this = list->first;
    Node<T>* curr = Q.list->first;
    while((curr != nullptr) || (curr_this != nullptr)){
        if(curr->data != curr_this->data) return false;
        curr=curr->next;
        curr_this = curr_this->next;
    }
if ((curr == nullptr)||(curr_this == nullptr)) return true;
else return false;
};

template <typename T>
Queue<T>::~Queue(){
    list->ForwardList_del(list);
    list->first = nullptr;
    list->last = nullptr;
};

template <typename T>
std::ostream& operator<< (std::ostream& file, Queue<T>& Q){
    Node<T> *curr= Q.list->first;
    if (curr==nullptr) {
        file<<"Error!!!";
        return file;
    }
    while (1) {
        if (curr->next!=nullptr) file<< curr->data << " ";
        else {
            file<< curr->data;
            break;
        }
        curr=curr->next;
    }
    return file;
};
    
template <typename T>
std::istream& operator>> (std::istream& file, Queue<T>& Q){
    T elem;
    file >> elem;
    Q.list->ForwardList_del(Q.list);
    Q.list->first = nullptr;
    while(file){
        Q.list->insert(Q.list, elem);
        file >> elem;
    }
    return file;
};
