(define (same-parity x . rest)
  (define (same-par? x y)
    (cond ((and (even? x) (even? y)) #t)
          ((and (not (even? x)) (not (even? y))) #t)
          (else #f)))
  (define (loop nums)
    (cond ((null? nums) nums)
          ((same-par? x (car nums)) (cons (car nums) (loop (cdr nums))))
          (else
            (loop (cdr nums)))))
  (loop (cons x rest)))

(define (even? n)
  (= (remainder n 2) 0))

(display (same-parity 1 2 3 4 5 6 7)) (newline)
(display (same-parity 2 3 4 5 6 7)) (newline)
