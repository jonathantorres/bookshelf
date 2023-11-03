; recursive version
(define (repeated f n)
  (cond ((= n 0) (lambda (x) x))
        ((= n 1) (lambda (x) (f x)))
        (else (compose f (repeated f (- n 1))))))

; iterative version that does not use "compose"
(define (repeated-iter f n)
  (define (iter r n)
    (if (= n 0)
      r
      (iter (f r) (- n 1))))
  (lambda (x) (iter x n)))

(define (compose f g)
  (lambda (x) (f (g x))))

(define (square x) (* x x))

(display ((repeated square 0) 5)) (newline) ; 5
(display ((repeated square 2) 5)) (newline) ; 625
