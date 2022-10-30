/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  while (curr != NULL) {
    ListNode * temp = curr;
    curr = curr->next;
    delete temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if (head_ == NULL) {
    ListNode * newNode = new ListNode(ndata);
    head_ = newNode;
    tail_ = newNode;
    head_->prev = NULL;
    tail_->next = NULL;
  } else {
    ListNode * newNode = new ListNode(ndata);
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_->prev = newNode;
    head_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if (head_ == NULL) {
    ListNode * tempHead = new ListNode(ndata);
    head_ = tempHead;
    tail_ = tempHead;
    head_->prev = NULL;
    tail_-> next = NULL;
  } else {
    ListNode * tempNode = new ListNode(ndata);
    tail_->next = tempNode;
    tempNode-> prev = tail_;
    tail_ = tempNode;
    tail_-> next = NULL;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  ListNode * l2;
  for (int i = 0; i < (splitPoint-1); i++) { 
    if (curr != NULL) {
      curr = curr->next;
    } else {
      return NULL;
    }
  }
  l2 = curr -> next;
  curr-> next = NULL;
  l2->prev = NULL;
  return l2;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (length_ < 3) {
    return;
  }
  ListNode *curr = head_;
  if (length_ == 3) {
      head_ = curr->next;
      ListNode * tempVal = curr->next;
      ListNode * tempCurr = curr;
      curr -> next = NULL;
      curr = tempVal;
      curr->next->next = tempCurr;   
      tail_ = tempCurr;
    } else {
      head_ = curr->next;
        for (int i = 0; i <= (length_-3); i+=3) {
          // if (i == (length_-2)) {
          //   ListNode * t1 = curr->next;
          //   ListNode * tempCurr = curr;
          //   curr -> next = curr->next->next->next;
          //   curr = t1;
          //   curr->next->next = tempCurr;   
          //   curr = curr->next->next;
          //   tail_ = curr; 
          //   tail_->next = NULL;
          //   return;
          // }
          ListNode * tempVal = curr->next;
          ListNode * tempCurr = curr;
          curr -> next = curr->next->next->next;
          curr = tempVal;
          curr->next->next = tempCurr;   
          curr = curr->next->next;
          if (curr-> next == NULL) {
            tail_ = curr;
            tail_ -> next = NULL;
            return;
          } else if (curr->next->next ==NULL) {
            tail_ = curr->next;
            tail_ -> next = NULL;
            return;
          } else if (curr->next->next->next == NULL) {
            tail_ = curr->next->next;
            tail_ -> next = NULL;
            return;
          }
          else {
            curr = curr->next;
          }
      }

    }


  
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }
  ListNode* curr = startPoint;
  ListNode* reversePrev = startPoint->prev; 
  ListNode* reverseNext = endPoint->next; 
  ListNode* tempStart = startPoint;
  ListNode* tempEnd = endPoint;

  ListNode* temp = NULL;
  while (curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  curr-> next = curr->prev;
  curr->prev = reversePrev;
  startPoint->next = reverseNext;
  if (reversePrev != NULL) {
    reversePrev -> next = endPoint;
  } else {
    head_ = endPoint;
  }

  if (reverseNext != NULL) {
    reverseNext->prev = startPoint;
  } else {
    tail_ = startPoint;
  }
  startPoint = tempStart;
  endPoint = tempEnd;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (head_ == NULL) { 
    return;
  }
  ListNode* curr = head_;
  ListNode* end = curr;
  while (curr != NULL) {
    int count = 1;
    while (count < n) {
      if(end != tail_) {
        end = end -> next;
      }
      count++;
    }
    reverse(curr, end);
    curr = curr->next;
    end = curr;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * curr1 = first;
	ListNode * curr2 = second;
	if (first == NULL) {
		return second;
	}
	if (second == NULL) {
		return first;
	}
  if (curr2->data < curr1->data) {
		curr1->prev = curr2;
		second = curr2->next;
		if (second != NULL) {
      second->prev = NULL;
    }
		curr2->next = curr1;
		first = curr2;
		curr2 = second;
	}
	while (second != NULL) {
		if (curr2->data < curr1->data){
			second = curr2->next;
			curr1->prev->next = curr2;
			curr2->prev = curr1->prev;
			curr2->next = curr1;
			curr1->prev = curr2;
			curr2 = second;
		}
		else if (curr1->next != NULL){
			curr1 = curr1->next;
		}
		else{
			curr1->next = curr2;
			curr2->prev = curr1;
			second = NULL;
		}
	}

  return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1 || chainLength == 0) {
		return start;
	}
	int length1 = chainLength/2;
	int length2 = chainLength-length1;
	ListNode * middle = split(start, length1);
	return merge(mergesort(start,length1), mergesort(middle,length2));
}
