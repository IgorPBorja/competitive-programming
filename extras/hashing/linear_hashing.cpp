#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <cstdlib>

constexpr double eps = 1e-5;

template<typename T, size_t PAGESIZE>
struct Page {
    uint32_t size = 0;

    Page(){}

    void add(const T& x){
        page[size++] = x;
    }
    
    void remove(const T& x){
        for (size_t i = 0; i < size; i++){
            if (page[i] == x){
                // shift left, overwriting
                for (size_t j = i; j + 1 < size; j++){
                    page[j] = page[j + 1];
                }
                --size;
                return;
            }
        }
        throw std::runtime_error("Value to remove not found in page");
    }

    bool find(const T& x){
        for (size_t i = 0; i < size; i++){
            if (page[i] == x){
                return true;
            }
        }
        return false;
    }

    typename std::array<T, PAGESIZE>::iterator begin(){
        return page.begin();
    }

    typename std::array<T, PAGESIZE>::iterator end(){
        return page.begin() + size;
    }

    std::array<T, PAGESIZE> page;
    std::shared_ptr<Page<T, PAGESIZE>> next = nullptr;
};

template<typename T, size_t PAGESIZE>
struct DoubleLinkedList {
    std::shared_ptr<Page<T, PAGESIZE>> head;
    int size;
    int num_pages;

    DoubleLinkedList<T, PAGESIZE>() : num_pages(1) , size(0) {
        // empty list
        head = std::make_shared<Page<T, PAGESIZE>>();
    }

    void add(const T& x){
        std::shared_ptr<Page<T, PAGESIZE>> cur = head;
        while (cur->next != nullptr && cur->size == PAGESIZE){
            cur = cur->next;
        }
        if (cur->size == PAGESIZE){ // and cur->next == nullptr
            // totally full
            std::shared_ptr<Page<T, PAGESIZE>> new_node_ptr = std::make_shared<Page<T, PAGESIZE>>();
            cur->next = new_node_ptr;
            cur = cur->next;
            ++num_pages;
        }
        cur->add(x);
        ++size;
    }

    bool remove(const T& x){
        std::shared_ptr<Page<T, PAGESIZE>> cur = head;
        while (cur != nullptr){
            if (cur->find(x)){
                cur->remove(x);
                --size;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void print(){
        std::shared_ptr<Page<T, PAGESIZE>> cur = head;
        while (cur != nullptr){
            std::cout << "(";
            for (auto it = cur->begin(); it != cur->end(); it++){
                std::cout << *it << ",";
            }
            std::cout << ")";
            std::cout << "->";
            cur = cur->next;
        }
        std::cout << "NULL" << std::endl;
    }
};

template<size_t PAGESIZE>
struct LinearHashing {
    double max_load, min_load;
    std::vector<DoubleLinkedList<int64_t, PAGESIZE>> buckets;
    int N = 0;
    int lvl = 0;
    int m;
    int occupied = 0, available;

    LinearHashing(
        double min_load, double max_load, int m
    ) : min_load(min_load), max_load(max_load), m(m), available(m * PAGESIZE) {
        buckets.resize(m);
    }

    double load() const {
        return double(occupied) / double(available);
    }

    int64_t hash(const int64_t key, int l){
        return key % ((1ll << l) * m);
    }

    void extend(){
        // creates new node
        buckets.emplace_back();
        available += PAGESIZE;

        DoubleLinkedList<int64_t, PAGESIZE> link = buckets[N]; 
        std::shared_ptr<Page<int64_t, PAGESIZE>> cur = link.head;
        // clean page
        available -= (PAGESIZE * (buckets[N].num_pages - 1));
        buckets[N].head = std::make_shared<Page<int64_t, PAGESIZE>>(); // erase
        buckets[N].num_pages = 1;
        buckets[N].size = 0;
        // redistribute
        while (cur != nullptr){
            for (const int64_t x: *cur){
                if (hash(x, lvl + 1) == N){
                    int old_num_pages = buckets[N].num_pages;
                    buckets[N].add(x);
                    available += (buckets[N].num_pages - old_num_pages) * PAGESIZE;
                } else {
                    int old_num_pages = buckets.back().num_pages;
                    buckets.back().add(x);
                    available += (buckets.back().num_pages - old_num_pages) * PAGESIZE;
                }
            }
            cur = cur->next;
        }
        // update
        ++N;
        if (N == ((1ll << lvl) * m)){
            ++lvl;
            N = 0;
        }
    }

    void contract(){
        --N;
        if (N < 0){
            --lvl;
            N = (1ll << lvl);
        }
        // merge page N with N + (2^l)m
        std::shared_ptr<Page<int64_t, PAGESIZE>> cur = buckets[N + (1ll << lvl) * m].head;
        while (cur != nullptr){
            for (const int64_t x: *cur){
                int old_num_pages = buckets[N].num_pages;
                buckets[N].add(x);
                available += (buckets[N].num_pages - old_num_pages) * PAGESIZE;
            }
            cur = cur->next;
        }
        available -= buckets[N + (1ll << lvl) * m].num_pages * PAGESIZE;
        buckets.pop_back();
    }

    void insert(const int64_t key){
        int64_t h_l = hash(key, lvl);
        int64_t target;
        if (h_l < N){
            // already redistributed
            // then h_{l + 1} will be the new position (according to redistribution)
            // this might be h_l or h_l + 2^l * m
            target = hash(key, lvl + 1);
        } else {
            target = h_l;
        }
        int old_num_pages = buckets[target].num_pages;
        buckets[target].add(key);
        // detects new page created
        available += (buckets[target].num_pages - old_num_pages) * PAGESIZE; 
        ++occupied;

        while (load() > max_load + eps){  // the eps is because of float imprecision
            extend();
        }
    }

    void remove(const int64_t key){
        int64_t h_l = hash(key, lvl);
        int64_t target;
        if (h_l < N){
            // already redistributed
            // then h_{l + 1} will be the new position (according to redistribution)
            // this might be h_l or h_l + 2^l * m
            target = hash(key, lvl + 1);
        } else {
            target = h_l;
        }
        bool removed = buckets[target].remove(key);
        if (removed) {
            --occupied;
        }
        while (load() < min_load - eps){
            contract();
        }
    }

    void print(){
        for (size_t i = 0; i < buckets.size(); i++){
            std::cout << "Node " << i << ": ";
            buckets[i].print();
        }
    }
};

int main(){
    std::vector<int> data = {
        8, 11, 10, 15, 17, 25, 44, 12
    };
    LinearHashing<2> table(0.7, 0.8, 2);

    for (const int x: data){
        table.insert(x);
        std::cout << "Table after inserting " << x << std::endl;
        table.print();
        std::cout << std::endl;
    }

    table.remove(8);
    std::cout << "Table after removing 8" << std::endl;
    table.print();
    std::cout << "load=" << table.load() << std::endl;
    table.remove(10);
    std::cout << "Table after removing 10" << std::endl;
    table.print();
    std::cout << "load=" << table.load() << std::endl;
    table.remove(25);
    std::cout << "Table after removing 25" << std::endl;
    table.print();
    std::cout << "load=" << table.load() << std::endl;
}
