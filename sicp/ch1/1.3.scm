(define (f a b c)
  (cond ((and (<= a b) (<= a c)) (sum-squares b c))
        ((and (<= b a) (<= b c)) (sum-squares a c))
        (else (sum-squares a b))))

(define (sum-squares a b)
  (+ (square a) (square b)))

(define (square x)
  (* x x))

(display (f 1 2 3))
(newline)
(display (f 2 2 1))
(newline)
(display (f 4 2 8))
(newline)
