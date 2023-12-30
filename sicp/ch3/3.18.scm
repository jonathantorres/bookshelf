(define (last-pair x)
  (if (null? (cdr x))
    x
    (last-pair (cdr x))))

(define (make-cycle x)
  (set-cdr! (last-pair x) x))

(define (cycle? x)
  (define lst '())
  (define (in-list? x lst)
    (cond ((null? lst) #f)
          ((eq? x (car lst)) #t)
          (else
            (in-list? x (cdr lst)))))
  (define (loop x)
    (cond ((null? x) #f)
          ((not (pair? x)) #f)
          ((in-list? (cdr x) lst) #t)
          (else
            (set! lst (cons x lst))
            (loop (cdr x)))))
  (loop x))

(define x (list 1 2 3))
(define y (list 1 2 3))
(define z (list 1 2 3))
(make-cycle y)
(make-cycle (cdr z))

(display (cycle? x)) (newline) ; #f
(display (cycle? y)) (newline) ; #t
(display (cycle? z)) (newline) ; #t
