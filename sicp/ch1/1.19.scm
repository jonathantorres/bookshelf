(define (fib n)
  (fib-iter 1 0 0 1 n))

(define (fib-iter a b p q count)
  (cond ((= count 0) b)
        ((even? count)
         (fib-iter a
                   b
                   (+ (square p) (square q))
                   (+ (* 2 p q) (square q))
                   (/ count 2)))
        (else (fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b p) (* a q))
                        p
                        q
                        (- count 1)))))

(define (square n)
  (* n n))

(define (even? n)
  (= (remainder n 2) 0))

(display (fib 10)) (newline)
(display (fib 20)) (newline)
(display (fib 50)) (newline)
(display (fib 100)) (newline)
