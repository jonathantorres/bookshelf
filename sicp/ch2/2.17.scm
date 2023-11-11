(define (last-pair l)
  (let ((lst (cdr l)))
    (if (null? lst)
      l
      (last-pair lst))))

(display (last-pair (list 23 72 149 34))) (newline)
(display (last-pair (list 1))) (newline)
