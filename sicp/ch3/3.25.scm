(define (make-table)
  (let ((local-table (list "*table*")))
    (define (assoc key records)
      (cond ((null? records) #f)
            ((equal? key (caar records)) (car records))
            (else
              (assoc key (cdr records)))))

    (define (lookup keys)
      (define (lookup-table keys table)
        (if (null? (cdr keys))
          (let ((record (assoc (car keys) (cdr table))))
            (if record
              (cdr record)
              #f))
          (let ((subtable (assoc (car keys) (cdr table))))
            (if subtable
              (lookup-table (cdr keys) subtable)
              #f))))
      (lookup-table keys local-table))

    (define (insert! keys value)
      (define (insert-table! keys table)
        (if (null? (cdr keys))
          (let ((record (assoc (car keys) (cdr table))))
            (if record
              (set-cdr! record value)
              (set-cdr! table
                        (cons (cons (car keys) value)
                              (cdr table)))))
          (let ((subtable (assoc (car keys) (cdr table))))
            (if subtable
              (insert-table! (cdr keys) subtable)
              (let ((new-subtable (cons (car keys) '())))
                (set-cdr! table
                          (cons new-subtable
                                (cdr table)))
                (insert-table! (cdr keys) new-subtable))))))
      (insert-table! keys local-table)
      'ok)
    (define (print)
      (display local-table)
      (newline))
    (define (dispatch m)
      (cond ((eq? m 'lookup-proc) lookup)
            ((eq? m 'insert-proc) insert!)
            ((eq? m 'print) print)
            (else
              (error "Unknown operation -- TABLE" m))))
    dispatch))

(define operation-table (make-table))
(define get (operation-table 'lookup-proc))
(define put (operation-table 'insert-proc))
(define print (operation-table 'print))


(put (list 'math '+) 43)
(put (list 'math '-) 45)
(put (list 'math '*) 42)

(put (list 'letters 'a) 97)
(put (list 'letters 'b) 98)

(put (list 'letters 'lower 'a) 97)
(put (list 'letters 'lower 'b) 98)

(display (get (list 'math '+))) (newline)
(display (get (list 'letters 'a))) (newline)
(display (get (list 'letters 'lower 'b))) (newline)
(display (get (list 'letters 'lower 'c))) (newline)
