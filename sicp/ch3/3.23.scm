(define (front-ptr deque) (car deque))
(define (rear-ptr deque) (cdr deque))
(define (set-front-ptr! deque item) (set-car! deque item))
(define (set-rear-ptr! deque item) (set-cdr! deque item))
(define (set-right-node! node item) (set-cdr! (cdr node) item))
(define (set-left-node! node item) (set-car! node item))

(define (make-deque) (cons '() '()))
(define (make-node item) (cons '() (cons item '())))
(define (node-value node) (cadr node))
(define (node-right node) (cddr node))
(define (node-left node) (car node))

(define (empty-deque? deque)
  (null? (front-ptr deque)))

(define (print-deque deque)
  (define (loop node)
    (if (null? node)
      node
      (begin
        (display (node-value node))
        (display " ")
        (loop (node-right node)))))

  (display "( ")
  (loop (front-ptr deque))
  (display ")")
  (newline)
  deque)

(define (front-deque deque)
  (if (empty-deque? deque)
    (error "FRONT called with an empty deque" deque)
    (node-value (front-ptr deque))))

(define (rear-deque deque)
  (if (empty-deque? deque)
    (error "REAR called with an empty deque" deque)
    (node-value (rear-ptr deque))))

(define (front-insert-deque! deque item)
  (let ((new-node (make-node item)))
    (cond ((empty-deque? deque)
           (set-front-ptr! deque new-node)
           (set-rear-ptr! deque new-node)
           deque)
          (else
            (set-right-node! new-node (front-ptr deque))
            (set-left-node! (front-ptr deque) new-node)
            (set-front-ptr! deque new-node)
            deque))))

(define (rear-insert-deque! deque item)
  (let ((new-node (make-node item)))
    (cond ((empty-deque? deque)
           (set-front-ptr! deque new-node)
           (set-rear-ptr! deque new-node)
           deque)
          (else
            (set-left-node! new-node (rear-ptr deque))
            (set-right-node! (rear-ptr deque) new-node)
            (set-rear-ptr! deque new-node)
            deque))))

(define (front-delete-deque! deque)
  (cond ((empty-deque? deque)
         (error "FRONT-DELETE! called with an empty deque" deque))
        (else
          (let ((new-front-node '()))
            (set! new-front-node (node-right (front-ptr deque)))
            (set-left-node! new-front-node '())
            (set-front-ptr! deque new-front-node)
            deque))))

(define (rear-delete-deque! deque)
  (cond ((empty-deque? deque)
         (error "REAR-DELETE! called with an empty deque" deque))
        (else
          (let ((new-rear-node '()))
            (set! new-rear-node (node-left (rear-ptr deque)))
            (set-right-node! new-rear-node '())
            (set-rear-ptr! deque new-rear-node)
            deque))))

; tests
(define d1 (make-deque))

(rear-insert-deque! d1 'a)
(rear-insert-deque! d1 'b)
(rear-insert-deque! d1 'c)
(front-insert-deque! d1 'f)
(rear-delete-deque! d1)
(print-deque d1)

