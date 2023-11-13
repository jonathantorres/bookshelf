(define x (list 1 3 (list 5 7) 9))
(display (car (cdr (car (cdr (cdr x))))))
(newline)

(define y (list (list 7)))
(display (car (car y)))
(newline)

(define z (list 1 (list 2 (list 3 (list 4 (list 5 (list 6 7)))))))
(display (car (cdr (car (cdr (car (cdr (car (cdr (car (cdr (car (cdr z)))))))))))))
(newline)
