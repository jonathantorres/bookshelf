(define (fast-mul a b)
  (iter 0 a b))

(define (iter res a b)
  (cond ((= a 0) res)
        ((even? a)
         (iter res (halve a) (double b)))
        (else (iter (+ b res) (halve (- a 1)) (double b)))))

(define (even? n)
  (= (remainder n 2) 0))

(define (halve x)
  (/ x 2))

(define (double x)
  (+ x x))

(display (fast-mul 0 0)) (newline)
(display (fast-mul 15 0)) (newline)
(display (fast-mul 1 1)) (newline)
(display (fast-mul 10 1)) (newline)
(display (fast-mul 2 2)) (newline)
(display (fast-mul 6 4)) (newline)
(display (fast-mul 5 5)) (newline)
(display (fast-mul 12 12)) (newline)
(display (fast-mul 100 100)) (newline)
