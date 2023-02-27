#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include <iostream>

#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template <typename T, class Compare = std::less<T>> class priority_queue {
  public:
    /**
     * TODO constructors
     */
    priority_queue() : rt(nullptr), siz(0) {}
    priority_queue(const priority_queue &other) : rt(tnode_copy(other.rt)), siz(other.siz) {}
    /**
     * TODO deconstructor
     */
    ~priority_queue() { tnode_clean(rt); }
    /**
     * TODO Assignment operator
     */
    priority_queue &operator=(const priority_queue &other) {
        if (this == &other)
            return *this;
        tnode_clean(rt);
        rt = tnode_copy(other.rt);
        siz = other.siz;
        return *this;
    }
    /**
     * get the top of the queue.
     * @return a reference of the top element.
     * throw container_is_empty if empty() returns true;
     */
    const T &top() const {
        if (siz == 0)
            throw container_is_empty();
        return rt->data;
    }
    /**
     * TODO
     * push new element to the priority queue.
     */
    void push(const T &e) {
        tnode *tmp = new tnode(e);
        siz++;
        rt = tnode_merge(rt, tmp);
    }
    /**
     * TODO
     * delete the top element.
     * throw container_is_empty if empty() returns true;
     */
    void pop() {
        if (siz == 0)
            throw container_is_empty();
        tnode *tmp = rt;
        rt = tnode_merge(rt->lson, rt->rson);
        delete tmp;
        siz--;
    }
    /**
     * return the number of the elements.
     */
    size_t size() const { return siz; }
    /**
     * check if the container has at least an element.
     * @return true if it is empty, false if it has at least an element.
     */
    bool empty() const { return siz == 0; }
    /**
     * merge two priority_queues with at least O(logn) complexity.
     * clear the other priority_queue.
     */
    void merge(priority_queue &other) {
        rt = tnode_merge(rt, other.rt);
        siz += other.siz;
        other.rt = nullptr;
        other.siz = 0;
    }

  private:
    size_t siz;

    struct tnode {
        T data;
        int dis;
        tnode *lson, *rson;
        tnode(const T &_data, int _dis = 0) : data(_data), dis(_dis), lson(nullptr), rson(nullptr) {}
    } * rt;

    tnode *tnode_copy(tnode *org) {
        tnode *tmp = new tnode(org->data, org->dis);
        if (org->lson)
            tmp->lson = tnode_copy(org->lson);
        if (org->rson)
            tmp->rson = tnode_copy(org->rson);
        return tmp;
    }
    void tnode_clean(tnode *org) {
        if (org == nullptr)
            return;
        if (org->lson) {
            tnode_clean(org->lson);
            org->lson = nullptr;
        }
        if (org->rson) {
            tnode_clean(org->rson);
            org->rson = nullptr;
        }
        delete org;
    }
    tnode *tnode_merge(tnode *nd1, tnode *nd2) {
        if (nd1 == nullptr)
            nd1 = nd2;
        if (nd2 == nullptr)
            nd2 = nd1;
        if (nd1 != nd2) {
            if (Compare()(nd1->data, nd2->data))
                std::swap(nd1, nd2);
            nd1->rson = tnode_merge(nd1->rson, nd2);
            if (nd1->lson == nullptr || nd1->lson->dis < nd1->rson->dis)
                std::swap(nd1->lson, nd1->rson);
            nd1->dis = nd1->rson ? (nd1->rson->dis + 1) : 1;
        }
        return nd1;
    }
};

template class priority_queue<int>;

} // namespace sjtu

#endif
