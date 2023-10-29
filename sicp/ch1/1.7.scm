; This updated version keeps track of the previous guess
; and uses that value against a tolerance with the current guess
; to stop if the two guesses are not far apart

(define (sqrt x)
  (sqrt-iter 1.0 0.0 x))

(define (sqrt-iter guess prev-guess x)
  (if (good-enough? guess prev-guess)
    guess
    (sqrt-iter (improve guess x) guess x)))

(define (good-enough? guess prev-guess)
  (< (abs (- guess prev-guess)) 0.001))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2))

(define (square x) (* x x))

; Small Number Tests
(display (sqrt 0)) (newline)
(display (sqrt 1)) (newline)
(display (sqrt 0.00000012)) (newline)
(display (sqrt 0.3432823)) (newline)

; Large Number Tests
(display (sqrt 87834682623)) (newline)
(display (sqrt 1832935637382)) (newline)
(display (sqrt 100000000000000000000)) (newline)

; Simple Tests
(display (sqrt 25)) (newline)
(display (sqrt 100)) (newline)
