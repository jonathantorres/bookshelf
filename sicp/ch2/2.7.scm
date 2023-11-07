(define (make-interval a b)
  (cons a b))

(define (lower-bound x)
  (car x))

(define (upper-bound x)
  (cdr x))

(define int (make-interval 1.2 5.89))

(display (lower-bound int)) (newline)
(display (upper-bound int)) (newline)
