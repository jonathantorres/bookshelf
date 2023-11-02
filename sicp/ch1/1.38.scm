(define (cont-frac n d k)
  (if (= k 1)
    (/ (n k) (d k))
    (/ (n k) (+ (d k) (cont-frac n d (- k 1))))))

(define (euler n)
  (+ 2.0 (cont-frac
    (lambda (i) 1.0)
    (lambda (i)
      (if (= (remainder i 3) 2)
        (/ (+ i 1) 1.5)
        1))
    n)))

(display (euler 10)) (newline)
