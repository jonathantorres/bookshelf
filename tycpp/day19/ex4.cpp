#include <iostream>

template <class T>
class List
{
    private:

    public:
        List():head(0),tail(0),theCount(0) { };
        virtual ~List();
        void insert(T value);
        void append(T value);
        int is_present(T value) const;
        int is_empty() const { return head == 0; }
        int count() const { return theCount; }
    private:
        class ListCell
        {
            public:
                ListCell(T value, ListCell *cell = 0):val(value),next(cell){ };
                T val;
                ListCell *next;
        };
        ListCell *head;
        ListCell *tail;
        int theCount;
};

template <class T>
List<T>::~List()
{
     ListCell *pt = head;

     while ( pt )
     {
          ListCell *tmp = pt;
          pt = pt->next;
          delete tmp;
     }
     head = tail = 0;
}

template <class T>
void List<T>::insert(T value)
{
     ListCell *pt = new ListCell( value, head );
     assert (pt != 0);

     // this line added to handle tail
     if ( head == 0 ) tail = pt;

     head = pt;
     theCount++;
}

template <class T>
void List<T>::append( T value )
{
     ListCell *pt = new ListCell( value );
     if ( head == 0 )
          head = pt;
     else
          tail->next = pt;

     tail = pt;
     theCount++;
}

template <class T>
int List<T>::is_present( T value ) const
{
     if ( head == 0 ) return 0;
     if ( head->val == value || tail->val == value )
          return 1;

     ListCell *pt = head->next;
     for (; pt != tail; pt = pt->next)
          if ( pt->val == value )
               return 1;

     return 0;
}

int main()
{
    List<int> l;
    l.insert(10);
    l.insert(11);
    l.insert(12);
    std::cout << l.count() << std::endl;
    std::cout << l.is_present(10) << std::endl;
    std::cout << l.is_present(200) << std::endl;
    return 0;
}
