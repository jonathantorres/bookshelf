; it works because we are appending each element
; of the list to the subset of the preceeding elements
(define (subsets s)
  (if (null? s)
    (list nil)
    (let ((rest (subsets (cdr s))))
      (append rest (map (lambda (x) (cons (car s) x)) rest)))))

(define nil '())

(define set (list 1 2 3))

(display (subsets set)) (newline)
