(define (last-pair x)
  (if (null? (cdr x))
    x
    (last-pair (cdr x))))

(define (make-cycle x)
  (set-cdr! (last-pair x) x))

(define (cycle? x)
  (define (checked-cdr p)
    (if (pair? p)
      (cdr p)
      '()))
  (define (loop s f)
    (cond ((or (null? s) (null? f)) #f)
          ((or (not (pair? s)) (not (pair? f))) #f)
          ((eq? s f) #t)
          (else
            (loop (checked-cdr s) (checked-cdr (checked-cdr f))))))
  (loop (checked-cdr x) (checked-cdr (checked-cdr x))))

(define x (list 1 2 3))
(define y (list 1 2 3))
(define z (list 1 2 3))
(make-cycle y)
(make-cycle (cdr z))

(display (cycle? x)) (newline) ; #f
(display (cycle? y)) (newline) ; #t
(display (cycle? z)) (newline) ; #t
