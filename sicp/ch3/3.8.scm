(define f
  (let ((last 0))
    (lambda (n)
      (let ((tmp last))
        (set! last n)
        tmp))))

(display (+ (f 0) (f 1))) (newline)
