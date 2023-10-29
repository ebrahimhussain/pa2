/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    // Initialize deque vector 
    vector<T> data;
    // n1 will point to left 
    int n1;
    // n2 will point to right
    int n2;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    /**
     * @todo Your code here!
     */
    // if vector was empty, n2 should still point to the first (and only) element
    data.push_back(newItem);
    if (data.size() <= 1) {
        n1 = 0;
        n2 = 0;
    }
    else {
        n2++;
    }
    // for (int i = 0; i < data.size(); i++) {
    //     std::cout << data[i] << ' ';
    // }
    // std::cout << std::endl;
    // std::cout << "n1: " << n1 << " n2: " << n2 << std::endl;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T temp = data[n1];
    std::cout << "BEFORE POP" << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "n1: " << n1 << " n2: " << n2 << std::endl;
    data[n1] = NULL;
    n1++;
    if (n1 > n2) {
        n1 = n2;
    }
    /**
     * @todo resize policy
    */
    // empty space is everything up to first index
    int empty = n1;
    // this condition is only true for > 0 elements
    int currSpace = n2 - n1 + 1;
    if (empty > currSpace) {
        vector<T> temp;
        // copy all elements (O(n))
        for (int i = n1; i < n2; i++) {
            temp.push_back(data[i]);
        }
        temp.push_back(data[n2]);
        data = temp;
        n1 = 0;
        n2 = data.size() - 1;
    }
    std::cout << "AFTER POP + RESIZE" << std::endl;
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "n1: " << n1 << " n2: " << n2 << std::endl;

    return temp;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T temp = data[n2];
    data.pop_back();
    n2--;
    if (n2 < 1) {
        n2 = 0;
    }
    /** 
     * @todo implement resizing policy
    */
   // empty space is everything up to first index
    int empty = n1;
    // this condition is only true for > 0 elements
    int currSpace = n2 - n1 + 1;
    if (empty > currSpace) {
        vector<T> temp;
        // copy all elements (O(n))
        for (int i = n1; i < n2; i++) {
            temp.push_back(data[i]);
        }
        data = temp;
        n1 = 0;
        n2 = data.size() - 1;
    }
    return temp;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    /**
     * @todo Your code here! 
     */
    return data[n1];
}


/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    /**
     * @todo Your code here! 
     */
    return data[n2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    /**
     * @todo Your code here! 
     */
    return (data.size() == 0 || (n1 == n2 && data[n1] == NULL));
}
