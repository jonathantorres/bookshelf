(define (cube-root x)
  (cube-root-iter 1.0 x))

(define (cube-root-iter guess x)
  (if (good-enough? guess x)
    guess
    (cube-root-iter (improve guess x) x)))

(define (improve guess x)
  (/ (+ (/ x (square guess))
        (* 2 guess))
     3))

(define (good-enough? guess x)
  (< (abs (- (cube guess) x)) 0.001))

(define (cube x) (* x x x))
(define (square x) (* x x ))


; Tests
(display (cube-root 20000000)) (newline)
(display (cube-root 100)) (newline)
(display (cube-root 10)) (newline)
(display (cube-root 0)) (newline)
(display (cube-root 1)) (newline)
(display (cube-root 5)) (newline)
(display (cube-root -1)) (newline)
