(define (carmichael? n)
  (define (iter a)
    (cond ((= a 0) #t)
          ((= (expmod a n n) a) (iter (- a 1)))
          (else #f)))
  (iter (- n 1)))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m)) m))
        (else
          (remainder (* base (expmod base (- exp 1) m)) m))))

(define (square x)
  (* x x ))

; running the tests on carmichael numbers
(display (carmichael? 561)) (newline)
(display (carmichael? 1105)) (newline)
(display (carmichael? 1729)) (newline)
(display (carmichael? 2465)) (newline)
(display (carmichael? 2821)) (newline)
(display (carmichael? 6601)) (newline)
(newline)

; non carmichael numbers
(display (carmichael? 100000)) (newline)
(display (carmichael? 1000000)) (newline)
(display (carmichael? 534238237)) (newline)

