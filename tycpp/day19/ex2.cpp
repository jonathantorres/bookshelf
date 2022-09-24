#include <iostream>

class List
{
    private:

    public:
        List():head(0),tail(0),theCount(0) { };
        virtual ~List();
        void insert(int value);
        void append(int value);
        int is_present(int value) const;
        int is_empty() const { return head == 0; }
        int count() const { return theCount; }
    private:
        class ListCell
        {
            public:
                ListCell(int value, ListCell *cell = 0):val(value),next(cell){ };
                int val;
                ListCell *next;
        };
        ListCell *head;
        ListCell *tail;
        int theCount;
};

void List::insert(int value)
{
     ListCell *pt = new ListCell( value, head );

     // this line added to handle tail
     if ( head == 0 ) tail = pt;

     head = pt;
     theCount++;
}

void List::append( int value )
{
     ListCell *pt = new ListCell( value );
     if ( head == 0 )
          head = pt;
     else
          tail->next = pt;

     tail = pt;
     theCount++;
}

int List::is_present( int value ) const
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
    return 0;
}
