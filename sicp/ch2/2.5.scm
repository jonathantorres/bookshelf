(define (cons a b)
  (* (expt 2 a) (expt 3 b)))

(define (car x)
  (if (even? x)
    (+ (car (/ x 2)) 1)
    0))

(define (cdr x)
  (if (= (remainder x 3) 0)
    (+ (cdr (/ x 3)) 1)
    0))

(define (even? x)
  (= (remainder x 2) 0))

(define a (cons 1 2))
(display (car a)) (newline)
(display (cdr a)) (newline)
