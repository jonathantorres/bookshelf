(define (make-interval a b)
  (cons a b))

(define (lower-bound x)
  (car x))

(define (upper-bound x)
  (cdr x))

(define (print-interval x)
  (display (lower-bound x))
  (display ",")
  (display (upper-bound x))
  (newline))

(define (add-interval x y)
  (make-interval
    (+ (lower-bound x) (lower-bound y))
    (+ (upper-bound x) (upper-bound y))))

(define (sub-interval x y)
  (make-interval
    (- (lower-bound x) (upper-bound y))
    (- (upper-bound x) (lower-bound y))))

(define a (make-interval 4 9))
(print-interval a)

(define b (make-interval 9 22))
(print-interval b)

(define c (add-interval a b))
(print-interval c)

(define d (sub-interval a b))
(print-interval d)
