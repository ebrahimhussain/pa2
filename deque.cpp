/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    // Initialize deque vector 
    vector<T> data;
    // n1 is index of leftmost element
    // n2 is index of rightmost element
    // both initialized with -1
    this->n1 = -1;
    this->n2 = -1;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{

    if (n2+1 < data.size()) {
        data.at(n2+1) = newItem;
    } else {
        data.push_back(newItem);
    }

    if (data.size() == 1) {
        n1 = 0;
        n2 = 0;
    } else {
        n2++;
    }
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
// only called when function is not empty
T Deque<T>::popL()
{

    T left_data = data[n1];

    n1++;
    int num_elements = n2 - n1 + 1;

    // resize if elements can fit from 0 -> n1
    if (n1 >= num_elements) {
        vector<T> new_data;

        for (int i=n1; i <= n2; i++) {
            new_data.push_back(this->data.at(i));
        }
        n1 = new_data.empty() ? -1 : 0;
        n2 = new_data.size() - 1;

        this->data = new_data;
    }

    return left_data;
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
    T right_data = data[n2];

    n2--;
    int num_elements = n2 - n1 + 1;

    
    // resize if elements can fit from 0 -> n1
    if (n1 >= num_elements) {
        vector<T> new_data;

        for (int i=n1; i <= n2; i++) {
            new_data.push_back(this->data.at(i));
        }
        n1 = new_data.empty() ? -1 : 0;
        n2 = new_data.size() - 1;

        this->data = new_data;
    }

    return right_data;
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
    return (n1 == -1 && n2 == -1);
}
