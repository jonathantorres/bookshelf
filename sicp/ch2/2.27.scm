(define nil '())

(define (deep-reverse items)
  (define (iter lst r)
    (cond ((null? lst) r)
          ((not (pair? (car lst)))
           (iter (cdr lst) (cons (car lst) r)))
          (else
            (let ((res (iter (car lst) nil)))
              (iter (cdr lst) (cons res r))))))
  (iter items nil))

(define x (list (list 1 2) (list 3 4)))
(define y (list (list 1 2) (list 3 4) 5 6 7))

(display (deep-reverse x)) (newline)
(display (deep-reverse y)) (newline)
