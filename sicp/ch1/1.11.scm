(define (f n)
  (if (< n 3)
    n
    (+ (f (- n 1)) (* 2 (f (- n 2))) (* 3 (f (- n 3))))))

(define (f-iter n)
  (define (iter a b c count)
    (if (= count 0)
      c
      (iter (+ a (* 2 b) (* 3 c))
            a
            b
            (- count 1))))
  (iter 2 1 0 n))

(display (f 20)) (newline)
(display (f-iter 20)) (newline)

(display (f 4)) (newline)
(display (f-iter 4)) (newline)

(display (f 3)) (newline)
(display (f-iter 3)) (newline)

(display (f 2)) (newline)
(display (f-iter 2)) (newline)

(display (f 1)) (newline)
(display (f-iter 1)) (newline)

(display (f 0)) (newline)
(display (f-iter 0)) (newline)
