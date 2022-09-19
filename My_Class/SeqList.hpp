//
// Created by cw on 2022/9/19.
//

#ifndef DATASTRUCTURESANDALGORITHMS_SEQLIST_HPP
#define DATASTRUCTURESANDALGORITHMS_SEQLIST_HPP


#ifndef DEFAULT_SIZE
// 预定义默认最大元素个数
#define DEFAULT_SIZE 1000
#endif

/**
 * 顺序表类模板
 * @tparam ElemType
 */
template<class ElemType>
class SeqList {
    // 数据成员
protected:
    // 元素存储空间
    ElemType *elems;
    // 顺序表最大元素个数
    int maxSize;
    // 元素个数
    int count;
public:
    // 构造函数
    explicit SeqList(int size = DEFAULT_SIZE);
    // 拷贝构造
    SeqList(SeqList<ElemType> &source);
    // 析构函数
    virtual ~SeqList();
    // 求线性表长度
    int length() const;
    // 判断线性表是否为空
    bool empty() const;
    // 清空线性表
    void clear();
    // 遍历线性表 : 函数指针
    void traverse(void (*visit)(const ElemType &)) const;
    // 得到指定元素值
    bool getElem(int position, ElemType &e) const;
    // 设定指定位置的元素值
    bool setElem(int position, const ElemType &e);
    // 删除元素
    bool remove(int position, ElemType &e);
    bool del(int position);
    // 插入元素
    bool Insert(int position, const ElemType &e);
    // 运算符重载
    SeqList<ElemType> &operator = (const SeqList<ElemType> & source);
};

template<class ElemType>
SeqList<ElemType>::SeqList(int size): maxSize(size), count(0), elems(new ElemType[maxSize]) {}

template<class ElemType>
SeqList<ElemType>::SeqList(SeqList<ElemType> &source) {
    maxSize = source.maxSize;
    count = source.count;
    elems = new ElemType[maxSize];
    // 值copy
    for(int i = 0; i < count; i++){
        elems[i] = source.elems[i];
    }
}

template<class ElemType>
SeqList<ElemType>::~SeqList() {
    delete[] elems;
}

template<class ElemType>
int SeqList<ElemType>::length() const {
    return count;
}

template<class ElemType>
bool SeqList<ElemType>::empty() const {
    return count == 0;
}

template<class ElemType>
void SeqList<ElemType>::clear() {
    count = 0;
}

template<class ElemType>
void SeqList<ElemType>::traverse(void (*visit)(const ElemType &)) const {
    // 对每个函数调用visit即可
    for(int i = 0; i < count; i++){
        (*visit)(elems[i]);
    }
}

template<class ElemType>
bool SeqList<ElemType>::getElem(int position, ElemType &e) const {
    if(position < 0 || position >= count){
        return false;
    }
    e = elems[position];
    return true;
}

template<class ElemType>
bool SeqList<ElemType>::setElem(int position, const ElemType &e) {
    if(position < 0 || position >= count){
        return false;
    }
    elems[position] = e;
    return true;
}
#endif //DATASTRUCTURESANDALGORITHMS_SEQLIST_HPP
