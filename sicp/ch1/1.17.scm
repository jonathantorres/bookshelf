(define (fast-mul a b)
  (cond ((= b 0) 0)
        ((even? b) (+ (double (fast-mul a (halve b)))))
        (else (+ a (fast-mul a (- b 1))))))

(define (even? n)
  (= (remainder n 2) 0))

(define (halve x)
  (/ x 2))

(define (double x)
  (+ x x))

(display (fast-mul 2 2)) (newline)
(display (fast-mul 6 4)) (newline)
(display (fast-mul 5 5)) (newline)
(display (fast-mul 100 100)) (newline)
