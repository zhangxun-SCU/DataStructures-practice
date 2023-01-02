cmake_minimum_required(VERSION 3.22)
project(DataStructuresAndAlgorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        DataStructuresAndAlgorithms
        main.cpp Exception.cpp
        Exception.h SeqList.hpp
        SingleLinkList.hpp SeqStack.hpp
        SeqStack.hpp
        CircularQueue.hpp
        BinaryTree.hpp
        BinaryHeap.hpp
        My_Class/SeqList.hpp
        PriorityQueue.hpp
        Sort.hpp
        Utils.hpp
        CircleLinkList.hpp
        Node.hpp
        Calculator.hpp
        DCLinkList.hpp
        CharString.hpp
        FileEditor.hpp
        Array.hpp
        Matrix.hpp
        Triple.hpp
        TripleSparseMatrix.hpp
        LinkStack.hpp
        LinkQueue.hpp
        RefGenListNode.hpp
        RefGenList.hpp
        HuffmanTree.hpp
        LinkHuffmanTree.hpp HuffmanCompress.hpp AdjMatrixDirGraph.hpp My_Class/Ackerman.cpp My_Class/Ackerman.h CourseScheduling.hpp)
