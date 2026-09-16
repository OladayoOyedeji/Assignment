class DLNode:
    
    def __init__(self, value=None,
                 next=None, prev=None,
                 is_sentinel=False):
        
        # To make things simple, I'm using sentinel nodes. Also,
        # I do not use a separate class for sentinel nodes. I simply
        # include a variable __is_sentinel to tell me if the node is
        # a sentinel node.
        
        self.__value = value
        self.__next = next
        self.__prev = prev
        self.__is_sentinel = is_sentinel
        
    def get_next(self):
        return self.__next
    
    def set_next(self, next):
        next.set_prev2(self)
        self.__next = next

    def set_next2(self, next):
        self.__next = next
        
    def get_prev(self):
        # ***** TO BE COMPLETED *****
        return self.__prev
    
    def set_prev(self, prev):
        # ***** TO BE COMPLETE *****
        # if 
        prev.set_next2(self)
        self.__prev = prev
        
    def set_prev2(self, prev):
        self.__prev = prev
        
    def get_value(self):
        return self.__value
    
    def get_is_sentinel(self):
        return self.__is_sentinel
    
    # Add properties prev, next_, is_sentinel, value.
    # Use next_ to avoid confusion with the next keyword.
    
    def __repr__(self):
        return "<DLNode %s value:%s, prev:%s, next:%s>" % (id(self),
                                                           self.__value,
                                                           id(self.__prev),
                                                           id(self.__next))
    def __str__(self):
        return "%s" % self.__value
    def __eq__(self, node):
        # ***** TO BE COMPLETED *****
        # Returns true if self.__value and node.__value are the same
        return (self.__value == node.__value)

class DLList:
    
    def __init__(self, xs=[]):
        head_sentinel = DLNode(is_sentinel=True)
        tail_sentinel = DLNode(is_sentinel=True)
        head_sentinel.set_next(tail_sentinel)
        tail_sentinel.set_prev(head_sentinel)
        self.head = None
        self.tail = None
        self.__tail_sentinel = tail_sentinel
        self.__head_sentinel = head_sentinel

        node = self.__head_sentinel
        for x in xs:
            node.set_next(DLNode(x))
            node = node.__next

        if head_sentinel.get_next() != tail_sentinel.get_prev():
            self.head = head_sentinel.get_next()
            self.tail = tail_sentinel.get_prev()
        node.set_next(self.__tail_sentinel)

    def insert_head(self, value):
        # [] <--> [] <--> []:  []
        #      []
        # [] <--> [] <--> []:  []
        #     \  /
        #      []
        sentinel = self.__head_sentinel
        next_ = sentinel.get_next()
        new = DLNode(value, next=next_, prev=sentinel)
        sentinel.set_next(new)
        next_.prev = new
        
    def insert_tail(self, value):
        sentinel = self.__tail_sentinel
        prev = sentinel.get_prev()
        new = DLNode(value, next=sentinel, prev=prev)
        sentinel.set_prev(new)
        prev.set_next(new)

    def delete_head(self):
        sentinel = self.__head_sentinel
        next_ = sentinel.get_next()
        next2_ = next_.get_next()
        sentinel.set_next(next2_)

        next2_.set_prev(sentinel)

    def delete_tail(self):
        sentinel = self.__tail_sentinel
        prev = sentinel.get_prev()
        prev2 = prev.get_prev()
        print(prev2)
        sentinel.set_prev(prev2)

        prev2.set_next(sentinel)

    def __clear__(self):
        h_sentinel = self.__head_sentinel
        t_sentinel = self.__tail_sentinel

        h_sentinel.set_next(t_sentinel)
        t_sentinel.set_prev(h_sentinel)

    def is_empty(self):
        h_sentinel = self.__head_sentinel
        t_sentinel = self.__tail_sentinel

        return (h_sentinel.get_next() == t_sentinel.get_prev())

    def __clear__(self):
        h_sentinel = self.__head_sentinel
        t_sentinel = self.__tail_sentinel

        h_sentinel.set_next(t_sentinel)
        t_sentinel.set_prev(h_sentinel)
        
    def __len__(self):
        size = 0
        
        h_sentinel = self.__head_sentinel
        t_sentinel = self.__tail_sentinel
        
        node = h_sentinel.get_next()
        
        while node != t_sentinel:
            node = node.get_next()
            size += 1

        return size

if __name__ == '__main__':
    xs = DLList()
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
    xs.insert_head(5)
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
    xs.insert_head(2)
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
    xs.insert_tail(6)
    print(xs.head, xs, len(xs), xs.is_empty())
    xs.insert_head(1234)
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
    xs.insert_tail(5678)
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
    print("Head deleted")
    x = xs.delete_head()
    print(x)
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
    x = xs.delete_tail()
    print(x)
    print(xs.head, xs, xs.tail, len(xs), xs.is_empty())
