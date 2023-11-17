(define (accumulate op initial sequence)
  (if (null? sequence)
    initial
    (op (car sequence) (accumulate op initial (cdr sequence)))))

(define (count-leaves t)
  (accumulate + 0
    (map
      (lambda (x)
        (cond ((null? x) 0)
              ((not (pair? x)) 1)
              (else
                (count-leaves x))))
      t)))

(define t1 (list (list 1 2) 3 4 (list 5 6) 7))
(define t2 (list 1 2 3 4))
(define t3 (list 1 (list 1 2 (list 1 2 3)) 3 4))

(display (count-leaves t1)) (newline) ; 7
(display (count-leaves t2)) (newline) ; 4
(display (count-leaves t3)) (newline) ; 8
